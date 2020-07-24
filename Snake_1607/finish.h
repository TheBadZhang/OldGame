#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>



void StartGame(void){
	initgraph(800,600);								//初始化图形环境
	setbkcolor(RGB(55,55,55));						//设置背景色为深灰色
	cleardevice();									//必须要清除原先的背景色，才能达到刷新的作用

	IMAGE pimage_maintitle;							//定义储存标题的变量
	IMAGE pimage_point;								//定义储存提示的变量

	loadimage(&pimage_maintitle,"res/pic_res/maintitle.jpg");	//加载标题图
	loadimage(&pimage_point,"res/pic_res/point.jpg");			//加载地市图

	putimage(0,0,&pimage_maintitle);				//输出标题图
	putimage(0,360,&pimage_point);					//输出提示图
//	SetWindowLong(GetHWnd(), GWL_EXSTYLE, WS_EX_TOOLWINDOW);	//这个函数好有趣，竟然改变了窗口的样子

	getch();										//让程序暂停在这
	cleardevice();									//清空屏幕
}