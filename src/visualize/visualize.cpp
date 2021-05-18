#include "visualize.h"

using namespace cv;

Mat visualizeLandmarks(const Mat& src,  const std::vector<Point2f>& landmarks)
{
    Mat output = src.clone();

    for(unsigned long k = 0; k < landmarks.size(); ++k)
        circle(output, landmarks[k], 5, Scalar(0,0,255), 4);

    return output;
}
