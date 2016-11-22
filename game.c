#include <stdio.h>
#include <string.h>

#ifdef SHOGI
#	define XMAX 9
#	define YMAX 9
#endif
#ifdef CHESS
#	define XMAX 8
#	define YMAX 8
#endif
#ifdef REVERSI
#	define XMAX 8
#	define YMAX 8
#endif

char bd[YMAX+2][XMAX+2];

void disp()
{
	int x,y;
	for(y = 1; y <= YMAX; y++)
		for(x = 1; x <= XMAX; x++)
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

#ifdef CHESS
	printf("INIT,8,8,check\n");
	for(i=1;i<=8;i++){
	bd[2][i]='p';	bd[7][i]='P';	// Pawn 
	}
	bd[1][1]='r';	bd[8][1]='R';	// Rook
	bd[1][2]='n';	bd[8][2]='N';	// Knight
	bd[1][3]='i';	bd[8][3]='I';	// Bishop
	bd[1][4]='q';	bd[8][4]='Q';	// Queen
	bd[1][5]='k';	bd[8][5]='K';	// King
	bd[1][6]='i';	bd[8][6]='I';	// Bishop
	bd[1][7]='n';	bd[8][7]='N';	// Knight
	bd[1][8]='r';	bd[8][8]='R';	// Rook

#endif
#ifdef REVERSI
	printf("INIT,8,8,green\n");
	bd[4][4]='W'; bd[5][4]='B';
	bd[4][5]='B'; bd[5][5]='W';
#endif
#ifdef SHOGI
	printf("INIT,9,9,yellow\n");
	for(i=1;i<=9;i++){
		bd[7][i]='f';
	}
	bd[8][8]='t';	// Hisha
	bd[8][2]='x';	// Kaku
	bd[9][1]='s';	// Kyosha
	bd[9][2]='u';	// Keima
	bd[9][3]='g';	// Gin
	bd[9][4]='a';	// Kin
	bd[9][5]='o';	// O
	bd[9][6]='a';	// Kin
	bd[9][7]='g';	// Gin
	bd[9][8]='u';	// Keima
	bd[9][9]='s';	// Kyosha
#endif
	fflush(stdout);

	for(;;){
		disp();
		disc = turn==0?'B':'W';
		printf("YOU=%c\n",disc);
		fflush(stdout);
		x=0;y=0;
		scanf("%d,%d",&x,&y);
		if(x>XMAX || y>YMAX || x<1 || y<1 )continue;
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
