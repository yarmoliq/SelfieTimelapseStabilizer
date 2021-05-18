#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <iostream>

#include "src/colorCorrection/adaptivePhotoAlignment.h"

using namespace cv;
using namespace face;

int main(int argc, char **argv)
{
    Mat img = imread(argv[1]);
    adaptiveAlignment(img);
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
    
    std::vector< std::vector<Point2f> > shapes;
    if (!facemark->fit(img, faces, shapes))
    {
        std::cout << "Could not landmark any faces :(\n";
        return 0;
    }
    
    //color correction

    for (size_t i = 0; i < faces.size(); ++i)
    {
        rectangle(img,faces[i], Scalar( 255, 0, 0 ), 4);
    }

    for (unsigned long i = 0; i < faces.size(); ++i)
    {
        for(unsigned long k = 0; k < shapes[i].size(); ++k)
            circle(img, shapes[i][k], 5, Scalar(0,0,255), 4);
    }

    imwrite("../photos/output.png", img);

    return 0;
}
