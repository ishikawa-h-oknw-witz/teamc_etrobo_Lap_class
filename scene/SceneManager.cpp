#include "SceneManager.h"

enum class JudgeType
{
    Distance,
    Angle,
    Color
};

struct Section
{
    int speed;
    float kp;
    float ki;
    float kd;

    JudgeType judgeType;

    int targetDistance;
    //float targetAngle;
    //Color targetColor;
};

// {速度, Kp, Ki, Kd, 判定種類, 目標距離, 目標角度, 目標色}
Section sections[] = {
    {100, 0.6, 0.0, 0.2, JudgeType::Distance,  600}, // 区間1
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance,  900}, // 区間2
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, 1400}, // 区間3
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance, 1700}, // 区間4
    {100, 0.5, 0.0, 0.2, JudgeType::Distance, 2100}, // 区間5
    { 70, 0.6, 0.0, 0.4, JudgeType::Distance, 2600}, // 区間6
    { 70, 0.5, 0.0, 0.4, JudgeType::Distance, 4400}, // 区間7
    {100, 0.6, 0.0, 0.2, JudgeType::Distance, 5400}  // 区間8
};

//コンストラクタ
SceneManager::SceneManager(
    LineTraceRunner& lineTraceRunner,
    GyroTraceRunner& gyroTraceRunner,
    PIDCalculator& pidCalculator,
    TrapezoidCalculator& trapezoidCalculator,
    TargetDistanceDetector& targetDistanceDetector)
    : mLineTraceRunner(lineTraceRunner),
      mGyroTraceRunner(gyroTraceRunner),
      mPIDCalculator(pidCalculator),
      mTrapezoidCalculator(trapezoidCalculator),
      mTargetDistanceDetector(targetDistanceDetector)
{
}

void SceneManager::setParameter(int sceneId)
{
    mSceneId = sceneId;

    const Section& section = sections[sceneId];

    // ライントレース
    mLineTraceRunner.setBaseSpeed(section.speed);

    // ジャイロトレース(ラリーで必要)

    // PID
    mPIDCalculator.setGain(
        section.kp,
        section.ki,
        section.kd);

    switch (section.judgeType)
    {
    case JudgeType::Distance:
        // シーン終了距離
        mTargetDistanceDetector.setTargetDistance(section.targetDistance);
        mEventDetector = &mTargetDistanceDetector;
        break;
        
    default:
        break;
    }
    // 台形制御(ラリーで必要)
}

bool SceneManager::isSceneFinished()
{
    return mEventDetector->judge();
}