#pragma once
#include "headline.h"

//����ݽ�������
class SpeechManager {
public:

	//���캯��
	SpeechManager();

	//��������
	~SpeechManager();

	//�˵�����
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������
	void initSpeech();

	//����12��ѡ��
	void createSpeech();

	//��ǩ
	void SpeechDraw();

	//����
	void SpeechContest();

	//��ʾ�������
	void showScore();

	//�������
	void saveRecord();

	//��ʼ����
	void startSpeech();

	//���������¼
	void loadRecord();

	//�鿴�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼����
	map<int, vector<string>> m_Record;

	//����ѡ�ֱ������ 12��
	vector<int> v1;

	//��һ�ֽ���ѡ�ֱ������ 6��
	vector <int> v2;

	//ʤ����ǰ����ѡ�ֱ������ 3��
	vector<int> vVictory;

	//��ű�������
	int m_Index;

	//��ű���Լ���Ӧ����ѡ�ֵ�����
	map<int, Speaker> m_Speaker;

};

