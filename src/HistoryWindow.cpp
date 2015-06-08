#include "HistoryWindow.h"
#include <readline/history.h>

HistoryWindow::HistoryWindow(string history_file) //constructor
{
	int i;
	HIST_ENTRY **the_list;
    read_history(hist_file);
    the_list = history_list ();
    for(i=0; i<10; i++){
       his[i] = (char*) xmalloc(strlen(the_list[i]->line) + 1);
       strcpy(his[i], the_list[i]->line);
       printf("%s\n", his[i]);
    }

}
