#pragma once
#include <opencv2/opencv.hpp>
static void on_brightness_chaged(int, void*);

void example()
{
	cv::Mat img = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat img2 = cv::imread("lenna.bmp", cv::IMREAD_COLOR);
	cv::Mat img3;
	cv::cvtColor(img2, img3, cv::COLOR_BGR2GRAY);		//grayscale을 color로 바꾸어줘야 할 경우

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
			dst.at<uchar>(i, j) = cv::saturate_cast<uchar>(src.at<uchar>(i, j) - 100);	//cv::saturate_cast : 0~255에서 고정될수 있도록 만들어줌
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
	cv::imshow("CAT", dst);	//src에 트랙바를 덮어 씌움
}

void brightness3()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;

	float alpha = 1.0f;
	cv::Mat dst = (1 + alpha) * src - 128 * alpha;	//명암비 급상승	-	
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

//void show_hit()	//히스토그램 구하기
//{
//	cv::Mat src = cv::imread("hawks.bmp", cv::IMREAD_GRAYSCALE);
//	
//	//람다 함수
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

//이미지를 나타내는 cv::Mat 객체에 대한 참조인 const cv::Mat& 유형의 입력 매개변수 img를 캡처합니다.
//auto calcGrayHist = [](const cv::Mat& img) {
//	cv::Mat hist;  // 히스토그램을 저장할 Mat 객체
//	int channels[] = { 0 };  // 사용할 채널 (그레이스케일 이미지이므로 하나의 채널만 사용)
//	int dims = 1;  // 히스토그램의 차원 (1차원)
//	int histSize[] = { 256 };  // 히스토그램의 구간 개수 (0~255 범위를 256개의 구간으로 나눔)
//	float graylevel[] = { 0, 256 };  // 히스토그램 구간의 범위 (0부터 255까지)
//	const float* ranges[] = { graylevel };  // 히스토그램 구간의 범위를 나타내는 포인터 배열
//	cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);  // 히스토그램 계산
//	return hist;  // 계산된 히스토그램을 반환
//};

cv::Mat calcGrayHist(const cv::Mat& img)	//히스토그램 set
{
	cv::Mat hist;
	int channels[] = { 0 };
	int dims = 1;   //흑백
	int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };
	cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);		//히스토그램 출력
	return hist;//      영상의 개수                   차원:1,영상이 하나니까
}

cv::Mat getGrayHistImage(const cv::Mat& hist)	//히스토그램 show_get
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
{               //히스토 그램: 0(어두움) ~ 255(밝음)
	cv::Mat src = cv::imread("hawkes.bmp", cv::IMREAD_GRAYSCALE);
	//람다 함수     [](){      };  함수 안에 함수만들어 쓸 수 있음, 한번만 쓸꺼라서
	//auto calcGrayHist = [](const cv::Mat& img) {
	//   cv::Mat hist;
	//   int channels[] = { 0 };
	//   int dims = 1;   //흑백
	//   int histSize[] = {256};
	//   float graylevel[] = { 0,256 };
	//   const float* ranges[] = { graylevel };
	//   cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);
	//   return hist;//      영상의 개수                    차원:1,영상이 하나니까
	//};
	cv::Mat hist1 = calcGrayHist(src);

	/*auto getGrayHistImage = [](const cv::Mat& hist)            //로컬함수
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
	cv::minMaxLoc(src, &gmin, &gmax);   //src에서 가장 작은 값과 가장 큰 값을 찾아줌
	cv::Mat dst = ((src - gmin) / (gmax - gmin)) * 255;      //p.221공식
	cv::Mat hist1 = calcGrayHist(src);
	cv::Mat hist_img = getGrayHistImage(hist1);
	cv::imshow("SRC", src);
	cv::imshow("HISTOGRAM", hist_img);

	cv::imshow("DST", dst);
	cv::imshow("DST_IMG", getGrayHistImage(calcGrayHist(dst)));

	cv::waitKey(0);
	cv::destroyAllWindows();
}

