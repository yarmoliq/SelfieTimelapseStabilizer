#include "visualize.h"

#include <string>

using namespace cv;

void visualizeLandmarks(const Mat& src, Mat& dst,  const std::vector<Point2f>& landmarks, bool putNumbers)
{
    dst = src.clone();

    for(unsigned long i = 0; i < landmarks.size(); ++i)
    {
        circle(dst, landmarks[i], 5, Scalar(0,0,255), 4);
        if(putNumbers)
        {
            putText(dst,
                std::to_string(i), //text
                landmarks[i],
                cv::FONT_HERSHEY_DUPLEX,
                1,
                CV_RGB(118, 255, 75), //font color
                2);
        }
    }


}
