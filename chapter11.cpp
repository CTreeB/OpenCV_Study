#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

//������ ����ȭ(p358)
static void on_thread(int position, void* user_data)
{
	cv::Mat src = *(static_cast<cv::Mat*>(user_data));
	cv::Mat dst;
	cv::threshold(src, dst, position, 255.0, cv::THRESH_BINARY);
	cv::imshow("DST", dst);

}

void using_threashold()
{
	//cv::Mat src = cv::imread("neutrophils.png", cv::IMREAD_GRAYSCALE);
	cv::Mat src = cv::imread("sudoku.jpg", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;

	cv::namedWindow("SRC");
	cv::namedWindow("DST");
	cv::imshow("SRC", src);
	cv::createTrackbar("Threshold", "DST", 0, 255, on_thread, (void*)&src);
	cv::setTrackbarPos("Threshold", "DST", 128);

	cv::waitKey();
	cv::destroyAllWindows();
}


//������ ����ȭ(p365)
static void on_trackbar(int position, void* user_data)
{
	cv::Mat src = *(static_cast<cv::Mat*>(user_data));
	int block_size = position;
	if (position % 2 == 0) --block_size;	//posiotion�� ¦���̰ų� 3���� ������, ������� Ȧ���� �����
	if (block_size < 3) block_size = 3;	
	
	cv::Mat dst;
	cv::adaptiveThreshold(src, dst, 255.0, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, block_size, 5.0);	//��� �ȼ��� - C = C�� ���� 5�� ���
	cv::imshow("DST", dst);
}

void adaptive_threshold()
{
	cv::Mat src = cv::imread("sudoku.jpg", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::imshow("src", src);

	cv::namedWindow("DST");
	cv::createTrackbar("Blocksize", "DST", 0, 200, on_trackbar, (void*)&src);	//blocksize - Ʈ���� ����, DST - �̹��� ���� ǥ�� 
	cv::setTrackbarPos("Blocksize", "DST", 11);
	cv::waitKey();
	cv::destroyAllWindows();
}


//�������� ����(p369)
void erode_dilate()
{
	cv::Mat src {cv::imread("milkdrop.bmp", cv::IMREAD_GRAYSCALE)};
	if (src.empty()) return;
	cv::Mat binary_image;
	cv::threshold(src, binary_image, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);	//--> 0.0���� �����ϸ�, otsu�� ����ȭ ��������
	
	cv::Mat dst_erode;
	cv::erode(binary_image, dst_erode, cv::Mat(), cv::Point(-1, -1), 10);	//3 x 3
	
	cv::Mat dst_dilate;
	cv::dilate(binary_image, dst_dilate, cv::Mat());	//3 x 3 ����Ʈ, for ������ ���ؼ�, �� ħ�Ľ�ų �� �ִ�
	cv::imshow("Erode", dst_erode);
	cv::imshow("Dilate", dst_dilate);
	cv::imshow("SRC", src);
	cv::imshow("binary_image", binary_image);
	cv::waitKey();
	cv::destroyAllWindows();
}

//open and close(p377)
void open_close()
{
	cv::Mat src = cv::imread("milkdrop.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::Mat binary_image;
	//��ó��->����ȭ(��üŽ���� ����ȭ)
	cv::threshold(src, binary_image, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);

	cv::Mat dst_open;
	cv::Mat dst_close;
	cv::morphologyEx(binary_image, dst_open, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1, -1), 3);	//ħ�� -> ��â

	cv::morphologyEx(binary_image, dst_close, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1, -1), 3);	//��â -> ħ��

	cv::imshow("SRC", src);
	cv::imshow("Binary_image", binary_image);
	cv::imshow("DST_OPEN", dst_open);
	cv::imshow("DST_CLOSE", dst_close);
	cv::waitKey();
	cv::destroyAllWindows();
	
}

