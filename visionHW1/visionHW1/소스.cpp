#include "opencv2/opencv.hpp"
#include "stdio.h"

using namespace std;
using namespace cv;
int main() {
	Mat m(4, 3, CV_32FC3);
	int a, b;
	double c;
	a = m.step;
	b = m.elemSize1();
	c = a / b;

	cout << "채널 -> " << m.channels() << endl;
	cout << "데이터타입 -> "  << m.type() << endl;
	cout << "step1() -> " << c << endl;
	cout << "깊이 -> " << m.depth() << endl;
	return 0;
}
