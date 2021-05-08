#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier mouth_cascade;

Mat detect(Mat frame);

int main()
{
    Mat image = imread("/mnt/c/Users/yarmo/Desktop/image.jpg", IMREAD_COLOR);

    String face_cascade_name = samples::findFile("cascades/frontalface_alt.xml");
    String eyes_cascade_name = samples::findFile("cascades/eye_tree_eyeglasses.xml");
    String mouth_cascade_name = samples::findFile("cascades/mouth.xml");

    if( !face_cascade.load( face_cascade_name ) )
    {
        std::cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        std::cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };
    if( !mouth_cascade.load( mouth_cascade_name ) )
    {
        std::cout << "--(!)Error loading mouth cascade\n";
        return -1;
    };


    imwrite("/mnt/c/Users/yarmo/Desktop/output.png", detect(image));

    return 0;
}

Mat detect(Mat frame )
{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    // std::vector<Rect> faces;
    // face_cascade.detectMultiScale( frame_gray, faces );

    // for ( size_t i = 0; i < faces.size(); i++ )
    // {
    //     Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
    //     ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );

    //     Mat faceROI = frame_gray( faces[i] );

    std::vector<Rect> eyes;
    eyes_cascade.detectMultiScale(frame_gray, eyes);

    for ( size_t j = 0; j < eyes.size(); j++ )
    {
        Point eye_center( eyes[j].x + eyes[j].width/2, eyes[j].y + eyes[j].height/2 );
        int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
        circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
    }
    
    std::vector<Rect> mouths;
    mouth_cascade.detectMultiScale(frame_gray, mouths);

    for ( size_t j = 0; j < mouths.size(); j++ )
    {
        Point mouth_center( mouths[j].x + mouths[j].width/2, mouths[j].y + mouths[j].height/2 );
        int radius = cvRound( (mouths[j].width + mouths[j].height)*0.25 );
        // circle( frame, mouth_center, radius, Scalar( 255, 0, 0 ), 4 );
        rectangle(frame, Point(mouths[j].x, mouths[j].y), Point(mouths[j].x + mouths[j].width, mouths[j].y + mouths[j].height), Scalar(255, 0, 0), 4);
    }
    // }
    return frame;
}
