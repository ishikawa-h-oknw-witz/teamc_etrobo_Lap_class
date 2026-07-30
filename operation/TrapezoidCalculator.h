#ifndef TRAPEZOID_CALCULATOR_H
#define TRAPEZOID_CALCULATOR_H

class TrapezoidCalculator
{
public:
    TrapezoidCalculator();

    void setParameter(
        int startSpeed,
        int maxSpeed,
        int endSpeed,
        float accelDistance,
        float decelDistance);

    int getSpeed(float currentDistance, float totalDistance);

private:
    int mStartSpeed;
    int mMaxSpeed;
    int mEndSpeed;

    float mAccelDistance;
    float mDecelDistance;
};

#endif