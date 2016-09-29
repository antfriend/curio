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

