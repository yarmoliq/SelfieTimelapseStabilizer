#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <iostream>

using namespace cv;
using namespace face;

int main(int argc, char **argv)
{
    Mat img1 = imread(argv[1], IMREAD_COLOR);
    Mat img2 = imread(argv[2], IMREAD_COLOR);

    Mat output;

    img2.copyTo(img1(cv::Rect(10,10,img2.cols, img2.rows)));

    imwrite("../photos/output.png", img1);

    return 0;
}
