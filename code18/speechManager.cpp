#pragma once
#include "headline.h"

//构造函数
SpeechManager::SpeechManager() {
	//初始化属性
	this->initSpeech();

	//创建12名选手
	this->createSpeech();

	//加载往届记录
	this->loadRecord();

}

//析构函数
SpeechManager::~SpeechManager() {

}

//菜单功能
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//初始化属性
void SpeechManager::initSpeech() {
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;

	//将存放记录的容器也清空
	this->m_Record.clear();
}

//创建12名选手
void SpeechManager::createSpeech() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		//创建具体选手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		//创建选手编号，并放入到v1容器中
		this->v1.push_back(i + 10001);

		//选手编号以及对应选手，放入到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//抽签
void SpeechManager::SpeechDraw() {
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签";
	cout << "------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "----------------------------" << endl;
	system("pause");
	cout << endl;
}


//比赛
void SpeechManager::SpeechContest() {
	cout << "------------第" << this->m_Index << "轮比赛正式开始-----------------" << endl;

	//准备临时容器 存放小组成绩,把key当成分数，value当成选手编号,降序排序
	multimap<double, int, greater<double>> groupScore;
	int num = 0; //记录人员个数 6人一组

	vector<int> v_Src;//比赛选手容器
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600~1000
		//	cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//降序排序
		d.pop_front();//去除最高分
		d.pop_back();//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / (double)d.size();//平均分

		////打印平均分
		//cout << "编号:" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 平均分：" << avg << endl;

		//将平均分放入map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将打分数据放入临时小组容器中
		groupScore.insert(make_pair(avg, *it));//key是得分，value是选手编号
		//每6人取出前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次:" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name
				  	 << " 比赛成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++){
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//小组容器清空
			cout << endl;

		}

	}
	cout << "-----------------第" << this->m_Index << "轮比赛完毕--------------------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::showScore() {
	cout << "---------------------第" << this->m_Index << "轮晋级选手信息如下：-----------------" << endl;;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号：" << *it << "姓名：" << this->m_Speaker[*it].m_Name << " 得分："
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存分数
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件

	//将每个选手数据写入文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;

	//更改文件不为空的状态
	this->fileIsEmpty = false;
}

//开始比赛
void SpeechManager::startSpeech() {
	//开始第一轮比赛
	//1.抽签
	this->SpeechDraw();

	//2.比赛
	this->SpeechContest();

	//3.显示晋级结果
	this->showScore();

	//开始第二轮比赛
	this->m_Index++;
	//1.抽签
	this->SpeechDraw();

	//2.比赛
	this->SpeechContest();

	//3.显示最终结果
	this->showScore();

	//4.保存分数到文件中
	this->saveRecord();

	//重置比赛，获取记录
	//初始化属性
	this->initSpeech();

	//创建12名选手
	this->createSpeech();

	//加载往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//加载往届记录
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//输入流对象 读取文件

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
	//	cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	
	//文件为空清空
	char ch;
	ifs >> ch;//读一个字符看看文件是否为空
	//ifs.eof()为真表示读到文件尾，该文件为空
	if (ifs.eof()) {
	//	cout << "文件为空" << endl;
		this->fileIsEmpty=true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);//将上面读取的单个字符再放回来
	int index = 0;//表示第几届
	string data;
	//一次读取一行
	while (ifs >> data) {
		vector<string> v;//存放6个string字符串

		int pos = -1;//查到","位置的变量
		int start = 0;

		while (true) {
			pos = data.find(",", start);//找到第一个","的位置
			if (pos == -1) {
				//未找到
				break;
			}
			//截取字符串
			string temp = data.substr(start, pos - start);
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;

	}
	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
	//	cout << "第"<<it->first+1 << "届冠军编号：" << it->second[0] << " 分数：" << it->second[1] << endl;
	//}
}

//查看往届记录
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件不存在，或者记录为空！" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第" << i + 1 << "届"
				<< "冠军编号：" << this->m_Record[i][0] << " 分数：" << this->m_Record[i][1] << " "
				<< "亚军编号：" << this->m_Record[i][2] << " 分数：" << this->m_Record[i][3] << " "
				<< "季军编号：" << this->m_Record[i][4] << " 分数：" << this->m_Record[i][5] << endl;
		}
	}

	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//打开模式 ios::trunc 如果存在文件则删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeech();

		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}
