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
