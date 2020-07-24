#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define		map_y	23
#define		map_x	39
#define		or		||
#define		and		&&
#define		quite	asd=='Q'||asd=='q'
#define		again	asd=='R'||asd=='r'
#define		up		asd=='w'&&asd=='W'
#define		down	asd=='s'&&asd=='S'
#define		left	asd=='a'&&asd=='A'
#define		right	asd=='d'&&asd=='D'
#define		snake_die(y,x)	map[y][x]==2||map[y][x]==3||map[y][x]==4||map[y][x]==5

int map[map_y][map_x];						//一种特别的地图，存储不同的数字来代表不同的符号“0‘ ’，1‘++’，2‘↑’，3‘↓’，4‘←’，5‘→’，6‘·’，7‘█’”
int map_time[map_y][map_x];					//一个用来存储非“‘0’，‘1’，‘7’”的存在时间，存在时间超过snake_long的数值，就会被‘0’取代
int snake_long=0;							//蛇长
int x,y;									//用作循环
int xxx,yyy;								//蛇头的位置
int food_x,food_y;							//食物生成的位置，只会在‘0’上生成
bool food_yn;								//用来保存地图上是否存在其他食物，有为false，无，为true，无就生成食物
bool map_yn=true;							//保存地图上是否没有‘0’，是为true，否为false，是就成为赢家结束游戏
char asd;								   //保存方向键的ASCII和‘q’'r'

void map_begin(void){						//游戏开始
	for(y=0;y<map_y;y++){
		for(x=0;x<map_x;x++){
			map[y][x]=0;
			map_time[y][x]=0;
			if(y==map_y-1)
				map[y][x]=1;
		}
	}
	srand(time(NULL));
	xxx = rand() % map_x;
	yyy = rand() % (map_y-1);
	map[yyy][xxx]=6;
}
bool food_s(void){							//游历map，检查是否有‘7’（食物）
	food_yn=true;
		for(y=0;y<map_y;y++){
			for(x=0;x<map_x;x++){
				if(map[y][x]==7){
					food_yn=false;			//有则将food_yn设置为false
				}
			}
		}
	return food_yn;
}
void food__s(bool food_yn){					//如果food_yn为true在地图上设置食物
	if(food_yn){
ee:		food_x = rand() % map_x;
		food_y = rand() % (map_y-1);
		if(map[food_y][food_x]!=0){
			goto ee;
		}
		map[food_y][food_x]=7;
	}
}
void over(void){							//失败
	system("cls");
	printf("you lose the game!!\n");
	system("pause");
	exit(1);
}
int main(){

th:	map_begin();							//调用函数map_begin()
	while(1){
		if(kbhit()){						//一个特别的函数，在conio.h中有定义，当键盘没有任何活动时返回0，有返回1
            asd = getch();
            if(again){
                system("cls");
                goto th;
            }
            if(quite){
                system("cls");
                exit(1);
            }
		}
		if(up){					//向上
			if(snake_die(yyy-1,xxx)){		//检查是否碰到自己
				over();						//是，游戏结束
			}
			if(map[yyy-1][xxx]==7){			//如果碰到‘7’snake_long+1
				snake_long +=1;
			}
			yyy -= 1;
			if(yyy < 0){
				yyy = map_y - 2;
			}
			map[yyy][xxx]=2;
		}
		if(down){							//向下
			if(snake_die(yyy+1,xxx)){		//检查是否碰到自己
				over();						//是，游戏结束
			}
			if(map[yyy+1][xxx]==7){			//如果碰到‘7’snake_long+1
				snake_long +=1;
			}
			yyy += 1;
			if(yyy > map_y - 2){
				yyy = 0;
			}
			map[yyy][xxx]=3;
		}
		if(left){							//向左
			if(snake_die(yyy,xxx-1)){		//检查是否碰到自己
				over();						//是，游戏结束
			}
			if(map[yyy][xxx-1]==7){			//如果碰到‘7’snake_long+1
				snake_long +=1;
			}
			xxx -= 1;
			if(xxx < 0){
				xxx = map_x - 1;
			}
			map[yyy][xxx]=4;
		}
		if(right){							//向右
			if(snake_die(yyy,xxx+1)){		//检查是否碰到自己
				over();						//是，游戏结束
			}
			if(map[yyy][xxx+1]==7){			//如果碰到‘7’snake_long+1
				snake_long +=1;
			}
			xxx += 1;
			if(xxx > map_x - 1){
				xxx = 0;
			}
			map[yyy][xxx]=5;
		}
		food__s(food_s());

		for(y=0;y<map_y;y++){					//输出
			for(x=0;x<map_x;x++){
				switch(map[y][x]){
				case 0:printf("  ");break;
				case 1:printf("++");break;
				case 2:printf("↑");break;
				case 3:printf("↓");break; 
				case 4:printf("←");break;
				case 5:printf("→");break;  
				case 6:printf("·");break;
				case 7:printf("█");break;
				default : break;
				}
			}
			printf("\n");
		}
		for(y=0;y<map_y-1;y++){
			for(x=0;x<map_x;x++){
				if(map[y][x]!=0 and map[y][x]!=7){
					map_time[y][x]+=1;
				}
				if(map[y][x]==0||map[y][x]==7){
					map_yn=false;
				}
				if(map_time[y][x]>snake_long){
					map[y][x]=0;
					map_time[y][x]=0;
				}
			}
		}
		if(map_yn){
			system("cls");
			printf("you're winner\n");
			system("pause");
		}
		Sleep(250);
		system("cls");
	}
	return 0;
}