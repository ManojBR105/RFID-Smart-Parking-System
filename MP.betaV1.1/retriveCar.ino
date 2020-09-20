void retriveCar(int pos)
{
  int i = 0;
  int level = ID[pos].level;
  count = 170;
  //digitalWrite(RL, HIGH);
  
  stepper1.rotate(ID[pos].angle);
  if (level == 0)
  {
    setmotors(F);
    while (i < 20)
    {
      printTime();
      Serial.println(i);
      stepper2.rotate(360);
      i++;
    }
    setmotors(B);
    stepper1.rotate(-ID[pos].angle);
    while (i < 85)
    {
      printTime();
      Serial.println(i);
      stepper2.rotate(360);
      i++;
    }
    setmotors(F);
    while (i)
    {
      printTime();
      stepper2.rotate(-360);
      if (i == 60)
        setmotors(B);
      i--;
    }
  }
  else
  {
    while (i < 85)
    {
      printTime();
      if (i == 60)
        setmotors(F);
      i++;
      stepper2.rotate(360);
    }
    setmotors(B);
    stepper1.rotate(-ID[pos].angle);
    setmotors(F);
    while (i)
    {
      printTime();
      stepper2.rotate(-360);
      if (i == 60)
        setmotors(B);
      i--;
    }
  }
  printTime();
  //digitalWrite(RL, LOW);
  delay(500);
}
