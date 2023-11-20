
#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

static cv::Ptr<cv::ml::KNearest> train_knn()
{
	cv::Mat digits(cv::imread("digits.png", cv::IMREAD_GRAYSCALE));	//����ȭ �Ϸ�Ǿ��ִ� png����
	if (digits.empty()) return nullptr;
	//smart pointer C++11 ��ǥ --> �ڵ������� heap ���� ����� --> delete �ʿ� ����
	cv::Mat train_image;
	cv::Mat train_labels;	//label == ���� �̹��� 
	for (int i = 0; i < 50; ++i)	//100 * 50 = 5000 tables
	{
		for (int j = 0; j < 100; ++j)
		{
			cv::Mat roi = digits(cv::Rect(j * 20, i * 20, 20, 20));
			cv::Mat roi_float;
			roi.convertTo(roi_float, CV_32FC1);	//open cv ������ Ÿ������ ��ȯ
			//roi_float.reshape(1, 1);	// 1���� ���·� ����� ��� �Ѵ�.(��źȭ)
			cv::Mat roi_flatten = roi_float.reshape(1, 1);
			train_image.push_back(roi_flatten);
			train_labels.push_back(i / 5);	// 5��°���� ���� �̹����� �ְڴ�.
		}
	}
	cv::Ptr<cv::ml::KNearest>knn = cv::ml::KNearest::create();	//�ַ̱�--> knn�� ��ü�� ����
	knn->train(train_image, cv::ml::ROW_SAMPLE, train_labels);	//�Ʒ��� �� knn��ü (train_labels == ����ǥ)
	return knn;	//�Ʒõ� ��ü ��ȯ
}

static cv::Point point_Prev(-1, -1); //Ŭ�� ���콺�� �������ϸ�, ��ǥ�� -1, -1 �ʱ�ȭ

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
	cv::Ptr<cv::ml::KNearest> knn(train_knn());	//knn == �Ʒõ� ��ü
	if (knn.empty())
	{
		std::cout << "Train ����" << std::endl;
		return;
	}
	std::cout << "�н� ����" << std::endl;
	cv::Mat input_display(400, 400, CV_8UC1);	//400 x 400
	cv::namedWindow("DISPLAY", cv::WINDOW_NORMAL);
	//cv::imshow("DISPLAY", input_display);
	cv::setMouseCallback("DISPLAY", on_mouse, static_cast<void*>(&input_display));
	while (true)
	{
		//ESC --> break;
		//SPACEBAR ������ �� mouse �Է� ���·� ��������
		int keyboard_key = cv::waitKey();
		if (keyboard_key == 27) break;	//ESC �϶� ����
		else if (keyboard_key == ' ')	//�����̽�
		{
			cv::Mat image_resize;	//����ڰ� ȭ������ ���� ���� �Է� �ȼ����� �𵨿� �°� 20 x 20 �ȼ��� �ٲ��࿩�Ѵ�
			cv::Mat image_float;
			cv::Mat image_flatten;	//����ڷ� ���� ���� �̹����� flatten�ؼ� �н��� �𵨿��� �Է°����� �ֱ� ���ؼ� flatten
			cv::Mat resource;	//�н��� ��� ����

			cv::resize(input_display, image_resize, cv::Size(20, 20), 0, 0, cv::INTER_AREA);
			image_resize.convertTo(image_float, CV_32FC1);
			image_flatten = image_float.reshape(1, 1); // 1 x 400 ��źȭ

			knn->findNearest(image_flatten, 5, resource); // k = 3, 5, 7, 9

			std::cout << cvRound(resource.at<float>(0, 0));	//�ε��� 0��° 0 �� Ȯ��
			input_display.setTo(0);	//ȭ���� �˰� �ʱ�ȭ
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
