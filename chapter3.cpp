#pragma once
#include "opencv2/opencv.hpp"//087p
#include <math.h>


void show_code3_7()
{
	cv::Mat img1;
	cv::Mat img2(480, 640, CV_8UC1);
	cv::Mat img3(480, 640, CV_8UC3);
	cv::Mat img4(cv::Size(480, 640), CV_8UC3);
	cv::Mat img5(480, 640, CV_8UC1, cv::Scalar(128));
	cv::Mat img6(480, 640, CV_8UC3, cv::Scalar(128, 128, 128));

	cv::Mat mat1{ cv::Mat::zeros(480, 640, CV_8UC1) };
	cv::Mat mat2{ cv::Mat::ones(480, 640, CV_8UC1) };
	cv::Mat mat3{ cv::Mat::eye(640, 640, CV_8UC1 * 255) };

	float data[] = { 1, 2, 3, 4, 5, 6 };
	cv::Mat mat4(2, 3, CV_32SC1, data);

	cv::Mat mat5 = (cv::Mat_<float>(2, 3)) << (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

	mat4.create(256, 256, CV_8UC3);		//������ �ִ� �� ���� ����� �� �ִ�.

	cv::imshow("MATRIX", mat4);
	cv::waitKey(5000);
}

//#1. 'CV_8UC1'
//CV: "��ǻ�� ����"�� �ǹ��մϴ�.
//8 : �� �ȼ� ���� ��Ÿ���� �� ���Ǵ� ��Ʈ ���� ��Ÿ���ϴ�.
//U : "unsigned"�� �ǹ��ϸ� �ȼ� ���� ������ �ƴ� �������� �ǹ��մϴ�.
//C1 : "single-channel"�� ���ڷ� �̹����� �ȼ� ������(ȸ����)�� ����(1) ä���� ������ ��Ÿ���ϴ�.
//'CV_8UC1'�� 8��Ʈ ��ȣ ���� ���� �ȼ� ���� ���� �̹��� ������ �����ϸ� ���� ä���� �����Ƿ� �׷��� ������ �̹����Դϴ�
//�̹��� �����ʹ� �� �ȼ� ��ġ���� ȸ���� ������ ��Ÿ���� ���� ä�ο��� 0(������)���� 255(���) ������ ���� �ƴ� ���� ������ �����˴ϴ�.

//#2. cv::Scalar(128, 128, 128): �̹����� �ʱ� �ȼ� ���� �����մϴ�.
//cv::Scalar ��ü (128, 128, 128)�� �߰� ȸ���� �ش��ϴ� ����(�Ķ���=128, ���=128, ������=128)�� ��Ÿ���ϴ�. 
//�̴� ��ü �̹����� �߰� ȸ������ �ʱ�ȭ���� �ǹ��մϴ�.

void show_code3_8()
{
	cv::Mat img1 {cv::imread("lenna.png")};
	cv::Mat img2 = img1;			//shallow copy, �̹����� �ּҸ� ����
	
	cv::Mat img3 = img1.clone();	//clone�� ���� �������� => ���� ����(deep copy)
									//clone�� ������� ������(���� ����) ---> img1�� �����ϸ� img2�� ������ �޴´�.(�����Ͱ� ���� ���� ����Ű�� �����̴�.)

	cv::namedWindow("IMAGE1");		//���� ����
	cv::namedWindow("IMAGE2");		//���� ����
	cv::namedWindow("IMAGE3");		//���� ����
	cv::namedWindow("IMAGE4");
	
	cv::imshow("IMAGE1", img1);
	cv::imshow("IMAGE2", img2);
	cv::imshow("IMAGE3", img3);
	img1 = ~img1;				//��Ʈ ����
	

	cv::imshow("IMAGE4", img1);		//���� ����� ���Ͽ��� ��Ʈ ���� ����
	cv::imshow("IMAGE5", img2);		//���� ����� ���Ͽ��� ��Ʈ ���� ����
	cv::imshow("IMAGE6", img3);		//���� ����� ���Ͽ��� ��Ʈ ���� ���� �ȵ�
	
	cv::waitKey(0);
}

void show_code3_9()
{
	cv::Mat img1 = cv::imread("cat.bmp");
	if (img1.empty())
	{
		std::cout << "File not found" << std::endl;
		return;
	}
	std::cout << img1.size() << std::endl;

	cv::Mat img2 = img1(cv::Rect(220, 120, 340, 240));
	cv::imshow("IMAGE1", img1);
	cv::imshow("IMAGE2", img2);
	cv::imshow("IMAGE3", ~img2);

	cv::Mat img3 = img1(cv::Rect(220, 120, 340, 240)).clone();
	cv::imshow("IMAGE4", img3);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void show_code3_10()
{
	cv::Mat mat1 = cv::Mat::zeros(10, 10, CV_8UC(1));	//CV_8UC(1)-->> 1ä��// CV_8UC(2)--->>2ä��// CV_8UC(3)--->>3ä��

	std::cout << mat1 << std::endl;
	uchar value = 0;
	for (int i = 0; i < mat1.rows; ++i)
	{
		for (int j = 0; j < mat1.rows; ++j)
		{
			++value;	//��µ� ���� ���������ּ���
			mat1.at<uchar>(i, j) = value;
		}
	}
	std::cout << "==============================================" << std::endl;
	for (int i = 0; i < mat1.rows; ++i)
	{
		uchar* p = mat1.ptr(i);					//�����Ϳ� row�� ��ǥ�ּҸ� �Ѱܼ�, *p�� column�� �����Ѵ�.		//CV_8UC()�� uchar�̴�.
		for (int j = 0; j < mat1.cols; ++j)
		{
			std::cout << static_cast<int>(p[j])/*�ƽ�Ű �ڵ尪�� int������ �ٲ���*/ << std::endl;
		}
	}
	/*std::cout << mat1 << std::endl;

	cv::imshow("MAT1", mat1);
	cv::waitKey(0);*/
}

void show_code3_11()
{
	cv::Mat img1 = cv::imread("coins.png", cv::IMREAD_UNCHANGED);
	if (img1.empty()) return;
	std::cout << "�̹��� �� : " << img1.cols << std::endl;
	std::cout << "�̹��� ���� : " << img1.rows << std::endl;
	std::cout << "�̹��� ������ : " << img1.size << std::endl;
	std::cout << "�ȼ��� �Ѱ��� ������ : " << img1.elemSize1() << std::endl;
	std::cout << "ä�� : " << img1.channels() << std::endl;		//RGB �����̶� 3ä�� --> cv::IMREAD_GRAYSCALE 1ä��
	if (img1.type() == CV_8UC1) std::cout << "GrayScale !! " << std::endl;
	else if (img1.type() == CV_8UC3) std::cout << "Color !! " << std::endl;
	else std::cout << "PNG 4 ä��" << std::endl;
}

void show_code3_12()
{
	float data[] = { 1.0f, 2.0f, 3.0f, 4.0f};
	cv::Mat mat1(2, 2, CV_32FC1, data);
	std::cout << mat1 << std::endl;
	cv::Mat mat2 = mat1.inv();		//���Լ�, ���Լ� ������ �ذ� ����, ������, �ٻ簪�� ���ؾ���
	std::cout << mat2 << std::endl;
	cv::Mat mat3 = mat1 * mat2;
	std::cout << mat3 << std::endl;

	cv::Mat mat4 = cv::Mat::eye(512, 512, CV_8UC1) * 255;	//����� �밢���
	
	cv::Mat mat5 = mat1.t();	//transpose --> row and column position swithing
	std::cout << mat5 << std::endl;

	cv::Mat img = cv::imread("lenna.png");
	cv::Mat img2 = img.t() + 100;	//transpose --> picture's position row & column swithing
	cv::imshow("EYE", mat4);
	cv::imshow("lenna", img2);
	cv::waitKey(0);
	cv::destroyAllWindows();
}