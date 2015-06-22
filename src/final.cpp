#include <cstdio>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>

#include "HistoryWindow.h"

#define N 80
#define BACKSIZE 2

// from rldefs.h
#if !defined (emacs_mode)
#  define no_mode -1
#  define vi_mode 0
#  define emacs_mode 1
#endif

using namespace std;

static char** my_completion(const char*, int ,int);
static int backward_kill_word_to_cmd (int, int);
//static int select_completion_predict (int, int);
void testdata_init(void);
char * my_generator(const char*, int);
void * xmalloc (int size);
char *change_directory(char *);
void home_directory(void);

// HistoryWindow
HistoryWindow* h_win;

// for testing
char* data[5] = {"CMD1 arg1 arg2", "CMD2", "CMD3", "cmd4", "cmd5 arg1"};
// total 100
int prob[5] = {40, 30, 20, 5, 5};

char homedir[300];

int main(int argc, char *argv[])
{
	char *buffer;
	
	home_directory();	
	char curdir[300];

	string buf;
	h_win = new HistoryWindow("../data/history_lilian_desktop", N, BACKSIZE);
	
	rl_attempted_completion_function = my_completion;
//	testdata_init();

	// in first_line to 
	rl_bind_key('\t', rl_complete);
	rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);
//	rl_bind_keyseq("\\C-m", select_completion_predict);
//	rl_bind_keyseq("\\C-j", select_completion_predict);

	getcwd(curdir,295);
	fprintf(stdout,"\n\33[1;36mcurrent directory : %s\33[m",curdir);
	while((buffer = readline("\n== SmartShell ==> ")) != NULL){
		
		rl_bind_key('\t', rl_complete);
		rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);
//		rl_bind_keyseq("\\C-m", select_completion_predict);
//		rl_bind_keyseq("\\C-j", select_completion_predict);
		//rl_bind_keyseq ("\\C-n", rl_backward_kill_word);
		//rl_bind_keyseq("\\C-t", rl_kill_word);
		buf = string(buffer);
		if (buf.compare("exit") == 0)
			break;
		if (buf[0] != 0){
			h_win->add_entry(buffer);
		}
		if (buf[0]=='c' && buf[1]=='d'){
			if((chdir(change_directory(buffer)))<0){
				fprintf(stdout,"cd ERROR!\n");
			}
		}
		else{
			cout << buffer << endl;
			system(buffer);
		}

		getcwd(curdir,295);
		fprintf(stdout,"\n\33[1;36mcurrent directory : %s\33[m",curdir);
	}
	return 0;
}


/*****
  text, start, end

matches: array of string(char*)
 *****/

static char** my_completion (const char * text, int start, int end)
{
	char **matches = (char**)NULL;
	int i, idx;
	char *c;

	if (start == 0)
		matches = rl_completion_matches((char*)text, &my_generator);
	else
		rl_bind_key('\t', rl_abort);
	
	free(matches[0]);
	matches[0] = (char*)xmalloc(strlen(matches[1]));
	c = strrchr(matches[1], '\t');
	idx = c - matches[1];
	strncpy(matches[0], matches[1], idx);
	cout << endl;
	i = 1;
	while(matches != NULL && matches[i] != NULL){
		cout << matches[i++] << endl;
	}

	rl_on_new_line();

	return (matches);
}

/*
static char** my_completion( const char * text , int start,  int end)
{
	char **matches;
	int ret;
	char str[5]="test"; 
	matches = (char **)NULL;
	//printf("[[%s]] %d,%d\n", text, start, end);  //text contains only ONE argument (seperated by blanks)
	//if (start == 0)
	//matches = rl_completion_matches ((char*)text, &my_generator);//TODO implement our func. to generate matches (replace rl_completion_matches())
	matches = rl_completion_matches ((char*)rl_line_buffer, &my_generator);
	//else //** file completion part
	//    rl_bind_key('\t',rl_abort);
	if (matches != NULL){
		char *string;
		string = matches[0];
		//        printf("\n\n==%s\n", string);
		//        printf("\n");
	}
	//    printf("rl_line_buffer: %s\n", rl_line_buffer);
	//    ret = printf("rl_point: %s\n", rl_point);

	printf("%s\n", buffer);
	buffer[0] = "\0"; //empty the buffer
	//printf("%s\n", candidate_list.c_str());
	cout << candidate_list.str() << endl;
	candidate_list.clear();
	candidate_list.str(string());

	//new prompt
	//rl_delete_text(0, end);
	rl_on_new_line();
	rl_bind_key('\t',rl_complete);

	//process matches, remove the part before start
	int i=0;	
	while(matches != NULL && matches[i] != NULL)
	{
		//printf("^^%s\n", matches[i]);
		strcpy(matches[i], string(matches[i]).substr(start).c_str()); //FIXME (in our own completion_matches func.)
		++i;
	}

	return (matches);

}
*/

char * my_generator(const char* text, int state)
{
	static int list_idx, len;
	char *name;
	char *r;
	char *probstr;

	if(!state){
		list_idx = 0;
		len = strlen(text);
		// TODO generate all possile list here
		// save in static local arr of str
		// or global arr of str
	}

	// TODO change to history list
	while (name = data[list_idx]){
		r = (char*) xmalloc(strlen(name) + 16);
		strcpy(r, name);
		// TODO add color to the prob str XD
		probstr = (char*) xmalloc(16);
		probstr[0] = '\t';
		sprintf(probstr+1,"\33[1;33m%d%\33[m",prob[list_idx]);
		strncat(r, probstr, strlen(probstr));
		free(probstr);
		list_idx++;
		return r;	
	}
	return ((char*)NULL);
}
/*
void testdata_init(void){

	data[0] = "CMD_A arg1 arg2 arg3 | CMD2 arg1 arg2";
	data[1] = "CMD_A arg1 arg2 arg3 | CMD2 arg1 arg2";
	data[2] = "CMD_A arg1 arg2 arg3 | CMD2 arg1 arg2";
	data[3] = "CMD_A arg1 arg2 arg3 | CMD2 arg1 arg2";
	data[4] = "CMD_A arg1 arg2 arg3 | CMD2 arg1 arg2";
}
*/
/*****
  reference to lib readline source code kill.c (function rl_backward_kill_word) and text.c
  kill all words except command (the 1st word)
 ******/

static int backward_kill_word_to_cmd (int count, int ignore)
{
	// in rl_backward_kill_word
	// I don't know the meaning of count here, so I keep these 2 lines
	if (count < 0)
		return (rl_kill_word(-count, ignore));
	else {
		int orig_point, prev_point;
		orig_point = rl_point;
		prev_point = orig_point;
		while (rl_point > 0){
			prev_point = rl_point;
			rl_backward_word (count, ignore);
		}
		if (rl_point != orig_point)
			rl_kill_text(orig_point, prev_point);
		// I don't know if there is not 2 lines below in emacs mode, what will happen
		// So I kept 2 lines below too
		// defs of emacs_mode is in rldefs.h (in librl source code), not in /usr/include/readline
		// I copied defs from rldefs.h in this file
		if (rl_editing_mode == emacs_mode)
			rl_mark = prev_point;
		rl_point = prev_point;
	}
	return 0;
}
/*
static int select_completion_predict (int count, int key)
{
	
*/

void * xmalloc (int size)
{
    void *buf;
 
    buf = malloc (size);
    if (!buf) {
        fprintf (stderr, "Error: Out of memory. Exiting.'n");
        exit (1);
    }
 
    return buf;
}

void home_directory(void){
	FILE *fd=popen("echo $HOME","r");
	fgets(homedir,295,fd);
	homedir[strlen(homedir)-1]='\0';
}

char *change_directory(char * command){
	int i;
	int my_len;
	char *newdir=(char*)malloc(300);

	if(command[3]=='~'){
		newdir[0]='\0';
		strcpy(newdir,homedir);
		my_len=strlen(homedir);
		for(i=4;i<strlen(command);i++){
			newdir[my_len+i-4]=command[i];
		}
		newdir[my_len+i-4]='\0';
		return newdir;
	}
	else{
		for(i=3;i<strlen(command);i++){
			newdir[i-3]=command[i];
		}
		newdir[i-3]='\0';
		return newdir;
	}
}
