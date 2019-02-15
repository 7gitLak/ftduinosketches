#include <FtduinoSimple.h>

void setup() {   
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
  pinMode ( LED_BUILTIN , OUTPUT ) ;
}

bool low2high(const bool init, const bool current)
{
  return (!init && current);
}

void oneStep() {
  bool bInit1 = ftduino.input_get(Ftduino::I1);
  bool bInit2 = ftduino.input_get(Ftduino::I2);  
  bool bCurrent1 = bInit1;
  bool bCurrent2 = bInit2;  
  
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
  ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
  bool bRunning1 = true;
  bool bRunning2 = true;
  
  digitalWrite ( LED_BUILTIN , HIGH ) ;
  
  while (bRunning1 || bRunning2)
  {   
    bCurrent1 = ftduino.input_get(Ftduino::I1);
    if(low2high(bInit1, bCurrent1)) {
      ftduino.motor_set(Ftduino::M1, Ftduino::BRAKE);      
      bRunning1 = false;
    }
    bInit1 = bCurrent1;
    
    bCurrent2 = ftduino.input_get(Ftduino::I2);
    if(low2high(bInit2, bCurrent2)) {
      ftduino.motor_set(Ftduino::M2, Ftduino::BRAKE);      
      bRunning2 = false;
    }
    bInit2 = bCurrent2;    
  }   
  
  digitalWrite ( LED_BUILTIN , LOW ) ;  
}


void loop() { 
  oneStep();
  delay(500);  

}
