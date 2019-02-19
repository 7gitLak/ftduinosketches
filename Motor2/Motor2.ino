#include <FtduinoSimple.h>

void setup() {   
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
  pinMode ( LED_BUILTIN , OUTPUT ) ;
}

bool isChange(const bool islow2high, const bool first, const bool second)
{
    if(low2high) {
        return low2high(first, second);
    }
    return high2low(first, second);
}

bool low2high(const bool first, const bool second)
{
  return (!first && second);
}

bool high2low(const bool first, const bool second)
{
  return (first && !second);
}

void oneStepForward() {
    oneStepBase(Ftduino::I1, Ftduino::I2, Ftduino::RIGHT, Ftduino::RIGHT, true, true);
}

void oneStepBack() {
    oneStepBase(Ftduino::I1, Ftduino::I2, Ftduino::LEFT, Ftduino::LEFT, true, true);
}

void oneStepLeft() {
    oneStepBase(Ftduino::I3, Ftduino::I4, Ftduino::LEFT, Ftduino::RIGHT, true, true);
   /* oneStepBase(Ftduino::I3, Ftduino::I2, Ftduino::BRAKE, Ftduino::RIGHT, true, true);
    oneStepBase(Ftduino::I1, Ftduino::I2, Ftduino::LEFT, Ftduino::BRAKE, false, true);*/
}

void oneStepRight() {
    oneStepBase(Ftduino::I3, Ftduino::I4, Ftduino::RIGHT, Ftduino::LEFT, true, true);
    /*oneStepBase(Ftduino::I3, Ftduino::I2, Ftduino::LEFT, Ftduino::BRAKE, true, true);
    oneStepBase(Ftduino::I1, Ftduino::I2, Ftduino::BRAKE, Ftduino::RIGHT, true, false);*/
}

void turnLeft() 
{
    oneStepBack();
    oneStepRight();
    oneStepRight();
}

void turnRight() 
{
    oneStepBack();
    oneStepLeft();
    oneStepLeft();
}

bool setMotor(uint8_t port, uint8_t mode)
{
    ftduino.motor_set(port, mode);
    if((Ftduino::LEFT == mode) || (Ftduino::RIGHT == mode)) 
    {
        return true;
    }
    return false;
}

void oneStepBase(uint8_t ch1, uint8_t ch2, uint8_t mode1, uint8_t mode2, const bool low2high1, const bool low2high2) 
{
  bool bInit1 = ftduino.input_get(ch1);
  bool bInit2 = ftduino.input_get(ch2);  
  bool bCurrent1 = bInit1;
  bool bCurrent2 = bInit2;  
  
  bool bRunning1 = setMotor(Ftduino::M1, mode1);
  bool bRunning2 = setMotor(Ftduino::M2, mode2);
  
  digitalWrite ( LED_BUILTIN , HIGH ) ;
  
  while (bRunning1 || bRunning2)
  {   
    bCurrent1 = ftduino.input_get(ch1);
    if(isChange(low2high1, bInit1, bCurrent1)) {
      bRunning1 = setMotor(Ftduino::M1, Ftduino::BRAKE);
    }
    bInit1 = bCurrent1;
    
    bCurrent2 = ftduino.input_get(ch2);
    if(isChange(low2high2, bInit2, bCurrent2)) {
      bRunning2 = setMotor(Ftduino::M2, Ftduino::BRAKE);
    }
    bInit2 = bCurrent2;    
  }   
  
  digitalWrite ( LED_BUILTIN , LOW ) ;  
}

void avoidObstacle() 
{
   if(ftduino.input_get(Ftduino::I5))
    {
        turnLeft();
    } 
   if(ftduino.input_get(Ftduino::I6))
    {
        turnRight();
    } 
}

void loop() { 
    avoidObstacle();
    oneStepForward();
    delay(200);  
}
