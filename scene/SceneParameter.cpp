#include "SceneParameter.h"

//{走行速度, 比例ゲイン, 積分ゲイン, 微分ゲイン}
Section sections[] = {
    {100, 0.6, 0.0, 0.2}, //区間１　直進　約60cm
    {70, 0.6, 0.0, 0.4},  //区間２　緩やかなカーブ　約30cm
    {100, 0.6, 0.0, 0.2},   //区間３　直進　約50cm
    {70, 0.6, 0.0, 0.4},  //区間４　緩やかなカーブ　約30cm
    {100, 0.5, 0.0, 0.2},  //区間５　直進　約40cm
    {70, 0.6, 0.0, 0.4}, //区間６　緩やかなカーブ　約30cm
    {70, 0.5, 0.0, 0.4},  //区間７　蛇行　約180cm
    {100, 0.6, 0.0, 0.2}   //区間８　直進　約100cm
};

//コンストラクタ
SceneParameter::SceneParameter(
    LineTraceRunner& linetraceRunner,
    GyroTraceRunner& gyrotraceRunner,
    PIDCalculate& pidCalculate,
    TrapezoidCalculator& trapezoidCalculator)
    : mLineTraceRunner(linetraceRunner),
      mGyroTraceRunner(gyrotraceRunner),
      mPIDCalculate(pidCalculate),
      mTrapezoidCalculate(trapezoidCalculate)
{
}

void SceneParameter::setParameter(int scene_id)
{
    const Section& section = sections[scene_id];

    // ライントレース走行
    mLineTraceRunner.setBaseSpeed(section.speed);

    // ジャイロトレース走行
    //mGyroTraceRunner.setBaseSpeed(section.speed);

    // PID
    mPIDCalculate.setGain(
        section.kp,
        section.ki,
        section.kd
    );

    // 台形制御（ラリーで必要）

}