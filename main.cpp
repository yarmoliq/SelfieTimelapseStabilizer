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
    CascadeClassifier face_cascade;
    face_cascade.load("models/haar/frontalface_alt.xml");

    Mat img = imread(argv[1]);
    Ptr<Facemark> facemark = createFacemarkKazemi();
    facemark->loadModel("models/face_landmark_model.dat");

    std::vector<Rect> faces;
    // resize(img,img,Size(460,460),0,0,INTER_LINEAR_EXACT);

    Mat gray;
    if(img.channels()>1){
        cvtColor(img, gray, COLOR_BGR2GRAY);
    }
    else{
        gray = img.clone();
    }

    equalizeHist( gray, gray );
    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );

    std::vector< std::vector<Point2f> > shapes;
    if (facemark->fit(img,faces,shapes))
    {
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            rectangle(img,faces[i], Scalar( 255, 0, 0 ), 4);
        }
        for (unsigned long i=0;i<faces.size();i++)
        {
            for(unsigned long k=0;k<shapes[i].size();k++)
                circle(img, shapes[i][k], 5, Scalar(0,0,255), 4);
        }
    }

    imwrite("../output.png", img);

    return 0;
}
