#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdlib.h>

#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

bool isHost = false;
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
void ProcessCommand(String commandString);
void CreateRandomCommandString(char *s, const int len);
MeRGBLed rgbled_7(7, 7==7?2:4);
MeIR ir;
int amountOfCommands = 10;

void SeperateAndExecuteCommands(String commandString)
{
  for(int i = commandString.length() - 1; i > -1; i--)
  {
    ProcessCommand(commandString[i]);
  }
}

void ProcessCommand(char command)
{
    if(command == 'a'){
        motor_9.run((9)==M1?-(-255):(-255));
        motor_10.run((10)==M1?-(255):(255));
        _delay(1);
        motor_9.run((9)==M1?-(255):(255));
        motor_10.run((10)==M1?-(-255):(-255));
        _delay(1);
        motor_9.run((9)==M1?-(0):(0));
        motor_10.run((10)==M1?-(0):(0));
    }
    
    if(command == 'b'){
        motor_9.run((9)==M1?-(255):(255));
        motor_10.run((10)==M1?-(-255):(-255));
        _delay(1);
        motor_9.run((9)==M1?-(-255):(-255));
        motor_10.run((10)==M1?-(255):(255));
        _delay(1);
        motor_9.run((9)==M1?-(0):(0));
        motor_10.run((10)==M1?-(0):(0));
    }
    
    if(command == 'c'){
        motor_9.run((9)==M1?-(255):(255));
        motor_10.run((10)==M1?-(255):(255));
        _delay(1);
        motor_9.run((9)==M1?-(-255):(-255));
        motor_10.run((10)==M1?-(-255):(-255));
        _delay(1);
        motor_9.run((9)==M1?-(0):(0));
        motor_10.run((10)==M1?-(0):(0));
    }
    
    if(command == 'd'){
        motor_9.run((9)==M1?-(50):(50));
        motor_10.run((10)==M1?-(-50):(-50));
        _delay(0.5);
        motor_9.run((9)==M1?-(-100):(-100));
        motor_10.run((10)==M1?-(100):(100));
        _delay(0.5);
        motor_9.run((9)==M1?-(100):(100));
        motor_10.run((10)==M1?-(-100):(-100));
        _delay(0.5);
        motor_9.run((9)==M1?-(-50):(-50));
        motor_10.run((10)==M1?-(50):(50));
        _delay(0.5);
        motor_9.run((9)==M1?-(0):(0));
        motor_10.run((10)==M1?-(0):(0));
    }
    
    if(command == 'e'){
        motor_9.run((9)==M1?-(100):(100));
        motor_10.run((10)==M1?-(-100):(-100));
        _delay(0.5);
        motor_9.run((9)==M1?-(255):(255));
        motor_10.run((10)==M1?-(255):(255));
        _delay(1);
        motor_9.run((9)==M1?-(-255):(-255));
        motor_10.run((10)==M1?-(-255):(-255));
        _delay(1);
        motor_10.run((10)==M1?-(100):(100));
        motor_9.run((9)==M1?-(-100):(-100));
        _delay(0.5);
        motor_9.run((9)==M1?-(0):(0));
        motor_10.run((10)==M1?-(0):(0));
    }
    
}


void setup(){
    ir.begin();
    if(isHost)
    {
      rgbled_7.setColor(0,50,0,0);
    }
    else
    {
      rgbled_7.setColor(0,0,0,50);
    }
    rgbled_7.show();
    pinMode(A7,INPUT);
}

void CreateRandomCommandString(char *s, const int len) {
    static const char alphanum[] =     "abcde";
 
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
 
    s[len] = 0;
}

void loop(){
    
    if(isHost){
        if((0^(analogRead(A7)>10?0:1))){//If button pressed.
          
            //I need to cast this... Must be using a C++ compile...
            char *p = (char*) malloc( sizeof(char) * ( amountOfCommands + 1 ) );
            CreateRandomCommandString(p, amountOfCommands);
          
            ir.sendString((String)p);
            SeperateAndExecuteCommands((String)p);
        }
    }
    if(!isHost){
        SeperateAndExecuteCommands(ir.getString());
    }
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

