#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <iostream>

#include "visualize/visualize.h"
#include "exif/exif.h"
#include "colorCorrection/adaptivePhotoAlignment.h"

#include "colorCorrection/colorCorrection.h"

using namespace cv;
using namespace face;

const unsigned int OUTPUT_WIDTH  = 3840;
const unsigned int OUTPUT_HEIGHT = 2160;

int main(int argc, char **argv)
{
    Mat img1 = imread(argv[1], IMREAD_COLOR);
    Mat img2 = imread(argv[2], IMREAD_COLOR);
    Mat output;
    
    colorCorrection(img2, img1, output, false, true);
    imwrite("../photos/output.png", output);

    return 0;
}