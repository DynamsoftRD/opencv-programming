#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

void GammaCorrection(Mat& src, Mat& dst, float fGamma)
{
	CV_Assert(src.data);

	// accept only char type matrices
	CV_Assert(src.depth() != sizeof(uchar));

	// build look up table
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
	}

	dst = src.clone();
	const int channels = dst.channels();
	switch (channels)
	{
	case 1:
	{

			  MatIterator_<uchar> it, end;
			  for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
				  //*it = pow((float)(((*it))/255.0), fGamma) * 255.0;
				  *it = lut[(*it)];

			  break;
	}
	case 3:
	{

			  MatIterator_<Vec3b> it, end;
			  for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
			  {

				  (*it)[0] = lut[((*it)[0])];
				  (*it)[1] = lut[((*it)[1])];
				  (*it)[2] = lut[((*it)[2])];
			  }

			  break;

	}
	}
}

int main(int argc, const char ** argv)
{
	string filename = "1.jpg";

	Mat img = imread(filename.c_str());
	//resize(img, img, Size(0, 0), 0.5, 0.5);
	imshow("1", img);

	Mat dst(img.rows, img.cols, img.type());
	GammaCorrection(img, dst,2);

	imshow("2", dst);

  waitKey();
  return 0;
}
