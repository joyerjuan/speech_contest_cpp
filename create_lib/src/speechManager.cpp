#include "speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
    //初始化容器和属性
    this->initSpeech();
    //创建12名选手
    this->createSpeaker();
    //获取往届记录
    this->loadRecord();
}

//展示菜单
void SpeechManager::show_Menu()
{
    cout<< "***********************************" << endl;
    cout<< "*********欢迎参加演讲比赛**********" << endl;
    cout<< "*********1.开始演讲比赛************" << endl;
    cout<< "*********2.查看往届记录************" << endl;
    cout<< "*********3.清空比赛记录************" << endl;
    cout<< "*********0.退出比赛程序************" << endl;
    cout<< "***********************************" << endl;
    cout << endl;
}

//退出系统
void SpeechManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    exit(0);
}

//初始化容器和属性
void SpeechManager::initSpeech()
{
    //容器都置空
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();

    //初始化比赛轮数
    this->m_Index = 1;
    //初始化记录容器
    this->m_Record.clear();
}

//创建12名选手
void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for(int i=0; i<nameSeed.size(); i++)
    {
        string name = "选手";
        name += nameSeed[i];
        //创建具体选手
        Speaker sp;
        sp.m_Name = name;
        for(int j=0; j<2; j++)
        {
            sp.m_Score[j] = 0;
        }

        //创建选手编号，并放入v1容器中
        this->v1.push_back(i+10001);

        //选手编号以及对应选手 放入map容器中
        this->m_Speaker.insert(make_pair(i+10001, sp));
    }
}

//开始比赛-比赛流程控制
void SpeechManager::starSpeech()
{
    //第一轮比赛
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示晋级结果
    this->showScore();

    //第二轮比赛
    this->m_Index++;
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示最终结果
    this->showScore();
    //4、保存分数
    this->saveRecord();

    //重置比赛，获取记录
    //初始化容器和属性
    this->initSpeech();
    //创建12名选手
    this->createSpeaker();
    //获取往届记录
    this->loadRecord();

    cout << "本届比赛完毕！" << endl;
}

//抽签
void SpeechManager::speechDraw()
{
    cout << "第<" << this->m_Index << ">轮比赛选手正在抽签" << endl;
    cout << "*********************************" << endl; 
    cout << "抽签后演讲顺序如下： " << endl;
    if(this->m_Index == 1)
    {
        //第一轮比赛
        random_shuffle(v1.begin() ,v1.end());
        for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        //第二轮比赛
        random_shuffle(v2.begin() ,v2.end());
        for(vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << "***********************************" << endl; 
    cout << endl;
}

//比赛
void SpeechManager::speechContest()
{
    cout << "*********第<" << this->m_Index << ">轮比赛正式开始*********" << endl;

    //准备临时容器，存放小组成绩
    multimap<double, int, greater<double>> groupScore;
    int num = 0; //记录人员个数 6人一组

    vector<int>v_Src;//比赛选手容器
    if(this->m_Index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }
    //遍历所有选手进行比赛
    for(vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
    {
        num++;
        //评委打分
        deque<double>d;
        for(int i=0; i<10; i++)
        {
            double temp_score = (rand()%401+600)/10.f; //600~1000
            //cout << temp_score << " ";
            d.push_back(temp_score);
        }
        //cout << endl;
        sort(d.begin(), d.end(), greater<double>()); //排序
        d.pop_front();//去除最高分
        d.pop_back();//去除最低分

        double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
        double avg = sum / (double)d.size();//平均分

        //打印平均分
        //cout << "编号： " << *it << " 姓名： " << this->m_Speaker[*it].m_Name << " 获取平均分： " << avg << endl;

        //将平均分放入到map容器中
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

        //将打分数据放到临时小组容器中
        groupScore.insert(make_pair(avg, *it)); //key是得分，value是具体选手编号
        //每6人取出前三名
        if(num % 6 == 0)
        { 
            cout << "第<" << num/6 << ">小组名次如下： " << endl;
            for(multimap<double, int, greater<double>>::iterator it=groupScore.begin(); it!=groupScore.end(); it++)
            {
                cout << "编号： " << it->second << " 姓名： " << this->m_Speaker[it->second].m_Name << " 成绩： " 
                    << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
            }

            //取走前三名
            int count = 0;
            for(multimap<double, int, greater<double>>::iterator it=groupScore.begin(); it!=groupScore.end() && count <3; it++, count++)
            {
                if(this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vVictory.push_back((*it).second);
                }
                
            }
            groupScore.clear();//小组容器清空
            cout << endl;
        }
    }
    cout << "***********第<" << this->m_Index << ">轮比赛完毕！***********" << endl;
    cout << endl;
}

//显示比赛结果
void SpeechManager::showScore()
{
    cout << "*********第<" << this->m_Index << ">轮晋级选手信息如下：*********" << endl;
    vector<int>v;
    if(this->m_Index == 1)   v = v2;
    else   v = vVictory;

    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "编号： " << *it << " 姓名： " << m_Speaker[*it].m_Name << " 得分： " 
            << m_Speaker[*it].m_Score[this->m_Index-1] << endl;
    }
    cout << endl;
    this->show_Menu();
}

//保存记录
void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件

    //将每个选手的数据写入到文件中
    for(vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
    {
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;

    //关闭文件
    ofs.close();
    cout << "记录已经保存" << endl;

    //更改文件不为空
    this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv", ios::in); //输入流对象，读取文件

    // if (!ifs.is_open())//文件打开失败
    // {
    //     this->fileIsEmpty = true;
    //     cout << "文件不存在！" << endl;
    //     ifs.close();
    //     return;
    // }

    char ch;
    ifs >> ch;
    if(ifs.eof())//文件已清空
    {
        cout << "文件为空！" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }
    
    //文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch);//读取的单个字符放回去
    string data;
    int index = 0;
    while(ifs >> data)
    {
        // cout << data << endl;
        vector<string> v;
        int pos = -1;//逗号位置游标
        int start = 0;
        while(true)
        {
            pos = data.find(",", start);//从0开始找“,”
            if(pos == -1)
                break;//找不到break返回
            string tmp = data.substr(start, pos-start); //找到了，进行分割，参数1 起始位置，参数2 截取长度
            // cout << tmp << endl;
            v.push_back(tmp);
            start = pos + 1;
        }
        this->m_Record.insert(make_pair(index,v));
        index++;
    }
    ifs.close();
    // for(map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
    // {
    //     cout << it->first << "冠军编号：" << it->second[0] << " 分数：" << it->second[1] << endl; 
    // }
}

//显示往届得分
void SpeechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        cout << "文件不存在，或记录为空！" << endl;
    }
    else
    {
        for(int i=0; i<this->m_Record.size(); i++)//10010,88.4,10004,85.3,10001,84.85,
        {
            cout << "第<" << i+1 << ">届" 
                <<"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
                <<"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
                <<"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
        }
    }
}

//清空记录
void SpeechManager::clearRecord()
{
    cout << "确认清空？" << endl;
    cout << "1、确认" << endl;
    cout << "2、返回" << endl;

    int select = 0;
    cin >> select ;
    if(select == 1)
    {
        //打开模式ios::trunc,如果存在删除文件并重新创建
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //初始化属性
        this->initSpeech();

        //创建选手
        this->createSpeaker();

        //获取往届记录
        this->loadRecord();

        cout << "清空完成！" << endl;
    }
}

//析构函数
SpeechManager::~SpeechManager()
{

}