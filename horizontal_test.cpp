#include "stdafx.h"
#include "horizontal_test.h"

#include <windows.h>
#include <iostream>
#include <vector> 
#include <iostream>
#include <fstream>        //读取文件数据的函数fin的头文件
#include <sstream>        //istringstream 必须包含这个头文件
#include <string>		  // 字符串处理头文件
#include <atlstr.h>

using namespace std;

string csv_string;//原始csv字符串
string point_str;//每个点对应的字符串

vector<pair<int, int>>  all_points;//所有点的信息

pair<int, int>  each_point;//每一个点
vector<int> point_x_and_y;//每个点的x和y


//字符串以固定字符拆分函数
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


//求平均值
double average(double *x, int len)
{
	double sum = 0;
	for (int i = 0; i < len; i++) // 求和
		sum += x[i];
	return sum / len; // 得到平均值
}


//求方差
double variance(double *x, int len)
{
	double sum = 0.0;
	double aver = average(x, len);
	for (int i = 0; i < len; i++) // 求和
		sum += pow(x[i] - aver, 2);
	return sum / len; // 得到平均值
}

//求标准差
double standard_deviation(double *x, int len)
{
	double vari = variance(x, len);
	return sqrt(vari); // 得到标准差
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow)
{
	//读取CSV文件，文件中保存着10个点的坐标
	ifstream fin;
	fin.open("F:\\belt0624_E(6).csv", ios::in);

	if (fin.is_open())
	{
		MessageBox(NULL, TEXT("coordinates.csv文件正常打开"), TEXT("读取文件"), MB_DEFBUTTON1 | MB_DEFBUTTON2);
	}
	else
		return -1;

	all_points.clear();
	point_x_and_y.clear();
	while (fin.good())//判断文件是否打开
	{
		getline(fin, csv_string, ';');
		stringstream sstr(csv_string);

		while (getline(sstr, point_str, '\n'))
		{
			stringstream sstr(point_str);

			string s(point_str);

			split(s, point_x_and_y, ',');
			point_x_and_y.resize(2);
			each_point.first = point_x_and_y[0];//x坐标
			each_point.second = point_x_and_y[1];//y坐标

			all_points.push_back(each_point);
		}
	}

	//根据CSV文件判断,找到其中坐标的Y值的最大值和最小值的绝对值不超过10
	all_points.resize(6);//找10个点比较

	int a[6];//用数组存放着10个点的y坐标
	for (int i = 0; i < 6; i++)
	{
		a[i] = all_points[i].second;
	}

	int max_y = a[0];//最大值
	for (int i = 0; i < 6; i++)
	{
		if (a[i] > max_y)
			max_y = a[i];
	}

	int min_y = a[0];//最小值
	for (int i = 0; i < 6; i++)
	{
		if (a[i] < min_y)
			min_y = a[i];
	}
	
	//平均值
	double sum = 0;
	for (int i = 0; i < 6; i++) // 求和
		sum += a[i];
	double aver_value = sum / 6; 
	//方差
	double fangcha = 0;
	for (int i = 0; i < 6; i++) // 求和
		fangcha += pow(a[i] - aver_value, 2);
	double ana_vari = fangcha / 6;
	//标准差
	double std_dev = sqrt(ana_vari);

	CString str;
	str.Format(_T("%f"), std_dev);
	if(std_dev > 3)
		MessageBox(NULL, TEXT("y坐标方差:") + str + TEXT(",方差很大，请重新调整摄像头或传送带"), TEXT("水平标测结果"), MB_DEFBUTTON1 | MB_DEFBUTTON2);
	else
		MessageBox(NULL, TEXT("y坐标方差:") + str + TEXT(",方差很小，摄像头与传送带水平，可以正常工作"), TEXT("水平标测结果"), MB_DEFBUTTON1 | MB_DEFBUTTON2);

	fin.close();
	fin.clear();

	return 0;
}
