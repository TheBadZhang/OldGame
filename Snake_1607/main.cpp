#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "finish.h"
#include "data.h"


void PlayGame(void){
	DataDispose a;
	a.loadpicture();
	a.loadpic();

	bool food_yn;
    //食物是否有五个，没有就会随机要不要随即出现食物，根据另一个函数Food_Yn();判断
    //超过五个则不进行任何处理
	bool win_yn;									//是否胜利，胜利条件看Win_Yn();
}
int main(int argc, char *argv[]){
th:	StartGame();									//开始游戏
	PlayGame();
	
	int IDCYN = MessageBox(NULL,"你输掉了游戏\n是否重新开局？","你输了",MB_YESNO|MB_ICONWARNING);
	if(IDCYN == IDYES){
		goto th;
	}
//	getch();										//使用输入，让程序暂停在这
	closegraph();									//关闭图形环境
	return 0;
}


