#include "manipulation.h"

Point2f referenceLandmarks[3];

const size_t LM1 = 36;
const size_t LM2 = 45;
const size_t LM3 = 57;

CascadeClassifier face_cascade;
Ptr<Facemark> facemark = createFacemarkLBF();

void loadModels()
{
    face_cascade.load("models/haar/frontalface_alt.xml");

    facemark->loadModel("models/lbfmodel.yaml");
}

void warpStabilize(const Mat& src, Mat& dst)
{
    std::vector<Point2f> landmarks;
    calculateLandmarks(src, landmarks);

    Point2f srcTri[3] =
    {
        landmarks[LM1],
        landmarks[LM2],
        landmarks[LM3]
    };

    Mat warp_mat = getAffineTransform( srcTri, referenceLandmarks );

    warpAffine( src, dst, warp_mat, dst.size() );
}

void setReferencePoints(const Mat& reference)
{
    std::vector<Point2f> landmarks;
    calculateLandmarks(reference, landmarks);

    referenceLandmarks[0] = landmarks[LM1];
    referenceLandmarks[1] = landmarks[LM2];
    referenceLandmarks[2] = landmarks[LM3];
}

void calculateLandmarks(const Mat& src, std::vector<Point2f>& output)
{
    Mat reduced;
    inscribeInto(src, reduced, Size(960, 960));

    Mat gray;
    cvtColor(reduced, gray, COLOR_BGR2GRAY);

    auto cl = createCLAHE(2, Size(8, 8));
    cl->apply(gray, gray);

    std::vector<Rect> faces;
    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );
    
    std::vector< std::vector<Point2f> > landmarks;
    if (!facemark->fit(reduced, faces, landmarks))
    {
        // std::cout << "Could not landmark any faces :(\n";
        return;
    }
    
    // std::vector<Point2f> lm = landmarks[0];
    scaleVector(landmarks[0], output, (float)src.cols / (float)reduced.cols);
}
