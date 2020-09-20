void Retrive()
{
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("ENTER YOUR CARD");
  digitalWrite(GL, LOW);
  int temp[4];
  int pos;
  int key;
  if (slot > 0) // check if there is any slot with car
  { //read UID
    while (! rfid.PICC_IsNewCardPresent())
      continue;
    while ( !rfid.PICC_ReadCardSerial())
      continue;

    for (int i = 0; i < 4; i++)
    {
      temp[i] = rfid.uid.uidByte[i];
    }
    key = temp[1];
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    Serial.println(key);
    pos = getslot(key);
    Serial.println(pos);
    if (pos == 4)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INVALID CARD.....");
    }
    else if (ID[pos].state == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CARD IS NOT USED....");
    }
    else
    {
      char buff[10];
      sprintf(buff, "SLOT NO.: %d", pos);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(buff);
      lcd.setCursor(0, 1);
      lcd.print("RETRIVING......");
      retriveCar(pos);
      slot--;;
      ID[pos].state = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    HAVE A      ");
      lcd.setCursor(0, 1);
      lcd.print("   NICE DAY     ");
      digitalWrite(GL, HIGH);
      digitalWrite(RL, LOW);
      delay(1200);
      digitalWrite(GL, LOW);
      lcd.clear();
    }
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SLOTS ARE EMPTY");
    delay(1200);
    lcd.clear();
  }
}
