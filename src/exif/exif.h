#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
// #include <opencv2/core/types.hpp>

#include <exiv2/exiv2.hpp>

#include <string>

using namespace cv;

enum ImageOrientation
{
    IMAGE_ORIENTATION_TL = 1, ///< Horizontal (normal)
    IMAGE_ORIENTATION_TR = 2, ///< Mirrored horizontal
    IMAGE_ORIENTATION_BR = 3, ///< Rotate 180
    IMAGE_ORIENTATION_BL = 4, ///< Mirrored vertical
    IMAGE_ORIENTATION_LT = 5, ///< Mirrored horizontal & rotate 270 CW
    IMAGE_ORIENTATION_RT = 6, ///< Rotate 90 CW
    IMAGE_ORIENTATION_RB = 7, ///< Mirrored horizontal & rotate 90 CW
    IMAGE_ORIENTATION_LB = 8  ///< Rotate 270 CW
};

void applyExifOrientation(const std::string& filename, Mat& img);

ImageOrientation getImageOrientatino(const std::string& filename);
