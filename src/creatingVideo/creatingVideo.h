#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <filesystem>

using namespace cv;
using namespace std;

void createVideo(const String& name, const vector<Mat>& images, Size size, int videoTime);

void createVideoWritter(VideoWriter& video, const String &name, Size size, int fps);

void addImageToVideo(VideoWriter &video, const Mat &image);

void renderVideo(VideoWriter &video);