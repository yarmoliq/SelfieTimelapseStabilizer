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

using namespace cv;
using namespace face;

const unsigned int OUTPUT_WIDTH  = 3840;
const unsigned int OUTPUT_HEIGHT = 2160;

int main(int argc, char **argv)
{
    Mat img = imread(argv[1], IMREAD_UNCHANGED);

    CascadeClassifier face_cascade;
    face_cascade.load("models/haar/frontalface_alt.xml");

    Ptr<Facemark> facemark = createFacemarkKazemi();
    facemark->loadModel("models/face_landmark_model.dat");

    // resize(img,img,Size(960,960),0,0,INTER_LINEAR_EXACT);

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
    
    std::vector<Point2f> lm = landmarks[0];
    auto output = visualizeLandmarks(img, lm);
    imwrite("../photos/output.png", output);

    return 0;
}
