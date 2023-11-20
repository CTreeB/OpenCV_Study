#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
static void setLabel(cv::Mat&, const std::vector<cv::Point>&, const cv::String&);
void labeling_base()
{
	uchar data[] = {
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,
	};

	cv::Mat src = cv::Mat(8, 8, CV_8UC1, data) * 255;

	cv::Mat labels;

	int cnt = cv::connectedComponents(src, labels);

	std::cout << "src:\n" << src << std::endl;
	std::cout << "label:\n" << labels << std::endl;
	std::cout << "number of labels:\n" << cnt << std::endl;

}

//���̺� ����
void labeling_stats()
{
	cv::Mat src = cv::imread("keyboard.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::Mat binary_image;
	cv::threshold(src, binary_image, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);
	
	cv::Mat labels;
	cv::Mat stats;
	cv::Mat centroids;
	int numberOfLables = cv::connectedComponentsWithStats(binary_image, labels, stats, centroids);
	cv::Mat dst;
	cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);
	for (int i = 1; i < numberOfLables; ++i)	//i = 0�� ���
	{
		int* ptr = stats.ptr<int>(i);
		if (ptr[4] < 20) continue;	//���� �ȼ� �ǳʶ�
		cv::rectangle(dst, cv::Rect(ptr[0], ptr[1], ptr[2], ptr[3]), cv::Scalar(0, 255, 255), 1);
	}
	
	cv::imshow("SRC", src);
	cv::imshow("BINARY", binary_image);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

//�ܰ��� ����
void contours_basis()
{
	cv::Mat src = cv::imread("contours.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(src, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	cv::Mat dst;
	cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);
	int index{ 0 };
	for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin(); it != contours.end(); ++it)	//end()���� nullptr�� ���� ����
	{
		cv::Scalar c(rand() & 255, rand() & 255, rand() & 255);
		cv::drawContours(dst, contours, index++, c, 2);
	}
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}


static void setLabel(cv::Mat& img, const std::vector<cv::Point>& pts, const cv::String& label)
{
	cv::Rect rect = cv::boundingRect(pts);
	cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 1);
	cv::putText(img, label, rect.tl(), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 255));
}


//�ܰ��� ó�� �Լ�(�̴�������Ʈ�� ���� �ڵ�)
void find_polygon()
{
	cv::Mat src = cv::imread("polygon.bmp", cv::IMREAD_COLOR);
	if (src.empty()) return;
	cv::Mat gray_scale;
	cv::cvtColor(src, gray_scale, cv::COLOR_BGR2GRAY);

	cv::Mat binary_image;
	cv::threshold(gray_scale, binary_image, 0.0, 255.0, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

	//�ܰ������� �����͸� �����ϴ� ���� �ڷ���
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(binary_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	
	for (auto&& pts : contours)	//pts : ��ǥ��
	{
		if (cv::contourArea(pts) < 400) continue;	//400 �ȼ� ���� ������ ������
			std::vector<cv::Point> approximate;		//�ܰ��� �׷���
			cv::approxPolyDP(pts, approximate, cv::arcLength(pts, true)*0.02, true);	//�ܰ��� ����

			int polygon_size = static_cast<int>(approximate.size());
			if (polygon_size == 3)
			{
				setLabel(src, pts, "Triangle");
			}
			else if (polygon_size == 4)
			{
				setLabel(src, pts, "Rectangle");
			}
			else if(polygon_size > 4)
			{
				double length = cv::arcLength(pts, true);
				double area = cv::contourArea(pts);
				double ratio = (4.0 * CV_PI * area) / (length * length);
					if (ratio > 0.8)
					{
						setLabel(src, pts, "CIR");
					}
			}

	}
	cv::imshow("SRC", src);
	cv::imshow("GRAY", gray_scale);
	cv::imshow("BINARY", binary_image);
	cv::waitKey();
	cv::destroyAllWindows();
}


