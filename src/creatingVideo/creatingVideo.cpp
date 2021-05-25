#include "creatingVideo.h"

void createVideo(const String &name, const vector<Mat> &images, Size size, int videoTime)
{
    VideoWriter video;
    createVideoWritter(video, name, size, videoTime/images.size());

    for (const auto &image : images)
    {
        addImageToVideo(video, image);
    }
    renderVideo(video);
}

void createVideoWritter(VideoWriter& video, const String &name, Size size, int fps)
{
    video.open(name, VideoWriter::fourcc('M','J','P','G'), fps, size);
}

void addImageToVideo(VideoWriter &video, const Mat &image)
{
    video.write(image);
}

void renderVideo(VideoWriter &video)
{
    video.release();
}