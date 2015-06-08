#include <string>
#include <vector>
#include <deque>
#include <map>
#include <readline/history.h>

class HistoryWindow
{
	public:
		HistoryWindow(std::string, int, int);
		void show_window(void);
		void add_entry(std::string);

	private:
		int win_size;
		std::deque<std::string> win_cmd_only;
		std::deque<std::string> win_with_args;
	
		int back_size;
		std::map<std::string, int>* cmd_cnt; //cmd_cnt[back_size][<cmd>]
		std::map<std::string, int>* c_a_cnt;

		std::map< std::string, std::map<std::string, int> > cmd_bi_cnt;
		std::map< std::string, std::map<std::string, int> > c_a_bi_cnt;
};
