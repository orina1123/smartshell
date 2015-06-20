#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
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
char *dupstr (char*);
void *xmalloc (int);
void history_init(char*);

const char* cmd [] ={ "hello", "world", "hell" ,"word", "quit", " " };
char* his [N];

//char* buffer;
HistoryWindow* h_win;
vector< pair<string, float> > list;

int main(int argc, char* argv[])
{
	int ret;
	char *buf;
	//buffer = (char *) malloc(sizeof(char)*200);
	rl_attempted_completion_function = my_completion;
	rl_bind_key('\t', rl_complete);
	rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);

	h_win = new HistoryWindow(argv[1], N, BACKSIZE);
	h_win->show_window();

	while((buf = readline("\n== SmartShell ==> "))!=NULL) { //TODO working directory
		//enable auto-complete
		rl_bind_key('\t',rl_complete);
		rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);
		//rl_bind_key('\t',rl_menu_complete);
		printf("cmd [%s]\n",buf);

		if (strcmp(buf,"exit")==0)
			break;
		if (buf[0]!=0)
		{
			//add_history(buf);
			h_win->add_entry(string(buf));
		}

		//execute the entered command
		system(buf);
	}

	//free(buf);

	return 0;
}
static char** my_completion( const char * text , int start,  int end)
{
	char **matches;
	int ret;
	char str[5]="test"; 
	matches = (char **)NULL;
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
			cout << "\t" << (*it).first << "\t" << fixed << (*it).second * 100 << "%" << endl;
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

void history_init(char* hist_file){
	register int i;
	register HIST_ENTRY **the_list;
	//read_history ("/home/lilian/.bash_history");
	//read_history_range ("/home/lilian/.bash_history", 490, 500);
	read_history(hist_file);
	the_list = history_list ();
	for(i=0; i<N; i++){
		his[i] = (char*) xmalloc(strlen(the_list[i]->line) + 1);
		strcpy(his[i], the_list[i]->line);
		//printf("%s\n", his[i]);
	}
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
