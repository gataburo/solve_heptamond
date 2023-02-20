#include "Printer.h"

Printer::Printer(const char* window_name, uint8_t width, uint8_t height) {
	strcpy_s(this->win_name, sizeof(this->win_name), window_name);
	this->array_width = width;
	this->array_height = height;
	this->img_width = (height + width + 2) * ZOOM_RATE;
	this->img_height = int((height + 1) * ZOOM_RATE * SQRT3) + 1;
	this->img = cv::Mat::zeros(this->img_height, this->img_width, CV_8UC3);
	cv::imshow(this->win_name, this->img);
	cv::moveWindow(this->win_name, 600, 300);
}

void Printer::print(uint8_t* fig, int wait_time) {
	this->img = cv::Mat::zeros(this->img_height, this->img_width, CV_8UC3);
	for (int i = 0; i < this->array_height; i++) {
		for (int j = 0; j < this->array_width; j++)
			if (fig[(i * this->array_width) + j] !=  0)
				this->printTriangle(i, j, fig[(i * this->array_width) + j]);
		//std::cout << "\n";
	}
	cv::imshow(this->win_name, this->img);
	cv::waitKey(wait_time);
}

void Printer::printTriangle(int y, int x, int color_index) {
	cv::Point points[3];
	if (x % 2 == 0) {
		points[0].x = y + x;
		points[0].y = y;
		points[1].x = y + x + 2;
		points[1].y = y;
		points[2].x = y + x + 1;
		points[2].y = y + 1;
	}
	else {
		points[0].x = y + x + 1;
		points[0].y = y;
		points[1].x = y + x;
		points[1].y = y + 1;
		points[2].x = y + x + 2;
		points[2].y = y + 1;
	}

	for (int i = 0; i < 3; i++) {
		points[i].x = points[i].x * ZOOM_RATE;
		points[i].y = (int)(points[i].y * ZOOM_RATE * SQRT3);
	}

	cv::fillConvexPoly(this->img, points, 3, this->refColorTable(color_index));//cv::Scalar(255, 0, 0));
}

cv::Scalar Printer::refColorTable(int index) {
	uint8_t g, b, r;
	int gbrf = index;

	if (index == 0) {
		g = b = r = 0;
	}
	else {
		g = (gbrf % 3) * 20 + (gbrf % 3 + 1) * gbrf * 3 * (24 - gbrf) * 2;
		b = (gbrf % 6) * 8 + ((gbrf + 1) % 3 + 1) * gbrf * 3 * (24 - gbrf) * 2;
		r = (gbrf % 9) * 5 + ((gbrf + 2) % 3 + 1) * gbrf * 3 * (24 - gbrf) * 2;
	}
	return cv::Scalar(g, b, r);
}
