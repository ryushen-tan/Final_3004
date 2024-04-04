#ifndef SESSIONINFO_H
#define SESSIONINFO_H


class SessionInfo
{
public:
    SessionInfo();
    float baselineBefore;
    float baselineAfter;
    void endSession();
};

#endif // SESSIONINFO_H
