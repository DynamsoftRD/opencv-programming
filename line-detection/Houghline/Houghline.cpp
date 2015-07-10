#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int DetectLines(const char* filename, const char* sourceName, const char* destName)
{
	Mat src = imread(filename, 0);
	if (src.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}

	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, COLOR_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 4);
	}

	imshow(sourceName, src);
	imshow(destName, cdst);

	return 0;
}

int main(int argc, char** argv)
{
	DetectLines("..\\1.bmp", "line src", "line dest");
	DetectLines("..\\2.jpg", "door src", "door dest");
	waitKey();

	return 0;
}
