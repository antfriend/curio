
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

