#ifndef PID_CALCULATOR_H
#define PID_CALCULATOR_H

class PIDCalculator
{
public:
    PIDCalculator();
    
    void setGain(float kp, float ki, float kd);
    
    float calculate(float error);

    void reset();
 
private:
    float mKp;
    float mKi;
    float mKd;
 
    float mIntegral;
 
    float mPreviousError;
};
 
#endif