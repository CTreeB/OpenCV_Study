
#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

static cv::Ptr<cv::ml::KNearest> train_knn()
{
	cv::Mat digits(cv::imread("digits.png", cv::IMREAD_GRAYSCALE));	//이진화 완료되어있는 png파일
	if (digits.empty()) return nullptr;
	//smart pointer C++11 발표 --> 자동적으로 heap 에서 사라짐 --> delete 필요 없음
	cv::Mat train_image;
	cv::Mat train_labels;	//label == 정답 이미지 
	for (int i = 0; i < 50; ++i)	//100 * 50 = 5000 tables
	{
		for (int j = 0; j < 100; ++j)
		{
			cv::Mat roi = digits(cv::Rect(j * 20, i * 20, 20, 20));
			cv::Mat roi_float;
			roi.convertTo(roi_float, CV_32FC1);	//open cv 데이터 타입으로 변환
			//roi_float.reshape(1, 1);	// 1차원 형태로 만들어 줘야 한다.(평탄화)
			cv::Mat roi_flatten = roi_float.reshape(1, 1);
			train_image.push_back(roi_flatten);
			train_labels.push_back(i / 5);	// 5번째마다 정답 이미지를 넣겠다.
		}
	}
	cv::Ptr<cv::ml::KNearest>knn = cv::ml::KNearest::create();	//싱귤러--> knn의 객체를 만듬
	knn->train(train_image, cv::ml::ROW_SAMPLE, train_labels);	//훈련이 된 knn객체 (train_labels == 정답표)
	return knn;	//훈련된 객체 반환
}

static cv::Point point_Prev(-1, -1); //클릭 마우스를 릴리즈하면, 좌표를 -1, -1 초기화

static void on_mouse(int event, int x, int y, int flag, void* userdata)
{
	cv::Mat image = *(static_cast<cv::Mat*>(userdata));
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		point_Prev = cv::Point(x, y);

	}
	else if (event == cv::EVENT_LBUTTONUP)
	{
		point_Prev = cv::Point(-1, -1);
	}
	else if (event == cv::EVENT_MOUSEMOVE && (flag & cv::EVENT_FLAG_LBUTTON))
	{
		cv::line(image, point_Prev, cv::Point(x, y), cv::Scalar(255, 255, 255), 40, cv::LINE_AA, 0);
		point_Prev = cv::Point(x, y);
		cv::imshow("IMAGE", image);
	}
}


void do_knn_machine_learning()
{
	cv::Ptr<cv::ml::KNearest> knn(train_knn());	//knn == 훈련된 객체
	if (knn.empty())
	{
		std::cout << "Train 실패" << std::endl;
		return;
	}
	std::cout << "학습 성공" << std::endl;
	cv::Mat input_display(400, 400, CV_8UC1);	//400 x 400
	cv::namedWindow("DISPLAY", cv::WINDOW_NORMAL);
	//cv::imshow("DISPLAY", input_display);
	cv::setMouseCallback("DISPLAY", on_mouse, static_cast<void*>(&input_display));
	while (true)
	{
		//ESC --> break;
		//SPACEBAR 눌렀을 떄 mouse 입력 상태로 만ㄷ르기
		int keyboard_key = cv::waitKey();
		if (keyboard_key == 27) break;	//ESC 일때 종료
		else if (keyboard_key == ' ')	//스페이스
		{
			cv::Mat image_resize;	//사용자가 화면으로 부터 받은 입력 픽셀값을 모델에 맞게 20 x 20 픽셀로 바꿔줘여한다
			cv::Mat image_float;
			cv::Mat image_flatten;	//사용자로 부터 받은 이미지를 flatten해서 학습된 모델에게 입력값으로 주기 위해서 flatten
			cv::Mat resource;	//학습된 결과 저장

			cv::resize(input_display, image_resize, cv::Size(20, 20), 0, 0, cv::INTER_AREA);
			image_resize.convertTo(image_float, CV_32FC1);
			image_flatten = image_float.reshape(1, 1); // 1 x 400 평탄화

			knn->findNearest(image_flatten, 5, resource); // k = 3, 5, 7, 9

			std::cout << cvRound(resource.at<float>(0, 0));	//인덱스 0번째 0 에 확인
			input_display.setTo(0);	//화면을 검게 초기화
			cv::imshow("DISPLAY", input_display);
		}
	}
	cv::destroyAllWindows();
	//cv::waitKey();
	//cv::destroyAllWindows();
}
////////////////////////////////////////////////////////////////////////////
//##########################################################################
////////////////////////////////////////////////////////////////////////////


//
//static cv::Ptr<cv::ml::KNearest> train_knn()
//{
//    cv::Mat digits = cv::imread("digits.png", cv::IMREAD_GRAYSCALE);
//    if (digits.empty()) return nullptr;
//
//    cv::Mat train_image;
//    cv::Mat train_labels;
//
//    for (int i = 0; i < 50; ++i)
//    {
//        for (int j = 0; j < 100; ++j)
//        {
//            cv::Mat roi = digits(cv::Rect(j * 20, i * 20, 20, 20));
//            cv::Mat roi_float;
//            roi.convertTo(roi_float, CV_32FC1);
//            cv::Mat roi_flatten = roi_float.reshape(1, 1);
//            train_image.push_back(roi_flatten); // Push the flattened image
//            train_labels.push_back(i / 5);
//        }
//    }
//
//    cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
//    knn->train(train_image, cv::ml::ROW_SAMPLE, train_labels);
//    return knn;
//}
//
//static cv::Point point_Prev(-1, -1);
//
//static void on_mouse(int event, int x, int y, int flags, void* userdata)
//{
//    cv::Mat image = *(static_cast<cv::Mat*>(userdata));
//
//    if (event == cv::EVENT_LBUTTONDOWN)
//    {
//        point_Prev = cv::Point(x, y);
//    }
//    else if (event == cv::EVENT_LBUTTONUP)
//    {
//        point_Prev = cv::Point(-1, -1);
//    }
//    else if (event == cv::EVENT_MOUSEMOVE && (flags & cv::EVENT_FLAG_LBUTTON))
//    {
//        //if (point_Prev.x == -1 || point_Prev.y == -1) return;
//        cv::line(image, point_Prev, cv::Point(x, y), cv::Scalar(255, 255, 255), 30, cv::LINE_AA, 0);
//        point_Prev = cv::Point(x, y);
//        cv::imshow("DISPLAY", image);
//    }
//}
//
//void do_knn_machine_learning()
//{
//    cv::Ptr<cv::ml::KNearest> knn = train_knn();
//
//    if (knn.empty())
//    {
//        std::cout << "Train failed" << std::endl;
//        return;
//    }
//
//    std::cout << "Training success" << std::endl;
//
//    cv::Mat input_display(400, 400, CV_8UC1);
//    cv::namedWindow("DISPLAY", cv::WINDOW_NORMAL);
//    cv::imshow("DISPLAY", input_display);
//    cv::setMouseCallback("DISPLAY", on_mouse, static_cast<void*>(&input_display));
//
//    while (true)
//    {
//        int keyboard_key = cv::waitKey();
//
//        if (keyboard_key == 27) break; // End when ESC
//
//        else if (keyboard_key == ' ') // Space
//        {
//            cv::Mat image_resize;
//            cv::Mat image_float;
//            cv::Mat image_flatten;
//            cv::Mat resource;
//
//            cv::resize(input_display, image_resize, cv::Size(20, 20), 0, 0, cv::INTER_AREA);
//            image_resize.convertTo(image_float, CV_32FC1);
//            image_flatten = image_float.reshape(1, 1);
//
//            knn->findNearest(image_flatten, 3, resource);
//
//            int predicted_label = static_cast<int>(resource.at<float>(0, 0));
//            std::cout << "Predicted Label: " << predicted_label << std::endl;
//
//            input_display.setTo(0);
//            cv::imshow("DISPLAY", input_display);
//        }
//    }
//
//    cv::destroyAllWindows();
//}
