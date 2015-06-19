#include <cstdio>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <iostream>

#include "HistoryWindow.h"

#define N 80
#define BACKSIZE 2


using namespace std;


static char** my_completion(const char*, int ,int);

// HistoryWindow
HistoryWindow* h_win;

int main(int argc, char *argv[])
{
	char *buffer;

	string buf;
	h_win = new HistoryWindow("../data/history_lilian_desktop", N, BACKSIZE);
	rl_attempted_completion_function = my_completion;

	while((buffer = readline("\n== SmartShell ==> ")) != NULL){
		//enable auto-complete
		rl_bind_key('\t', rl_complete);
		//enable ESC functionality
		//rl_bind_key('', );
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

	/*printf("%s\n", buffer);
	buffer[0] = "\0"; //empty the buffer*/
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
