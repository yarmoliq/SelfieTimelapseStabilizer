#include "colorCorrection.h"

void imageStats(const Mat &image, Scalar &lMean, Scalar &aMean, Scalar &bMean, Scalar &lStd, Scalar &aStd, Scalar &bStd)
{
    std::vector<Mat> chanels;
    split(image, chanels);
    meanStdDev(chanels[0], lMean, lStd);
    meanStdDev(chanels[1], aMean, aStd);
    meanStdDev(chanels[2], bMean, bStd);
}

void fixExtremValues(Mat &image, Mat &out, const bool adaptiveRange)
{
    double min, max;

    minMaxIdx(image, &min, &max);
    if (!adaptiveRange || min < 0 || max > 255)
    {
        double minA = min > 0 ? min : 0;
        double maxA = max < 255 ? max : 255;
        out = (maxA - minA) * (image - min) / (max - min) + minA;
    }
    else
    {
        out = image;
        for (int i = 0; i < out.size().width; ++i)
        {
            for (int j = 0; j < out.size().height; ++j)
            {
                auto &colors = out.at<Vec3f>(i, j);
                for (int k = 0; k < colors.rows; ++k)
                {
                    if (colors[k] > 255)
                    {
                        colors[k] = 255;
                    }
                    else if (colors[k] < 0)
                    {
                        colors[k] = 0;
                    }
                }
            }
        }
    }
}

// variables with _ is locally
void colorCorrection(Mat &target, Mat &source, Mat &out, const bool adaptiveRange, const bool preservePaper)
{
    cvtColor(source, source, COLOR_BGR2Lab);
    cvtColor(target, target, COLOR_BGR2Lab);
    Mat source_ = Mat(source.size(), CV_32F);
    source.convertTo(source_, CV_32F);
    Mat target_ = Mat(target.size(), CV_32F);
    target.convertTo(target_, CV_32F);

    colorCorrectionWithoutConversion(target_, target_, source_, out, adaptiveRange, preservePaper);
}

void colorCorrection(const Mat &target, Mat &face, Mat &source, Mat &out, const bool adaptiveRange, const bool preservePaper)
{
    cvtColor(source, source, COLOR_BGR2Lab);
    cvtColor(face, face, COLOR_BGR2Lab);
    cvtColor(target, target, COLOR_BGR2Lab);
    Mat source_ = Mat(source.size(), CV_32F);
    source.convertTo(source_, CV_32F);
    Mat face_ = Mat(face.size(), CV_32F);
    face.convertTo(face_, CV_32F);
    Mat target_ = Mat(target.size(), CV_32F);
    target.convertTo(target_, CV_32F);

    colorCorrectionWithoutConversion(target_, face_, source_, out, adaptiveRange, preservePaper);
}

void colorCorrectionWithoutConversion(Mat &target, Mat &face, Mat &source, Mat &out, const bool adaptiveRange, const bool preservePaper)
{
    Scalar lMeanSrc, aMeanSrc, bMeanSrc, lStdSrc, aStdSrc, bStdSrc;
    imageStats(source, lMeanSrc, aMeanSrc, bMeanSrc, lStdSrc, aStdSrc, bStdSrc);

    Scalar lMeanTarget, aMeanTarget, bMeanTarget, lStdTarget, aStdTarget, bStdTarget;
    imageStats(face, lMeanTarget, aMeanTarget, bMeanTarget, lStdTarget, aStdTarget, bStdTarget);

    std::vector<Mat> chanelsTarget;
    split(target, chanelsTarget);

    chanelsTarget[0] -= lMeanTarget;
    chanelsTarget[1] -= aMeanTarget;
    chanelsTarget[2] -= bMeanTarget;

    if (!preservePaper)
    {
        // scale by the standard deviations using paper proposed factor
        multiply(chanelsTarget[0], (lStdTarget[0] / lStdSrc[0]), chanelsTarget[0]);
        multiply(chanelsTarget[1], (aStdTarget[0] / aStdSrc[0]), chanelsTarget[1]);
        multiply(chanelsTarget[2], (bStdTarget[0] / bStdSrc[0]), chanelsTarget[2]);
    }
    else
    {
        // scale by the standard deviations using reciprocal of paper proposed factor
        chanelsTarget[0] = (lStdSrc[0] / lStdTarget[0]) * chanelsTarget[0];
        chanelsTarget[1] = (aStdSrc[0] / aStdTarget[0]) * chanelsTarget[1];
        chanelsTarget[2] = (bStdSrc[0] / bStdTarget[0]) * chanelsTarget[2];
    }

    chanelsTarget[0] += lMeanSrc;
    chanelsTarget[1] += aMeanSrc;
    chanelsTarget[2] += bMeanSrc;

    // clip/scale the pixel intensities to [0, 255] if they fall
    // outside this range
    fixExtremValues(chanelsTarget[0], chanelsTarget[0], adaptiveRange);
    fixExtremValues(chanelsTarget[1], chanelsTarget[1], adaptiveRange);
    fixExtremValues(chanelsTarget[2], chanelsTarget[2], adaptiveRange);

    //create  out mat and merge all convert color
    out = Mat(target.size(), target.type());
    merge(chanelsTarget, out);
    //out = Mat(target.size(), CV_8UC3);
    out.convertTo(out, CV_8U);
    cvtColor(out, out, COLOR_Lab2BGR);
}
