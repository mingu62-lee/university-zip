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

	cout << "ä�� -> " << m.channels() << endl;
	cout << "������Ÿ�� -> "  << m.type() << endl;
	cout << "step1() -> " << c << endl;
	cout << "���� -> " << m.depth() << endl;
	return 0;
}
