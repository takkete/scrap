#include <stdio.h>
#include <string.h>

char bd[10][10];

void disp()
{
	int x,y;
	for(y = 1; y <= 8; y++)
		for(x = 1; x <= 8; x++)
			if(bd[y][x] != 0 )
				printf("%d%d,%c\n",x,y,bd[y][x]);
}

int check(int x, int y, int xx, int yy, char bw, int first);

int check(int x, int y, int xx, int yy, char bw, int first)
{
	int my_x = x + xx;
	int my_y = y + yy;

	if(bd[my_y][my_x] == bw)
		if(first == 1)
			return 0;
		else
			return 1;

	switch(bd[my_y][my_x]){
	case	0:
		return 0;	
	}

	if(!check(my_x,my_y, xx,yy, bw, 0) )
		return 0;

	bd[my_y][my_x] = bw;
	return 1;
}

int main(int argc, char* argv[])
{
	int i;
	char disc;
	int xx[]={-1,-1, 0, 1, 1, 1, 0, -1};
	int yy[]={ 0,-1,-1,-1, 0, 1, 1,  1};
	int x,y,turn=0,t,turnend_flag;
	char c;

	memset(bd,0,sizeof(bd));

	bd[4][4]='W'; bd[5][4]='B';
	bd[4][5]='B'; bd[5][5]='W';

	for(;;){
		disp();
		disc = turn==0?'B':'W';
		printf("YOU=%c\n",disc);
		fflush(stdout);
		x=0;y=0;
		scanf("%d,%d",&x,&y);
		if(x>8 || y>8 || x<1 || y<1 )continue;
		turnend_flag = 0;
		if(bd[y][x] == 0)
			for(i=0;i<8;i++)
				if(check(x,y, xx[i],yy[i], disc, 1)){
					bd[y][x] = disc;
					turnend_flag = 1;
				}
		if(turnend_flag)
			turn = 1 - turn;
	}

	return 0;
}
