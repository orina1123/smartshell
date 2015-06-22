#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "HistoryWindow.h"

#define N 80
#define BACKSIZE 2
#define OUTPUT_NUM 5

// from rldefs.h
#if !defined (emacs_mode)
#  define no_mode -1
#  define vi_mode 0
#  define emacs_mode 1
#endif


using namespace std;

static char** my_completion(const char*, int ,int);
char* my_generator(const char*,int);
static int backward_kill_word_to_cmd (int, int);
static int select_completion_predict (int, int);
char *dupstr (char*);
void *xmalloc (int);
void home_directory(void);
char *change_directory(char *);

HistoryWindow* h_win;
vector< pair<string, float> > list;
int global_list_idx = -1;
// initial to < 0 value prevent execute select_completion_predict to get null in vector list
int global_list_idx_max = 0;

char homedir[300];

int main(int argc, char* argv[])
{
	int ret;
	char *buf;

	home_directory();
	char curdir[300];

	rl_attempted_completion_function = my_completion;
	rl_bind_key('\t', rl_complete);
	rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);
	rl_bind_keyseq("\\C-p", select_completion_predict);
	rl_bind_keyseq("\\C-n", select_completion_predict);

	h_win = new HistoryWindow(argv[1], N, BACKSIZE);
	h_win->show_window();

	getcwd(curdir,295);
	fprintf(stdout,"\n\33[1;36mcurrent directory : %s\33[m",curdir);
	while((buf = readline("\n== SmartShell ==> "))!=NULL) { //TODO working directory

		//enable auto-complete
		rl_bind_key('\t',rl_complete);
		rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);
		rl_bind_keyseq("\\C-p", select_completion_predict);
		rl_bind_keyseq("\\C-n", select_completion_predict);

		if (strcmp(buf,"exit")==0)
			break;
		if (buf[0]!=0)
		{
			//add_history(buf);
			h_win->add_entry(string(buf));
		}
		if (buf[0]=='c' && buf[1]=='d'){
			if((chdir(change_directory(buf)))<0){
				fprintf(stdout,"cd ERROR!\n");
			}
		}
		else{
			cout << buf << endl;
			system(buf);
		}

		getcwd(curdir,295);
		fprintf(stdout,"\n\33[1;36mcurrent directory : %s\33[m",curdir);
	}

	//free(buf);

	return 0;
}
static char** my_completion( const char * text , int start,  int end)
{
	char **matches = (char **)NULL;
	//printf("\n[[%s]] %d,%d\n", text, start, end);  //text contains only ONE argument (seperated by blanks)
	
	//generate candidate list before completion
	if(start == 0 && end == 0)
	{
		list = h_win->get_cmd_match_list(string(rl_line_buffer));
	}
	else
	{
		list = h_win->get_c_a_match_list(string(rl_line_buffer));
	}
	if(list.size() > 0)
	{
		cout << endl;
		cout.precision(2);
		for(vector< pair<string, float> >::iterator it = list.begin(); it != list.end(); ++it)
		{
			cout << "\t\33[1;33m" << (*it).first << "\33[m\t" << fixed << (*it).second * 100 << "%" << endl;
		}
	}

	//if (start == 0)
	matches = rl_completion_matches ((char*)text, &my_generator);
	//cerr << "(got matches)" << endl; //OK
	//matches = rl_completion_matches ((char*)rl_line_buffer, &my_generator);
	//else //** file completion part
	//    rl_bind_key('\t',rl_abort);


	//new prompt
	//rl_delete_text(0, end);
	if(matches != NULL)
	{
		rl_on_new_line();
		rl_bind_key('\t',rl_complete);
	}

	//complete by the first condidate
	if(matches != NULL && matches[1] != NULL)
	{
		matches[0] = (char*) xmalloc(strlen(matches[1]) + 1);
		strcpy(matches[0], matches[1]);
	}

	//process matches, remove the part before start
	int i=0;	
	while(matches != NULL && matches[i] != NULL)
	{
		//printf("^^%s\n", matches[i]);
		strcpy(matches[i], string(matches[i]).substr(start).c_str());
		++i;
	}

	//cerr << "(before return)" << endl; //OK
	global_list_idx = 0;
	global_list_idx_max = list.size();
	return (matches);
}

char* my_generator(const char* text, int state)
{
	static int list_index, len;
	char *name;
	char *r;
	if (!state) {
		list_index = 0;
		len = strlen (text);
	}
	while(list_index < list.size()) 
	{
		string next_line = list.at(list_index).first;

		list_index++;
		return (dupstr( (char*)(next_line.c_str()) ));
	}

	//cerr << "my_generator()" << list_index << " " << list.size() << endl;
	/* If no names matched, then return NULL. */
	return ((char *)NULL);
}

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

static int select_completion_predict (int count, int key)
{
	/*cout << endl << "infunc " << key << endl;
	cout << count << endl;
	cout << global_list_idx << " " << global_list_idx_max << endl;
	*/
	int idx = (key == 14) ? global_list_idx +1 : global_list_idx -1;
	if(idx < 0)
		return 0;
	if(idx >= global_list_idx_max)
		return 0;
	global_list_idx = idx;

	//char *new_str = list.at(idx).first.c_str();
	//cout << "before rl_buf " << rl_line_buffer << endl;
	rl_delete_text(0, rl_point);
	//cout << "after del: " << rl_point << endl;
	rl_point = 0;
	rl_insert_text(list.at(idx).first.c_str());
	//cout << "after ins: " << rl_point << endl;
	//cout << endl << rl_line_buffer << endl;
	//cout << "rl_point: " << rl_point << endl;
	if (rl_editing_mode == emacs_mode)
		rl_mark = rl_point;
	
	//free(rl_line_buffer);

	//rl_line_buffer = (char*)xmalloc(list.at(idx).first.size()+1);
	//strcpy(rl_line_buffer, list.at(idx).first.c_str());
//	cout << endl;
//	rl_on_new_line();
	return 0;
	
}

char * dupstr (char * s) {
	char *r;

	r = (char*) xmalloc ((strlen (s) + 1));
	strcpy (r, s);
	return (r);
}

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
