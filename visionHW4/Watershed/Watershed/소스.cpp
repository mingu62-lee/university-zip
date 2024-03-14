#include <iostream>
#include <opencv2/opencv.hpp>
#include "watershedSegment.h"

using namespace std;
using namespace cv;

int main() {
	cv::Mat image = cv::imread("hand_sample2.jpg");

	cv::imshow("Original Image", image); //����

	cv::Mat gray_image;
	cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
	cv::imshow("Gray Image", gray_image); //gray����
	cv::Mat binary_image;
	cv::threshold(gray_image, binary_image, 90, 255, cv::THRESH_BINARY_INV);
	cv::imshow("Binary Image", binary_image); //�����������κ�ȯ(���Ͼ�Բ�inverse)
	cv::Mat fg;
	cv::erode(binary_image, fg, cv::Mat(), cv::Point(-1, -1), 12); //ħ��
	cv::imshow("Foreground", fg);

	cv::Mat bg;
	cv::dilate(binary_image, bg, cv::Mat(), cv::Point(-1, -1), 40); //��â
	cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);

	cv::imshow("Background", bg);
	cv::Mat markers(binary_image.size(), CV_8U, cv::Scalar(0));
	markers = fg + bg; //ħ��+��â= ��Ŀ������������. ���ͽ���˰��� �Է����� ����.
	cv::imshow("Marker", markers);



	WatershedSegmenter segmenter; //���ͽ�����Ұ�ü����

	segmenter.setMarkers(markers); //set��Ŀ�ϸ�signed �̹����ιٲ�

	segmenter.process(image); //0,128,255�α�����

	cv::imshow("Segmentation", segmenter.getSegmentation());



	cv::imshow("Watershed", segmenter.getWatersheds()); // 0,255�α�����

	cv::waitKey(0);

	return 0;
}

