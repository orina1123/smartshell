#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "HistoryWindow.h"
#include <readline/history.h>

using namespace std;

HistoryWindow::HistoryWindow(std::string hist_file, int win_size, int back_size) //constructor
{
	//settings
	this->win_size = win_size;
	this->back_size = back_size;

	this->cmd_cnt = new map< string, map<string, int> >[this->back_size + 1];
	this->c_a_cnt = new map< string, map<string, int> >[this->back_size + 1];

	//load history file 
    read_history(hist_file.c_str());

	//read history entries
	HIST_ENTRY **hist_list = history_list();
	int i = 0;
    while(hist_list[i] != NULL)
	{
		string full_line = string(hist_list[i]->line);

		this->win_with_args.push_back(full_line);
		
		string cmd = this->get_cmd_part(full_line);
		this->win_cmd_only.push_back(cmd);

		++i;
    }

	//shrink to window size
	while(this->win_with_args.size() > this->win_size)
	{
		this->win_with_args.pop_front();
		this->win_cmd_only.pop_front();
	}

}

void HistoryWindow::show_window(void)
{
	for(deque<string>::iterator it = this->win_with_args.begin(); it != this->win_with_args.end(); ++it)
	{
		printf("%s\n", (*it).c_str());
	}
	printf(">[Window size = %d]<\n", this->win_size);
}

void HistoryWindow::add_entry(string full_line)
{
	//GNU History Library storage
	add_history(full_line.c_str());

	this->add_cnt(full_line); //FIXME
	this->win_with_args.push_back(full_line);
	this->win_cmd_only.push_back(this->get_cmd_part(full_line));

	string last_line = this->win_with_args.front();
	this->win_with_args.pop_front();
	this->win_cmd_only.pop_front();
	this->del_cnt(last_line);
}

void HistoryWindow::add_cnt(string add_line)
{
	string cmd = this->get_cmd_part(add_line);
	deque<string>::size_type q_size = this->win_with_args.size();
	for(int i=1; i<=this->back_size; ++i)
	{
		if(q_size-i < 0)
			break;

		//cmd + arg 
		string pre_c_a = this->win_with_args[q_size-i];
		this->c_a_cnt[i][pre_c_a][add_line] += 1;

		//cmd only
		string pre_cmd = this->get_cmd_part(pre_c_a);
		this->cmd_cnt[i][pre_cmd][cmd] += 1;
	}

//	if(this->cmd_2_cnt.find)
//	TODO
}

void HistoryWindow::del_cnt(string del_line)
{
	//TODO
}

string HistoryWindow::get_cmd_part(string full_line)
{
	size_t blank_pos = full_line.find(" ");
	string cmd;
	if(blank_pos != string::npos)
		cmd = full_line.substr(blank_pos+1);
	else
		cmd = full_line;
	
	return cmd;
}
