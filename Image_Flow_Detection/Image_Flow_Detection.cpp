#include "opencv2\core.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\video\tracking.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	CvCapture* webcam_image = cvCreateCameraCapture(0);

	if (!webcam_image) {
		cout << "No webcam found!!!" << endl;

		return -1;
	}

	//IplImage* previousimage = cvQueryFrame(webcam_image);
	Mat previous, previous_gray, current, current_gray, flow, flow_gray;

	int width = (int)cvGetCaptureProperty(webcam_image, CV_CAP_PROP_FRAME_WIDTH);

	int height = (int)cvGetCaptureProperty(webcam_image, CV_CAP_PROP_FRAME_HEIGHT);

	int x = 0;
	std::string s = "CamCapture" + std::to_string(x) + ".avi";
	const char* c = s.c_str();


	while (true)
	{
		double fps = 30;
		char key1 = cvWaitKey(1000 / fps);
		if (key1 == 'x') {
			break;
		}
		else
		{
			IplImage* current_image = cvQueryFrame(webcam_image);
			current = Mat(current_image);
			cvtColor(current, current_gray, COLOR_BGR2GRAY);

			if (previous_gray.empty() == false) {

				calcOpticalFlowFarneback(previous_gray, current_gray, flow_gray, 0.4, 1, 12, 2, 8, 1.2, 0);
				bool saveImage = false;

				for (int y = 0; y < current.rows; y += 5) {
					for (int x = 0; x < current.cols; x += 5)
					{
						const Point2f flow_at_xy = flow_gray.at<Point2f>(y, x) * 10;
						if ((flow_at_xy.x < -30.0f || flow_at_xy.x>30.0f) && (flow_at_xy.y < -30.0f || flow_at_xy.y>30.0f)) {
							line(current, Point(x, y), Point(cvRound(x + flow_at_xy.x), cvRound(y + flow_at_xy.y)), Scalar(255, 0, 0));
							circle(current, Point(x, y), 1, Scalar(0, 0, 0), -1);
							//saveImage = true;

							imshow("Image flow", current);
						}
						else {
							imshow("Image flow", current);
						}
					}
				}
				if (saveImage) {
					//namedWindow("prew", WINDOW_AUTOSIZE);
					//imshow("prew", current);


					CvVideoWriter *writer = cvCreateVideoWriter(c, -1, 30, cvSize(width, height));
					CvCapture* capture = cvCreateCameraCapture(0);
					if (!capture) {
						cout << "No webcam found!!" << endl;
						return -1;
					}
					while (1)
					{
						IplImage* image_to_save = cvQueryFrame(capture);
						cvShowImage("capWindow", image_to_save);
						cvWriteFrame(writer, current_image);

						double fps = 30;
						char key2 = cvWaitKey(1000 / fps);
						if (key2 == 27) break;
					}
					cvReleaseCapture(&capture);
					cvReleaseVideoWriter(&writer);
					cvDestroyWindow("capWindow");

					//namedWindow(c, WINDOW_AUTOSIZE);
					//cvShowImage(c, current_image);
					//cvSaveImage(c, current_image, 0);
					x += 1;
					saveImage = false;
				}
				// fill previous image again
				std::swap(previous_gray, current_gray);
			}
			else
			{
				std::swap(previous_gray, current_gray);
			}

		}
	}
	//exit(0);
	return 0;
}