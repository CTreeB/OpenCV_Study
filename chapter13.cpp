#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

//���ø� ��Ī
void tmeplate_maching()
{
	cv::Mat image = cv::imread("circuit.bmp", cv::IMREAD_COLOR);
	cv::Mat patch_image = cv::imread("crystal.bmp", cv::IMREAD_COLOR);

	if (image.empty() or patch_image.empty()) return;
	cv::Mat resource;
	cv::matchTemplate(image, patch_image, resource, cv::TM_CCOEFF_NORMED);	//-1 ~ 1 ���� ����
	cv::Mat resource_norm;
	cv::normalize(resource, resource_norm, 0.0, 255.0, cv::NORM_MINMAX, CV_8UC1);
	double max_value{ 0.0 };
	cv::Point max_location;
	cv::minMaxLoc(resource, nullptr, static_cast<double*>(&max_value), nullptr, static_cast<cv::Point*>(&max_location));
	//-->matchTmeplate �Լ� ������ ���� minMaxLoc �Լ����� max���� ã�Ƽ� �����ͷ� �����
	std::cout << "Max value : " << max_value << std::endl;
	cv::rectangle(image, cv::Rect(max_location.x, max_location.y, patch_image.cols, patch_image.rows), cv::Scalar(0, 0, 255), 2);

	cv::imshow("IMAGE", image);
	cv::imshow("patch", patch_image);
	cv::imshow("RESOLUTION", resource_norm);
	cv::waitKey();
	cv::destroyAllWindows();

}

//�� �ν�
void detect_face()
{
	cv::Mat src = cv::imread("lenna.png");
	if (src.empty()) return;
	cv::CascadeClassifier classifier("haarcascade_frontalface_default.xml");
	cv::CascadeClassifier eye_classifier("haarcascade_eye.xml");
	if (classifier.empty())
	{
		std::cout << "Haar ���� ������� �����" << std::endl;		//���� ���� �� --> ���
		return;
	}
	std::vector<cv::Rect> faces;	//���̽��� ã�� ��ǥ�� ���Ϳ� ����
	classifier.detectMultiScale(src, faces);
	for (auto&& face : faces)	//��ǥ���� ȭ�鿡 �ϳ��� �����ͼ� �����
	{
		cv::rectangle(src, face, cv::Scalar(255, 0, 255), 2);

		cv::Mat faceROI = src(face);
		std::vector<cv::Rect> eyes;
		eye_classifier.detectMultiScale(faceROI, eyes);

		for (auto&& eye : eyes)
		{
			cv::Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			cv::circle(faceROI, center, eye.width / 2, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
		}

	}
	cv::imshow("SRC", src);
	cv::waitKey();
	cv::destroyAllWindows();

}

//KNN �˰��� �ʱ�ü ���� �н�
