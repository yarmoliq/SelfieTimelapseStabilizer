#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

Mat visualizeLandmarks(const Mat& src,  const std::vector<Point2f>& landmarks);
