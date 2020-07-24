#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <graphics.h>
 
const int W = 20; //宽
const int H = 15; //高
const int L = 30; //块大小（这个不建议修改
 
int snake [W * H * 2] = {0};  //蛇
int snakeLength;      //蛇长，迟到食物会增加
int headX, headY;     //朝向，总有一个是 0，不然斜着走
int foodX, foodY;      //食物坐标（目前之设置了一个食物
int interval = 500;    //时间间隔，单位是 ms，可以用 Q，E 来调节间隔以便调节游戏速度
 
void drawBody (int x, int y) {
	// 这个 x，y 为像素，用于画蛇身
	setfillcolor (EGERGB (23, 187, 38));
	bar (x + 3, y + 3, x + 27, y + 27);
}
void drawFood (int x, int y) {
	// 这个 x，y 为像素，用于画食物
	setfillcolor (EGERGB (214, 214, 214));
	bar (x + 7, y + 7, x + 23, y + 23);
}
 
void init (void) {
// 初始化，也就是新开一局
	for (int i = 0; i < W*H*2-1; i += 1) { snake [i] = 0; }
	snake [0] = rand () % W;
	snake [1] = rand () % H;
	// 初始化 蛇 相关
	foodX = rand () % W;
	foodY = rand () % H;
	// 初始化食物位置
	headX = 0; headY = 0;
	switch (rand () % 4) {
		case 0: headX = -1; break;
		case 1: headX = 1;  break;
		case 2: headY = -1; break;
		case 3: headY = 1;  break;
	}
	// 初始化蛇头方向
	snakeLength = 1;
	// 初始化蛇长
}
void control (void) {
// 按键处理，移动和调节时间间隔
	if (keystate (VK_UP)) {
		headY = -1; headX = 0;
	} else if (keystate (VK_DOWN)) {
		headY = 1; headX = 0;
	} else if (keystate (VK_LEFT)) {
		headX = -1; headY = 0;
	} else if (keystate (VK_RIGHT)) {
		headX = 1; headY = 0;
	} else if (keystate (81)) {
		interval -= 10;
	} else if (keystate (69)) {
		interval += 10;
	}
}
void edgeCheck (void) {
// 边界处理，当蛇头到达墙边，此时可以穿墙而过，到达另一边
	if (snake [0] < 0) {
		snake [0] = W - 1;
	} else if (snake [0] > W - 1) {
		snake [0] = 0;
	} else if (snake [1] < 0) {
		snake [1] = H - 1;
	} else if (snake [1] > H - 1) {
		snake [1] = 0;
	}
}
bool foodCheck (int x, int y) {
// 检查食物生成位置不在蛇身上，是返回 true，否返回 false
	for (int i = 0; i < snakeLength; i += 1) {
		if (x == snake [2 * i] && y == snake [2 * i + 1]) {
			return true;
		}
	}
	return false;
}
// 其实这两个函数长的真的好像，但是上面那个检查了蛇头，下面不检查蛇头
bool bodyCheck (int x, int y) {
// 检查蛇头是否吃到自己，是返回 true，否返回 false
	for (int i = 2; i < snakeLength; i += 1) {
		if (x == snake [2 * i] && y == snake [2 * i + 1]) {
			return true;
		}
	}
	return false;
}
bool move (void) {
// 移动，用 headX，和 headY 决定蛇头往哪一个方向移动
	if (snake [0] + headX == foodX &&
	    snake [1] + headY == foodY) {
// 有没有吃到食物，吃到则增加蛇长，并重新生成食物
		snakeLength += 1;
re:		foodX = rand () % W;
		foodY = rand () % H;
		if (foodCheck (foodX, foodY)) {
		// 若食物生成在蛇身上，则重新生成（BUG 就在这里了，蛇身要是先占满屏幕就没有食物的位置了）
			goto re;
		}
	}
	for (int i = 2 * snakeLength - 1; i > 1; i -= 2) {
	// 移动蛇身，很客观世界的操作
		snake [i - 1] = snake [i - 3];
		snake [  i  ] = snake [i - 2];
	}
	snake [0] += headX;
	snake [1] += headY;
	// 移动蛇头
	edgeCheck ();
	// 边界检测
	if (bodyCheck (snake [0], snake [1])) {
	// 如果蛇吃到了自己，move 返回 ture，否则 返回 false
		return true;
	} else {
	        return false;
	}
}
 
 
void show (void) {
// 简单的把蛇身和食物的位置画出来
	drawFood (foodX * L, foodY * L);
	
	for (int i = 2 * snakeLength - 1; i > 1; i -= 2) {
		drawBody (snake [i - 1] * L, snake [i] * L);
		
		if (abs ( snake [i - 1] - snake [i - 3]) <= 1 &&
		    abs ( snake [  i  ] - snake [i - 2]) <= 1) {
		    // 填补两个蛇身之间的空隙，上面这个绝对值是解决蛇穿墙的问题
		    // 如果不检测蛇身之间的距离，会突然发现屏幕中间出现一个蛇身
			int x = ((snake [i - 1] + snake [i - 3]) * L) / 2;
			int y = ((snake [  i  ] + snake [i - 2]) * L)/ 2;
			drawBody (x, y);
		}
	}
	drawBody (snake [0] * L, snake [1] * L);
}
 
int main () {
	
	srand (time (0)+clock ());
  // 随机种子
	setinitmode (INIT_RENDERMANUAL);
	initgraph (L * W, L * H);
 
	init ();
	int lastTime = clock ();
 
	for (;is_run (); delay_fps (60), cleardevice ()) {
		control ();
		if (clock () - lastTime > interval) {
			if (move ()) { init (); }
			lastTime = clock ();
		}
		show ();
	}
 
	getch ();
	closegraph ();
 
	return 0;
}