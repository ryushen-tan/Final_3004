#include "SessionInfo.h"

SessionInfo::SessionInfo() : 
    baselineBefore(0.0), 
    baselineAfter(0.0) 
{
}

double SessionInfo::getBaselineBefore() const
{
    return baselineBefore;
}

double SessionInfo::getBaselineAfter() const
{
    return baselineAfter;
}

void SessionInfo::setBaselineBefore(double baseline)
{
    baselineBefore = baseline;
}

void SessionInfo::setBaselineAfter(double baseline)
{
    baselineAfter = baseline;
}
