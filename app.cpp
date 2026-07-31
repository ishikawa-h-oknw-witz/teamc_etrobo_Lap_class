//攻略パッケージ
#include "app.h"
//シーンパッケージ
#include "SceneManager.h"
//制御パッケージ            
#include "LineTraceRunner.h"
#include "GyroTraceRunner.h"
//演算パッケージ
#include "PIDCalculator.h"
#include "TrapezoidCalculator.h"
#include "DistanceCalculator.h"
//デバイスパッケージ
#include "Motor.h"
#include "ForceSensor.h" 
#include "ColorSensor.h"
//ログ用
#include "Logger.h"
//タスク系
#include "kernel.h"   
#include "kernel_cfg.h"

using namespace spikeapi;

/* インスタンス生成 */
Motor leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true);
Motor rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);
ForceSensor forceSensor(EPort::PORT_D);
ColorSensor colorSensor(EPort::PORT_E);

PIDCalculator pidCalculator;
TrapezoidCalculator trapezoidCalculator;
DistanceCalculator distanceCalculator(leftWheel, rightWheel);

LineTraceRunner lineTraceRunner(leftWheel, rightWheel, colorSensor, pidCalculator);
GyroTraceRunner gyroTraceRunner(leftWheel, rightWheel, distanceCalculator, pidCalculator, trapezoidCalculator);

TargetDistanceDetector targetDistanceDetector(distanceCalculator);
SceneManager sceneManager(lineTraceRunner, gyroTraceRunner, pidCalculator, trapezoidCalculator, targetDistanceDetector, distanceCalculator);

Logger logger(colorSensor, leftWheel, rightWheel);
/* インスタンス生成ここまで */

/* ログタスク */
void logger_task(intptr_t exinf)
{
    logger.output();
    ext_tsk();
}

/* メインタスク */
void main_task(intptr_t exinf)
{
    /* Bluetooth初期化＆接続待ち＆ログタスク起動100msec周期 */
    logger.init();
    sta_cyc(LOGGER_TASK_CYC);

    //フォースセンサボタン押下待ち
    while (!forceSensor.isTouched());

    //HSV構造体定義
    ColorSensor::HSV hsv;

    //メインループ10msec周期
    while(true)
    {
        //HSV取得
        colorSensor.getHSV(hsv);

        sceneManager.setSceneID(0);
        if(sceneManager.SceneExecute())
        {
            break;
        }

        // 青検知
        if (hsv.h >= 200 && hsv.h <= 260 &&
            hsv.s >= 50 &&
            hsv.v >= 20)
        {
            Logger::printf("青検知");
            leftWheel.stop();
            rightWheel.stop();
            break;
        }
        Logger::printf("ループ");
        tslp_tsk(10 * 1000);
    }
    ext_tsk(); 
}


