#pragma once
#include "headline.h"

//���캯��
SpeechManager::SpeechManager() {
	//��ʼ������
	this->initSpeech();

	//����12��ѡ��
	this->createSpeech();

	//���������¼
	this->loadRecord();

}

//��������
SpeechManager::~SpeechManager() {

}

//�˵�����
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//��ʼ������
void SpeechManager::initSpeech() {
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ����������
	this->m_Index = 1;

	//����ż�¼������Ҳ���
	this->m_Record.clear();
}

//����12��ѡ��
void SpeechManager::createSpeech() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		//����ѡ�ֱ�ţ������뵽v1������
		this->v1.push_back(i + 10001);

		//ѡ�ֱ���Լ���Ӧѡ�֣����뵽map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ǩ
void SpeechManager::SpeechDraw() {
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ";
	cout << "------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->m_Index == 1) {
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		//�ڶ��ֱ���
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


//����
void SpeechManager::SpeechContest() {
	cout << "------------��" << this->m_Index << "�ֱ�����ʽ��ʼ-----------------" << endl;

	//׼����ʱ���� ���С��ɼ�,��key���ɷ�����value����ѡ�ֱ��,��������
	multimap<double, int, greater<double>> groupScore;
	int num = 0; //��¼��Ա���� 6��һ��

	vector<int> v_Src;//����ѡ������
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600~1000
		//	cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//��������
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);//�ܷ�
		double avg = sum / (double)d.size();//ƽ����

		////��ӡƽ����
		//cout << "���:" << *it << " ������" << this->m_Speaker[*it].m_Name << " ƽ���֣�" << avg << endl;

		//��ƽ���ַ���map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//��������ݷ�����ʱС��������
		groupScore.insert(make_pair(avg, *it));//key�ǵ÷֣�value��ѡ�ֱ��
		//ÿ6��ȡ��ǰ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С���������:" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name
				  	 << " �����ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++){
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//С���������
			cout << endl;

		}

	}
	cout << "-----------------��" << this->m_Index << "�ֱ������--------------------" << endl;
	system("pause");
}

//��ʾ�������
void SpeechManager::showScore() {
	cout << "---------------------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-----------------" << endl;;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "ѡ�ֱ�ţ�" << *it << "������" << this->m_Speaker[*it].m_Name << " �÷֣�"
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//�������
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ�

	//��ÿ��ѡ������д���ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;

	//�����ļ���Ϊ�յ�״̬
	this->fileIsEmpty = false;
}

//��ʼ����
void SpeechManager::startSpeech() {
	//��ʼ��һ�ֱ���
	//1.��ǩ
	this->SpeechDraw();

	//2.����
	this->SpeechContest();

	//3.��ʾ�������
	this->showScore();

	//��ʼ�ڶ��ֱ���
	this->m_Index++;
	//1.��ǩ
	this->SpeechDraw();

	//2.����
	this->SpeechContest();

	//3.��ʾ���ս��
	this->showScore();

	//4.����������ļ���
	this->saveRecord();

	//���ñ�������ȡ��¼
	//��ʼ������
	this->initSpeech();

	//����12��ѡ��
	this->createSpeech();

	//���������¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

//���������¼
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//���������� ��ȡ�ļ�

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
	//	cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	
	//�ļ�Ϊ�����
	char ch;
	ifs >> ch;//��һ���ַ������ļ��Ƿ�Ϊ��
	//ifs.eof()Ϊ���ʾ�����ļ�β�����ļ�Ϊ��
	if (ifs.eof()) {
	//	cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty=true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);//�������ȡ�ĵ����ַ��ٷŻ���
	int index = 0;//��ʾ�ڼ���
	string data;
	//һ�ζ�ȡһ��
	while (ifs >> data) {
		vector<string> v;//���6��string�ַ���

		int pos = -1;//�鵽","λ�õı���
		int start = 0;

		while (true) {
			pos = data.find(",", start);//�ҵ���һ��","��λ��
			if (pos == -1) {
				//δ�ҵ�
				break;
			}
			//��ȡ�ַ���
			string temp = data.substr(start, pos - start);
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;

	}
	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
	//	cout << "��"<<it->first+1 << "��ھ���ţ�" << it->second[0] << " ������" << it->second[1] << endl;
	//}
}

//�鿴�����¼
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ������ڣ����߼�¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "��" << i + 1 << "��"
				<< "�ھ���ţ�" << this->m_Record[i][0] << " ������" << this->m_Record[i][1] << " "
				<< "�Ǿ���ţ�" << this->m_Record[i][2] << " ������" << this->m_Record[i][3] << " "
				<< "������ţ�" << this->m_Record[i][4] << " ������" << this->m_Record[i][5] << endl;
		}
	}

	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//��ģʽ ios::trunc ��������ļ���ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������
		this->initSpeech();

		//����ѡ��
		this->createSpeech();

		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}
