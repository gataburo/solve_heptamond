#pragma once

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/version.hpp>
#ifdef _DEBUG
#define LIBEXT CVAUX_STR(CV_VERSION_MAJOR) CVAUX_STR(CV_VERSION_MINOR) CVAUX_STR(CV_VERSION_REVISION) CV_VERSION_STATUS "d.lib"
#else
#define LIBEXT CVAUX_STR(CV_VERSION_MAJOR) CVAUX_STR(CV_VERSION_MINOR) CVAUX_STR(CV_VERSION_REVISION) CV_VERSION_STATUS ".lib"
#endif
#ifdef HAVE_OPENCV_WORLD
#pragma comment(lib, "opencv_world"       LIBEXT)
#else
#pragma comment(lib, "opencv_core"        LIBEXT)
#pragma comment(lib, "opencv_highgui"     LIBEXT)
#pragma comment(lib, "opencv_imgproc"     LIBEXT)
#pragma comment(lib, "opencv_video"       LIBEXT)
#pragma comment(lib, "opencv_videoio"     LIBEXT)
#pragma comment(lib, "opencv_features2d"  LIBEXT)
#pragma comment(lib, "opencv_objdetect"   LIBEXT)
#pragma comment(lib, "opencv_calib3d"     LIBEXT)
#pragma comment(lib, "opencv_imgcodecs"   LIBEXT)
#ifdef HAVE_OPENCV_XFEATURES2D
#pragma comment(lib, "opencv_xfeatures2d" LIBEXT)
#endif
#endif

#define ZOOM_RATE 20
#define SQRT3 1.7320508

class Printer {
private:
	char win_name[32];
	cv::Mat img;
	uint8_t array_width;
	uint8_t array_height;
	uint16_t img_width;
	uint16_t img_height;
public:
	Printer(const char* name, uint8_t width, uint8_t hegiht);
	void print(uint8_t* fig, int wait_time);
private:
	void printTriangle(int i, int j, int color_index);
	cv::Scalar refColorTable(int i);
};