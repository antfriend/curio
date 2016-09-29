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
#include "WProgram.h"
void setup();
void loop();
void PauseBehavior();
void ZeroLoop();
void LoopFirstSwitch();
void LoopSecondSwitch();
void LoopThirdSwitch();
void TurnTowardsTheLight();
void pause(int inMilliseconds);
void SwivelArraySeqExe();
void OneLoop();
void LookSideToSide();
void StandAtAverageLightHeight();
void SlowWalk();
void HardToStarboard();
void HardToPort();
void Squats();
void StepForward();
void ScootForward();
void forward(int daLevel);
void port(int daLevel);
void starboard(int daLevel);
void aft(int daLevel);
void stand(int daLevel);
void MoveAll(int mWhere);
void MoveRLeg(int Where);
void MoveLLeg(int lWhere);
void MoveBLeg(int Where);
void GetEyeValues();
void BreakfastSerial();
void say(char daString[32]);
void TestLegs();
void MoveLeftUpNDown();
void UPnDOWN();
void EyeLights1();
void EyeLights2();
void AllOff();
void Pulse();
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
  boolean TheSwitchChanged = false;
  RestCounter++;
  if (RestCounter > RestCounterTrigger)
  {
     RestCounter = 0;
     RestCounterTrigger = random(100,1000);
     PauseBehavior();
     TheSwitchChanged = true;
  }
  //detect if state changed
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



//great set of legs
void SwivelArraySeqExe()
{
  SwivelArrayCurrentPos++;
  if(6 >= SwivelArrayCurrentPos)
  {
    SwivelArrayCurrentPos = 0;
  }
  //PortLegValue = SwivelArrayPort[SwivelArrayCurrentPos];
  //StarboardLegValue = SwivelArrayStarboard[SwivelArrayCurrentPos];
  //AftLegValue = SwivelArrayAft[SwivelArrayCurrentPos];
  
  port(SwivelArrayPort[SwivelArrayCurrentPos]);
  starboard(SwivelArrayStarboard[SwivelArrayCurrentPos]);
  aft(SwivelArrayAft[SwivelArrayCurrentPos]);
  pause(5);
}

void OneLoop()
{
  //loop all the legs up and down - together at first, then independently, 
  //by light level
  //int PortLegValue = PortLegMEDIUM;
  //int StarboardLegValue = StarboardLegMEDIUM;
  //int AftLegValue = AftLegMEDIUM;
  
  //int PortLegMax = PortLegMEDIUM + MinMaxExtremes;
  //int PortLegMin = PortLegMEDIUM - MinMaxExtremes;
  //int PortLegDir = -1;
  //int StarboardLegMax = StarboardLegMEDIUM + MinMaxExtremes;
  //int StarboardLegMin = StarboardLegMEDIUM - MinMaxExtremes;
  //int StarboardLegDir = -1;
  //int AftLegMax = AftLegMEDIUM + MinMaxExtremes;  
  //int AftLegMin = AftLegMEDIUM - MinMaxExtremes;
  //int AftLegDir = -1;
  
  int EyeAverage = 0;
  GetEyeValues();
  EyeAverage = (StarboardEye + PortEye + AftEye)/3;
  //figure out how much to vary each Leg max 
  
  //increment leg movement===========================================
  //Port leg
  PortLegValue = PortLegValue + PortLegDir;
  if (PortLegValue >= PortLegMax)
  {
     PortLegValue = PortLegMax;
     PortLegDir = -4;
  }
  if (PortLegValue <= PortLegMin)
  {
     PortLegValue = PortLegMin;
     PortLegDir = 4;
  }
  //Starboard leg
  StarboardLegValue = StarboardLegValue + StarboardLegDir;
  if(StarboardLegValue >= StarboardLegMax)
  {
      StarboardLegValue = StarboardLegMax;
      StarboardLegDir = -4;
  }
  if(StarboardLegValue <= StarboardLegMin)
  {
      StarboardLegValue = StarboardLegMin;
      StarboardLegDir = 4;
  }
  //Aft leg
  AftLegValue = AftLegValue + AftLegDir;
  if (AftLegValue >= AftLegMax)
  {
    AftLegValue = AftLegMax;
    AftLegDir = -4;
  }
  if (AftLegValue <= AftLegMin)
  {
    AftLegValue = AftLegMin;
    AftLegDir = 4;
  }
  
  //write values to legs
  LLeg.write(PortLegValue);
  RLeg.write(StarboardLegValue);
  BLeg.write(PortLegValue);
  pause(5);
}


void LookSideToSide()
{
  aft(TALL);
  starboard(SHORT);
  port(SHORT);
  AllOff();
  digitalWrite(BLU, HIGH);
  pause(300);
  digitalWrite(RED, HIGH);
  port(TALL);
  pause(200);
  digitalWrite(RED, LOW);
  pause(100);
  starboard(TALL);
  port(SHORT);
  digitalWrite(RED, HIGH);
  pause(200);
  digitalWrite(RED, LOW);
  pause(100);
}

void StandAtAverageLightHeight()
{
  //int ForAverage = (PortEye + StarboardEye)/2;  //compare the for eyes
                                                //to the aft eye
                                                //sway turn to face the light
                                                
  int daEyeMax = 700;//daAverage;//2;//500;
  int daHeightMax = 2;
  int daEyeMinimum = 300;
  //int daHeight = map(daAverage, 0, daEyeMax, 0, daHeightMax);
  //stand(daHeight);pause(25);
  port(map(PortEye, daEyeMinimum, daEyeMax, 0, daHeightMax));
  starboard(map(StarboardEye, daEyeMinimum, daEyeMax, 0, daHeightMax));
  aft(map(AftEye, daEyeMinimum, daEyeMax, 0, daHeightMax));
  pause(2);
}
  
void SlowWalk()
{
  int aTimTim = 0;
  int aTimTimMin = 25;
  int aTimTimMax = 110;
  int aTimTom = 100;
  for (int i=aTimTimMin;i<aTimTimMax;i=i+5)
  {
    aTimTim = i;
  digitalWrite(RED, HIGH);
  aft(SHORT);pause(aTimTim);aft(TALL);
  port(SHORT);pause(aTimTim);port(TALL);pause(aTimTim);
  stand(MEDIUM);pause(aTimTom);
  digitalWrite(RED, LOW);
  aft(SHORT);pause(aTimTim);aft(TALL);
  starboard(SHORT);pause(aTimTim);starboard(TALL);pause(aTimTim);
  stand(MEDIUM);pause(aTimTom);
  }
}
void HardToStarboard()
{
  //turn hard to the RIGHT
  int aTimTim = 0;
  int aTimTimMin = 2;
  int aTimTimMax = 100;
  int aTimTom = 100;
  stand(SHORT);pause(100);
  for (int i=aTimTimMin;i<aTimTimMax;i=i+30)
  {
   //aft(SHORT);pause(i);aft(TALL);pause(i);
   port(SHORT);pause(i);port(TALL);//pause(i);
   starboard(SHORT);pause(i);starboard(TALL);pause(i);
   stand(MEDIUM);pause(i);
  }

}
void HardToPort()
{
 //turn hard to the LEFT
  int aTimTim = 0;
  int aTimTimMin = 2;
  int aTimTimMax = 100;
  int aTimTom = 100;
  stand(SHORT);pause(100);
  for (int i=aTimTimMin;i<aTimTimMax;i=i+30)
  {
   //aft(SHORT);pause(i);aft(TALL);pause(i);
   port(SHORT);pause(i);port(TALL);//pause(i);
   starboard(SHORT);pause(i);starboard(TALL);pause(i);
   stand(MEDIUM);pause(i);
  }
  /*
  stand(SHORT);pause(500);
  stand(TALL);pause(200);
  stand(MEDIUM);pause(300);
  */
}


void Squats()
{
  for (int i = 6;i>0;i--)
  {
    digitalWrite(BLU, HIGH);  
    stand(2);pause(50*i);
    digitalWrite(GRN, HIGH); 
    stand(1);pause(50*i);
    digitalWrite(RED, HIGH); 
    stand(0);pause(50*i);
    digitalWrite(RED, LOW);
    digitalWrite(GRN, LOW);
    digitalWrite(BLU, LOW);
  }
}

void StepForward()
{
  const int DADELAY = 50;
    stand(MEDIUM);pause(3*DADELAY);
    
    starboard(SHORT);
    port(TALL);pause(DADELAY);
    aft(TALL);
    pause(3*DADELAY);
    
    stand(MEDIUM);pause(3*DADELAY);
    
    port(SHORT);
    starboard(TALL);pause(DADELAY);
    aft(TALL);
    pause(150);
}

void ScootForward()
{
  const int DADELAY = 50;
    stand(SHORT);pause(3*DADELAY);
    
    aft(TALL);pause(DADELAY);
    forward(MEDIUM);aft(MEDIUM);
    pause(3*DADELAY);
}

void forward(int daLevel)
{
  //left leg, RED
 switch (daLevel)
 {//stand height. 0 is lowest.
   case 0:
   RLeg.write(0); 
   LLeg.write(120);
   break;
   case 1:
   RLeg.write(90); 
   LLeg.write(62);
   break;
   default://highest or anything
   RLeg.write(180); 
   LLeg.write(5);
 }
}


void port(int daLevel)
{
  //left leg, RED
 switch (daLevel)
 {//stand height. 0 is lowest.
   case 0:
   LLeg.write(120);
   break;
   case 1:
   LLeg.write(PortLegMEDIUM);
   break;
   default://highest or anything
   LLeg.write(9);
 }
}
void starboard(int daLevel)
{
  //right leg, GRN
 switch (daLevel)
 {//stand height. 0 is lowest.
   case 0:
   RLeg.write(0);  
   break;
   case 1:
   RLeg.write(StarboardLegMEDIUM);  
   break;
   default://highest or anything
   RLeg.write(170);
 }
}
void aft(int daLevel)
{
  //back leg, BLU
 switch (daLevel)
 {//stand height. 0 is lowest.
   case 0:
   BLeg.write(0);   
   break;
   case 1:
   BLeg.write(AftLegMEDIUM);   
   break;
   default://highest or anything
   BLeg.write(180);
 }
}

void stand(int daLevel)
{
  port(daLevel);
  starboard(daLevel);
  aft(daLevel);
}
void MoveAll(int mWhere)
{
  MoveRLeg(mWhere);
  pause(10);
  MoveLLeg(mWhere);
  pause(10);
  MoveBLeg(mWhere);
  pause(10);
}

void MoveRLeg(int Where)
{
  const int LowerLimit = 10;
  const int UpperLimit = 150;
  Where = constrain(Where, 0, 100);//accept a value of 0 to 100
  
  Where = map(Where, 0, LowerLimit, 100, UpperLimit);
  RLeg.write(Where);
}

void MoveLLeg(int lWhere)
{
  const int LowerLimit = 10;
  const int UpperLimit = 150;
  lWhere = constrain(lWhere, 0, 100);//accept a value of 0 to 100
  lWhere = 100 - lWhere;
  lWhere = map(lWhere, 0, LowerLimit, 100, UpperLimit);
  LLeg.write(lWhere);
}
void MoveBLeg(int Where)
{
  const int LowerLimit = 10;
  const int UpperLimit = 190;
  Where = constrain(Where, 0, 100);//accept a value of 0 to 100
  Where = map(Where, 0, LowerLimit, 100, UpperLimit);
  BLeg.write(Where);
}



const int EyeIntervalTarget = 50;
int EyeIntervalCounter = 0;

void GetEyeValues()
{
    EyeIntervalCounter++;
    if (EyeIntervalCounter >= EyeIntervalTarget)
    {
      digitalWrite(OscilliscopeOutPin,HIGH);
      EyeIntervalCounter = 0;
      PortEye = analogRead(PortEyePin);
      StarboardEye = analogRead(StarboardEyePin);
      AftEye = analogRead(AftEyePin);
      if (LOW==Oscillator)
      {
        digitalWrite(OscilliscopeOutPin,HIGH);
        Oscillator = HIGH;
      }
      else
      {
        digitalWrite(OscilliscopeOutPin,LOW);
        Oscillator = LOW;
      }
    }
}


void BreakfastSerial()
{
  //say("reading cereal...");
  if (daSerial.available() > 0)
  {
    char ch = daSerial.read();
    say("done reading.");
      switch(ch)
      {
        case '1':
          daSerial.print("1-");
          say("OneLoop");
          OneLoop();
          break;
        case '2':
          daSerial.print("2-");
          say("LookSideToSide");
          LookSideToSide();
          break;
        case '3':
          daSerial.print("3-");
          say("SlowWalk");
          SlowWalk();
          break;
        case '4':
          daSerial.print("4-");
          say("HardToStarboard");
          HardToStarboard();
          break;
        case '5':
          daSerial.print("5-");
          say("HardToPort");
          HardToPort();
          break;
        case '6':
          daSerial.print("6-");
          say("Squats");
          Squats();
          break;
        case '7':
          daSerial.print("7-");
          say("StepForward");
          StepForward();
          break;
        case '8':
          daSerial.print("8-");
          say("ScootForward");
          ScootForward();
          break;
        case '9':
          daSerial.print("9-");
          say("forward 5");
          forward(5);
          break;
        case '0':
          daSerial.print("0-");
          say("MoveLeftUpNDown");
          MoveLeftUpNDown();
          break;
        default:
          daSerial.print(ch);say("? What's that?");
          break;
      }
  }
}

void say(char daString[32])
{
  daSerial.println(daString);
}

void TestLegs()
{
  MoveRLeg(0);
  pause(300);
  MoveRLeg(90);
  pause(300);
  
  MoveLLeg(0);
  pause(300);
  MoveLLeg(90);
  pause(300);

  MoveBLeg(0);
  pause(300);
  MoveBLeg(90);
  pause(1000);
}

void MoveLeftUpNDown()
{
  for(int i = 0; i < 101; i++)
  {
    MoveLLeg(i);
    pause(10);    
  }
  pause(1000);
  for(int i = 100; i > 0; i--)
  {
    MoveLLeg(i);
    pause(10);    
  }
}

void UPnDOWN()
{
  MoveAll(0);
  pause(300);
 // MoveAll(50);
  pause(100);
  MoveAll(100);
  pause(400);
  /*
  for(int i = 0; i < 100; i++)
  {
    MoveAll(i);
    pause(1);    
  }
  for(int i = 100; i > 0; i--)
  {
    MoveAll(i);
    pause(1);    
  }
*/
}


void EyeLights1()
{
      for (int i=25;i<50;i=i+5)
    {
      digitalWrite(RED, HIGH);
      digitalWrite(GRN, HIGH);
      digitalWrite(BLU, HIGH);
      delay(i);//pause for switch bounce
      digitalWrite(RED, LOW);
      digitalWrite(GRN, HIGH);
      digitalWrite(BLU, LOW);
      delay(i);//pause for switch bounce 
      digitalWrite(RED, HIGH);
      digitalWrite(GRN, LOW);
      digitalWrite(BLU, LOW);
      delay(i);//pause for switch bounce
      digitalWrite(RED, HIGH);
      digitalWrite(GRN, LOW);
      digitalWrite(BLU, HIGH);
      delay(i);//pause for switch bounce 
      digitalWrite(RED, LOW);
      digitalWrite(GRN, LOW);
      digitalWrite(BLU, HIGH);
      delay(i);//pause for switch bounce
      AllOff();
      delay(i);//pause for switch bounce  
    }
}

void EyeLights2()
{
  //nuther light show
}

void AllOff()
{
    digitalWrite(RED, LOW);
    digitalWrite(GRN, LOW);
    digitalWrite(BLU, LOW);  
}
void Pulse()
{
 int daBrightness = 0;
 for (int i=0;i<10;i++) 
 {
  for(int j=0;j<100;j++)
 {
   daBrightness++;
   if (daBrightness > 25)
   {
      daBrightness = 0;
       
   }
  delay(1);
 }
  for(int j=100;j>0;j--)
 {
   
  delay(1);
 }
 
 }
}


int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

