#include "HistoryWindow.h"

#define N 50
#define BACKSIZE 2

int main()
{
	HistoryWindow h_win("test_history", N, BACKSIZE);

	h_win.show_window();

	return 0;
}
