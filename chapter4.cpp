#pragma once
#include "opencv2/opencv.hpp"
#include <string> 
//static void on_mouse(int, int, int, int, void*);
static void on_level_changed(int, void*);

void show_camera()
{
	cv::VideoCapture cap(0);	//Default my webcamera
	if (!cap.isOpened())
	{
		std::cerr << "Camera does not exist" << std::endl;
		return;
	}
	std::cout << "Height : " << cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) << std::endl;
	std::cout << "Width : " << cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)) << std::endl;
	cv::Mat frame;
	while (true)
	{

		cap >> frame;
		if (frame.empty())
		{
			std::cout << "Frame has a problem" << std::endl;
			break;
		}
		cv::imshow("CAMERA", ~frame);
		if (cv::waitKey(10) == 27) break;	//27SEC

	}
	cap.release();
	cv::destroyAllWindows();
}

void show_movie()
{
	std::cout << cv::getBuildInformation() << std::endl;
	cv::VideoCapture cap("stopwatch.avi");
	if (!cap.isOpened())
	{
		std::cerr << "No camera" << std::endl;
		return;
	}
	std::cout << "Height : " << cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) << std::endl;
	std::cout << "Width : " << cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)) << std::endl;
	std::cout << "Count : " << cvRound(cap.get(cv::CAP_PROP_FRAME_COUNT)) << std::endl;
	double fps = cap.get(cv::CAP_PROP_FPS);
	int delay = cvRound(1000 / fps);
	
	cv::Mat inversed;
	cv::Mat frame;
	
	while (true)
	{
		cap >> frame; // 카메라에서 읽은 영상을 frame matrix
		inversed = ~frame;
		if (inversed.empty()) break;	//영상이 다 끝난경우
		cv::imshow("CAMERA", frame);
		cv::imshow("INVERSED", inversed);
		if (cv::waitKey(delay) == 27) break;	//정상적인 영상재생
	}
	//cap.release();
	/*cv::destroyAllWindows();*/
}

void show_video_record()
{

	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		std::cerr << "카메라없습니다" << std::endl;
		return;
	}

	int height = cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	int width = cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	std::cout << height << std::endl;	//높이
	std::cout << width << std::endl;	//폭
	double fps = cap.get(cv::CAP_PROP_FPS);
	int delay = cvRound(1000 / fps);
	cv::Mat frame;
	int fourcc = cv::VideoWriter::fourcc('X', '2', '6', '4');
	cv::VideoWriter output("R_OUTPUT.avi", fourcc, fps, cv::Size(width, height));
	if (!output.isOpened())
	{
		std::cerr << "파일이 문제가 있습니다." << std::endl;
		return;
	}
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			std::cerr << "프레임이 적절하게 만들어지지 못합니다." << std::endl;
			break;
		}

		output << frame;

		cv::imshow("CAMERA", frame);
		if (cv::waitKey(delay) == 27) break;	//27 번키는 ESC key
	}
	cv::destroyAllWindows();
}

void show_draw_lines()
{
	cv::Mat canvas(600, 600, CV_8UC(3), cv::Scalar(255, 255, 255));
	cv::line(canvas, cv::Point(50, 50), cv::Point(200, 50), cv::Scalar(0, 0, 255));
	cv::line(canvas, cv::Point(50, 50), cv::Point(200, 100), cv::Scalar(255, 0, 255), 10);

	cv::arrowedLine(canvas, cv::Point(50, 200), cv::Point(150, 200), cv::Scalar(0, 255, 0), 2);
	cv::drawMarker(canvas, cv::Point(30, 350), cv::Scalar(0, 0, 255), cv::MARKER_DIAMOND);
	cv::drawMarker(canvas, cv::Point(70, 350), cv::Scalar(0, 255, 0), cv::MARKER_CROSS);
	cv::drawMarker(canvas, cv::Point(110, 350), cv::Scalar(255, 0, 0), cv::MARKER_SQUARE);
	cv::drawMarker(canvas, cv::Point(150, 350), cv::Scalar(100, 100, 100), cv::MARKER_STAR);
	cv::drawMarker(canvas, cv::Point(190, 350), cv::Scalar(50, 50, 50), cv::MARKER_TRIANGLE_DOWN);
	cv::drawMarker(canvas, cv::Point(230, 350), cv::Scalar(200, 10, 50), cv::MARKER_TRIANGLE_UP);

	imshow("CANVAS", canvas);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void show_draw_polygons()
{
	cv::Mat canvas(500, 500, CV_8UC(3), cv::Scalar(255, 255, 255));
	cv::rectangle(canvas, cv::Rect(50, 50, 100, 50), cv::Scalar(0, 0, 255), 3);		//Rect(50, 50, 100, 50)  --> x, y, 가로(사각형), 세로(사각형)
	cv::rectangle(canvas, cv::Rect(50, 150, 100, 50), cv::Scalar(0, 0, 100), -1);	//-1은 내부를 채워달라는 의미
	cv::circle(canvas, cv::Point(300, 120), 30, cv::Scalar(255, 255, 0), -1, cv::LINE_AA);	//LINE_Antialiancing --> 원의 표면을 매끈하게 만들어줌
	cv::ellipse(canvas, cv::Point(120, 300), cv::Size(60, 30), 20, 0, 270, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);//cv::Size(60, 30), 20(start angle) --> 0 ~ 270도 까지 그려줌 
	
	std::vector<cv::Point> points;
	points.push_back(cv::Point(250, 250));
	points.push_back(cv::Point(300, 250));
	points.push_back(cv::Point(300, 300));
	points.push_back(cv::Point(350, 300));
	points.push_back(cv::Point(350, 350));
	points.push_back(cv::Point(250, 350));
	points.push_back(cv::Point(250, 350));
	points.push_back(cv::Point(250, 350));
	points.push_back(cv::Point(250, 350));
	cv::polylines(canvas, points, true, cv::Scalar(255, 0, 255), 3);	//true --> 폐곡선 만들어줌
	
	cv::imshow("CANVAS", canvas);
	cv::waitKey(0);
	cv::destroyAllWindows();

}

void show_draw_text()
{
	cv::Mat canvas(500, 500, CV_8UC(3), cv::Scalar(255, 255, 255));

	cv::putText(canvas, "I NEED YOU, However!! I want you, Nevertheless!! i miss you", cv::Point(20, 50), cv::FONT_HERSHEY_TRIPLEX | cv::FONT_ITALIC, 0.4, cv::Scalar(0, 0, 255));

	cv::imshow("canvas", canvas);
	cv::waitKey();
	cv::destroyAllWindows();
}

void show_draw_center()
{
	cv::Mat canvas(200, 640, CV_8UC3, cv::Scalar(255, 255, 255));

	const cv::String text = "Hello World";
	int font_face = cv::FONT_HERSHEY_PLAIN;
	double font_scale = 2.0;
	int thickness = 1;
	cv::Size size_text = cv::getTextSize(text, font_face, font_scale, thickness, 0);
	cv::Size cnavas_size = canvas.size();

	cv::Point center ((cnavas_size.width - size_text.width ) / 2, (cnavas_size.height + size_text.height) / 2 );
	cv::putText(canvas, text, center, font_face, font_scale, cv::Scalar(255, 0, 0), thickness);
	cv::imshow("canvas", canvas);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void keyboard_event()
{
	cv::Mat img = cv::imread("lenna.bmp");
	if (img.empty()) return;
	cv::imshow("lenna", img);
	while (true)
	{
		int key_value = cv::waitKey(0);
		std::cout << key_value << std::endl;
		if (key_value == 'i' or key_value == 'I')
		{
			img = ~img;
			cv::imshow("INV_LENNA", img);
		}
		else
		{
			if (key_value == 27 or key_value == 'q' or key_value == 'Q')
			{
				std::cout << "종료" << std::endl;
				break;
			}
		}
	}
	//cv::waitKey();
	cv::destroyAllWindows();
}

//flag는 일반적으로 프로그램 흐름을 제어하고, 결정을 내리거나, 코드의 여러 부분 간에 정보를 전달하는 데 사용됩니다.
//on_mouse는 외부로 노출되는 것이 아니기에, static으로 숨겨준다.
static cv::Mat img;	//img를 모든 함수에서 접근할수 있게 하기 위해, 전역 공간(static)으로 올림
static cv::Point pt_old;

static void on_mouse(int mouse_event, int mouse_x, int mouse_y, int flag, void*)	//마우스 이벤트 / x,y,z좌표
{
	switch (mouse_event)
	{
	case cv::EVENT_LBUTTONDOWN:
		pt_old = cv::Point(mouse_x, mouse_y);		//클릭 BT down (pt_old) ---> 클릭 BT up
		std::cout << "y : " << mouse_y << "x : " << mouse_x << std::endl;
		break;
	case cv::EVENT_LBUTTONUP:
		std::cout << "EVENT_LBUTTON_UP" << "y : " << mouse_y << "x : " << mouse_x << std::endl;
		break;
	case cv::EVENT_MOUSEMOVE:
		if (flag & cv::EVENT_FLAG_LBUTTON)
		{
			cv::line(img, pt_old, cv::Point(mouse_x, mouse_y), cv::Scalar(0, 255, 255), 2);
			cv::imshow("LENNA", img);
			pt_old = cv::Point(mouse_x, mouse_y);
		}
		break;
	}
}

void mouse_event()
{
	img = cv::imread("lenna.bmp");
	if (img.empty()) return;
	cv::namedWindow("LENNA");
	cv::setMouseCallback("LENNA", on_mouse);
	cv::imshow("LENNA", img);
	cv::waitKey();
	cv::destroyAllWindows;
}

void trackbar_event()
{
	cv::Mat canvas(800, 800, CV_8UC1);
	cv::namedWindow("CANVAS");
	cv::createTrackbar("Level", "CANVAS", 0, 16, on_level_changed, (void*)&canvas);	//16단계로 조절
	cv::imshow("Canvas", canvas);
	cv::waitKey();
	cv::destroyAllWindows();
}

void on_level_changed(int pos, void* user_data)
{
	cv::Mat img = *(static_cast<cv::Mat*>(user_data));
	img.setTo(pos * 16);	//16단계로 조절 가능하게 * 해줌.
	cv::imshow("Canvas", img);
}
//마스크에서 0이 아닌 픽셀로 표시되는 src 이미지 부분에 녹색을 적용합니다.

void mask_setTo()
{
	cv::Mat src = cv::imread("lenna.bmp");
	cv::Mat mask = cv::imread("mask_smile.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty() or mask.empty()) return;
	src.setTo(cv::Scalar(0, 255, 0), mask);
	cv::imshow("LENNA", src);
	cv::imshow("MASK", mask);
	cv::waitKey();
	cv::destroyAllWindows();
}
//"mask_plane.bmp" 이미지를 읽고 회색조 형식으로 변환하면 각 픽셀 값이 원본 이미지의 해당 픽셀 위치에서 회색 강도를 나타내는 단일 채널 이미지가 생성됩니다.
void mask_copyTo()
{
	cv::Mat src = cv::imread("airplane.bmp");
	cv::Mat mask = cv::imread("mask_plane.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat dst = cv::imread("field.bmp");
	cv::imshow("ORIGINAL", dst);
	cv::imshow("SRC", src);
	cv::imshow("MASK", mask);
	if (src.empty() or mask.empty() or dst.empty()) return;
	src.copyTo(dst, mask);
	cv::imshow("CHANGED", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

void time_inverse()
{
	cv::Mat img{cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE)};
	if (img.empty()) return;
	cv::imshow("lenna", img);

	//sum함수와 mean함수
	cv::Scalar total_pixel = cv::sum(img)[0];	//0채널의 총 픽셀값을 알수 있다.
	std::cout << "총 픽셀값은 : " << static_cast<int>(total_pixel[0]) << std::endl;
	cv::Scalar mean_pixel = cv::mean(img)[0];
	std::cout << "평균 픽셀값은 : " << static_cast<int>(mean_pixel[0]) << std::endl;
	
	//minMaxLoc함수 min -- 가장 어두운 위치, max -- 가장 밝은 위치
	double min_value = 0.0;
	double max_value = 0.0;
	cv::Point min_pt;
	cv::Point max_pt;
	cv::minMaxLoc(img, &min_value, &max_value, &min_pt, &max_pt);
	std::cout << "min value : " << min_value << std::endl;
	std::cout << "max vaule : " << max_value << std::endl;
	std::cout << "min Position : " << min_pt << std::endl;
	std::cout << "max Position: " << max_pt << std::endl;

	//시간 측정
	cv::Mat dst{cv::Mat(img.rows, img.cols, img.type())};
	cv::TickMeter tick;
	tick.start();

	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			dst.at<uchar>(i,j) = 255 - img.at<uchar>(i, j);		//비트반전영상
		}
	}

	tick.stop();
	std::cout << "걸린 연산 시간 : " << tick.getAvgTimeMilli() << std::endl;	//복사하는데 걸리는 시간
	cv::imshow("inverse", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}
