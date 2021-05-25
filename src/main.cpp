#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <math.h>
#include <filesystem>

#include "visualize/visualize.h"
#include "imgManipulation/manipulation.h"
#include "creatingVideo/creatingVideo.h"

using namespace cv;
using namespace face;
namespace fs = std::filesystem;

const unsigned int OUTPUT_WIDTH  = 3840;
const unsigned int OUTPUT_HEIGHT = 2160;

int main(int argc, char **argv)
{
    Mat reference = imread(argv[1], IMREAD_COLOR);

    loadModels();

    setReferencePoints(reference);

    Mat output(OUTPUT_HEIGHT, OUTPUT_WIDTH, CV_8UC3);

    std::string outDir = argv[3];
    fs::create_directory(outDir);
    fs::create_directory(outDir + "photos/");

    VideoWriter video;
    createVideoWritter(video, outDir + "result0.avi", Size(OUTPUT_WIDTH, OUTPUT_HEIGHT), 1);

    size_t counter = 0;
    for (const auto & entry : fs::directory_iterator(argv[2]))
    {
        Mat img = imread(entry.path(), IMREAD_COLOR);
        warpStabilize(img, output, reference);
        addImageToVideo(video, output);
        imwrite(outDir + "photos/" + std::to_string(counter++) + ".jpg", output);
    }

    renderVideo(video);
    return 0;
}
