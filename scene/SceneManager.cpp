#include "SceneManager.h"

//{走行距離(mmまで), 走行速度, 比例ゲイン, 積分ゲイン, 微分ゲイン}
Section sections[] = {
    {600, 100, 0.6, 0.0, 0.2}, //区間１　直進　約60cm
    {900, 70, 0.6, 0.0, 0.4},  //区間２　緩やかなカーブ　約30cm
    {1400, 100, 0.6, 0.0, 0.2},   //区間３　直進　約50cm
    {1700, 70, 0.6, 0.0, 0.4},  //区間４　緩やかなカーブ　約30cm
    {2100, 100, 0.5, 0.0, 0.2},  //区間５　直進　約40cm
    {2600, 70, 0.6, 0.0, 0.4}, //区間６　緩やかなカーブ　約30cm
    {4400, 70, 0.5, 0.0, 0.4},  //区間７　蛇行　約180cm
    {5400, 100, 0.6, 0.0, 0.2}   //区間８　直進　約100cm
};

//コンストラクタ
SceneManager::SceneManager(
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

void SceneManager::setParameter(int scene_id)
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