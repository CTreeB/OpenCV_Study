#pragma once
#include <opencv2/opencv.hpp>
static void on_mouse(int event, int x, int y, int flags, void* userdata);

void affine_transform()
{
	cv::Mat src = cv::imread("tekapo.bmp");
	if (src.empty()) return;
	std::cout << src.size << std::endl;
	cv::Point2f srcPts[3];
	cv::Point2f dstPts[3];
	srcPts[0] = cv::Point2f(0, 0);
	srcPts[1] = cv::Point2f(src.cols - 1.0f, 0.0f);
	srcPts[2] = cv::Point2f(src.cols - 1.0f, src.rows - 1.0f);

	dstPts[0] = cv::Point2f(0.0f, 0.0f);
	dstPts[1] = cv::Point2f(src.cols - 50.0f, 50.0f);
	dstPts[2] = cv::Point2f(src.cols - 0.0f, src.rows - 0.0f);

	cv::Mat M = cv::getAffineTransform(srcPts, dstPts);

	cv::Mat dst;
	cv::warpAffine(src, dst, M, cv::Size());
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void affine_translation()
{
	cv::Mat src = cv::imread("tekapo.bmp");
	float m = 0.0f;
	std::cin >> m;
	cv::Mat M = cv::Mat_<float>({ 2, 3 }, { 1.0f, m, 0.0f, 0.0f, 1.0f, 0.0f });
	cv::Mat dst;
	cv::warpAffine(src, dst, M, cv::Size(cvRound(src.cols + src.rows * m), src.rows));
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}

void affine_resize()
{
	cv::Mat src = cv::imread("rose.bmp");
	if (src.empty())
	{
		std::cerr << "파일이 없음" << std::endl;
		return;
	}
	cv::Mat dst1, dst2, dst3, dst4;
	cv::resize(src, dst1, cv::Size(), 4.0, 4.0, cv::INTER_NEAREST);
	cv::imshow("SRC", src);
	cv::imshow("DST1", dst1(cv::Rect(400, 500, 400, 400))); //너비 400 높이 500

	cv::resize(src, dst2, cv::Size(), 4.0, 4.0);
	cv::imshow("DST2", dst2(cv::Rect(400, 500, 400, 400))); //너비 400 높이 500

	cv::resize(src, dst3, cv::Size(), 4.0, 4.0, cv::INTER_CUBIC);
	cv::imshow("DST3", dst3(cv::Rect(400, 500, 400, 400))); //너비 400 높이 500

	cv::resize(src, dst4, cv::Size(), 4.0, 4.0, cv::INTER_LANCZOS4);
	cv::imshow("DST4", dst4(cv::Rect(400, 500, 400, 400))); //너비 400 높이 500

	cv::waitKey();
	cv::destroyAllWindows();
}

void affine_rotation()
{
	cv::Mat src = cv::imread("tekapo.bmp");
	if (src.empty()) return;
	cv::Point2f center (src.cols / 2, src.rows / 2);
	cv::Mat M = cv::getRotationMatrix2D(center, 20.0, 1.0);

	cv::Mat dst;
	cv::warpAffine(src, dst, M, cv::Size());
	cv::imshow("SRC", src);
	cv::imshow("DST", dst);
	cv::waitKey();
	cv::destroyAllWindows();
}

void affine_flip()
{
	cv::Mat src{cv::imread("eastsea.bmp")};
	if (src.empty()) return;
	cv::imshow("SRC", src);
	cv::Mat dst;
	cv::flip(src, dst, 1);		// 1 -- 좌우 대칭
	cv::imshow("좌우대칭", dst);

	cv::flip(src, dst, 0);		// 0 -- 상하 대칭
	cv::imshow("상하대칭", dst);

	cv::flip(src, dst, -1);		// -1 -- 좌우 & 상하 대칭
	cv::imshow("좌우 & 상하 대칭", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}


static cv::Point2f dstQuad[4];
static cv::Point2f srcQuad[4];
static cv::Mat src = cv::imread("card.bmp");
static int count = 0;

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		if (count < 4)	//4개의 점
		{
			srcQuad[count++] = cv::Point2f(x, y);	// 클릭시 좌표를 배열에 저장한다.
			cv::circle(src, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
			cv::imshow("SRC", src);
		}

			if (count == 4)	//4개의 점
			{
				int width = 200;
				int height = 300;
				dstQuad[0] = cv::Point2f(0, 0);
				dstQuad[1] = cv::Point2f(width - 1, 0);
				dstQuad[2] = cv::Point2f(width -1 ,height - 1);
				dstQuad[3] = cv::Point2f(0, height - 1);
				cv::Mat M = cv::getPerspectiveTransform(srcQuad, dstQuad);	//원본(src) 점과 결과(dst) 점을 M에 주면 값을 구해준다.
				cv::Mat dst;
				cv::warpPerspective(src, dst, M, cv::Size(width, height));
				cv::imshow("DST", dst);
			}
		}
}

void perspective()
{
	src = cv::imread("card.bmp");
	if (src.empty()) return;
	cv::namedWindow("SRC");
	cv::imshow("SRC", src);
	cv::setMouseCallback("SRC", on_mouse);
	cv::waitKey();
	cv::destroyAllWindows();
}

