#include<stdio.h>
#include<string>
#include<iostream>
#include<opencv.hpp>
#include <io.h>
#include "subtittle_s.h"
using namespace cv;
using namespace std;
std::vector<std::string> GetFiles(std::string folder_path);
int main(int argc, char** argv)
{
	string in_path;
	cout << "image folder:";
	cin >> in_path;
	cout << "run:" << in_path << endl;
	vector<string> imgF_s = GetFiles(in_path);
	vector<Mat> img_s;
	for (int i = 0; i < imgF_s.size(); i++)
	{
		//cout << imgF_s[i] << endl;
		img_s.push_back(imread(imgF_s[i]));
	}
	Mat res = ss::sub_stitch(img_s);
	imwrite("res.png",res);
}

std::vector<std::string> GetFiles(std::string folder_path)
{
	std::vector<std::string> files;
	//文件句柄
	//intptr_t hFile = 0;//Win10
	long long hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	try
	{
		if ((hFile = _findfirst(p.assign(folder_path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//如果是目录,迭代之  
				//如果不是,加入列表  
				if (!(fileinfo.attrib & _A_SUBDIR))
				{
					files.push_back(p.assign(folder_path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
	catch (std::exception e)
	{
	}
	return files;
}

