/*
CURIO
   debugger - jumper pin wire for scope
   digital out to pin 10 for sampling frequency of eyes
   serial write binary values to pin 10 for scope debugger
 */
#include <SoftwareServo.h>
#include <NewSoftSerial.h>

#define rxPin 7
#define txPin 8
NewSoftSerial daSerial(rxPin, txPin);

const int RED = 2;
const int GRN = 1;
const int BLU = 0;
const int StarboardEyePin = 0;
const int AftEyePin = 1;
const int PortEyePin = 2;
const int RLegPin = 3;
const int LLegPin = 4;
const int BLegPin = 5;
const int OscilliscopeOutPin = 6;

const int ThirdBitPin = 17;
const int SecondBitPin = 18;
const int FirstBitPin = 19;

const int MinMaxExtremes = 60;
const int PortLegMEDIUM = 62;
int PortLegValue = PortLegMEDIUM;
const int StarboardLegMEDIUM = 90;
int StarboardLegValue = StarboardLegMEDIUM;
const int AftLegMEDIUM = 90;
int AftLegValue = AftLegMEDIUM;

int PortLegMax = PortLegMEDIUM + MinMaxExtremes;
int PortLegMin = PortLegMEDIUM - MinMaxExtremes;
int PortLegDir = 1;

int StarboardLegMax = StarboardLegMEDIUM + MinMaxExtremes;
int StarboardLegMin = StarboardLegMEDIUM - MinMaxExtremes;
int StarboardLegDir = -1;

int AftLegMax = AftLegMEDIUM + MinMaxExtremes;  
int AftLegMin = AftLegMEDIUM - MinMaxExtremes;
int AftLegDir = -1;

const int TALL = 2;//tallest
const int MEDIUM = 1;//medium
const int SHORT = 0;//shortest squat

SoftwareServo RLeg;
SoftwareServo LLeg;
SoftwareServo BLeg;

int SwitchState = 0;
int PreviousSwitchState = 0;
boolean FirstSwitch = LOW;
boolean SecondSwitch = LOW;
boolean ThirdSwitch = LOW;
boolean TheSwitchChanged = true;

int StarboardEye = 0;
int PortEye = 0;
int AftEye = 0;

int MetabolicCount = 0;
int RestCounter = 0;
int RestCounterTrigger = 100;
boolean Oscillator = LOW;

//swivel array
int SwivelArrayStarboard[6]={TALL,TALL,TALL,SHORT,SHORT,SHORT};
int SwivelArrayPort[6]={TALL,SHORT,SHORT,SHORT,TALL,TALL};
int SwivelArrayAft[6]={SHORT,SHORT,TALL,TALL,TALL,SHORT};
int SwivelArrayCurrentPos=0;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(FirstBitPin, INPUT);
  digitalWrite(FirstBitPin, HIGH);
  pinMode(SecondBitPin, INPUT);
  digitalWrite(SecondBitPin, HIGH);
  pinMode(ThirdBitPin, INPUT);
  digitalWrite(ThirdBitPin, HIGH);
  pinMode(OscilliscopeOutPin,OUTPUT);
  digitalWrite(OscilliscopeOutPin,LOW);
  //oscilloscope test at 50ms
  for(int i=0;i<100;i++)
  {
    digitalWrite(OscilliscopeOutPin,HIGH);
    delay(25);
    digitalWrite(OscilliscopeOutPin,LOW);
    delay(25);
  }
  randomSeed(analogRead(5));
  RLeg.attach(RLegPin);
  LLeg.attach(LLegPin);
  BLeg.attach(BLegPin);
  //stand ready
  stand(SHORT);pause(150);
  digitalWrite(RED, HIGH);
  digitalWrite(GRN, HIGH);
  digitalWrite(BLU, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(GRN, LOW);
  digitalWrite(BLU, LOW);  
   
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  daSerial.begin(9600);
  //delay(500);
  say(" ");
  say(" ");
  say("hello");
  delay(300);
  say("I am a robot!");
  delay(300);
  daSerial.print("I ");
  delay(200);
  daSerial.print("am ");
  delay(200);
  daSerial.print("C");delay(100);
  daSerial.print("u");delay(100);
  daSerial.print("r");delay(100);
  daSerial.print("i");delay(100);
  daSerial.print("o");delay(100);
  say(".");
}

void loop()                  
{
  
  RestCounter++;
  if (RestCounter > RestCounterTrigger)
  {
     RestCounter = 0;
     RestCounterTrigger = 100; //random(100,1000);
     say("resting");
     delay(1000);
     //PauseBehavior();
     //TheSwitchChanged = true;
  }
  //detect if state changed and if so, initialize
   IfSwitchChanged();
   
   MetabolicCount++;
   switch (SwitchState)
   {
     case 0:
       //say("switch pos 0");
       RestCounter=0;
       //say("got to BreakfastSerial");//debug
       BreakfastSerial();
       //say("got past BreakfastSerial");//debug
       break;
     case 1:
       //say("switch pos 1");
       LoopFirstSwitch();
       break;
     case 2:// 0
       //no 2 bit - this won't happen
     case 3:// 1
       //no 2 bit - this won't happen
     case 4:
       //OneLoop();
       say("switch pos 4");
       SwivelArraySeqExe();
       pause(100);
       break;
     case 5:
       OneLoop();
       break;
     case 6:// 4
       //no 2 bit - this won't happen
     case 7:// 5
       //no 2 bit - this won't happen
     case 8:
       OneLoop();
       break;
     case 9:
       //OneLoop();
       //say("switch pos 9");
       GetEyeValues();
       StandAtAverageLightHeight();
       break;
   }
  /* //do the loop routines
  if (FirstSwitch == HIGH) LoopFirstSwitch();
  if (SecondSwitch == HIGH) LoopSecondSwitch();
  if (ThirdSwitch == HIGH) LoopThirdSwitch();
  */
}

void PauseBehavior()
{
  int daCase = 0;
  daCase = random(0, 4);
  switch(daCase)
  {
     case 0:
       digitalWrite(RED, HIGH);
       delay(500);
       digitalWrite(RED, LOW);
       digitalWrite(RED, HIGH);
       //SlowWalk();
       break;
     case 1:
       digitalWrite(RED, HIGH);
       delay(500);
       digitalWrite(RED, LOW);
       digitalWrite(GRN, HIGH);
       LookSideToSide();
       LookSideToSide();
       break;
     case 2:
       digitalWrite(RED, HIGH);
       delay(500);
       digitalWrite(RED, LOW);
       digitalWrite(BLU, HIGH);
       SlowWalk();
       break;
     default:
       digitalWrite(RED, HIGH);
       delay(500);
       digitalWrite(BLU, HIGH);
       digitalWrite(GRN, HIGH);
       //SlowWalk();
       break;
  }
  delay(random(250,3000));
}

void ZeroLoop()
{
  //do nothing
  
}

void LoopFirstSwitch()
{
    //Squats();
    digitalWrite(BLU, HIGH);
    GetEyeValues();
    digitalWrite(BLU, LOW);
    delay(50);
    StandAtAverageLightHeight();
    delay(200);
    if(MetabolicCount > 100)
    {
      MetabolicCount = 0;
      say("Squats");
      delay(200);
    }
}

void LoopSecondSwitch()
{  
  say("TurnTowardsTheLight");
  TurnTowardsTheLight();
}

void LoopThirdSwitch()
{
  //randomize through all the tests
    //StepForward();
    //ScootForward();  
    //stand(MEDIUM);pause(500);
    //delay(100);  
    //SlowWalk();
    say("aww, null");
}

void TurnTowardsTheLight()
{
   GetEyeValues();
  int aTimTim = 0;
  int aTimTimMin = 10;
  int aTimTimMax = 40;
  int aTimStep = 10;
  int aTimTom = aTimTimMax;
  //stand(SHORT);pause(aTimTom);
  for (int i=aTimTimMin;i<aTimTimMax;i=i+aTimStep)
  {
    if(StarboardEye > PortEye)
    {
      starboard(SHORT);pause(i);starboard(TALL);//pause(i);
      port(SHORT);pause(i);port(TALL);pause(i);
    }
     else
    {
       port(SHORT);pause(i);port(TALL);//pause(i);
       starboard(SHORT);pause(i);starboard(TALL);pause(i);
    } 
   //stand(MEDIUM);pause(i);
  }
}

void pause(int inMilliseconds)
{
  int daIncrement = 20;
  SoftwareServo::refresh(); 
  for(int i=0;i<=inMilliseconds;i++)
  {
    if(i > daIncrement)
    {
      daIncrement = daIncrement + 20;
      SoftwareServo::refresh(); 
    }
    delay(1);
  }
}

void IfSwitchChanged(){
  if (FirstSwitch == digitalRead(FirstBitPin)) TheSwitchChanged = true;
  if (SecondSwitch == digitalRead(SecondBitPin)) TheSwitchChanged = true;  
  if (ThirdSwitch == digitalRead(ThirdBitPin)) TheSwitchChanged = true;

  if (TheSwitchChanged == true)//begin Switched State Initialization===================
  { 
    //say("rct=" + char(RestCounterTrigger));
    PreviousSwitchState = SwitchState; 
    MetabolicCount=0;
    TheSwitchChanged=false;
    say("Changing...");
    EyeLights1();   
    //delay(500);
    pause(250);//pause for switch bounce 
    if (LOW == digitalRead(FirstBitPin))
    {
      FirstSwitch = HIGH;
        SwitchState = 1;
    }
    else
    {
      FirstSwitch = LOW;
      SwitchState = 0;
    }
    if (LOW == digitalRead(SecondBitPin))
    {
      SecondSwitch = HIGH;
      SwitchState = SwitchState + 8;
    }
    else
    {
      SecondSwitch = LOW;
    }
    if (LOW == digitalRead(ThirdBitPin))
    {
      ThirdSwitch = HIGH;
      SwitchState = SwitchState + 4;
    }
    else
    { 
      ThirdSwitch = LOW;
      //SwitchState = SwitchState;
    }
     int iMax = 30;
     for (int i = 10; i < iMax; i=i+5)
     {
       digitalWrite(RED, ThirdSwitch); 
       digitalWrite(GRN, FirstSwitch); 
       digitalWrite(BLU, SecondSwitch); 
       delay(i);
       digitalWrite(RED, SecondSwitch); 
       digitalWrite(GRN, ThirdSwitch); 
       digitalWrite(BLU, FirstSwitch); 
       delay(i);
       digitalWrite(RED, FirstSwitch); 
       digitalWrite(GRN, SecondSwitch); 
       digitalWrite(BLU, ThirdSwitch); 
       delay(i);
     }
     digitalWrite(RED, LOW);
     digitalWrite(GRN, LOW);
     digitalWrite(BLU, LOW);
     daSerial.print(SwitchState);
     say(" is  the switch state");
     switch (SwitchState)
     {
       case 0://*
         //low power mode
         stand(SHORT);pause(500);
         break;
       case 1://*
         digitalWrite(RED, HIGH);
         digitalWrite(GRN, LOW);
         digitalWrite(BLU, LOW);
         stand(MEDIUM);pause(500);
         //say("Case 1");
         PortLegMax = PortLegMEDIUM + MinMaxExtremes;
         PortLegMin = PortLegMEDIUM - MinMaxExtremes;
         StarboardLegMax = StarboardLegMEDIUM + MinMaxExtremes;
         StarboardLegMin = StarboardLegMEDIUM - MinMaxExtremes;
         AftLegMax = AftLegMEDIUM + MinMaxExtremes;  
         AftLegMin = AftLegMEDIUM - MinMaxExtremes;
         //say("did it");//debug
         break;
       case 2:// 0
         // no 2 bit         
         break;
       case 3:// 1
         // no 2 bit
         break;
       case 4://*
         digitalWrite(RED, LOW);
         digitalWrite(GRN, HIGH);
         digitalWrite(BLU, LOW);
         stand(MEDIUM);pause(500);
         PortLegMax = PortLegMEDIUM + 20;
         PortLegMin = PortLegMEDIUM - 20;
         StarboardLegMax = StarboardLegMEDIUM + 20;
         StarboardLegMin = StarboardLegMEDIUM - 20;
         AftLegMax = AftLegMEDIUM + MinMaxExtremes;  
         AftLegMin = AftLegMEDIUM - MinMaxExtremes;
         break;
       case 5://*
         digitalWrite(RED, HIGH);
         digitalWrite(GRN, HIGH);
         digitalWrite(BLU, LOW);
         stand(TALL);pause(500);
         PortLegMax = PortLegMEDIUM + MinMaxExtremes;
         PortLegMin = PortLegMEDIUM - MinMaxExtremes;
         StarboardLegMax = StarboardLegMEDIUM + MinMaxExtremes;
         StarboardLegMin = StarboardLegMEDIUM - MinMaxExtremes;
         AftLegMax = AftLegMEDIUM + 20;  
         AftLegMin = AftLegMEDIUM - 20;
         break;
       case 6:// 4
         // no 2 bit
         break;
       case 7://5
         // no 2 bit
         break;
       case 8:
         digitalWrite(RED, LOW);
         digitalWrite(GRN, LOW);
         digitalWrite(BLU, HIGH);
         stand(TALL);pause(500);
         PortLegMax = PortLegMEDIUM + 20;
         PortLegMin = PortLegMEDIUM - 20;
         StarboardLegMax = StarboardLegMEDIUM + MinMaxExtremes;
         StarboardLegMin = StarboardLegMEDIUM - MinMaxExtremes;
         AftLegMax = AftLegMEDIUM + MinMaxExtremes;  
         AftLegMin = AftLegMEDIUM - MinMaxExtremes;
         break;
       case 9:
         digitalWrite(RED, HIGH);
         digitalWrite(GRN, LOW);
         digitalWrite(BLU, HIGH);
         stand(TALL);pause(500);
         PortLegMax = PortLegMEDIUM + 20;
         PortLegMin = PortLegMEDIUM - 20;
         StarboardLegMax = StarboardLegMEDIUM + 40;
         StarboardLegMin = StarboardLegMEDIUM - 40;
         AftLegMax = AftLegMEDIUM + MinMaxExtremes;  
         AftLegMin = AftLegMEDIUM - MinMaxExtremes;
         break;
     }
   }//end Switched State Initialization================================
 }

