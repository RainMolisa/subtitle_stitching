#pragma once
#include<opencv.hpp>
#include<string>
#include<vector>

namespace ss
{
	int get_subtitle_h(cv::Mat& img);
	cv::Mat sub_stitch(std::vector<cv::Mat>& img)
	{
		cv::Mat res;
		int rows = img[0].rows;
		int cols = img[0].cols;
		int sub_height = get_subtitle_h(img[0]);
		int len = img.size();
		int r_rows = rows + (len - 1) * sub_height;
		res.create(r_rows, cols, CV_8UC3);
		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				res.at<uchar>(y, 3 * x + 0) = img[0].at<uchar>(y, 3 * x + 0);
				res.at<uchar>(y, 3 * x + 1) = img[0].at<uchar>(y, 3 * x + 1);
				res.at<uchar>(y, 3 * x + 2) = img[0].at<uchar>(y, 3 * x + 2);
			}
		}
		for (int i = 1; i < img.size(); i++)
		{
			for (int y = rows - sub_height; y < rows; y++)
			{
				for (int x = 0; x < cols; x++)
				{
					res.at<uchar>(rows + (i - 1) * sub_height + y - rows + sub_height, 3 * x + 0) = img[i].at<uchar>(y, 3 * x + 0);
					res.at<uchar>(rows + (i - 1) * sub_height + y - rows + sub_height, 3 * x + 1) = img[i].at<uchar>(y, 3 * x + 1);
					res.at<uchar>(rows + (i - 1) * sub_height + y - rows + sub_height, 3 * x + 2) = img[i].at<uchar>(y, 3 * x + 2);
				}
			}
			
		}
		return res;
	}
	int get_subtitle_h(cv::Mat& img)
	{
		int res=50;
		return res;
	}
};