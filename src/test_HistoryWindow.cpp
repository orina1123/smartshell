#include <stdio.h>
#include "HistoryWindow.h"

#define N 50
#define BACKSIZE 2

int main()
{
	HistoryWindow h_win("test_history", N, BACKSIZE);

	h_win.show_window();

	printf("==after add==\n");
	h_win.add_entry("test a1 a2");

	h_win.show_window();

	return 0;
}
