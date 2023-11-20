#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

void sobel_edge()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;

	cv::Mat dx; //x���� �̺п�
	cv::Mat dy;	//y���� �̺п�

	cv::Sobel(src, dx, CV_32FC1, 1, 0);	// x ���и� �̺�
	cv::Sobel(src, dy, CV_32FC1, 0, 1);	// y ���и� �̺�
	cv::imshow("SRC", src);
	cv::imshow("Dx", dx);
	cv::imshow("Dy", dy);
	//�Һ� ###################
	cv::Mat mag;	//ũ�⸦ Ȯ���� matrix
	cv::magnitude(dx, dy, mag);
	mag.convertTo(mag, CV_8UC1);	//��ǻ�ʹ� �׷��̽����Ϸ� �� ���ֱ� ������ ���� �ڷ����� �ٲ���
	cv::imshow("mag", mag);

	cv::Mat real_edge;
	real_edge = mag > 100;		//Ư�� �׷����Ʈ ���� �� �� �ְ� ��--> �Ӱ谪
	cv::imshow("real_edge", real_edge);

	cv::waitKey();
	cv::destroyAllWindows();
}

void canny_edge()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::Mat dst1;	// 1 : 2 ����
	cv::Mat dst2;	// 1 : 3 ����

	cv::Canny(src, dst1, 50, 100, 3, true);	//100 �̻�� ����� �Ӱ谪(����,����)�������� ���, 50�Ʒ��� ������ ����
	cv::Canny(src, dst2, 50, 150, 3, true);	//150 �̻�� ����� �Ӱ谪(����,����)�������� ���, 50�Ʒ��� ������ ����
	
	cv::imshow("src", dst1);
	cv::imshow("src1", dst2);

	cv::waitKey();
	cv::destroyAllWindows();

}

void hought_lines()
{
	cv::Mat src = cv::imread("building.jpg", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::Mat edge;
	cv::Canny(src, edge, 50, 150);

	std::vector<cv::Vec2f> lines;
	cv::HoughLines(edge, lines, 1.0, CV_PI / 180, 250);
	cv::Mat dst;
	cv::cvtColor(edge, dst, cv::COLOR_GRAY2BGR);
	for (int i = 0; i < lines.size(); ++i)
	{
		float r = lines[i][0];	//���Ȱ�
		float t = lines[i][1];	// ��Ÿ��
		//����ǥ ---> x,y ��ǥ��
		double cos_t = cos(t);	
		double sin_t = sin(t);
		double x0 = r * cos_t;
		double y0 = r * sin_t;
		double alpha = 1000;
		cv::Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		cv::Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		cv::line(dst, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
	}
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

void hough_line_segments()
{
	cv::Mat src = imread("building.jpg", cv::IMREAD_GRAYSCALE);

	if (src.empty()) return;

	cv::Mat edge;
	cv::Canny(src, edge, 50, 150);

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);
	//�ּ� 5�ȼ� �Ÿ��� ��������
	cv::Mat dst;
	cv::cvtColor(edge, dst, cv::COLOR_GRAY2BGR);
	
	for (cv::Vec4i l : lines)
	{
		cv::line(dst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
	}

	cv::imshow("src", src);
	cv::imshow("dst", dst);

	cv::waitKey();
	cv::destroyAllWindows();

}

void hough_circles()
{
	cv::Mat src = imread("coins2.png", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	
	cv::Mat blurred;	//�������� �� �� ã�� �� �ֵ���, ��ȿ�� ����
	cv::blur(src, blurred, cv::Size(3, 3));
	
	std::vector<cv::Vec3f> circles;//--> Vec3f : 3���� Ÿ���� �����Ҽ� �ִ� ����

	cv::Mat dst;
	cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);	//-> 3ä�� �÷��� ����
	//�� ã��
	cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1, 100, 100, 50);	//--> 70�ȼ� ���� Ŀ��, ������ �ν�
	
	for (auto&& circle : circles)	//circles���� ���� �ͼ� circle�� ����. // int i = 0; i < circles.size(); ++i �� ���� ���
	{
		cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
		int radius = cvRound(circle[2]);
		cv::circle(dst, center, radius, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
	}

	cv::imshow("src", src);
	cv::imshow("dst", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}

