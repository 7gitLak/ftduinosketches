#include <FtduinoSimple.h>

void setup() {   
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
  pinMode ( LED_BUILTIN , OUTPUT ) ;
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
    oneStepBase(Ftduino::I1, Ftduino::I2, Ftduino::RIGHT, Ftduino::RIGHT);
}

void oneStepBack() {
    oneStepBase(Ftduino::I1, Ftduino::I2, Ftduino::LEFT, Ftduino::LEFT);
}

void oneStepLeft() {
    oneStepBase(Ftduino::I3, Ftduino::I4, Ftduino::LEFT, Ftduino::RIGHT);
}

void oneStepRight() {
    oneStepBase(Ftduino::I3, Ftduino::I4, Ftduino::RIGHT, Ftduino::LEFT);
}

void oneStepBase(uint8_t ch1, uint8_t ch2, uint8_t mode1, uint8_t mode2) {
  bool bInit1 = ftduino.input_get(ch1);
  bool bInit2 = ftduino.input_get(ch2);  
  bool bCurrent1 = bInit1;
  bool bCurrent2 = bInit2;  
  
  ftduino.motor_set(Ftduino::M1, mode1);
  ftduino.motor_set(Ftduino::M2, mode2);
  bool bRunning1 = true;
  bool bRunning2 = true;
  
  digitalWrite ( LED_BUILTIN , HIGH ) ;
  
  while (bRunning1 || bRunning2)
  {   
    bCurrent1 = ftduino.input_get(ch1);
    if(low2high(bInit1, bCurrent1)) {
      ftduino.motor_set(Ftduino::M1, Ftduino::BRAKE);      
      bRunning1 = false;
    }
    bInit1 = bCurrent1;
    
    bCurrent2 = ftduino.input_get(ch2);
    if(low2high(bInit2, bCurrent2)) {
      ftduino.motor_set(Ftduino::M2, Ftduino::BRAKE);      
      bRunning2 = false;
    }
    bInit2 = bCurrent2;    
  }   
  
  digitalWrite ( LED_BUILTIN , LOW ) ;  
}


void loop() { 
  oneStepForward();
  delay(500);  

}
