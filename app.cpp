//攻略パッケージ
#include "app.h"
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

void runGate(int gateNo);   //基準点通過番号を引数にゲート通過から帰還までを行う
void runTopRow(int No);     //横ゲート通過処理　ゲート通過番号①～④
void runMiddleRow(int No);  //縦ゲート通過処理　ゲート通過番号⑤～⑨
void runBottomRow(int No);  //横ゲート通過処理　ゲート通過番号⑩～⑬
void runBasePointToQr();    //基準点から1つ目のQRまでの走行を行う
void runQrToBasePoint();    //1つ目のQRから基準点までの走行を行う
void runQrToQr(int cell);   //QRからQRまでの走行を行う、引数で何マス分進むかを指定
void passGate();            //ゲートを通過して、通過前の場所に戻ってくるまでの走行を行う
void middle_passGate();     //縦ゲート用の通過処理

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

    //フォースセンサボタン押下待ち
    while (!forceSensor.isTouched());

    //HSV構造体定義
    ColorSensor::HSV hsv;

    //メインループ10msec周期
    while(true)
    {
        //HSV取得
        colorSensor.getHSV(hsv);
        //ライントレース走行開始
        lineTraceRunner.run();
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
        tslp_tsk(10 * 1000);
    }
    ext_tsk(); 
}

void runGate(int gateNo)
{
    switch(gateNo)
    {
        case 1:
            // ゲート①攻略
            runTopRow(0);
            break;

        case 2:
            // ゲート②攻略
            runTopRow(1);
            break;

        case 3:
            // ゲート③攻略
            runTopRow(2);
            break;

        case 4:
            // ゲート④攻略
            runTopRow(3);
            break;

        case 5:
            // ゲート⑤攻略
            runMiddleRow(0);
            break;

        case 6:
            // ゲート⑥攻略
            runMiddleRow(1);
            break;

        case 7:
            // ゲート⑦攻略
            runMiddleRow(2);
            break;

        case 8:
            // ゲート⑧攻略
            runMiddleRow(3);
            break;

        case 9:
            // ゲート⑨攻略
            runMiddleRow(4);
            break;

        case 10:
            // ゲート⑩攻略
            runBottomRow(0);
            break;

        case 11:
            // ゲート⑪攻略
            runBottomRow(1);
            break;

        case 12:
            // ゲート⑫攻略
            runBottomRow(2);
            break;

        case 13:
            // ゲート⑬攻略
            runBottomRow(3);
            break;

        default:
            // 不正なゲート番号
            break;
    }
}

//横ゲート通過処理　ゲート通過番号①～④
void runTopRow(int No)
{
    runBasePointToQr();
    runQrToQr(No);
    gyroTraceRunner.turn(-90);
    tslp_tsk(100000);
    passGate();
    gyroTraceRunner.turn(-90);
    tslp_tsk(100000);
    runQrToQr(No);
    runQrToBasePoint();
}

//縦ゲート通過処理　ゲート通過番号⑤～⑨
void runMiddleRow(int No)
{
    runBasePointToQr();
    runQrToQr(No);
    middle_passGate();
    gyroTraceRunner.turn(-180);
    tslp_tsk(100000);
    runQrToQr(No);
    runQrToBasePoint();
}

//横ゲート通過処理　ゲート通過番号⑩～⑬
void runBottomRow(int No)
{
    runBasePointToQr();
    runQrToQr(No);
    gyroTraceRunner.turn(90);
    tslp_tsk(100000);
    passGate();
    gyroTraceRunner.turn(90);
    tslp_tsk(100000);
    runQrToQr(No);
    runQrToBasePoint();
}

void runBasePointToQr()
{
    gyroTraceRunner.move(true, 260);
}

void runQrToBasePoint()
{
    gyroTraceRunner.move(true, 260);
}

void runQrToQr(int cell)
{
    gyroTraceRunner.move(true, 250*cell);
}

void passGate()
{
    gyroTraceRunner.move(true, 260);
    tslp_tsk(100*1000);
    gyroTraceRunner.move(false, 260);
}

void middle_passGate()
{
    gyroTraceRunner.move(true, 130);
    tslp_tsk(100*1000);
    gyroTraceRunner.move(false, 130);
}


