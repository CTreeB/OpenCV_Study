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

	mat4.create(256, 256, CV_8UC3);		//기존에 있는 걸 만들어서 사용할 수 있다.

	cv::imshow("MATRIX", mat4);
	cv::waitKey(5000);
}

//#1. 'CV_8UC1'
//CV: "컴퓨터 비전"을 의미합니다.
//8 : 각 픽셀 값을 나타내는 데 사용되는 비트 수를 나타냅니다.
//U : "unsigned"를 의미하며 픽셀 값이 음수가 아닌 정수임을 의미합니다.
//C1 : "single-channel"의 약자로 이미지에 픽셀 데이터(회색조)의 단일(1) 채널이 있음을 나타냅니다.
//'CV_8UC1'은 8비트 부호 없는 정수 픽셀 값을 갖는 이미지 형식을 설명하며 단일 채널을 가지므로 그레이 스케일 이미지입니다
//이미지 데이터는 각 픽셀 위치에서 회색의 강도를 나타내는 단일 채널에서 0(검은색)에서 255(흰색) 범위의 음이 아닌 정수 값으로 구성됩니다.

//#2. cv::Scalar(128, 128, 128): 이미지의 초기 픽셀 값을 설정합니다.
//cv::Scalar 개체 (128, 128, 128)는 중간 회색에 해당하는 색상(파란색=128, 녹색=128, 빨간색=128)을 나타냅니다. 
//이는 전체 이미지가 중간 회색으로 초기화됨을 의미합니다.

void show_code3_8()
{
	cv::Mat img1 {cv::imread("lenna.png")};
	cv::Mat img2 = img1;			//shallow copy, 이미지의 주소를 공유
	
	cv::Mat img3 = img1.clone();	//clone을 쓰면 완전복사 => 깊은 복사(deep copy)
									//clone을 사용하지 않으면(얕은 복사) ---> img1을 수정하면 img2도 영향을 받는다.(포인터가 같은 곳을 가리키기 때문이다.)

	cv::namedWindow("IMAGE1");		//얕은 복사
	cv::namedWindow("IMAGE2");		//얕은 복사
	cv::namedWindow("IMAGE3");		//깊은 복사
	cv::namedWindow("IMAGE4");
	
	cv::imshow("IMAGE1", img1);
	cv::imshow("IMAGE2", img2);
	cv::imshow("IMAGE3", img3);
	img1 = ~img1;				//비트 반전
	

	cv::imshow("IMAGE4", img1);		//얕은 복사된 파일에는 비트 반전 적용
	cv::imshow("IMAGE5", img2);		//얕은 복사된 파일에는 비트 반전 적용
	cv::imshow("IMAGE6", img3);		//깊은 복사된 파일에는 비트 반전 적용 안됨
	
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
	cv::Mat mat1 = cv::Mat::zeros(10, 10, CV_8UC(1));	//CV_8UC(1)-->> 1채널// CV_8UC(2)--->>2채널// CV_8UC(3)--->>3채널

	std::cout << mat1 << std::endl;
	uchar value = 0;
	for (int i = 0; i < mat1.rows; ++i)
	{
		for (int j = 0; j < mat1.rows; ++j)
		{
			++value;	//출력된 값을 증가시켜주세요
			mat1.at<uchar>(i, j) = value;
		}
	}
	std::cout << "==============================================" << std::endl;
	for (int i = 0; i < mat1.rows; ++i)
	{
		uchar* p = mat1.ptr(i);					//포인터에 row의 대표주소를 넘겨서, *p로 column에 접근한다.		//CV_8UC()가 uchar이다.
		for (int j = 0; j < mat1.cols; ++j)
		{
			std::cout << static_cast<int>(p[j])/*아스키 코드값을 int형으로 바꿔줌*/ << std::endl;
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
	std::cout << "이미지 폭 : " << img1.cols << std::endl;
	std::cout << "이미지 높이 : " << img1.rows << std::endl;
	std::cout << "이미지 사이즈 : " << img1.size << std::endl;
	std::cout << "픽셀의 한개의 사이즈 : " << img1.elemSize1() << std::endl;
	std::cout << "채널 : " << img1.channels() << std::endl;		//RGB 파일이라서 3채널 --> cv::IMREAD_GRAYSCALE 1채널
	if (img1.type() == CV_8UC1) std::cout << "GrayScale !! " << std::endl;
	else if (img1.type() == CV_8UC3) std::cout << "Color !! " << std::endl;
	else std::cout << "PNG 4 채널" << std::endl;
}

void show_code3_12()
{
	float data[] = { 1.0f, 2.0f, 3.0f, 4.0f};
	cv::Mat mat1(2, 2, CV_32FC1, data);
	std::cout << mat1 << std::endl;
	cv::Mat mat2 = mat1.inv();		//역함수, 역함수 있으면 해가 있음, 없으면, 근사값을 구해야함
	std::cout << mat2 << std::endl;
	cv::Mat mat3 = mat1 * mat2;
	std::cout << mat3 << std::endl;

	cv::Mat mat4 = cv::Mat::eye(512, 512, CV_8UC1) * 255;	//역행렬 대각행렬
	
	cv::Mat mat5 = mat1.t();	//transpose --> row and column position swithing
	std::cout << mat5 << std::endl;

	cv::Mat img = cv::imread("lenna.png");
	cv::Mat img2 = img.t() + 100;	//transpose --> picture's position row & column swithing
	cv::imshow("EYE", mat4);
	cv::imshow("lenna", img2);
	cv::waitKey(0);
	cv::destroyAllWindows();
}