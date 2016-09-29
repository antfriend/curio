
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


