void setmotors(int M)
{
if(M==0)
{
  analogWrite(PWM, SPEED);
  digitalWrite(FWD, LOW);
  digitalWrite(BWD, HIGH);
  delay(1500);
  digitalWrite(FWD, LOW);
  digitalWrite(BWD, LOW);
}

if(M==1)  
{
 
  analogWrite(PWM, SPEED);
  digitalWrite(FWD, HIGH);
  digitalWrite(BWD, LOW);
  delay(900);
  digitalWrite(FWD, LOW);
  digitalWrite(BWD, LOW); 
  
  }  
  
  
}
