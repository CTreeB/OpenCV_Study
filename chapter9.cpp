#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

void sobel_edge()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;

	cv::Mat dx; //x성분 미분용
	cv::Mat dy;	//y성분 미분용

	cv::Sobel(src, dx, CV_32FC1, 1, 0);	// x 성분만 미분
	cv::Sobel(src, dy, CV_32FC1, 0, 1);	// y 성분만 미분
	cv::imshow("SRC", src);
	cv::imshow("Dx", dx);
	cv::imshow("Dy", dy);
	//소벨 ###################
	cv::Mat mag;	//크기를 확인할 matrix
	cv::magnitude(dx, dy, mag);
	mag.convertTo(mag, CV_8UC1);	//컴퓨터는 그레이스케일로 볼 수있기 때문에 영상 자료형을 바꿔줌
	cv::imshow("mag", mag);

	cv::Mat real_edge;
	real_edge = mag > 100;		//특정 그래디언트 값만 볼 수 있게 함--> 임계값
	cv::imshow("real_edge", real_edge);

	cv::waitKey();
	cv::destroyAllWindows();
}

void canny_edge()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::Mat dst1;	// 1 : 2 비율
	cv::Mat dst2;	// 1 : 3 비율

	cv::Canny(src, dst1, 50, 100, 3, true);	//100 이상과 연결된 임계값(강한,약한)엣지까지 출력, 50아래의 엣지는 삭제
	cv::Canny(src, dst2, 50, 150, 3, true);	//150 이상과 연결된 임계값(강한,약한)엣지까지 출력, 50아래의 엣지는 삭제
	
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
		float r = lines[i][0];	//라디안값
		float t = lines[i][1];	// 세타값
		//극좌표 ---> x,y 좌표계
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
	//최소 5픽셀 거리는 직선으로
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
	
	cv::Mat blurred;	//원본에서 더 잘 찾을 수 있도록, 블러효과 삽입
	cv::blur(src, blurred, cv::Size(3, 3));
	
	std::vector<cv::Vec3f> circles;//--> Vec3f : 3가지 타입을 저장할수 있는 벡터

	cv::Mat dst;
	cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);	//-> 3채널 컬러로 저장
	//원 찾기
	cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1, 100, 100, 50);	//--> 70픽셀 보다 커야, 원으로 인식
	
	for (auto&& circle : circles)	//circles에서 갖고 와서 circle에 담음. // int i = 0; i < circles.size(); ++i 와 같은 기능
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

