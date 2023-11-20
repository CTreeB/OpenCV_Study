#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

static void on_hue_change(int, void*);

void color_inverse()
{
	cv::Mat src = cv::imread("butterfly.jpg", cv::IMREAD_COLOR);
	cv::imshow("SRC", src);
	cv::Mat B(src.size(), CV_8UC1);
	cv::Mat G(src.size(), CV_8UC1);
	cv::Mat R(src.size(), CV_8UC1);
	cv::Mat dst(src.size(), src.type());

	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			cv::Vec3b& p1 = src.at<cv::Vec3b>(i, j);

			cv::Vec3b& p2 = dst.at<cv::Vec3b>(i, j);

			p2[0] = 255 - p1[0];
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p2[2];

			uchar& p_b = B.at<uchar>(i, j);
			p_b = p1[0];

			uchar& p_g = G.at<uchar>(i, j);
			p_g = p1[1];

			uchar& p_r = R.at<uchar>(i, j);
			p_r = p1[2];

			//B.at<uchar>(i, j) = p1[0];	//blue
			//G.at<uchar>(i, j) = p1[1];	//green
			//R.at<uchar>(i, j) = p1[2];	//red


		}
	}

	cv::imshow("Blue channel", B);
	cv::imshow("Green channel", G);
	cv::imshow("Red channel", R);
	cv::imshow("dst", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

void color_grayscale()
{
	cv::Mat src = cv::imread("butterfly.jpg");

	cv::Mat dst;

	cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);// == cv::imread("butterfly.jpg",cv::IMREAD_GRAYCALE());

	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

void color_split()	//색상 채널 나누기(p344)
{
	cv::Mat src = cv::imread("candies.png");
	if (src.empty()) return;
	std::vector<cv::Mat> bgr_planes;
	cv::split(src, bgr_planes);

	cv::imshow("src", src);
	cv::imshow("blue", bgr_planes[0]);
	cv::imshow("Green", bgr_planes[1]);
	cv::imshow("Red", bgr_planes[2]);
	cv::waitKey();
	cv::destroyAllWindows();
}

void color_equalizerHist()
{
	cv::Mat src = cv::imread("pepper.bmp", cv::IMREAD_COLOR);
	if (src.empty()) return;
	cv::Mat dst;
	cv::cvtColor(src, dst, cv::COLOR_BGR2YCrCb);	// BGR -->YCrCb 타입으로 변형
	std::vector<cv::Mat> ycrcb_channels;

	cv::split(dst, ycrcb_channels);		

	cv::equalizeHist(ycrcb_channels[0], ycrcb_channels[0]);	// Y 성분 이퀄라이즈화 해줌

	cv::Mat dst_y;
	cv::merge(ycrcb_channels, dst_y);	// 다시 합쳐줌 --> dst_y 영상 생성

	cv::Mat src_dst;
	cv::cvtColor(dst_y, src_dst, cv::COLOR_YCrCb2BGR);	// YCrCb --> BGR 타입으로 변형

	cv::imshow("SRC", src);
	cv::imshow("SRC_DST", src_dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

static int lower_bound = 40;
static int upper_bound = 80;
static cv::Mat src;
static cv::Mat src_hsv;
static cv::Mat mask;

//색상 범위 지정에 의한 영역 분할
static void on_hue_change(int, void*)	
{
	cv::Scalar lower(lower_bound, 100, 0);
	cv::Scalar upper(upper_bound, 255, 255);
	cv::inRange(src_hsv, lower, upper, mask);
	cv::imshow("SRC", mask);
}

void using_imRange()
{
	src = cv::imread("candies.png");
	if (src.empty()) return;
	cv::cvtColor(src, src_hsv, cv::COLOR_BGR2HSV);
	cv::namedWindow("SRC");
	//cv::imshow("SRC_HSV", src_hsv);
	cv::createTrackbar("LOWER HUE", "SRC", &lower_bound, 179, on_hue_change);
	cv::createTrackbar("UPPER HUE", "SRC", &upper_bound, 179, on_hue_change);
	cv::waitKey();
	cv::destroyAllWindows();
}
