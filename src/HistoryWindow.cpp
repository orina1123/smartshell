#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include "HistoryWindow.h"
#include <readline/history.h>

using namespace std;

HistoryWindow::HistoryWindow(string hist_file, int win_size, int back_size) //constructor
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
	vector<string> tmp;
    while(hist_list[i] != NULL)
	{
		string full_line = string(hist_list[i]->line);

		tmp.push_back(full_line);

		++i;
    }

	//push into window
	for(i = tmp.size() - this->win_size; i<tmp.size(); ++i)
	{
		string full_line = tmp[i];
		string cmd = this->get_cmd_part(full_line);
		
		/*this->all_c_a.insert(full_line);
		this->all_cmd.insert(cmd);*/

		this->all_c_a[full_line] = i+1;
		this->all_cmd[cmd] = i+1;

		this->add_cnt(full_line);
		this->win_with_args.push_back(full_line);
		this->win_cmd_only.push_back(cmd);

		//cout << *rit << endl;
		//this->add_entry(*rit);
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
	string cmd = this->get_cmd_part(full_line);
	
	//GNU History Library storage
	add_history(full_line.c_str());
	//cout << "##" << history_length << endl;

	/*this->all_c_a.insert(full_line);
	this->all_cmd.insert(cmd);*/

	this->all_c_a[full_line] = history_length;
	this->all_cmd[cmd] = history_length;

	this->add_cnt(full_line);
	this->win_with_args.push_back(full_line);
	this->win_cmd_only.push_back(cmd);

	if(this->win_with_args.size() > this->win_size)
	{
		string last_line = this->win_with_args.front();
		this->win_with_args.pop_front();
		this->win_cmd_only.pop_front();
		this->del_cnt(last_line);
	}
}

void HistoryWindow::add_cnt(string add_line) //call BEFORE push
{
	string cmd = this->get_cmd_part(add_line);
	int q_size = this->win_with_args.size();
	for(int i=1; i<=this->back_size; ++i)
	{
		if(q_size-i < 0)
			break;

		//cmd + arg 
		//cout << q_size-i << endl;
		string pre_c_a = this->win_with_args[q_size-i];
		this->c_a_cnt[i][pre_c_a][add_line] += 1;

		//cmd only
		string pre_cmd = this->get_cmd_part(pre_c_a);
		//cout << "#" << pre_cmd << "#" << endl;
		this->cmd_cnt[i][pre_cmd][cmd] += 1;
	}

	if(q_size-1 > 0)
	{
		string pre2_c_a = this->win_with_args[q_size-2];
		string pre1_c_a = this->win_with_args[q_size-1];
		//cout << pre2_c_a << " // " << pre1_c_a << endl;
		this->c_a_2_cnt[make_pair(pre2_c_a, pre1_c_a)][add_line] += 1;	
		
		string pre2_cmd = this->win_cmd_only[q_size-2];
		string pre1_cmd = this->win_cmd_only[q_size-1];
		this->cmd_2_cnt[make_pair(pre2_cmd, pre1_cmd)][this->get_cmd_part(add_line)] += 1;
	}
}

void HistoryWindow::del_cnt(string del_line) //call AFTER pop
{
	string del_cmd = this->get_cmd_part(del_line);
	int q_size = this->win_with_args.size();
	for(int i=1; i<=this->back_size; ++i)
	{
		string c_a = this->win_with_args[i-1];
		//cout << del_line << " // " << c_a << endl;
		//cout << c_a_cnt[i][del_line][c_a] << endl;
		this->c_a_cnt[i][del_line][c_a] -= 1;
		//cout << c_a_cnt[i][del_line][c_a] << endl;
		
		string cmd = this->get_cmd_part(c_a);
		this->cmd_cnt[i][del_cmd][cmd] -= 1;
	}
	
	string next1_c_a = this->win_with_args[0];
	string next2_c_a = this->win_with_args[1];
	this->c_a_2_cnt[make_pair(del_line, next1_c_a)][next2_c_a] -= 1;

	string next1_cmd = this->win_cmd_only[0];
	string next2_cmd = this->win_cmd_only[1];
	this->cmd_2_cnt[make_pair(del_cmd, next1_cmd)][next2_cmd] -= 1;
}

int HistoryWindow::get_cmd_cnt(int i, string pre_cmd, string cmd)
{
	return this->cmd_cnt[i][pre_cmd][cmd];
}

int HistoryWindow::get_c_a_cnt(int i, string pre_c_a, string c_a)
{
	return this->c_a_cnt[i][pre_c_a][c_a];
}

int HistoryWindow::get_cmd_2_cnt(string pre2_cmd, string pre1_cmd, string cmd)
{
	return this->cmd_2_cnt[make_pair(pre2_cmd, pre1_cmd)][cmd];
}

int HistoryWindow::get_c_a_2_cnt(string pre2_c_a, string pre1_c_a, string c_a)
{
	return this->c_a_2_cnt[make_pair(pre2_c_a, pre1_c_a)][c_a];
}

/*bool cmp(const std::pair<string,int> &left, const std::pair<string,int> &right) 
{
	return (right.second < left.second); 
}*/
vector< pair<string, float> > HistoryWindow::get_cmd_match_list(string input)
{
	vector< pair<string, float> > ret_list;

	vector< tuple<string, int, int> > candidates;
	string pre_cmd = this->win_cmd_only.back();
	//cout << "##" << pre_cmd << endl;
	int sum_cnt = 0;
	//for(set<string>::iterator it = this->all_cmd.begin(); it != this->all_cmd.end(); ++it)
	for(map<string, int>::iterator it = this->all_cmd.begin(); it != this->all_cmd.end(); ++it)//get candidate from all appeared command
	{
		string cmd = it->first;
		int h_num = it->second;
		//cout << "**" << cmd << endl;
		int cnt = this->get_cmd_cnt(1, pre_cmd, cmd);
		if(input.compare( cmd.substr(0, input.length()) ) == 0)
		{
		  //cout << "**" << cmd << endl;
		  candidates.push_back(make_tuple(cmd, cnt, h_num));
		  sum_cnt += cnt;
		}
	}

	std::sort(candidates.begin(), candidates.end(), [](const tuple<string, int, int> &a, const tuple<string, int, int> &b)
			{
				//return b.second<a.second;
				if( get<1>(b) < get<1>(a) ) return true;
				if( get<1>(b) > get<1>(a) ) return false;

				//same prob.
				if( get<2>(b) < get<2>(a) ) return true;
				if( get<2>(b) > get<2>(a) ) return false;

				return false;
			});
	//std::sort(candidates.begin(), candidates.end());
	for(vector< tuple<string, int, int> >::iterator it = candidates.begin(); it != candidates.end(); ++it)
	{
		string cmd = get<0>(*it);
		int cnt = get<1>(*it);
		int h_num = get<2>(*it);
		//cout << cmd << " " << cnt << " " << h_num << endl;
		
		float prob;
		if(sum_cnt > 0)
			prob = (float)cnt / sum_cnt;
		else
			prob = 0.0;

		ret_list.push_back(make_pair(cmd, prob));
		//cout << cnt << " / " << sum_cnt << endl;
	}

	return ret_list;
}
vector< pair<string, float> > HistoryWindow::get_c_a_match_list(string input)
{
	vector< pair<string, float> > ret_list;

	//vector< pair<string, int> > candidates;
	vector< tuple<string, int, int> > candidates;
	string pre_c_a = this->win_with_args.back();
	int sum_cnt = 0;
	//for(set<string>::iterator it = this->all_c_a.begin(); it != this->all_c_a.end(); ++it)//get candidate from all appeared command
	for(map<string, int>::iterator it = this->all_c_a.begin(); it != this->all_c_a.end(); ++it)//get candidate from all appeared command
	{
		//string c_a = *it;
		string c_a = it->first;
		int h_num = it->second;

		int cnt = this->get_c_a_cnt(1, pre_c_a, c_a);
		if(input.compare( c_a.substr(0, input.length()) ) == 0)
		{
			candidates.push_back(make_tuple(c_a, cnt, h_num));
			sum_cnt += cnt;
		}
	}

	//std::sort(candidates.begin(), candidates.end(), cmp);
	std::sort(candidates.begin(), candidates.end(), [](const tuple<string, int, int> &a, const tuple<string, int, int> &b)
			{
				//return b.second<a.second;
				if( get<1>(b) < get<1>(a) ) return true;
				if( get<1>(b) > get<1>(a) ) return false;

				//same prob.
				if( get<2>(b) < get<2>(a) ) return true;
				if( get<2>(b) > get<2>(a) ) return false;

				return false;
			});

	//for(vector< pair<string, int> >::iterator it = candidates.begin(); it != candidates.end(); ++it)
	for(vector< tuple<string, int, int> >::iterator it = candidates.begin(); it != candidates.end(); ++it)
	{
		/*string c_a = (*it).first;
		int cnt = (*it).second;*/
		
		string c_a = get<0>(*it);
		int cnt = get<1>(*it);
		int h_num = get<2>(*it);
		//cout << c_a << " " << cnt << " " << h_num << endl;

		float prob;
		if(sum_cnt > 0)
			prob = (float)cnt / sum_cnt;
		else
			prob = 0.0;
		ret_list.push_back(make_pair(c_a, prob)); //TODO implement different count combination method
	//	cout << cnt << " / " << sum_cnt << endl;
	}

	return ret_list;
}


string HistoryWindow::get_cmd_part(string full_line)
{
	size_t blank_pos = full_line.find(" ");
	string cmd;
	if(blank_pos != string::npos)
		cmd = full_line.substr(0, blank_pos);
	else
		cmd = full_line;
	
	return cmd;
}
