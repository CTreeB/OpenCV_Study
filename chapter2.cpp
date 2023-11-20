#include "opencv2/opencv.hpp"  //iostream 포함되어 있음

using namespace cv;
using namespace std;

//void show_code2()
//{
//    cv::Mat image1 {cv::imread("lenna.png", IMREAD_UNCHANGED)};    //Mat- matrix - 2차원 행렬 
//    cv::Mat image2 {cv::imread("dog.png")};     //jpg - raw사진 한장이 매우 큼, 압축 --> BMP 4채널,PNG(무손실 압축) - 원복 축소, 확대시 원본 보존 JPG(손실압축) - 원본 복원 힘듬(손실: 이미지열화)
//    cv::Mat image3;
//
//    if (image1.empty() or image2.empty())
//    {
//        std::cerr << "files are not found" << std::endl;     //cerr: standar error
//        return ;    //void는 return 값을 못가진다.
//    }
//
//    image3 = image1.clone();    //---> 깊은 복사
//    std::cout << "몇 차원 ?" << image1.dims << std::endl;
//
//    std::cout << "colum : " << image1.cols << std::endl;
//    std::cout << "row : " << image1.rows << std::endl;
//    cv::namedWindow("Lenna");
//    cv::namedWindow("dog");
//    cv::imshow("Lenna", image1); //원래는 숫자로 되어있는 자료를 imshow cv라이브러리 함수가 이미지로 변환 시켜줌
//    cv::imshow("dog", image2);
//    cv::namedWindow("Clone");
//    //cv::namedWindow("Clone", image3);
//    cv::waitKey(0);     //특정키를 받을 때까지 창을 닫지말고 기다려라 //waitKey를 사용하지 않으면, 지역영역을 빠져나가서 종료된다.
//}

typedef unsigned int UINT;
//void show_code3()
//{
//    UINT number1{ 10u };
//    Point_<int> point1{(10, 20)};
//    Point point2 = point1;
//    Point point3;
//    point3 = point2;
//}

//void show_code3_1()
//{
//    namedWindow("IMAGE");
//    for (int i = 0; i < 256; ++i)
//    {
//        Mat image(512, 512, CV_8UC3, Scalar(0,i,0));
//        imshow("IMAGE", image);
//        waitKey(5);
//    }
//    waitKey(0);
//}

//void show_code4()
//{
//    for (int i = 0; i < 10; ++i)
//    {
//       std::string str = format("Temp %d", i);  //문자열 정수 함께 출력 가능해짐 format
//       std::cout << str << std::endl;
//    }
//}