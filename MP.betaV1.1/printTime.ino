void printTime()
{
  char buff[3];
  sprintf(buff,"%3d",count);
  lcd.setCursor(13, 1);
  lcd.print(buff);
  count--;
}
