#ifndef SESSIONINFO_H
#define SESSIONINFO_H

/* Purpose of class: SessionInfo to store the baseline values before and after the session
 *
 * Data Members:
 * - double baselineBefore: To store the baseline value before the session
 * - double baselineAfter: To store the baseline value after the session
 * 
 * Class functions:
 * - SessionInfo(): Constructor to initialize the SessionInfo object
 * - getBaselineBefore(): Getter to get the baseline value before the session
 * - getBaselineAfter(): Getter to get the baseline value after the session
 * - setBaselineBefore(double): Setter to set the baseline value before the session
 * - setBaselineAfter(double): Setter to set the baseline value after the session
 */

class SessionInfo
{
public:
    SessionInfo();

    double getBaselineBefore() const;
    double getBaselineAfter() const;

    void setBaselineBefore(double);
    void setBaselineAfter(double);
private:
    double baselineBefore;
    double baselineAfter;
};

#endif // SESSIONINFO_H
