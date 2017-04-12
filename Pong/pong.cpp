// encoded is GBK, notice!!


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <graphics.h>
// 调用图形库

#include "Timecount.h"
// 测量时间，如果该头文件报错，请注释掉盖头文件以及使用过的函数

#define PI 3.14159265
#define rad(num) PI/180 * num	// 角度制转弧度制
#define deg(num) 180/PI * num	// 弧度制转角度制
#define BallSideLength 20		// 球的大小（边长，以像素为单位）


// #define 标准输出 printf

class Pong {

	public:
	PIMAGE num;
	// 存储数字样式的 PIMAGE 变量
	MOUSEMSG mice;
	// 存储鼠标信息的结构体
	int WindowSizeWidth, WindowSizeHeight;
	// 窗口的大小信息
	int BallX, BallY;
	// 球的中心位置
	int Way;		//球飞行的方向（以度为单位）
	int Speed;		//球飞行的速度（以像素为单位）
	
	Pong(int WindowSizeWidth, int WindowSizeHeight) {
	// 构造函数
		srand(time(NULL));
		// 设置随机种子
		setinitmode(SHOW_CONSOLE);
		// 设置初始化图形界面样式
		this -> WindowSizeWidth = WindowSizeWidth;
		this -> WindowSizeHeight = WindowSizeHeight;
		// 给窗口大小们赋值
		BallX = WindowSizeWidth/2;
		BallY = (WindowSizeHeight-150)/2 + 110;
		// 将球放置在屏幕正中间（不包括分数计算和边框）
		Way = rand()%360;
		// 设置随机起始方向
		initgraph(WindowSizeWidth, WindowSizeHeight);
		// 初始化图形界面
		Load();
		// 调用 Load 函数
	}

	void init(int WindowSizeWidth, int WindowSizeHeight) {

		cleardevice();
		// 清空屏幕
		setlinewidth(5);
		// 设置线宽
		setfillcolor(RGB(255, 255, 255));
		// 设置线色
		line(WindowSizeWidth/2, 130, WindowSizeWidth/2, WindowSizeHeight-20);
		// 画分界线
	}
	void Control(void) {

		setfillcolor(RGB(255, 255, 255));
		// 设置填充色为白色
		bar(WindowSizeWidth - 20, mice.y - 30, WindowSizeWidth - 10, mice.y + 30);
		// 画板子
		mice = GetMouseMsg();
		// 获取鼠标消息
		if (mice.y < 160) {
			mice.y = 160;
		}
		if (mice.y > WindowSizeHeight - 50) {
			mice.y = WindowSizeHeight - 50;
		}
		// 控制板子范围
		// setfillcolor(RGB(0, 0, 0));
		// // 设置填充色为黑色
		// bar(WindowSizeWidth - 20, mice.y - 30, WindowSizeWidth - 10, mice.y + 30);
		// 把板子覆盖掉
	}
	void Ball(void) {

		bar(BallX - BallSideLength/2,
			BallY - BallSideLength/2,
			BallX + BallSideLength/2,
			BallY + BallSideLength/2);
	}
	void Computer(void) {


	}
	void PutNum(
		int nums,			//输出的数字
		bool s				//输出数字的玩家，如果是真（true）就是左边的玩家
	){
		int x = 480;
		if (s) {
			// 如果是左边的玩家，则把坐标设置为0
			x = 0;
		}
		if (nums > 99) {
			// 如果输入的数据大于这个函数所能表示的，将会返回
			return ;
		}
		putimage(x, 0, 60, 110, num, 6 * (nums/10), 0, 6, 11);
		// 打印十位数
		putimage(x + 60, 0, 60, 110, num, 6 * (nums%10), 0, 6, 11);
		// 打印个位数
	}
	private:
	void Load(void) {
	// 数据加载函数
		this -> num = newimage();
		getimage_pngfile(num,"num.png");
	}
};

int main(int argc, char * argv[]) {

	Pong a(600, 480);
	while (true) {

		a.init(600, 480);
		a.PutNum(22, true);
		a.PutNum(33, false);
		a.Ball();
		a.Control();
		// Sleep(1);
	}

	getch();
	closegraph();
	
	return 0;
}
