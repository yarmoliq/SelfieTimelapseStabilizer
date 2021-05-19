#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/mcc.hpp>
#include <vector>
#include "adaptivePhotoAlignment.h"

using namespace cv;
using namespace std;
using namespace mcc;
using namespace ccm;

//apply color correction to image
//target - mat for correction
//source - template for correction
//out - result
//minMaxNormalization - set normalization format
//preservePaper - should color transfer strictly follow methodology
//      layed out in original paper? The method does not always produce
//      aesthetically pleasing results.
//      If False then target chanels will scaled using the reciprocal of
//      the scaling factor proposed in the paper.
void colorCorrection(Mat &target, Mat &source, Mat &out, bool minMaxNormalization = false, bool preservePaper = true);

//normalization array
void normalize(Mat &array, Mat &out, bool minMaxNormalization = true);

//get information about image
void imageStats(const Mat &image, Scalar &lMean, Scalar &aMean, Scalar &bMean, Scalar &lStd, Scalar &aStd, Scalar &bStd);