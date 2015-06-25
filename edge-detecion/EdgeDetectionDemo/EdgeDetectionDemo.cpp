#include "imgproc/imgproc.hpp"
#include "highgui/highgui.hpp"

#ifdef _DEBUG // Change lib version: opencv_core{version}.lib
#pragma comment(lib, "opencv_core2410d.lib") 
#pragma comment(lib, "opencv_imgproc2410d.lib")
#pragma comment(lib, "opencv_highgui2410d.lib")
#else
#pragma comment(lib, "opencv_core2410.lib") 
#pragma comment(lib, "opencv_imgproc2410.lib")
#pragma comment(lib, "opencv_highgui2410.lib")
#endif

using namespace cv;

int main( int, char** argv )
{
	const char * file_name = "f:\\test.jpg";
	
	Mat src, src_gray;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	const char* src_name = "Source";
	const char* sobel_name = "Sobel";
	const char* canny_name = "Canny";
	const char* laplace_name = "Laplace";

	src = imread( file_name );

	cvtColor( src, src_gray, COLOR_RGB2GRAY );
	GaussianBlur( src_gray, src_gray, Size(3,3), 0, 0, BORDER_DEFAULT );

	namedWindow( src_name, WINDOW_AUTOSIZE );
	namedWindow( sobel_name, WINDOW_AUTOSIZE );
	namedWindow( canny_name, WINDOW_AUTOSIZE );
	namedWindow( laplace_name, WINDOW_AUTOSIZE );

	//This is for source image.
	imshow(src_name, src);

	//This is for sobel edge detection.
	Mat sobel_dst;
	Mat sobel_abs_dst;
	Sobel(src_gray, sobel_dst, ddepth, 1, 1, kernel_size);
	convertScaleAbs(sobel_dst, sobel_abs_dst);
	imshow( sobel_name, sobel_abs_dst );
  
	//This is for canny edge detection.
	Mat canny_dst;
	Canny(src_gray, canny_dst, 50, 200, 3, false);
	imshow(canny_name, canny_dst);

	//This is for laplace edge detection.
	Mat laplace_dst;
	Mat laplace_abs_dst;
	Laplacian( src_gray, laplace_dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( laplace_dst, laplace_abs_dst );
	imshow( laplace_name, laplace_abs_dst);

	waitKey(0);

	return 0;
}


