//	$ gcc -lcurses curses.c

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#define WIDTH 15
#define HEIGHT 7

unsigned char *map[] ={
"|-------+     +---------+     +-------+     +-------+   |",
"|       |     |         |     |       |     |       |   |",
"|       |     |         |     |       |     |       |   |",
"|       +-+ +-+         +-+ +-+       +-+ +-+       +-+ |",
"|         | |             | |           | |           | |",
"| POOL    | |   POOL      | |   POOL    | |   POOL    | |",
"|         | |             | |           | |           | |",
"|         | |             | |           | |           | |",
"|       +-+ +-+         +-+ +-+       +-+ +-+       +-+ |",
"|       |     |         |     |       |     |       |   |",
"|       |     |         |     |       |     |       |   |",
"|-------+     +---------+     +-------+     +-------+   |",
"|                        Enemy                          |",
"|-------+     +---------+     +-------+     +-------+   |",
"|       |     |         |     |       |     |       |   |",
"|       |     |         |     |       |     |       |   |",
"|       +-+ +-+         +-+ +-+       +-+ +-+       +-+ |",
"|         | |             | |           | |           | |",
"| POOL    | |   POOL      | |   POOL    | |   POOL    | |",
"|         | |             | |           | |           | |",
"|         | |             | |           | |           | |",
"|       +-+ +-+         +-+ +-+       +-+ +-+       +-+ |",
"|       |     |         |     |       |     |       |   |",
"|       |     |         |     |       |     |       |   |",
"|-------+     +---------+     +-------+     +-------+   |",
"|                        Enemy         Enemy            |",
"|-------+     +---------+     +-------+     +-------+   |",
"|       |     |         |     |       |     |       |   |",
"|       |     |         |     |       |     |       |   |",
"|       +-+ +-+         +-+ +-+       +-+ +-+       +-+ |",
"|         | |             | |           | |           | |",
"| POOL    | |   POOL      | |   POOL    | |   POOL    | |",
"|         | |             | |           | |           | |",
"|         | |             | |           | |           | |",
"|       +-+ +-+         +-+ +-+       +-+ +-+       +-+ |",
"|       |     |         |     |       |     |       |   |",
"|       |     |         |     |       |     |       |   |",
"|-------+     +---------+     +-------+     +-------+   |",
};

void update_map(int x, int y)
{
	int i;
	char buf_map[WIDTH+1];

	for(i=0; i<HEIGHT; i++){
		strncpy(buf_map, map[y+i] + (x-WIDTH/2),WIDTH);
		buf_map[WIDTH] = 0;
		mvaddstr(i, 0, buf_map);
	}
}

int main()
{
	int x=7,y=5;
	char ch = ' ';

	initscr();
	cbreak();
	curs_set(0);
	update_map(x,y);
	while(1){
		ch = getch();
		switch(ch){
		case	'j':y = y + 1;break;
		case	'k':y = y - 1;break;
		case	'h':x = x - 1;break;
		case	'l':x = x + 1;break;
		}
		clrtoeol();
		update_map(x,y);

		refresh();
	}

	endwin();
	return 0;
}
