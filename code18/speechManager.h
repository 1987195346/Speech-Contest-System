#pragma once
#include "headline.h"

//设计演讲管理类
class SpeechManager {
public:

	//构造函数
	SpeechManager();

	//析构函数
	~SpeechManager();

	//菜单功能
	void show_Menu();

	//退出系统
	void exitSystem();

	//初始化属性
	void initSpeech();

	//创建12名选手
	void createSpeech();

	//抽签
	void SpeechDraw();

	//比赛
	void SpeechContest();

	//显示比赛结果
	void showScore();

	//保存分数
	void saveRecord();

	//开始比赛
	void startSpeech();

	//加载往届记录
	void loadRecord();

	//查看往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届记录容器
	map<int, vector<string>> m_Record;

	//比赛选手编号容器 12人
	vector<int> v1;

	//第一轮晋级选手编号容器 6人
	vector <int> v2;

	//胜利者前三名选手编号容器 3人
	vector<int> vVictory;

	//存放比赛论数
	int m_Index;

	//存放编号以及对应具体选手的容器
	map<int, Speaker> m_Speaker;

};

