#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
using namespace std;

//设计演讲管理类
class SpeechManager
{
public:
    //构造函数
    SpeechManager();

    //展示菜单
    void show_Menu();

    //退出系统
    void exitSystem();

    //析构函数
    ~SpeechManager();

    //初始化容器和属性
    void initSpeech();

    //创建12名选手
    void createSpeaker();

    //开始比赛-比赛流程控制
    void starSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //成员属性
    //保存第一轮比赛选手编号容器 12人
    vector<int> v1;

    //保存第二轮比赛选手（第一轮晋级）编号容器 6人
    vector<int> v2;

    //保存胜出前三名选手编号容器 3人
    vector<int> vVictory;

    //存放编号以及对应选手的容器
    map<int, Speaker> m_Speaker;

    //存放比赛轮数
    int m_Index;
};

