#include <stdio.h>

#define Z ' '
#define _ '_'
#define Q 'Q'
#define X 'X'

char bd[10][10]={
	Z,  '1','2','3','4','5','6','7','8',   Z ,

	Z,   _ , _ , _ , _ , _ , _ , _ , _ ,  '1',
	Z,   _ , _ , _ , _ , _ , _ , _ , _ ,  '2',
	Z,   _ , _ , _ , _ , _ , _ , _ , _ ,  '3',
	Z,   _ , _ , _ , Q , X , _ , _ , _ ,  '4',
	Z,   _ , _ , _ , X , Q , _ , _ , _ ,  '5',
	Z,   _ , _ , _ , _ , _ , _ , _ , _ ,  '6',
	Z,   _ , _ , _ , _ , _ , _ , _ , _ ,  '7',
	Z,   _ , _ , _ , _ , _ , _ , _ , _ ,  '8',

	Z,   Z , Z , Z , Z , Z , Z , Z , Z ,   Z ,
};

void disp()
{
	int x,y;
	for(y = 0; y < 9; y++){
		for(x = 0; x < 10; x++){
			printf("%c",bd[y][x]);
			printf("|");
		}
		printf("\n");
	}
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
	case	_:
	case	Z:
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
	int xx[]={-1,-1, 0, 1, 1, 1, 0, -1};
	int yy[]={ 0,-1,-1,-1, 0, 1, 1,  1};
	int x,y,turn=0,t;

	for(;;){
		disp();
		printf("You are %s. X=? Y=?", turn==0 ?"BLACK(Q)":"WHITE(X)");
		scanf("%d,%d",&x,&y);
		if(x>8 || y>8 || x<1 || y<1 )continue;
		t = turn==0?'Q':'X';
		for(i=0;i<8;i++)
			if(check(x,y, xx[i],yy[i], t, 1)){
				bd[y][x] = t;
				break;
			}
		if(i==8)continue;

		turn = 1 - turn;
	}

	return 0;
}
