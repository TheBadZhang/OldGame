// encoded is GBK, notice!!


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <graphics.h>
// ����ͼ�ο�

#include "Timecount.h"
// ����ʱ�䣬�����ͷ�ļ�������ע�͵���ͷ�ļ��Լ�ʹ�ù��ĺ���

#define PI 3.14159265
#define rad(num) PI/180 * num	// �Ƕ���ת������
#define deg(num) 180/PI * num	// ������ת�Ƕ���
#define BallSideLength 20		// ��Ĵ�С���߳���������Ϊ��λ��


// #define ��׼��� printf

class Pong {

	public:
	PIMAGE num;
	// �洢������ʽ�� PIMAGE ����
	MOUSEMSG mice;
	// �洢�����Ϣ�Ľṹ��
	int WindowSizeWidth, WindowSizeHeight;
	// ���ڵĴ�С��Ϣ
	int BallX, BallY;
	// �������λ��
	int Way;		//����еķ����Զ�Ϊ��λ��
	int Speed;		//����е��ٶȣ�������Ϊ��λ��
	
	Pong(int WindowSizeWidth, int WindowSizeHeight) {
	// ���캯��
		srand(time(NULL));
		// �����������
		setinitmode(SHOW_CONSOLE);
		// ���ó�ʼ��ͼ�ν�����ʽ
		this -> WindowSizeWidth = WindowSizeWidth;
		this -> WindowSizeHeight = WindowSizeHeight;
		// �����ڴ�С�Ǹ�ֵ
		BallX = WindowSizeWidth/2;
		BallY = (WindowSizeHeight-150)/2 + 110;
		// �����������Ļ���м䣨��������������ͱ߿�
		Way = rand()%360;
		// ���������ʼ����
		initgraph(WindowSizeWidth, WindowSizeHeight);
		// ��ʼ��ͼ�ν���
		Load();
		// ���� Load ����
	}

	void init(int WindowSizeWidth, int WindowSizeHeight) {

		cleardevice();
		// �����Ļ
		setlinewidth(5);
		// �����߿�
		setfillcolor(RGB(255, 255, 255));
		// ������ɫ
		line(WindowSizeWidth/2, 130, WindowSizeWidth/2, WindowSizeHeight-20);
		// ���ֽ���
	}
	void Control(void) {

		setfillcolor(RGB(255, 255, 255));
		// �������ɫΪ��ɫ
		bar(WindowSizeWidth - 20, mice.y - 30, WindowSizeWidth - 10, mice.y + 30);
		// ������
		mice = GetMouseMsg();
		// ��ȡ�����Ϣ
		if (mice.y < 160) {
			mice.y = 160;
		}
		if (mice.y > WindowSizeHeight - 50) {
			mice.y = WindowSizeHeight - 50;
		}
		// ���ư��ӷ�Χ
		// setfillcolor(RGB(0, 0, 0));
		// // �������ɫΪ��ɫ
		// bar(WindowSizeWidth - 20, mice.y - 30, WindowSizeWidth - 10, mice.y + 30);
		// �Ѱ��Ӹ��ǵ�
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
		int nums,			//���������
		bool s				//������ֵ���ң�������棨true��������ߵ����
	){
		int x = 480;
		if (s) {
			// �������ߵ���ң������������Ϊ0
			x = 0;
		}
		if (nums > 99) {
			// �����������ݴ�������������ܱ�ʾ�ģ����᷵��
			return ;
		}
		putimage(x, 0, 60, 110, num, 6 * (nums/10), 0, 6, 11);
		// ��ӡʮλ��
		putimage(x + 60, 0, 60, 110, num, 6 * (nums%10), 0, 6, 11);
		// ��ӡ��λ��
	}
	private:
	void Load(void) {
	// ���ݼ��غ���
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
