#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;


class Timecount{
    public:
	_LARGE_INTEGER time_start;	//开始时�?
    _LARGE_INTEGER time_over;		//结束时间
	double dqFreq;				//计时器频�?
	LARGE_INTEGER f;		    //计时器频�?
    clock_t start_time;
	clock_t end_time;
    void Startcount(void){
	    QueryPerformanceFrequency(&f);
        dqFreq=(double)f.QuadPart;
	    start_time=clock();
        QueryPerformanceCounter(&time_start);//计时器开始计�?
    }
    void Overcount(void){
        QueryPerformanceCounter(&time_over);//计时器结束计�?
   		end_time=clock();
        // cout<<"Running time is :"<<((time_over.QuadPart-time_start.QuadPart)/dqFreq)*1000<<"ms"<<endl;//单位为秒，精度为1000 000/（cpu主频）微�?
   		cout<< "Running time is: "<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间
    }
}timecount;