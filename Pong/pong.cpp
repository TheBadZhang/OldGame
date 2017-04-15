// encoded is GBK, notice!!


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define SHOW_CONSOLE
// ���ó�ʼ��ͼ�ν�����ʽ������ #include<graphics.h> ǰʹ�ã�
#include <graphics.h>
// ����ͼ�ο�


#define PI 3.14159265
#define rad(num) PI/180 * num	// �Ƕ���ת������
#define deg(num) 180/PI * num	// ������ת�Ƕ���
#define BallSideLength 40		// ��Ĵ�С���߳���������Ϊ��λ��
#define BallMoveLength 2		// ��ÿ���ƶ��ľ��루������Ϊ��λ��
#define Board 180				// ���ӵĳ���
#define WWidth 800				// ��Ļ�Ŀ�ȣ������߿�
#define WHeight 480				// ��Ļ�ĸ߶ȣ������߿�

#define Left true
#define Right false
// ���������



class Pong {

	private:
	PIMAGE num;
	// �洢������ʽ�� PIMAGE ����
	MOUSEMSG mice;
	// �洢�����Ϣ�Ľṹ��
	int WindowSizeWidth, WindowSizeHeight;
	// ���ڵĴ�С��Ϣ
	double BallX, BallY;
	// �������λ��
	int Way;		//����еķ����Զ�Ϊ��λ��
	int LScore, RScore;
	public:
	Pong(int WindowSizeWidth, int WindowSizeHeight) {
	// ���캯��
		srand(time(NULL));
		// �����������
		this -> WindowSizeWidth = WindowSizeWidth;
		this -> WindowSizeHeight = WindowSizeHeight;
		// �����ڴ�С�Ǹ�ֵ
		BallX = WindowSizeWidth/2;
		BallY = (WindowSizeHeight-150)/2 + 110;
		// �����������Ļ���м䣨��������������ͱ߿�
		// ��������110���أ��߿�20����
		Way = 90 - rand()%180;
		// ���������ʼ������-180��180֮��
		LScore = 0;
		RScore = 0;
		// ��ʼ������Ϊ0
		initgraph(WindowSizeWidth, WindowSizeHeight);
		// ��ʼ��ͼ�ν���
		setcaption("Pong");
		// ���ô��ڱ���
		setlinewidth(5);
		// �����߿�
		setfillcolor(RGB(255, 255, 255));
		// ������ɫ
		Load();
		// ���� Load ����
	}

	void init(void) {

		cleardevice();
		// �����Ļ
		line(WindowSizeWidth/2, 130, WindowSizeWidth/2, WindowSizeHeight);
		// ���ֽ���
	}
	void Control(void) {

		setfillcolor(RGB(255, 255, 255));
		// �������ɫΪ��ɫ
		bar(WindowSizeWidth - 20,
			mice.y - Board/2,
			WindowSizeWidth - 10,
			mice.y + Board/2);
		// ������
		if (mousemsg()){
			mice = GetMouseMsg();
		}
		// ����������Ϣ�ͻ�ȡ�����Ϣ
		if (mice.y < 130 + Board/2) {
			mice.y = 130 + Board/2;
		}
		if (mice.y > WindowSizeHeight - Board/2) {
			mice.y = WindowSizeHeight - Board/2;
		}
		// ���ư��ӷ�Χ
	}
	void Ball(void) {
		// �����
		bar(BallX - BallSideLength/2,
			BallY - BallSideLength/2,
			BallX + BallSideLength/2,
			BallY + BallSideLength/2);
		BallMove();
		// �����򶯺���
		BallHit();
		// ��������ײ����
	}
	void Score(void) {
		PutNum(LScore, Left);
		PutNum(RScore, Right);
	}
	private:
	void Load(void) {
	// ���ݼ��غ���
		this -> num = newimage();
		getimage_pngfile(num,"num.png");
	}
	void PutNum(
		int nums,			//���������
		bool s				//������ֵ���ң�������棨true��������ߵ����
	){
	// ������ӡ����
		int x = WindowSizeWidth - 120;
		if (s) {
			// �������ߵ���ң������������Ϊ0
			x = 0;
		}
		putimage(x, 0, 60, 110, num, 6 * ((nums/10)%10), 0, 6, 11);
		// ��ӡʮλ��
		putimage(x + 60, 0, 60, 110, num, 6 * (nums%10), 0, 6, 11);
		// ��ӡ��λ��
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
				// �����������Ļ���м䣨��������������ͱ߿�
				LScore++;
				Way = 90 - rand()%180;
				// ���������ʼ������-180��180֮��
			}
		}else if (BallX <= BallSideLength/2) {
			if (Way < 0 && Way > -90) {
				Way = -Way;
			}else if (Way < -90 && Way > -180) {
				Way = -Way;
			}
		// ��ǽ����ײ���
		}else if (BallY <= 130 + BallSideLength/2) {
			if (Way > 0 && Way < 90) {
				Way = 180 - Way;
			}else if (Way < 0 && Way > -90) {
				Way = -(180 + Way);
			}
		// ��ǽ����ײ���
		}else if (BallY >= WindowSizeHeight - BallSideLength/2) {
			if (Way > 90 && Way < 180) {
				Way = 180 - Way;
			}else if (Way < -90 && Way > -180) {
				Way = -(180 + Way);
			}
		// ��ǽ����ײ���
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
