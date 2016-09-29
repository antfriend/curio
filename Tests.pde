
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

