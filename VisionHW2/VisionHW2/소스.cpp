#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void detectHScolor(const cv::Mat&  image, double minHue, double maxHue, double minSat, double  maxSat, cv::Mat&  mask) {
	//�� ������ ���� ����, ä�� ���� ����
	cv::Mat hsv;
	cv::cvtColor(image, hsv, COLOR_BGR2HSV);

	vector<cv::Mat>  channels;
	cv::split(hsv, channels);    //HSV ä�� �и�
	//Hue ����ũ:0~180
	cv::Mat  mask1;   //maxHue ���ϴ� 255, �̻��� 0
	cv::threshold(channels[0], mask1, maxHue, 255, cv::THRESH_BINARY_INV);
	cv::Mat  mask2; //minHue ���ϴ� 0, �̻��� 255   
	cv::threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY);
	cv::Mat hueMask;
	if (minHue < maxHue)  hueMask = mask1 & mask2;
	else hueMask = mask1 | mask2;
	//���� ������ 0�� ������ �� �� 160 ~ 10 ���� ����
	//ä�� ����ũ
	cv::threshold(channels[1], mask1, maxSat, 255, cv::THRESH_BINARY_INV);
	cv::threshold(channels[1], mask2, minSat, 255, cv::THRESH_BINARY);

	cv::Mat satMask;
	satMask = mask1 & mask2;
	//0�� 255�� ������ mask: 255�� ���� �� ����: �̿����� ���� ���󿡼� //copy
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
	//detected ���









	/*Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	vector<cv::Mat>  channels;
	split(hsv, channels);
	//channels[0] ����(H),  channels[1]  ä��(S),  channels[2]  ��(V)
	//�� ä�� ���
	imshow("Original", image);
	imshow("Hue", channels[0]);
	imshow("Saturate", channels[1]);
	imshow("Value", channels[2]);
	waitKey(0);*/
}