#pragma once
#include <opencv2/opencv.hpp>

class WatershedSegmenter {
private:
	cv::Mat  markers;
public:
	void  setMarkers(const cv::Mat& markerImage) {
		markerImage.convertTo(markers, CV_32S);
	}
	//convertTo(OutputArray m, int rtype, double alpha=1, double beta=0 ) const
	//m(x,y) = saturate_cast<rType>( alpha x (*this)(x,y) + beta )
	cv::Mat  process(const cv::Mat& image) {
		cv::watershed(image, markers);
		return markers;    //-1, 128, 250 
	}
	cv::Mat  getSegmentation() {
		cv::Mat  tmp;
		markers.convertTo(tmp, CV_8U);    return  tmp;
	}
	cv::Mat  getWatersheds() {
		cv::Mat tmp;
		markers.convertTo(tmp, CV_8U, 255, 255);    return  tmp;
	}
};
