#pragma once
#include <opencv2/opencv.hpp>
static void on_brightness_chaged(int, void*);

void example()
{
	cv::Mat img = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat img2 = cv::imread("lenna.bmp", cv::IMREAD_COLOR);
	cv::Mat img3;
	cv::cvtColor(img2, img3, cv::COLOR_BGR2GRAY);		//grayscale�� color�� �ٲپ���� �� ���

	cv::imshow("IMG", img);
	cv::imshow("IMG2", img2);
	cv::imshow("IMG3", img3);

	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			uchar temp1 = img.at<uchar>(i, j);
			int temp2 = temp1 - 50;
			if (temp2 <= 0) temp2 = 0;
			img.at<uchar>(i, j) = static_cast<uchar>(temp2);
		}
	}

	cv::imshow("changed", img);
	cv::Mat img4;
	cv::waitKey();
	cv::destroyAllWindows();
}

void brightness()
{
	cv::Mat src = cv::imread("dog.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat dst(src.rows, src.cols, src.type());
	//cv::Mat dst(512, 512, CV_8UC1);

	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			dst.at<uchar>(i, j) = cv::saturate_cast<uchar>(src.at<uchar>(i, j) - 100);	//cv::saturate_cast : 0~255���� �����ɼ� �ֵ��� �������
		}
	}

	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

void brightness2()
{
	cv::Mat src = cv::imread("cat.bmp", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("CAT");
	cv::createTrackbar("CAT_BRIGHT", "CAT", 0, 100, on_brightness_chaged, &src);
	cv::imshow("CAT", src);
	cv::waitKey();
	cv::destroyAllWindows();
}

void on_brightness_chaged(int position, void* userdata)
{
	cv::Mat src = *(static_cast<cv::Mat*>(userdata));
	cv::Mat dst = src + position;
	cv::imshow("CAT", dst);	//src�� Ʈ���ٸ� ���� ����
}

void brightness3()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;

	float alpha = 1.0f;
	cv::Mat dst = (1 + alpha) * src - 128 * alpha;	//��Ϻ� �޻��	-	
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

//void show_hit()	//������׷� ���ϱ�
//{
//	cv::Mat src = cv::imread("hawks.bmp", cv::IMREAD_GRAYSCALE);
//	
//	//���� �Լ�
//	auto calcGrayHist = [](const cv::Mat& img) {
//		cv::Mat hist;
//		int channels[] = { 0 };
//		int dims = 1;
//		int histSize[] = { 256 };
//		float graylevel[] = { 0, 256 };
//		const float* ranges[] = { graylevel };
//		cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);
//		return hist;
//	};
//
//	cv::Mat his1 = calcGrayHist(src);
//
//	auto getGrayHistImage = [](const cv::Mat& hist) {
//		double histMax;
//		cv::minMaxLoc(hist, 0, &histMax);
//		cv::Mat imgHsit(100, 256, CV_8UC1, cv::Scalar(255));
//		for (int i = 0; i < 256; ++i)
//		{
//			cv::line(imgHsit, cv::Point(i, 100), cv::Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), cv::Scalar(0));
//		}
//		return imgHsit;
//	};
//
//	cv::Mat hist_img = getGrayHistImage(his1);
//	cv::imshow("SRC", src);
//	cv::imshow("HISTOGRAH", hist_img);
//	cv::waitKey();
//	cv::destroyAllWindows();
//}

//�̹����� ��Ÿ���� cv::Mat ��ü�� ���� ������ const cv::Mat& ������ �Է� �Ű����� img�� ĸó�մϴ�.
//auto calcGrayHist = [](const cv::Mat& img) {
//	cv::Mat hist;  // ������׷��� ������ Mat ��ü
//	int channels[] = { 0 };  // ����� ä�� (�׷��̽����� �̹����̹Ƿ� �ϳ��� ä�θ� ���)
//	int dims = 1;  // ������׷��� ���� (1����)
//	int histSize[] = { 256 };  // ������׷��� ���� ���� (0~255 ������ 256���� �������� ����)
//	float graylevel[] = { 0, 256 };  // ������׷� ������ ���� (0���� 255����)
//	const float* ranges[] = { graylevel };  // ������׷� ������ ������ ��Ÿ���� ������ �迭
//	cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);  // ������׷� ���
//	return hist;  // ���� ������׷��� ��ȯ
//};

cv::Mat calcGrayHist(const cv::Mat& img)	//������׷� set
{
	cv::Mat hist;
	int channels[] = { 0 };
	int dims = 1;   //���
	int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };
	cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);		//������׷� ���
	return hist;//      ������ ����                   ����:1,������ �ϳ��ϱ�
}

cv::Mat getGrayHistImage(const cv::Mat& hist)	//������׷� show_get
{
	double histMax;
	cv::minMaxLoc(hist, 0, &histMax);
	cv::Mat imgHist(100, 256, CV_8UC1, cv::Scalar(255));
	for (int i = 0; i < 256; i++)
	{
		cv::line(imgHist, cv::Point(i, 100), cv::Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), cv::Scalar(0));
	}
	return imgHist;
}

void show_hit()      //p.216,p.221
{               //������ �׷�: 0(��ο�) ~ 255(����)
	cv::Mat src = cv::imread("hawkes.bmp", cv::IMREAD_GRAYSCALE);
	//���� �Լ�     [](){      };  �Լ� �ȿ� �Լ������ �� �� ����, �ѹ��� ������
	//auto calcGrayHist = [](const cv::Mat& img) {
	//   cv::Mat hist;
	//   int channels[] = { 0 };
	//   int dims = 1;   //���
	//   int histSize[] = {256};
	//   float graylevel[] = { 0,256 };
	//   const float* ranges[] = { graylevel };
	//   cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);
	//   return hist;//      ������ ����                    ����:1,������ �ϳ��ϱ�
	//};
	cv::Mat hist1 = calcGrayHist(src);

	/*auto getGrayHistImage = [](const cv::Mat& hist)            //�����Լ�
	{
	   double histMax;
	   cv::minMaxLoc(hist, 0, &histMax);
	   cv::Mat imgHist(100, 256, CV_8UC1, cv::Scalar(255));
	   for (int i = 0; i < 256; i++)
	   {
		  cv::line(imgHist, cv::Point(i, 100), cv::Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), cv::Scalar(0));
	   }
	   return imgHist;
	};*/
	cv::Mat hist_img = getGrayHistImage(hist1);
	cv::imshow("SRC", src);
	cv::imshow("HISTOGRAM", hist_img);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void histogram_stretching()   //p,222
{
	cv::Mat src = cv::imread("hawkes.bmp", cv::IMREAD_GRAYSCALE);

	if (src.empty())
	{
		return;
	}

	double gmin = 0.0;
	double gmax = 0.0;
	cv::minMaxLoc(src, &gmin, &gmax);   //src���� ���� ���� ���� ���� ū ���� ã����
	cv::Mat dst = ((src - gmin) / (gmax - gmin)) * 255;      //p.221����
	cv::Mat hist1 = calcGrayHist(src);
	cv::Mat hist_img = getGrayHistImage(hist1);
	cv::imshow("SRC", src);
	cv::imshow("HISTOGRAM", hist_img);

	cv::imshow("DST", dst);
	cv::imshow("DST_IMG", getGrayHistImage(calcGrayHist(dst)));

	cv::waitKey(0);
	cv::destroyAllWindows();
}

