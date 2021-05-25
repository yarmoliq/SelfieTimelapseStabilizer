#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>

#include <vector>

using namespace cv;
using namespace face;

extern Point2f referenceLandmarks[3];

extern const size_t LM1;
extern const size_t LM2;
extern const size_t LM3;

extern CascadeClassifier face_cascade;
extern Ptr<Facemark> facemark;

void loadModels();

// inscribes image into a rectangle of the given size
// returns src if smaller than the given size
void inscribeInto(InputArray src, OutputArray dst, const Size& size);

void scaleVector(const std::vector<Point2f>& inVec, std::vector<Point2f>& outVec, float k);

void calculateLandmarks(const Mat& src, std::vector<Point2f>& output);

void setReferencePoints(const Mat& reference);

void warpStabilize(const Mat& src, Mat& dst);
