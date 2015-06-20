#include <stdio.h>
#include <iostream>
#include "HistoryWindow.h"

#define N 80
#define BACKSIZE 2

int main(int argc, char* argv[])
{
	HistoryWindow h_win(argv[1], N, BACKSIZE);

	h_win.show_window();

	cout << "n(\"git push\", \"git commit\") " << h_win.get_c_a_cnt(1, "git push", "git commit") << endl;
	cout << "n(\"exit\", \"git push\") " << h_win.get_c_a_cnt(1, "exit", "git push") << endl;
	cout << "n(\"git push\", xxx, \"git pull\") " << h_win.get_c_a_cnt(2, "git push", "git pull") << endl;
	cout << "n(\"git ...\", xxx, \"git ...\") " << h_win.get_cmd_cnt(2, "git", "git") << endl;
	cout << "n(\"git push\", \"git commit\", \"git pull\") " << h_win.get_c_a_2_cnt("git push", "git commit", "git pull") << endl;
	cout << "n(\"git ...\", \"cd ...\", \"cp ...\") " << h_win.get_cmd_2_cnt("git", "cd", "cp") << endl;
	cout << "n(\"exit ...\", \"git ...\", \"git ...\") " << h_win.get_cmd_2_cnt("exit", "git", "git") << endl;
	
	cout << "try match: g" << endl;
	cout << "(cmd_only)" << endl;
	vector< pair<string, float> > list = h_win.get_cmd_match_list("g");
	cout.precision(4);
	for(vector< pair<string, float> >::iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << "\t" << (*it).first << " " << fixed << (*it).second << endl;

	}	
	cout << "(with_args)" << endl;
	list = h_win.get_c_a_match_list("g");
	cout.precision(4);
	for(vector< pair<string, float> >::iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << "\t" << (*it).first << " " << fixed << (*it).second << endl;

	}
	
	cout << "try match: gr" << endl;
	cout << "(cmd_only)" << endl;
	list = h_win.get_cmd_match_list("gr");
	cout.precision(4);
	for(vector< pair<string, float> >::iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << "\t" << (*it).first << " " << fixed << (*it).second << endl;

	}	
	cout << "(with_args)" << endl;
	list = h_win.get_c_a_match_list("gr");
	cout.precision(4);
	for(vector< pair<string, float> >::iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << "\t" << (*it).first << " " << fixed << (*it).second << endl;

	}

	printf("\n\n==after add==\n");
	h_win.add_entry("test a1 a2");

	h_win.show_window();
	cout << "n(\"git push\", \"git commit\") " << h_win.get_c_a_cnt(1, "git push", "git commit") << endl;
	cout << "n(\"exit\", \"git push\") " << h_win.get_c_a_cnt(1, "exit", "git push") << endl;
	cout << "n(\"git push\", xxx, \"git pull\") " << h_win.get_c_a_cnt(2, "git push", "git pull") << endl;
	cout << "n(\"git ...\", xxx, \"git ...\") " << h_win.get_cmd_cnt(2, "git", "git") << endl;
	cout << "n(\"git push\", \"git commit\", \"git pull\") " << h_win.get_c_a_2_cnt("git push", "git commit", "git pull") << endl;
	cout << "n(\"git ...\", \"cd ...\", \"cp ...\") " << h_win.get_cmd_2_cnt("git", "cd", "cp") << endl;
	cout << "n(\"exit ...\", \"git ...\", \"git ...\") " << h_win.get_cmd_2_cnt("exit", "git", "git") << endl;

	return 0;
}
