// encoded is GBK, notice!!


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define SHOW_CONSOLE
// 设置初始化图形界面样式（需在 #include<graphics.h> 前使用）
#include <graphics.h>
// 调用图形库


#define PI 3.14159265
#define rad(num) PI/180 * num	// 角度制转弧度制
#define deg(num) 180/PI * num	// 弧度制转角度制
#define BallSideLength 40		// 球的大小（边长，以像素为单位）
#define BallMoveLength 2		// 球每次移动的距离（以像素为单位）
#define Board 180				// 板子的长度
#define WWidth 800				// 屏幕的宽度（包括边框）
#define WHeight 480				// 屏幕的高度（包括边框

#define Left true
#define Right false
// 特殊的设置



class Pong {

	private:
	PIMAGE num;
	// 存储数字样式的 PIMAGE 变量
	MOUSEMSG mice;
	// 存储鼠标信息的结构体
	int WindowSizeWidth, WindowSizeHeight;
	// 窗口的大小信息
	double BallX, BallY;
	// 球的中心位置
	int Way;		//球飞行的方向（以度为单位）
	int LScore, RScore;
	public:
	Pong(int WindowSizeWidth, int WindowSizeHeight) {
	// 构造函数
		srand(time(NULL));
		// 设置随机种子
		this -> WindowSizeWidth = WindowSizeWidth;
		this -> WindowSizeHeight = WindowSizeHeight;
		// 给窗口大小们赋值
		BallX = WindowSizeWidth/2;
		BallY = (WindowSizeHeight-150)/2 + 110;
		// 将球放置在屏幕正中间（不包括分数计算和边框）
		// 分数计算110像素，边框20像素
		Way = 90 - rand()%180;
		// 设置随机起始方向，在-180到180之间
		LScore = 0;
		RScore = 0;
		// 初始化分数为0
		initgraph(WindowSizeWidth, WindowSizeHeight);
		// 初始化图形界面
		setcaption("Pong");
		// 设置窗口标题
		setlinewidth(5);
		// 设置线宽
		setfillcolor(RGB(255, 255, 255));
		// 设置线色
		Load();
		// 调用 Load 函数
	}

	void init(void) {

		cleardevice();
		// 清空屏幕
		line(WindowSizeWidth/2, 130, WindowSizeWidth/2, WindowSizeHeight);
		// 画分界线
	}
	void Control(void) {

		setfillcolor(RGB(255, 255, 255));
		// 设置填充色为白色
		bar(WindowSizeWidth - 20,
			mice.y - Board/2,
			WindowSizeWidth - 10,
			mice.y + Board/2);
		// 画板子
		if (mousemsg()){
			mice = GetMouseMsg();
		}
		// 如果有鼠标消息就获取鼠标消息
		if (mice.y < 130 + Board/2) {
			mice.y = 130 + Board/2;
		}
		if (mice.y > WindowSizeHeight - Board/2) {
			mice.y = WindowSizeHeight - Board/2;
		}
		// 控制板子范围
	}
	void Ball(void) {
		// 输出球
		bar(BallX - BallSideLength/2,
			BallY - BallSideLength/2,
			BallX + BallSideLength/2,
			BallY + BallSideLength/2);
		BallMove();
		// 调用球动函数
		BallHit();
		// 调用球碰撞函数
	}
	void Score(void) {
		PutNum(LScore, Left);
		PutNum(RScore, Right);
	}
	private:
	void Load(void) {
	// 数据加载函数
		this -> num = newimage();
		getimage_pngfile(num,"num.png");
	}
	void PutNum(
		int nums,			//输出的数字
		bool s				//输出数字的玩家，如果是真（true）就是左边的玩家
	){
	// 分数打印函数
		int x = WindowSizeWidth - 120;
		if (s) {
			// 如果是左边的玩家，则把坐标设置为0
			x = 0;
		}
		putimage(x, 0, 60, 110, num, 6 * ((nums/10)%10), 0, 6, 11);
		// 打印十位数
		putimage(x + 60, 0, 60, 110, num, 6 * (nums%10), 0, 6, 11);
		// 打印个位数
	}
	void BallMove(void) {
		BallX = BallX + BallMoveLength*sin(rad(Way));
		BallY = BallY - BallMoveLength*cos(rad(Way));
	}
	void BallHit(void) {
		if (BallX >= WindowSizeWidth - 30) {
			if (abs(BallY - mice.y) < BallSideLength/2 + Board/2){
				if (Way > 90 && Way < 180) {
					Way = -Way;
				}else if (Way > 0 && Way < 90) {
					Way = -Way;
				}
				RScore++;
			}else {
				BallX = WindowSizeWidth/2;
				BallY = (WindowSizeHeight-150)/2 + 110;
				// 将球放置在屏幕正中间（不包括分数计算和边框）
				LScore++;
				Way = 90 - rand()%180;
				// 设置随机起始方向，在-180到180之间
			}
		}else if (BallX <= BallSideLength/2) {
			if (Way < 0 && Way > -90) {
				Way = -Way;
			}else if (Way < -90 && Way > -180) {
				Way = -Way;
			}
		// 左墙壁碰撞检测
		}else if (BallY <= 130 + BallSideLength/2) {
			if (Way > 0 && Way < 90) {
				Way = 180 - Way;
			}else if (Way < 0 && Way > -90) {
				Way = -(180 + Way);
			}
		// 上墙壁碰撞检测
		}else if (BallY >= WindowSizeHeight - BallSideLength/2) {
			if (Way > 90 && Way < 180) {
				Way = 180 - Way;
			}else if (Way < -90 && Way > -180) {
				Way = -(180 + Way);
			}
		// 下墙壁碰撞检测
		}
	}
};

int main(int argc, char * argv[]) {

	Pong pong(WWidth, WHeight);
	while (true) {

		pong.init();
		pong.Score();
		pong.Ball();
		// pong.BallMove();
		// pong.BallHit();
		pong.Control();
		Sleep(1);
	}

	return 0;
}
