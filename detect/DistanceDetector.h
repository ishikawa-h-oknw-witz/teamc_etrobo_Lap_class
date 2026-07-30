#ifndef DISTANCE_DETECTOR_H
#define DISTANCE_DETECTOR_H

#include "Motor.h"

using namespace spikeapi;

class DistanceDetector
{
public:

    DistanceDetector(
        Motor& leftMotor,
        Motor& rightMotor);

    /**
     * 走行距離計測開始
     */
    void reset();

    /**
     * 現在の走行距離取得(mm)
     */
    float getDistance();

private:

    Motor& mLeftMotor;

    Motor& mRightMotor;

    static constexpr float TIRE_DIAMETER = 56.0f;
};

#endif