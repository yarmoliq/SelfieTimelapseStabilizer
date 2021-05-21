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
void colorCorrection(Mat &target, Mat &source, Mat &out, bool adaptiveRange = false, bool preservePaper = true);

//fix min and max values in image
//if adaptiveRange is false, range = [0, 255]
//if adaptiveRange is false, range = [min or if min < 0 is 0, max of if max > 255 is 255]
void fixExtremValues(Mat &image, Mat &out, bool adaptiveRange = false);

//get information about image
void imageStats(const Mat &image, Scalar &lMean, Scalar &aMean, Scalar &bMean, Scalar &lStd, Scalar &aStd, Scalar &bStd);