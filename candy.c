#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

int main()
{
	int x,y,c,w,h,key;
	char candy_str[10];

	int delay=2000000;
	int point=0;
	int candy=0;

        srand(time(NULL));

	initscr();

	noecho();
	cbreak();
	timeout(0);

	getmaxyx(stdscr, h, w);

	start_color();
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_WHITE, COLOR_GREEN);
	init_pair(6, COLOR_WHITE, COLOR_BLUE);
	init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_WHITE);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);

	erase();

	while(1){
		y = rand() % (h-1) + 1;
		x = rand() % (w-1) + 1;
		do{
			c = rand() % 8 + 1;
		}while( c==0 || c==3 || c==1 || c==8 );

		attrset(COLOR_PAIR(0));
		move(0, 0);
		addstr("CANDY=");
		move(0, 6);
		sprintf(candy_str,"%d",candy);
		addstr(candy_str);
	
		attrset(COLOR_PAIR(c));
		move(y, x);
		addstr(">o<");

		if(candy++ > 100)
			break;
		
		refresh();

		usleep(delay);

		key = getch();
		if(key == (c + '0')){
			attrset(COLOR_PAIR(0));
			move(y, x);
			addstr("   ");
			refresh();
			candy--;
			point++;
		}else{
			delay-=100000;
			if(delay < 0){
				delay = 100000;
			}
		}
		if(key == 'q')break;
	}

	endwin();

	printf("\n");
	printf("--------------------------------------\n");
	printf("GAME OVER!\n\n");
	printf("YOU GOT %d POINTS !!\n",point*100);
	printf("--------------------------------------\n");

	return (0);
}


/*
usage

~$ gcc -lncurses candy.c
~$ ./a.out

*/
