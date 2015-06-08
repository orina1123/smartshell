#include <stdlib.h>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "HistoryWindow.h"
#include <readline/history.h>

HistoryWindow::HistoryWindow(std::string hist_file, int win_size, int back_size) //constructor
{
	//settings
	this->win_size = win_size;
	this->back_size = back_size;

	this->cmd_cnt = (std::map<std::string, int>*) malloc((this->back_size + 1)*sizeof(std::map<std::string, int>));
	this->c_a_cnt = (std::map<std::string, int>*) malloc((this->back_size + 1)*sizeof(std::map<std::string, int>));

	//load history file 
    read_history(hist_file.c_str());

	//read history entries
	HIST_ENTRY **hist_list = history_list();
	int i = 0;
    while(hist_list[i] != NULL)
	{
		std::string full_line = std::string(hist_list[i]->line);

		this->win_with_args.push_back(full_line);
		
		std::size_t blank_pos = full_line.find(" ");
		std::string cmd;
		if(blank_pos != std::string::npos)
			cmd = full_line.substr(blank_pos+1);
		else
			cmd = full_line;
		this->win_cmd_only.push_back(cmd);

		++i;
    }

}

void HistoryWindow::show_window(void)
{
	for(std::deque<std::string>::iterator it = this->win_with_args.begin(); it != this->win_with_args.end(); ++it)
	{
		printf("%s\n", (*it).c_str());
	}
	printf(">[Window size = %d]<\n", this->win_size);
}

void HistoryWindow::add_entry(std::string full_line)
{
	//GNU History Library storage
	add_history(full_line.c_str());

	//TODO
}
