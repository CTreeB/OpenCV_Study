#include "opencv2/opencv.hpp"  //iostream ���ԵǾ� ����

using namespace cv;
using namespace std;

//void show_code2()
//{
//    cv::Mat image1 {cv::imread("lenna.png", IMREAD_UNCHANGED)};    //Mat- matrix - 2���� ��� 
//    cv::Mat image2 {cv::imread("dog.png")};     //jpg - raw���� ������ �ſ� ŭ, ���� --> BMP 4ä��,PNG(���ս� ����) - ���� ���, Ȯ��� ���� ���� JPG(�սǾ���) - ���� ���� ����(�ս�: �̹�����ȭ)
//    cv::Mat image3;
//
//    if (image1.empty() or image2.empty())
//    {
//        std::cerr << "files are not found" << std::endl;     //cerr: standar error
//        return ;    //void�� return ���� ��������.
//    }
//
//    image3 = image1.clone();    //---> ���� ����
//    std::cout << "�� ���� ?" << image1.dims << std::endl;
//
//    std::cout << "colum : " << image1.cols << std::endl;
//    std::cout << "row : " << image1.rows << std::endl;
//    cv::namedWindow("Lenna");
//    cv::namedWindow("dog");
//    cv::imshow("Lenna", image1); //������ ���ڷ� �Ǿ��ִ� �ڷḦ imshow cv���̺귯�� �Լ��� �̹����� ��ȯ ������
//    cv::imshow("dog", image2);
//    cv::namedWindow("Clone");
//    //cv::namedWindow("Clone", image3);
//    cv::waitKey(0);     //Ư��Ű�� ���� ������ â�� �������� ��ٷ��� //waitKey�� ������� ������, ���������� ���������� ����ȴ�.
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
//       std::string str = format("Temp %d", i);  //���ڿ� ���� �Բ� ��� �������� format
//       std::cout << str << std::endl;
//    }
//}