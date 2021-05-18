#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <iostream>

#include "visualize/visualize.h"
#include "imgManipulation/manipulation.h"

using namespace cv;
using namespace face;

const unsigned int OUTPUT_WIDTH  = 3840;
const unsigned int OUTPUT_HEIGHT = 2160;

int main(int argc, char **argv)
{
    Mat original = imread(argv[1], IMREAD_COLOR);

    CascadeClassifier face_cascade;
    face_cascade.load("models/haar/frontalface_alt.xml");

    Ptr<Facemark> facemark = createFacemarkLBF();
    facemark->loadModel("models/lbfmodel.yaml");

    Mat img;

    inscribeInto(original, img, Size(960, 960));

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // equalizeHist( gray, gray );
    // adaptive histogram equalization
    auto cl = createCLAHE(2, Size(8, 8));
    cl->apply(gray, gray);

    std::vector<Rect> faces;
    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );
    
    std::vector< std::vector<Point2f> > landmarks;
    if (!facemark->fit(img, faces, landmarks))
    {
        std::cout << "Could not landmark any faces :(\n";
        return 0;
    }
    
    std::vector<Point2f> lm;
    scaleVector(landmarks[0], lm, (float)original.cols / (float)img.cols);

    Mat output;
    visualizeLandmarks(original, output, lm);
    imwrite("../photos/output.png", output);

    return 0;
}
