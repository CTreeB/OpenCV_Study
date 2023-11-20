#pragma once
#include <opencv2/opencv.hpp>
//������ ����� ���� �ɷ� �ؾ��Ѵ�.
void operating()
{
	cv::Mat img1 = cv::imread("lenna256.bmp", cv::IMREAD_GRAYSCALE);
	std::cout << img1.size << std::endl;	//400 X 600 --> �̹��� ���� 600 x 400
	cv::Mat img2 = cv::imread("square.bmp", cv::IMREAD_GRAYSCALE);
	std::cout << img2.size << std::endl;
}

void arithmatic1()
{
	cv::Mat img1 = cv::imread("lenna256.bmp", cv::IMREAD_GRAYSCALE);
	std::cout << img1.size << std::endl;	//400 X 600 --> �̹��� ���� 600 x 400
	cv::Mat img2 = cv::imread("square.bmp", cv::IMREAD_GRAYSCALE);
	std::cout << img2.size << std::endl;
	if (img1.empty() or img2.empty()) return;
	//for (int i = 0; i < img2.rows; ++i)
	//{
	//	for (int j = 0; j < img2.cols; ++j)
	//	{
	//		uchar pixel = img2.at<uchar>(i, j);	//��½�, �ƽ�Ű�ڵ尪 
	//		std::cout << static_cast<int>(pixel) << " ";	//���������� Ÿ��ĳ����		0 or 255(����ũ ���� �ƴ϶�)
	//	}
	//	std::cout << std::endl;
	//}

	cv::Mat dst1 = img1 + img2;
	cv::Mat dst2 = img1 - img2;
	cv::Mat dst3(256, 256, CV_8UC1);
	for (int i = 0; i < img2.rows; ++i)
{
	for (int j = 0; j < img2.cols; ++j)
	{
		dst3.at<uchar>(i, j) = cv::saturate_cast<uchar>(img1.at<uchar>(i, j) * img2.at<uchar>(i, j));	//���������� Ÿ��ĳ����		0 or 255(����ũ ���� �ƴ϶�)
	}
	std::cout << std::endl;
}


	cv::imshow("IMG1", img1);
	cv::imshow("IMG2", img2);
	cv::imshow("DST1", dst1);
	cv::imshow("DST2", dst2);
	cv::imshow("DST3", dst3);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void arithmatic2()
{
	cv::Mat src1 = cv::imread("lenna256.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat src2 = cv::imread("square.bmp", cv::IMREAD_GRAYSCALE);
	if (src1.empty() or src2.empty()) return;

	cv::Mat dst;
	cv::add(src1, src2, dst);

	cv::Mat dst2;
	cv::subtract(src1, src2, dst2);

	cv::Mat dst3;
	cv::absdiff(src1, src2, dst3);	//���밪(absolute) ������ ���� --> ��ü Ž���� ���

	cv::Mat dst4;
	cv::addWeighted(src1, 1, src2, 0.15, 0, dst4);	//���� �ռ� ���� ���� (����,����, ����, ����, ����, ��������)

	cv::imshow("SRC1", src1);
	cv::imshow("SRC2", src2);
	cv::imshow("DST", dst);
	cv::imshow("DST2", dst2);
	cv::imshow("DST3", dst3);
	cv::imshow("DST4", dst4);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void logical()
{
	cv::Mat src1 = cv::imread("lenna256.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat src2 = cv::imread("square.bmp", cv::IMREAD_GRAYSCALE);
	if (src1.empty() or src2.empty()) return;

	cv::Mat dst(256, 256, CV_8UC1);

	cv::imshow("SRC1", src1);
	cv::imshow("SRC2", src2);

	/*dst = src1 & src2;*/
	cv::bitwise_and(src1, src2, dst);
	cv::imshow("DST", dst);

	/*dst = src1 | src2;*/
	cv::bitwise_or(src1, src2, dst);
	cv::imshow("DST2", dst);

	/*dst = src1 ^ src2;*/
	cv::bitwise_xor(src1, src2, dst);
	cv::imshow("DST3", dst);		//ex-or == abloute different

	/*dst = ~src1;*/
	cv::bitwise_not(src1, dst);
	cv::imshow("DST4", dst);

	cv::waitKey(0);
	cv::destroyAllWindows();

}

void filter_embossing()
{
	cv::Mat src = cv::imread("rose.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;

	float filter_data[] = { -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
	cv::Mat emboss(3, 3, CV_32FC1, filter_data);
	cv::Mat dst;
	cv::filter2D(src, dst, -1, emboss, cv::Point(-1, -1), 128);
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void filter_bluring()
{
	cv::Mat src = cv::imread("rose.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::Mat dst;
	cv::blur(src, dst, cv::Size(3, 3));

	//3 x 3 anker�� Ȱ��.
	float blur_filter[] = { 1/9.f, 1/9.f, 1/9.f, 1/9.f, 1 / 9.f, 1 / 9.f, 1 / 9.f, 1 / 9.f, 1/9.f };
	
	cv::Mat dst2(3, 3, CV_32FC1, blur_filter);
	cv::Mat dst3;
	cv::filter2D(src, dst3, -1, dst2, cv::Point(-1, -1), 0);
	cv::Mat dst4;

	//��հ� ����
	for (int ksize = 3; ksize <= 7; ksize = ksize + 2)
	{
		cv::blur(src, dst4, cv::Size(ksize, ksize));
		cv::String desc = cv::format("Blur : %d X %d", ksize, ksize);
		cv::imshow(desc, dst4);
		cv::waitKey();
	}

	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::imshow("DST3", dst3);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void fliter_GaussianBlur()
{
	cv::Mat src = cv::imread("rose.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::imshow("SRC", src);
	cv::Mat dst;
	for (int sigma = 1; sigma <= 5; ++sigma)
	{
		cv::GaussianBlur(src, dst, cv::Size(), static_cast<double>(sigma));	//sigma == 1.0
		cv::String text = cv::format("Sigma : %d", sigma);
		cv::putText(dst, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
		cv::imshow(text, dst);
		cv::waitKey();
	}
	cv::destroyAllWindows();
}

void filter_unshar_mask()
{
	cv::Mat src = cv::imread("rose.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::imshow("SRC", src);
	cv::Mat blurred;	//�Լ��� ���� ��� ���� ��Ŵ
	float alpha = 1.0f;
	for (int sigma = 1; sigma <= 5; ++sigma)
	{
		cv::GaussianBlur(src, blurred, cv::Size(), sigma);		//����þ� ��-->>�ٸ� ���� ����ص� ��.
		cv::Mat dst = (1 + alpha) * src - (alpha * blurred);	//
		cv::String text = cv::format("sigma : %d", sigma);
		cv::putText(dst, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
		cv::imshow(text, dst);
		cv::waitKey();
		cv::destroyAllWindows;
	}

}

void noise_gaussian()	//����� �ǵ������� ����
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::imshow("lenna", src);
	cv::Mat dst;
	for (int stddev = 10; stddev <= 30; stddev += 10)
	{
		cv::Mat noise(src.size(), CV_32SC1);	//noise ���� -1~1
		cv::randn(noise, 0, stddev);
		cv::add(src, noise, dst, cv::noArray(), CV_8UC1);
		cv::String text = cv::format("STDDEV : %d", stddev);
		cv::putText(dst, text, cv::Point(10, 30), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255), cv::LINE_AA);
		cv::imshow(text, dst);
		cv::waitKey();
	}
	
	cv::destroyAllWindows();
}

void filter_bilateral()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	if (src.empty()) return;
	cv::imshow("SRC", src);
	cv::Mat dst1;	//Gaussian
	cv::Mat dst2;	//Bilateral
	cv::Mat noise(src.size(), CV_32SC1);	// -2.0 ~ 2.0
	cv::randn(noise, 0, 5);
	cv::add(src, noise, src, cv::noArray(), CV_8UC1);
	cv::imshow("noise_SRC", src);

	cv::GaussianBlur(src, dst1, cv::Size(), 5);
	cv::imshow("Gaussian", dst1);

	cv::bilateralFilter(src, dst2, -1, 10, 5);
	cv::imshow("Bilateral", dst2);

	cv::waitKey();
	cv::destroyAllWindows();
}

void filter_median()
{
	cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	cv::imshow("SRC", src);
	int num = static_cast<int>(src.total()) * 0.1;		//�ȼ� ��Ż * 0.1
	for (int i = 0; i < num; ++i)
	{
		int x = rand() % src.cols;	//cols�� ���� �Ѿ �� ����(������ ����)
		int y = rand() % src.rows;	//rows�� ���� �Ѿ �� ����(������ ����)
		src.at<uchar>(y, x) = (i % 2) * 255;
	}
	cv::imshow("salttandPepper", src);

	cv::Mat dst1;	//Gaussian
	cv::Mat dst2;	//median

	cv::GaussianBlur(src, dst1, cv::Size(), 1);
	cv::imshow("Gaussian", dst1);

	cv::medianBlur(src, dst2, 3);	// 3 --> 3 x 3
	cv::imshow("Median", dst2);

	cv::waitKey();
	cv::destroyAllWindows();
}

// �ҽ� �̹���(src)�� ����þ� ��(Gaussian blur)�� �����ϰ� ����� dst�� �����մϴ�.
// cv::Size() ���ڴ� Ŀ�� ũ�⸦ �����ϸ�, �̴� ǥ�� ����(sigma)�� ���� �����˴ϴ�.
// sigma ���� double�� ĳ��Ʈ�˴ϴ�.
//cv::GaussianBlur(src, dst, cv::Size(), static_cast<double>(sigma)); // sigma == 1.0
// cv::format �Լ��� ����Ͽ� �ñ׸�(sigma) ���� ǥ���ϴ� �ؽ�Ʈ ���ڿ��� �����մϴ�.
// ���� ���ڿ� "Sigma : %d"�� ���� �ñ׸� ������ ��ü�˴ϴ�.
//cv::String text = cv::format("Sigma : %d", sigma);
// ������ �ؽ�Ʈ�� ��� �̹���(dst) ���� ��ġ�մϴ�.
// �ؽ�Ʈ�� cv::Point(10, 30) ��ġ�� ��ġ�˴ϴ�.
// FONT_HERSHEY_SIMPLEX�� �۲� ������ �����ϰ�, 1.0�� �۲� ũ�⸦ �����մϴ�.
// cv::Scalar(255)�� �ؽ�Ʈ ������ ������� �����մϴ�.
// �� 1�� �ؽ�Ʈ �β���, cv::LINE_AA�� ��Ƽ �ٸ���� ��带 �����մϴ�.
//cv::putText(dst, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
// ��� �̹���(dst)�� �ؽ�Ʈ�� ǥ�õ� â���� ǥ���մϴ�.
// â ������ �ؽ�Ʈ ���ڿ��� �����˴ϴ�.
//cv::imshow(text, dst);
// Ű �Է��� ����մϴ�.
//cv::waitKey();



