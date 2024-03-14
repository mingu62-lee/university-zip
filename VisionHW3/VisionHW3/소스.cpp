#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
	cv::Mat image = cv::imread("food.jpg", 0);
	cv::imshow("Image", image);
	cv::Mat result;

	cv::Mat sobelX, sobelY;
	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	cv::imshow("SobelX", sobelX);
	cv::waitKey();

	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
	cv::imshow("SobelY", sobelY);
	cv::waitKey();

	cv::Sobel(image, sobelX, CV_16S, 1, 0);
	cv::Sobel(image, sobelY, CV_16S, 0, 1);
	cv::Mat  sobel;
	sobel = abs(sobelX) + abs(sobelY);//L1-norm

	double  sobmin, sobmax;
	cv::minMaxLoc(sobel, &sobmin, &sobmax);
	cv::Mat  sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255. / sobmax, 255);
	cv::imshow("Sobel Magnitude", sobelImage);
	cv::waitKey();
	// sobelImage =>영역 경계화

	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 190, 255, cv::THRESH_BINARY);
	cv::imshow("Sobel1190", sobelThresholded);
	cv::threshold(sobelImage, sobelThresholded, 225, 255, cv::THRESH_BINARY);
	cv::imshow("Sobel1225", sobelThresholded);
	cv::waitKey();

	cv::Mat norm, dir;
	cv::Sobel(image, sobelX, CV_32F, 1, 0);
	cv::Sobel(image, sobelY, CV_32F, 0, 1);
	cv::cartToPolar(sobelX, sobelY, norm, dir);
	cout << "sobelX=" << sobelX.at<float>(30, 40) << "  sobelY=" << sobelY.at<float>(30, 40) << endl;
	cout << "norm=" << norm.at<float>(30, 40) << "  dir=" << dir.at<float>(30, 40) << endl;
	 
	return 0;
}