#include<iostream>
using namespace std;
#include "speechManager.h"
#include <string>
#include <ctime>
 int main()
 {
    //随机数种子
    //srand(unsigned int)time(NULL);
    //创建管理类的对象
    SpeechManager sm;

    int choice = 0;//用来存储用户选项
    while (true)
    {
        sm.show_Menu();
        cout << "请输入你的选择： " << endl;
        cin >> choice; //接收用户选择

        switch (choice)
        {
        case 1: //开始比赛
            sm.starSpeech();
            break;
        case 2: //查看记录
            sm.showRecord();
            break;
        case 3: //清空记录
            sm.clearRecord();
            break;
        case 0: //退出系统
            sm.exitSystem();
            break;
        default:
            break;
        }
    }
    return 0;
 }