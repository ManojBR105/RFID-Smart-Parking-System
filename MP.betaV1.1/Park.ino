void Park()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLACE YOUR CARD");
  Serial.print("PARK");
  digitalWrite(GL, LOW);

  int temp[4];
  int key;
  int pos;
  if (slot < 7)// check if any slots are left
  {
    //read UID
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
    Serial.println(ID[pos].level);
    if (pos == 4)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INVALID CARD.....");
      delay(500);
    }
    else if (ID[pos].state == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CARD ALREDY USED");
      delay(1000);
    }
    else
    {
      char buff[10];
      sprintf(buff, "SLOT NO.: %d", pos);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(buff);
      lcd.setCursor(0, 1);
      lcd.print("Parking...");
      parkCar(pos);
      slot++;      
      ID[pos].state = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   THANK YOU..  ");
      lcd.setCursor(0, 1);
      lcd.print("PARKING CMPLTED");
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
    lcd.print(" ALL SLOTS FULL ");
    delay(1200);
    lcd.clear();
  }
}
