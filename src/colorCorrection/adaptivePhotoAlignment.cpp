#include "adaptivePhotoAlignment.h"

void adaptiveAlignment(Mat& src)
{
    // Split the image into different channels
    std::vector<Mat> rgbChannels = std::vector<Mat>(3);
    split(src, rgbChannels);

    // Apply aligment
    auto cl = createCLAHE(2, Size(8, 8));
    cl->apply(rgbChannels[0], rgbChannels[0]);
    cl->apply(rgbChannels[1], rgbChannels[1]);
    cl->apply(rgbChannels[2], rgbChannels[2]);

    // Merging chanels
    merge(rgbChannels, src);
}