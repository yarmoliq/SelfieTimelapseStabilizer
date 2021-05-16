#include "visualize.h"

using namespace cv;

Mat visualizeLandmarks(const Mat& src,  const std::vector<Point2f>& landmarks)
{
    Mat output = src.clone();

    // for (size_t i = 0; i < faces.size(); ++i)
    // {
    //     rectangle(img,faces[i], Scalar( 255, 0, 0 ), 4);
    // }

    for(unsigned long k = 0; k < landmarks.size(); ++k)
        circle(output, landmarks[k], 5, Scalar(0,0,255), 4);

    return output;
}
