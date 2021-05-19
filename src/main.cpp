#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <iostream>
#include <math.h>

#include "visualize/visualize.h"
#include "imgManipulation/manipulation.h"

using namespace cv;
using namespace face;

const unsigned int OUTPUT_WIDTH  = 3840;
const unsigned int OUTPUT_HEIGHT = 2160;

const size_t LM1 = 36;
const size_t LM2 = 45;
const size_t LM3 = 57;

Point2f referenceLandmarks[3] =
{
    Point2f(1617.88, 1043.13),
    Point2f(2229.85, 999.402),
    Point2f(1978,    1601.35)
};

Mat original;

int main(int argc, char **argv)
{
    original = imread(argv[1], IMREAD_COLOR);

    CascadeClassifier face_cascade;
    face_cascade.load("models/haar/frontalface_alt.xml");

    Ptr<Facemark> facemark = createFacemarkLBF();
    facemark->loadModel("models/lbfmodel.yaml");

    Mat reduced;
    inscribeInto(original, reduced, Size(960, 960));

    Mat gray;
    cvtColor(reduced, gray, COLOR_BGR2GRAY);

    // adaptive histogram equalization
    auto cl = createCLAHE(2, Size(8, 8));
    cl->apply(gray, gray);

    std::vector<Rect> faces;
    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );
    
    std::vector< std::vector<Point2f> > landmarks;
    if (!facemark->fit(reduced, faces, landmarks))
    {
        std::cout << "Could not landmark any faces :(\n";
        return 0;
    }
    
    std::vector<Point2f> lm = landmarks[0];
    scaleVector(landmarks[0], lm, (float)original.cols / (float)reduced.cols);

    Mat output(OUTPUT_HEIGHT, OUTPUT_WIDTH, CV_8UC3);

    Point2f srcTri[3];
    srcTri[0] = lm[LM1];
    srcTri[1] = lm[LM2];
    srcTri[2] = lm[LM3];

    Mat warp_mat = getAffineTransform( srcTri, referenceLandmarks );

    warpAffine( original, output, warp_mat, output.size() );

    imwrite("../photos/output.png", output);

    return 0;
}
