#include <iostream>
#include <chrono>

//openCV include files
#include "opencv2\highgui.hpp"
#include "opencv2\core.hpp"

#define DEBUG 0;
using namespace std;
using namespace std::chrono;
using namespace cv;

void wait_for_ms(int wait_duration) {

	steady_clock::time_point t = steady_clock::now();
	steady_clock::duration d{ 0 };

	while (duration_cast<milliseconds>(d) < duration<long long, milli>{wait_duration})
	{
		d = steady_clock::now() - t;
	}

#ifdef DEBUG
	cout << "waited for: " << duration_cast<milliseconds>(d).count() << "ms" << endl;
#endif // DEBUG
}

int main() {

	wait_for_ms(5000);
	CvCapture* webcam_image = cvCreateCameraCapture(0);

	if (!webcam_image) {
		cout << "No webcam found!!!" << endl;

		return -1;
	}
	
	Mat 
	
	return 0;
}