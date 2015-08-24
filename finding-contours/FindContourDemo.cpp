#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#ifdef _DEBUG
#pragma comment(lib, "opencv_core2410d.lib")
#pragma comment(lib, "opencv_imgproc2410d.lib")
#pragma comment(lib, "opencv_highgui2410d.lib")
#else
#pragma comment(lib, "opencv_core2410.lib")
#pragma comment(lib, "opencv_imgproc2410.lib")
#pragma comment(lib, "opencv_highgui2410.lib")
#endif

using namespace cv;
using namespace std;

int main( int, char** argv )
{
	const char * file_name = "F:\\shape.png";
	
	Mat src_mat, gray_mat, canny_mat;
	Mat contour_mat;
	Mat bounding_mat;

	const char* src_name = "Source";
	const char* contours_name = "Contours";
	const char* bounding_name = "Bounding";

	//1.Read image file & clone.
	src_mat = imread( file_name );
	contour_mat = src_mat.clone();
	bounding_mat = src_mat.clone();
	
	//2. Convert to gray image and apply canny edge detection
	cvtColor( src_mat, gray_mat, COLOR_RGB2GRAY );
	Canny(gray_mat, canny_mat, 30, 128, 3, false);

	//3. Find & process the contours
	//3.1 find contours on the edge image.
	vector< vector< cv::Point> > contours;
	findContours(canny_mat, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	//3.2 draw contours & property value on the source image.
	double area, length;
	drawContours(contour_mat, contours, -1, cv::Scalar(0), 2);	//draw contours on the image
	for(int i = 0; i < contours.size(); ++i)
	{
		Point2f center;
		float radius;

		area = contourArea(contours[i]);
		length = arcLength(contours[i], true);
		minEnclosingCircle(contours[i], center, radius);

		//draw contour property value at the contour center.
		char buffer[64] = {0};		
		sprintf(buffer, "Area: %.2lf", area);
		putText(contour_mat, buffer, center, FONT_HERSHEY_SIMPLEX, .6, Scalar(0), 1);

		sprintf(buffer, "Length: %.2lf", length);
		putText(contour_mat, buffer, Point(center.x,center.y+20), FONT_HERSHEY_SIMPLEX, .6, Scalar(0), 1);

	}

	//3.3 find bounding of each contour, and draw it on the source image.
	for(int i = 0; i < contours.size(); ++i)
	{
		Point2f points[4];
		Point2f center;
		float radius;
		Rect rect;
		RotatedRect rotate_rect;
		
		//compute the bounding rect, rotated bounding rect, minum enclosing circle.
		rect = boundingRect(contours[i]);
		rotate_rect = minAreaRect(contours[i]);
		minEnclosingCircle(contours[i], center, radius);

		rotate_rect.points(points);
		
		vector< vector< Point> > polylines;
		polylines.resize(1);
		for(int j = 0; j < 4; ++j)
			polylines[0].push_back(points[j]);

		//draw them on the bounding image.
		cv::rectangle(bounding_mat, rect, Scalar(0,0,255), 2);
		cv::polylines(bounding_mat, polylines, true, Scalar(0, 255, 0), 2);
		cv::circle(bounding_mat, center, radius, Scalar(255, 0, 0), 2);

	}

	//4. show window
	namedWindow( src_name, WINDOW_AUTOSIZE );
	namedWindow( contours_name, WINDOW_AUTOSIZE );
	namedWindow( bounding_name, WINDOW_AUTOSIZE );

	imshow(src_name, src_mat);
	imshow(contours_name, contour_mat);
	imshow(bounding_name, bounding_mat);

	waitKey(0);

	return 0;
}