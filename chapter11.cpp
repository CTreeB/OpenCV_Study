#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

//영상의 이진화(p358)
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


//적응형 이진화(p365)
static void on_trackbar(int position, void* user_data)
{
	cv::Mat src = *(static_cast<cv::Mat*>(user_data));
	int block_size = position;
	if (position % 2 == 0) --block_size;	//posiotion이 짝수이거나 3보다 작으면, 블럭사이즈를 홀수로 만들기
	if (block_size < 3) block_size = 3;	
	
	cv::Mat dst;
	cv::adaptiveThreshold(src, dst, 255.0, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, block_size, 5.0);	//평균 픽셀값 - C = C는 보통 5를 사용
	cv::imshow("DST", dst);
}

void adaptive_threshold()
{
	cv::Mat src = cv::imread("sudoku.jpg", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::imshow("src", src);

	cv::namedWindow("DST");
	cv::createTrackbar("Blocksize", "DST", 0, 200, on_trackbar, (void*)&src);	//blocksize - 트랙바 네임, DST - 이미지 영상에 표시 
	cv::setTrackbarPos("Blocksize", "DST", 11);
	cv::waitKey();
	cv::destroyAllWindows();
}


//모폴로지 연산(p369)
void erode_dilate()
{
	cv::Mat src {cv::imread("milkdrop.bmp", cv::IMREAD_GRAYSCALE)};
	if (src.empty()) return;
	cv::Mat binary_image;
	cv::threshold(src, binary_image, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);	//--> 0.0으로 설정하면, otsu가 이진화 진행해줌
	
	cv::Mat dst_erode;
	cv::erode(binary_image, dst_erode, cv::Mat(), cv::Point(-1, -1), 10);	//3 x 3
	
	cv::Mat dst_dilate;
	cv::dilate(binary_image, dst_dilate, cv::Mat());	//3 x 3 디폴트, for 구문을 통해서, 더 침식시킬 수 있다
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
	//전처리->이진화(객체탐색은 이진화)
	cv::threshold(src, binary_image, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);

	cv::Mat dst_open;
	cv::Mat dst_close;
	cv::morphologyEx(binary_image, dst_open, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1, -1), 3);	//침식 -> 팽창

	cv::morphologyEx(binary_image, dst_close, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1, -1), 3);	//팽창 -> 침식

	cv::imshow("SRC", src);
	cv::imshow("Binary_image", binary_image);
	cv::imshow("DST_OPEN", dst_open);
	cv::imshow("DST_CLOSE", dst_close);
	cv::waitKey();
	cv::destroyAllWindows();
	
}

