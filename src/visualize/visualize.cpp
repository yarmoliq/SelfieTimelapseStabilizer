#include "visualize.h"

#include <string>

using namespace cv;

void visualizeLandmarks(const Mat& src, Mat& dst,  const std::vector<Point2f>& landmarks)
{
    dst = src.clone();

    for(unsigned long k = 0; k < landmarks.size(); ++k)
    {
        circle(dst, landmarks[k], 5, Scalar(0,0,255), 4);
	putText(dst,
            std::to_string(k), //text
            landmarks[k],
            cv::FONT_HERSHEY_DUPLEX,
            1,
            CV_RGB(118, 255, 75), //font color
            2);
    }


}
