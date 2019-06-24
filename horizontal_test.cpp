#include "stdafx.h"
#include "horizontal_test.h"

#include <windows.h>
#include <iostream>
#include <vector> 
#include <iostream>
#include <fstream>        //��ȡ�ļ����ݵĺ���fin��ͷ�ļ�
#include <sstream>        //istringstream ����������ͷ�ļ�
#include <string>		  // �ַ�������ͷ�ļ�
#include <atlstr.h>

using namespace std;

string csv_string;//ԭʼcsv�ַ���
string point_str;//ÿ�����Ӧ���ַ���

vector<pair<int, int>>  all_points;//���е����Ϣ

pair<int, int>  each_point;//ÿһ����
vector<int> point_x_and_y;//ÿ�����x��y


//�ַ����Թ̶��ַ���ֺ���
void split(const string& s, vector<int>& sv, const char flag = ' ')
{
	sv.clear();
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag)) {
		sv.push_back(stoi(temp));
	}
	return;
}


//��ƽ��ֵ
double average(double *x, int len)
{
	double sum = 0;
	for (int i = 0; i < len; i++) // ���
		sum += x[i];
	return sum / len; // �õ�ƽ��ֵ
}


//�󷽲�
double variance(double *x, int len)
{
	double sum = 0.0;
	double aver = average(x, len);
	for (int i = 0; i < len; i++) // ���
		sum += pow(x[i] - aver, 2);
	return sum / len; // �õ�ƽ��ֵ
}

//���׼��
double standard_deviation(double *x, int len)
{
	double vari = variance(x, len);
	return sqrt(vari); // �õ���׼��
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow)
{
	//��ȡCSV�ļ����ļ��б�����10���������
	ifstream fin;
	fin.open("F:\\belt0624_E(6).csv", ios::in);

	if (fin.is_open())
	{
		MessageBox(NULL, TEXT("coordinates.csv�ļ�������"), TEXT("��ȡ�ļ�"), MB_DEFBUTTON1 | MB_DEFBUTTON2);
	}
	else
		return -1;

	all_points.clear();
	point_x_and_y.clear();
	while (fin.good())//�ж��ļ��Ƿ��
	{
		getline(fin, csv_string, ';');
		stringstream sstr(csv_string);

		while (getline(sstr, point_str, '\n'))
		{
			stringstream sstr(point_str);

			string s(point_str);

			split(s, point_x_and_y, ',');
			point_x_and_y.resize(2);
			each_point.first = point_x_and_y[0];//x����
			each_point.second = point_x_and_y[1];//y����

			all_points.push_back(each_point);
		}
	}

	//����CSV�ļ��ж�,�ҵ����������Yֵ�����ֵ����Сֵ�ľ���ֵ������10
	all_points.resize(6);//��10����Ƚ�

	int a[6];//����������10�����y����
	for (int i = 0; i < 6; i++)
	{
		a[i] = all_points[i].second;
	}

	int max_y = a[0];//���ֵ
	for (int i = 0; i < 6; i++)
	{
		if (a[i] > max_y)
			max_y = a[i];
	}

	int min_y = a[0];//��Сֵ
	for (int i = 0; i < 6; i++)
	{
		if (a[i] < min_y)
			min_y = a[i];
	}
	
	//ƽ��ֵ
	double sum = 0;
	for (int i = 0; i < 6; i++) // ���
		sum += a[i];
	double aver_value = sum / 6; 
	//����
	double fangcha = 0;
	for (int i = 0; i < 6; i++) // ���
		fangcha += pow(a[i] - aver_value, 2);
	double ana_vari = fangcha / 6;
	//��׼��
	double std_dev = sqrt(ana_vari);

	CString str;
	str.Format(_T("%f"), std_dev);
	if(std_dev > 3)
		MessageBox(NULL, TEXT("y���귽��:") + str + TEXT(",����ܴ������µ�������ͷ���ʹ�"), TEXT("ˮƽ�����"), MB_DEFBUTTON1 | MB_DEFBUTTON2);
	else
		MessageBox(NULL, TEXT("y���귽��:") + str + TEXT(",�����С������ͷ�봫�ʹ�ˮƽ��������������"), TEXT("ˮƽ�����"), MB_DEFBUTTON1 | MB_DEFBUTTON2);

	fin.close();
	fin.clear();

	return 0;
}
