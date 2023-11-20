//#pragma once
//#include <opencv2/opencv.hpp>
//#include <vector>

////������Ʈ ���� ����
//void detect_edge_by_mouse()
//{
//	static cv::Rect box;
//	cv::Mat img{(cv::imread("lenna.png"))};
//	if (img.empty()) return;
//	cv::namedWindow("Edge");
//	static bool isFinish{ false };	//checking ��
//	static bool makeDraw{ false };
//	auto click_mouse{ [](int event, int x, int y, int, void*) {// �߿�!!
//		if (event == cv::EVENT_MOUSEMOVE && !isFinish)
//		{
//			box.width = x - box.x;	//���� ����
//			box.height = y - box.y;
//		}
//
//		else if (event == cv::EVENT_LBUTTONDOWN && !isFinish)	//���콺�� Ŭ��������, �ٸ� �Լ��� ȣ�������
//		{
//			makeDraw = true;
//			box = cv::Rect(x, y, 0, 0);
//		}
//
//		else if (event == cv::EVENT_LBUTTONUP && !isFinish)	//up--> �巡���ߴٴ� �ǹ�
//		{
//			makeDraw = false;
//			if (box.width < 0)	//���� ���� ����(�ڽ�)�� ����� Ŭ��, �巡�� �Ǿ�����(����)�� �����(������)���� �ٲ������ 
//			{
//				box.x += box.width;
//				box.width *= -1;
//			}
//			if (box.height < 0)
//			{
//				box.y += box.height;
//				box.height *= -1;	//����� �ٲ�
//			}
//			isFinish = true;	//�ѹ��� �����ϰ� Ż���ϰ� �������
//		}
//	} };
//
//	cv::setMouseCallback("Edge", click_mouse, (void*)&img);	//
//
//	while (!isFinish)	//
//	{
//		cv::Mat temporary{img.clone()};	//������ �̹���
//		if (makeDraw)
//		{
//			cv::rectangle(temporary, box, cv::Scalar(0, 0, 225), 2);
//		}
//		cv::imshow("Edge", temporary);
//		if (cv::waitKey(20) == 27) break;		//0.02�� �ִٰ� ȭ�鿡 ����
//		
//	}
//
//	//ȭ�鿡 �ڽ��� �׷��� �� => R.O.I -> �� ������ŭ edge �׷��ֱ�
//	cv::Mat gray_scale;
//	cv::cvtColor(img, gray_scale, cv::COLOR_BGR2GRAY);
//	cv::Mat patch_area{gray_scale(box)};	//�׷��̽����� �ȿ� �ڽ� ������ matrix�� edge�� �������
//	cv::Canny(patch_area, gray_scale, 30, 30 * 2.5, 3);	
//	cv::imshow("Edge Detection", ~gray_scale);	//-->ȭ���� ��İ� ����(gray_scale) --> �Ͼ�� ������� ~gray_scale
//	cv::waitKey();
//	cv::destroyAllWindows();
//}
//
//
////���� ���� 2
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
////���� ���� 3
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
//				background.at<cv::Vec3b>(i,j) = src.at<cv::Vec3b>(i, j);	//���� ����
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
////���� ���� 4
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
//	std::cout << "�ɸ� �ð� : " << timer.getTimeSec() << "�� �ɸ�" << std::endl;
//
//	cv::imshow("SRC", src);
//	cv::imshow("DST", dst);
//	cv::waitKey();
//	cv::destroyAllWindows();
//}
