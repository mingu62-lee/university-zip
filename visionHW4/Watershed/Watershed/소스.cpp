#include <iostream>
#include <opencv2/opencv.hpp>
#include "watershedSegment.h"

using namespace std;
using namespace cv;

int main() {
	cv::Mat image = cv::imread("hand_sample2.jpg");

	cv::imshow("Original Image", image); //원본

	cv::Mat gray_image;
	cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
	cv::imshow("Gray Image", gray_image); //gray영상
	cv::Mat binary_image;
	cv::threshold(gray_image, binary_image, 90, 255, cv::THRESH_BINARY_INV);
	cv::imshow("Binary Image", binary_image); //이진영상으로변환(손하얗게끔inverse)
	cv::Mat fg;
	cv::erode(binary_image, fg, cv::Mat(), cv::Point(-1, -1), 12); //침식
	cv::imshow("Foreground", fg);

	cv::Mat bg;
	cv::dilate(binary_image, bg, cv::Mat(), cv::Point(-1, -1), 40); //팽창
	cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);

	cv::imshow("Background", bg);
	cv::Mat markers(binary_image.size(), CV_8U, cv::Scalar(0));
	markers = fg + bg; //침식+팽창= 마커영상으로조합. 워터쉐드알고리즘에 입력으로 사용됨.
	cv::imshow("Marker", markers);



	WatershedSegmenter segmenter; //워터쉐드분할객체생성

	segmenter.setMarkers(markers); //set마커하면signed 이미지로바뀜

	segmenter.process(image); //0,128,255로구성됨

	cv::imshow("Segmentation", segmenter.getSegmentation());



	cv::imshow("Watershed", segmenter.getWatersheds()); // 0,255로구성됨

	cv::waitKey(0);

	return 0;
}

