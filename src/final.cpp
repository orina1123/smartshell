#include <cstdio>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <iostream>

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

//static char** my_completion(const char*, int ,int);
static int esc_function(int, int);
static int backward_kill_word_to_cmd (int, int);

// HistoryWindow
HistoryWindow* h_win;

int main(int argc, char *argv[])
{
	char *buffer;

	string buf;
	h_win = new HistoryWindow("../data/history_lilian_desktop", N, BACKSIZE);
	//rl_attempted_completion_function = my_completion;


	// in first_line to 
	rl_bind_key('\t', rl_complete);
	rl_bind_keyseq("\\C-k", backward_kill_word_to_cmd);

	while((buffer = readline("\n== SmartShell ==> ")) != NULL){
		//enable auto-complete
		rl_bind_key('\t', rl_complete);
		//enable ESC functionality, esc in ascii == 27
		//rl_bind_key(ESC, esc_function);
		rl_bind_keyseq ("\\C-k", backward_kill_word_to_cmd);
		//rl_bind_keyseq ("\\C-n", rl_backward_kill_word);
		//rl_bind_keyseq("\\C-t", rl_kill_word);
		buf = string(buffer);
		if (buf.compare("exit") == 0)
			break;
		if (buf[0] != 0){
			h_win->add_entry(buffer);
		}
		cout << buffer << endl;
		system(buffer);

	}
	return 0;
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
//matches = rl_completion_matches ((char*)rl_line_buffer, &my_generator);
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
