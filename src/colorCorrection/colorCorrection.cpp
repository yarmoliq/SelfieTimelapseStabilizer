#include "colorCorrection.h"

void imageStats(const Mat &image, Scalar &lMean, Scalar &aMean, Scalar &bMean, Scalar &lStd, Scalar &aStd, Scalar &bStd)
{
    std::vector<Mat> chanels;
    split(image, chanels);
    meanStdDev(chanels[0], lMean, lStd);
    meanStdDev(chanels[1], aMean, aStd);
    meanStdDev(chanels[2], bMean, bStd);
}

void normalize(Mat &array, Mat &out, const bool minMaxNormalization)
{
    double min, max;
    if (minMaxNormalization)
    {
        minMaxIdx(array, &min, &max);
        double minA = min > 0 ? min : 0;
        double maxA = max < 255 ? max : 255;
        if (min < 0 || max > 255)
        {
            out = (maxA - minA) * (array - min) / (max - min) + minA;
        }
        else
        {
            out = array;
        }
    }
    else
    {
        min = 0;
        max = 255;
        // adaptiveAlignment(array, out);
        normalize(array, out, min, max, NORM_MINMAX);
    }
}

void colorCorrection(Mat &target, Mat &source, Mat &out, const bool minMaxNormalization, const bool preservePaper)
{
    cvtColor(source, source, COLOR_BGR2Lab);
    cvtColor(target, target, COLOR_BGR2Lab);

    Scalar lMeanSrc, aMeanSrc, bMeanSrc, lStdSrc, aStdSrc, bStdSrc;
    imageStats(source, lMeanSrc, aMeanSrc, bMeanSrc, lStdSrc, aStdSrc, bStdSrc);

    Scalar lMeanTarget, aMeanTarget, bMeanTarget, lStdTarget, aStdTarget, bStdTarget;
    imageStats(target, lMeanTarget, aMeanTarget, bMeanTarget, lStdTarget, aStdTarget, bStdTarget);

    std::vector<Mat> chanelsTarget;
    split(target, chanelsTarget);

    chanelsTarget[0] -= lMeanTarget;
    chanelsTarget[1] -= aMeanTarget;
    chanelsTarget[2] -= bMeanTarget;

    if (preservePaper)
    {
        // scale by the standard deviations using paper proposed factor
        multiply(chanelsTarget[0], (lStdTarget / lStdSrc), chanelsTarget[0]);
        multiply(chanelsTarget[1], (aStdTarget / aStdSrc), chanelsTarget[1]);
        multiply(chanelsTarget[2], (bStdTarget / bStdSrc), chanelsTarget[2]);
    }
    else
    {
        // scale by the standard deviations using reciprocal of paper proposed factor
        multiply(chanelsTarget[0], (lStdSrc / lStdTarget), chanelsTarget[0]);
        multiply(chanelsTarget[1], (aStdSrc / aStdTarget), chanelsTarget[1]);
        multiply(chanelsTarget[2], (bStdSrc / bStdTarget), chanelsTarget[2]);
    }

    chanelsTarget[0] += lMeanSrc;
    chanelsTarget[1] += aMeanSrc;
    chanelsTarget[2] += bMeanSrc;

    // clip/scale the pixel intensities to [0, 255] if they fall
    // outside this range
    normalize(chanelsTarget[0], chanelsTarget[0], minMaxNormalization);
    normalize(chanelsTarget[1], chanelsTarget[1], minMaxNormalization);
    normalize(chanelsTarget[2], chanelsTarget[2], minMaxNormalization);

    //create  out mat and merge all convert color
    out = Mat(target.size(), target.type());
    merge(chanelsTarget, out);
    cvtColor(out, out, COLOR_Lab2BGR);
}