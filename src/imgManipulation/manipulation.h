#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>

using namespace cv;

// inscribes image into a rectangle of the given size
// returns src if smaller than the given size
void inscribeInto(InputArray src, OutputArray dst, const Size& size);

void scaleVector(const std::vector<Point2f>& inVec, std::vector<Point2f>& outVec, float k);
