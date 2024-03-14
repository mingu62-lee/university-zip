#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void detectHScolor(const cv::Mat&  image, double minHue, double maxHue, double minSat, double  maxSat, cv::Mat&  mask) {
	//얼굴 영역의 색상 범위, 채도 범위 설정
	cv::Mat hsv;
	cv::cvtColor(image, hsv, COLOR_BGR2HSV);

	vector<cv::Mat>  channels;
	cv::split(hsv, channels);    //HSV 채널 분리
	//Hue 마스크:0~180
	cv::Mat  mask1;   //maxHue 이하는 255, 이상은 0
	cv::threshold(channels[0], mask1, maxHue, 255, cv::THRESH_BINARY_INV);
	cv::Mat  mask2; //minHue 이하는 0, 이상은 255   
	cv::threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY);
	cv::Mat hueMask;
	if (minHue < maxHue)  hueMask = mask1 & mask2;
	else hueMask = mask1 | mask2;
	//색상 범위가 0을 포함할 때 즉 160 ~ 10 사이 색상
	//채도 마스크
	cv::threshold(channels[1], mask1, maxSat, 255, cv::THRESH_BINARY_INV);
	cv::threshold(channels[1], mask2, minSat, 255, cv::THRESH_BINARY);

	cv::Mat satMask;
	satMask = mask1 & mask2;
	//0와 255로 구성된 mask: 255인 곳이 얼굴 영역: 이영역만 원본 영상에서 //copy
	mask = hueMask & satMask;
}

int main() {
	Mat image = imread("BALLOON2.bmp");
	if (image.empty()) {
		cout << "Image unloaded" << endl;
		return 0;
	}

	Mat mask;
	detectHScolor(image, 100, 130, 40, 360, mask);
	imshow("Mask", mask);
	waitKey(0);
	Mat detected(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	image.copyTo(detected, mask);
	imshow("Original", image);
	imshow("Detected", detected);
	waitKey(0);
	return 0;
	//detected 출력









	/*Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	vector<cv::Mat>  channels;
	split(hsv, channels);
	//channels[0] 색상(H),  channels[1]  채도(S),  channels[2]  명도(V)
	//각 채널 출력
	imshow("Original", image);
	imshow("Hue", channels[0]);
	imshow("Saturate", channels[1]);
	imshow("Value", channels[2]);
	waitKey(0);*/
}