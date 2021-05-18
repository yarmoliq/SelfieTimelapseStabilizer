#include "manipulation.h"

#include <algorithm>

void inscribeInto(InputArray src, OutputArray dst, const Size& size)
{
    if(!(src.cols() > size.width or src.rows() > size.height))
    {
        src.copyTo(dst);
        return;
    }

    float k = std::min((float)size.width / (float)src.cols(), (float)size.height / (float)src.rows());

    resize(src, dst, Size(), k, k, INTER_AREA);
}

void scaleVector(const std::vector<Point2f>& inVec, std::vector<Point2f>& outVec, float k)
{
    outVec.assign(inVec.begin(), inVec.end());
    for(Point2f& point: outVec)
    {
        point.x *= k;
        point.y *= k;
    }
}
