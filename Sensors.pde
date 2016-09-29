
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


