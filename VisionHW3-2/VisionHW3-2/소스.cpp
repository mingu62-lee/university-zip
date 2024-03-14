#include <opencv2/opencv.hpp>
#include <iostream>
#include "laplacianZC.h"

using namespace std;


int main() {
	cv::Mat  image = cv::imread("food.jpg",0);
	cv::imshow("Image", image);
	cv::Mat  laplace;
	cv::Laplacian(image, laplace, CV_8U, 1, 1, 128);
	cv::imshow("Laplacian", laplace);

	LaplacianZC  laplacian;
	laplacian.setApeture(7);
	cv::Mat  flap = laplacian.computeLaplacian(image);
	double  lapmin, lapmax;
	cv::minMaxLoc(flap, &lapmin, &lapmax);
	cout << "Laplacian value range = [" << lapmin << ", " << lapmax << " ] \n" ;
	laplace = laplacian.getLaplacianImage();
	cv::imshow("Laplacian(7)", laplace);
	cv::waitKey();
	cv::Mat  zeros;
	zeros = laplacian.getZeroCrossing(flap);
	cv::imshow("Zero-crossings", 255 - zeros);
	cv::waitKey();

	cv::Mat enhanced;
	cv::Laplacian(image, laplace, CV_32F, 1);
	laplace.convertTo(laplace, CV_8U);
	enhanced = image - laplace;
	enhanced.convertTo(enhanced, CV_8U);
	cv::imshow("LaplacianEnhanced", enhanced);
	cv::waitKey();

	cv::Mat dog;
	cv::Mat  gauss20, gauss22, dogImage;
	cv::GaussianBlur(image, gauss20, cv::Size(), 2.0);
	cv::GaussianBlur(image, gauss22, cv::Size(), 2.2);
	cv::subtract(gauss22, gauss20, dog, cv::Mat(), CV_32F);//saturate
	dog.convertTo(dogImage, CV_8U, 10.0, 128);
	cv::imshow("DoG Image", dogImage);
	cv::waitKey();
	zeros = laplacian.getZeroCrossing(dog);
	cv::imshow("Zero-crossings of DoG", 255 - zeros);
	cv::waitKey();

	cv::GaussianBlur(image, image, cv::Size(7, 7), 2.5);
	flap = laplacian.computeLaplacian(image);
	cv::minMaxLoc(flap, &lapmin, &lapmax);
	cout << "Laplacian of G value range = [" << lapmin << ", " << lapmax << " ] ";
	laplace = laplacian.getLaplacianImage();
	cv::imshow("LaplacianGaussian(7)", laplace);
	cv::waitKey();
	zeros = laplacian.getZeroCrossing(flap);
	cv::imshow("Zero-crossings of LoG", 255 - zeros);
	cv::waitKey();


	return 0;
}