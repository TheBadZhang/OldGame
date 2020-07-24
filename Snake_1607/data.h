#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>

#define bool char
#define true 1
#define false 0


class DataDispose{
	public:											//公有的行为和属性
/****************************判断食物是否撞在蛇上的函数*********************
		bool Snack_Yn(int x, int y, struct Sanck *sanck){//判断食物是否撞在蛇上的函数
			if(x==sanck->sanck_x){
				if(y==sanck->sanck_y){
					return true;
				}
			}
			sanck=sanck->next;
			if(sanck==NULL){
				return false;
			}
		}//判断生成的位置有没有蛇身的存在如果有，就返回true，没有则为false
/******************************创建新蛇节的函数****************************
		void creatbody(struct Snack *){//创建新蛇节的函数
			struct Snack *p1;
			p1=(struct Snack *)malloc(sizeof(struct Sanck));//申请新节点	
			Snack->next=p1;									//目前最后一个节点的下一个指针设为新申请的p1
			p1->next=NULL;									//把新建的节点的指向下一个节点的指针设为NULL
		}//当蛇头迟到了食物的时候便会调用这个函数以创建新的蛇节
/*******************加载图片的函数，把所有图片一次性加载到内存中*************/
		void loadpicture(void){//加载图片的函数，把所有图片一次性加载到内存中
			loadimage(&pic_res.food_pic,				"res/pic_res/food_picture.jpg");
			loadimage(&pic_res.snbo_pic,				"res/pic_res/snack_body.jpg");
			loadimage(&pic_res.scoreBG,					"res/pic_res/scoreBG.jpg");
			loadimage(&pic_res.words.Life,				"res/pic_res/Life.jpg");
			loadimage(&pic_res.words.Mode,				"res/pic_res/Mode.jpg");
			loadimage(&pic_res.words.modes.easy,		"res/pic_res/words/modes/easy.jpg");
			loadimage(&pic_res.words.modes.normal,		"res/pic_res/words/modes/normal.jpg");
			loadimage(&pic_res.words.modes.diffcult,	"res/pic_res/words/modes/diffcult.jpg");
			loadimage(&pic_res.words.Score,				"res/pic_res/Score.jpg");
			loadimage(&pic_res.words.Time,				"res/pic_res/Time.jpg");
			loadimage(&pic_res.words.semicolon,				"res/pic_res/snack_body.jpg");
			loadimage(&pic_res.nums.num_zeroL,			"res/pic_res/nums/num_zeroL.jpg");
			loadimage(&pic_res.nums.num_zeroD,			"res/pic_res/nums/num_zeroD.jpg");
			loadimage(&pic_res.nums.num_two,				"res/pic_res/nums/num_two.jpg");
			loadimage(&pic_res.nums.num_three,			"res/pic_res/nums/num_three.jpg");
			loadimage(&pic_res.nums.num_four,			"res/pic_res/nums/num_four.jpg");
			loadimage(&pic_res.nums.num_five,			"res/pic_res/nums/num_five.jpg");
			loadimage(&pic_res.nums.num_six,				"res/pic_res/nums/num_six.jpg");
			loadimage(&pic_res.nums.num_seven,			"res/pic_res/nums/num_seven.jpg");
			loadimage(&pic_res.nums.num_eight,			"res/pic_res/nums/num_eight.jpg");
			loadimage(&pic_res.nums.num_nine,			"res/pic_res/nums/num_nine.jpg");
			//队形很重要，这必须得再提一遍
		}
/*******************初始化固定界面的函数，把固定界面输入到屏幕中*************/
		void loadpic_time(void){
			putimage(640,60,&pic_res.nums.num_zeroD);
			putimage(658,60,&pic_res.nums.num_zeroD);
			putimage(676,60,&pic_res.nums.num_zeroD);
			putimage(694,60,&pic_res.words.semicolon);
			putimage(712,60,&pic_res.nums.num_zeroD);
			putimage(730,60,&pic_res.nums.num_zeroD);
			putimage(748,60,&pic_res.words.semicolon);
			putimage(766,60,&pic_res.nums.num_zeroD);
			putimage(784,60,&pic_res.nums.num_zeroD);
		}
		void loadpic_life(void){
			putimage(640,165,&pic_res.nums.num_zeroD);
			putimage(694,165,&pic_res.nums.num_zeroD);
			putimage(748,165,&pic_res.nums.num_zeroD);
		}
		void loadpic_score(void){
			for(int a=0;a<6;a++){
				for(int b=0;b<6;b++){
					putimage(640+b*18,375+a*12,&pic_res.nums.num_zeroD);
				}
			}
		}
		void loadpic(void){
			putimage(600,0,&pic_res.scoreBG);
			putimage(620,16,&pic_res.words.Time);
			loadpic_time();
			putimage(620,120,&pic_res.words.Life);
			loadpic_life();
			putimage(620,225,&pic_res.words.Mode);
			putimage(640,270,&pic_res.words.modes.easy);
			putimage(620,333,&pic_res.words.Score);
			loadpic_score();
		}
/*************************************************************************/
/*		void DataD(void){
			data.snack.snack_x=rand(time(NULL))%20;
			data.snack.snack_y=rand()%20;               //初始化第一个蛇节的位置
			for(int i=0;i<food_maxnum;i++){
				data.food[i].food_x=rand();
				data.food[i].food_y=rand();
				if(Snack_Yn()){
					i--;
				}else{									//这个好像还要再创建一个函数才能完美的完成任务
				putimage(data.food[i].food_x * 30 + 7,data.food[i].food_y * 30 + 7,&food_picture);
				//然后就puimage
				//这应该放在别的函数里，术业有专攻
				}
			}
		}*/
/*************************************************************************/
		
	protected:											//受保护的行为和属性
		const int food_maxnum;							//食物最多个数
		int snack_eatfood;								//蛇吃了食物的数量
		int score;										//分数
		int rest_life;									//剩余生命
		struct Picture_resource{						//图片资源
			IMAGE food_pic;								//食物的图片
			IMAGE snbo_pic;								//蛇身的图片
			IMAGE scoreBG;								//分数背景
			struct Words{								//文字图片资源
				IMAGE Time;								//图片字样“Time”
				IMAGE Life;								//图片字样“Life”
				IMAGE Mode;								//图片字样“Mode”
				struct Modes{
					IMAGE easy;							//简单难度模式字样
					IMAGE normal;						//一般难度模式字样
					IMAGE diffcult;						//困难难度模式字样
				}modes;
				IMAGE Score;							//图片字样“Score”
				IMAGE semicolon;						//分号，时间要用
			}words;
			struct Number{								//数字字样图片资源
				IMAGE num_zeroL;						//0明亮的
				IMAGE num_zeroD;						//0暗淡的
				IMAGE num_one;							//…………
				IMAGE num_two;
				IMAGE num_three;
				IMAGE num_four;
				IMAGE num_five;
				IMAGE num_six;
				IMAGE num_seven;
				IMAGE num_eight;
				IMAGE num_nine;
			}nums;
		}pic_res;
/*		struct Data{
			struct Snack{
				int snack_x, snack_y;					//这个蛇节的位置
				int snack_lifetime;                     //这个蛇节的存活时间
				struct Snack *next;						//指向下一个蛇节的指针
			}snack;
			struct Food{
				int food_time;                          //食物存活了多久，越久，越容易消失
				int food_x, food_y;						//食物位置
			}food[food_maxnum];
		}data;*/
	private:											//禁止外部访问的行为和属性
};