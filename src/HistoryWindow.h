#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <readline/history.h>

using namespace std;

class HistoryWindow
{
	public:
		HistoryWindow(string, int, int);
		void show_window(void);
		void add_entry(string);
		int get_cmd_cnt(int, string, string);
		int get_c_a_cnt(int, string, string);	
		int get_cmd_2_cnt(string, string, string);
		int get_c_a_2_cnt(string, string, string);
		vector< pair<string, float> > get_cmd_match_list(string);
		vector< pair<string, float> > get_c_a_match_list(string);

	private:
		int win_size;
		deque<string> win_cmd_only;
		deque<string> win_with_args;
		map<string, int> all_cmd; //cnt -> last_history_num
		map<string, int> all_c_a;
	
		int back_size;
		map< string, map<string, int> >* cmd_cnt; //cmd_cnt[ back_size ][ cmd[i-back_size] ][ cmd[i] ] = n(cmd[i-back_size], cmd[i])
		map< string, map<string, int> >* c_a_cnt;

		map< pair<string, string>, map<string, int> > cmd_2_cnt; //cmd_2_cnt[ (cmd[i-2], cmd[i-1]) ][ cmd[i] ] = n(cmd[i-2], cmd[i-1], cmd[i])
		map< pair<string, string>, map<string, int> > c_a_2_cnt;

		string get_cmd_part(string);
		void add_cnt(string);
		void del_cnt(string);
};
