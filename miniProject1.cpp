//#pragma once
//#include <opencv2/opencv.hpp>
//#include <vector>

////프로젝트 참고 예제
//void detect_edge_by_mouse()
//{
//	static cv::Rect box;
//	cv::Mat img{(cv::imread("lenna.png"))};
//	if (img.empty()) return;
//	cv::namedWindow("Edge");
//	static bool isFinish{ false };	//checking 용
//	static bool makeDraw{ false };
//	auto click_mouse{ [](int event, int x, int y, int, void*) {// 중요!!
//		if (event == cv::EVENT_MOUSEMOVE && !isFinish)
//		{
//			box.width = x - box.x;	//시험 내용
//			box.height = y - box.y;
//		}
//
//		else if (event == cv::EVENT_LBUTTONDOWN && !isFinish)	//마우스를 클릭했을떄, 다른 함수를 호출시켜줌
//		{
//			makeDraw = true;
//			box = cv::Rect(x, y, 0, 0);
//		}
//
//		else if (event == cv::EVENT_LBUTTONUP && !isFinish)	//up--> 드래그했다는 의미
//		{
//			makeDraw = false;
//			if (box.width < 0)	//내가 만든 범위(박스)를 벗어나서 클릭, 드래그 되었을때(음수)를 양수값(범위값)으로 바꿔줘야함 
//			{
//				box.x += box.width;
//				box.width *= -1;
//			}
//			if (box.height < 0)
//			{
//				box.y += box.height;
//				box.height *= -1;	//양수로 바꿈
//			}
//			isFinish = true;	//한번만 실행하고 탈출하게 만들어줌
//		}
//	} };
//
//	cv::setMouseCallback("Edge", click_mouse, (void*)&img);	//
//
//	while (!isFinish)	//
//	{
//		cv::Mat temporary{img.clone()};	//복사한 이미지
//		if (makeDraw)
//		{
//			cv::rectangle(temporary, box, cv::Scalar(0, 0, 225), 2);
//		}
//		cv::imshow("Edge", temporary);
//		if (cv::waitKey(20) == 27) break;		//0.02초 있다가 화면에 나옴
//		
//	}
//
//	//화면에 박스를 그려준 후 => R.O.I -> 그 영역만큼 edge 그려주기
//	cv::Mat gray_scale;
//	cv::cvtColor(img, gray_scale, cv::COLOR_BGR2GRAY);
//	cv::Mat patch_area{gray_scale(box)};	//그레이스케일 안에 박스 사이즈 matrix의 edge를 만들어줌
//	cv::Canny(patch_area, gray_scale, 30, 30 * 2.5, 3);	
//	cv::imshow("Edge Detection", ~gray_scale);	//-->화면이 까맣게 나옴(gray_scale) --> 하얗게 만들어줌 ~gray_scale
//	cv::waitKey();
//	cv::destroyAllWindows();
//}
//
//
////시험 예제 2
//void solve_problem2()
//{
//	cv::Mat image = cv::imread("lenna.png", cv::IMREAD_COLOR);
//	if (image.empty()) return;
//	for (int i = 0; i < image.rows; ++i) {
//
//		for (int j = 0; j < image.cols; ++j)
//		{
//			cv::Vec3b& p = image.at<cv::Vec3b>(i, j);
//			p[0] = cv::saturate_cast<uchar>(120 + p[0]);
//			p[1] = cv::saturate_cast<uchar>(120 + p[1]);
//			p[2] = cv::saturate_cast<uchar>(120 + p[2]);
//		}
//	}
//	cv::imshow("IMAGE", image);
//	cv::waitKey(0);
//	cv::destroyAllWindows();
//}
//
//
////시험 예제 3
//void solve_problem3()
//{
//	const cv::Mat src {cv::imread("lenna.bmp", cv::IMREAD_COLOR)};
//	if (src.empty()) return;
//	cv::Mat background(src.size(), src.type());
//	const int32_t WIDTH { 400U };
//	const int32_t HEIGHT{ 400U };	//400 x 400
//	const int32_t START_X{ cvRound((src.rows - WIDTH) / 2) };
//	const int32_t START_Y{ cvRound((src.cols - HEIGHT) / 2) };
//	const int32_t END_X{ cvRound(START_X + WIDTH) };
//	const int32_t END_Y{ cvRound(START_Y + HEIGHT) };
//
//	for (int i = 0; i < src.rows; ++i)
//	{
//		for (int j = 0; j < src.cols; ++j)
//		{
//			if ((START_X <= j and j < END_X) and (START_Y <= i and i < END_Y))
//			{
//				background.at<cv::Vec3b>(i,j) = src.at<cv::Vec3b>(i, j);	//색상 복사
//			}
//			else
//			{
//				background.at<cv::Vec3b>(i, j) = cv::Vec3b(100, 150, 0);
//			}
//		}
//	}
//
//	cv::imshow("SRC", src);
//	cv::imshow("BG", background);
//	cv::waitKey();
//	cv::destroyAllWindows();
//}
//
//
////시험 예제 4
//void solve_problem4()
//{
//	const cv::Mat src{cv::imread("lenna.bmp", cv::IMREAD_COLOR)};
//	if (src.empty()) return;
//	cv::Mat dst(src.size(), src.type());
//
//	cv::TickMeter timer;
//	timer.start();
//
//	for (int i = 0; i < src.rows; ++i)
//	{
//		for (int j = 0; j < src.cols; ++j)
//		{
//			cv::Vec3b& p_src = const_cast<cv::Vec3b&>(src.at<cv::Vec3b>(i, j));
//			cv::Vec3b& p_dst = dst.at<cv::Vec3b>(i, j);
//			p_dst = p_src;
//		}
//	}
//
//	timer.stop();
//	std::cout << "걸린 시간 : " << timer.getTimeSec() << "초 걸림" << std::endl;
//
//	cv::imshow("SRC", src);
//	cv::imshow("DST", dst);
//	cv::waitKey();
//	cv::destroyAllWindows();
//}
