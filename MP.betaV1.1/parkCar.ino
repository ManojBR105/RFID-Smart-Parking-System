void parkCar(int pos)
{

  int i = 0;
  int level = ID[pos].level;
  count = 170;
  //digitalWrite(RL, HIGH);
  while (i < 85) {
    Serial.println(i);
    printTime();
    stepper2.rotate(360);//move upto 60
    if (i == 60)
      setmotors(F);//move forward
    i++;
  }
  setmotors(B);//pick_up

  stepper1.rotate(ID[pos].angle);//rotate the motor to required slot angle
  if (level == 1)// if car has to be parked of 1st floor
  {
    setmotors(F);//place
    while (i) {
      printTime();
      Serial.println(i);
      stepper2.rotate(-360);
      if (i == 60)
        setmotors(B);//
      i--;
    }
  }
  else
  {
    while (i) //Go upto zero
    {
      printTime();
      Serial.println(i);
      stepper2.rotate(-360);
      if (i == 20)
        setmotors(F);
      i--;
    }
    setmotors(B);//back to original position
  }
  stepper1.rotate(-ID[pos].angle);//move back to home position
  printTime();
  //digitalWrite(RL, LOW);
  delay(500);
}
