#include <Arduino.h>
#include <BasicStepperDriver.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define MOTOR_STEPS 200
#define RPM1 10
#define RPM2 180
#define MICROSTEPS 16

#define SS_PIN 10
#define RST_PIN 9

#define GL  A0
#define RL  A1
#define SW1 A2
#define SW2 A3

#define DIR1  5
#define STEP1 4
#define DIR2  3
#define STEP2 2
#define PWM  6
#define BWD  7
#define FWD  8
#define SPEED  200
#define F 1
#define B 0

int Park_st = 1;
int Retr_st = 1;
int PrevPark_st = 1;
int PrevRetr_st = 1;
int slot = 3;
int count;



void Park();
void Retrive();
void setmotors(int);
int getslot(int);
void printTime();
void parkCar(int);
void retriveCar(int);


LiquidCrystal_I2C lcd(0x27, 16, 2);
BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);
MFRC522 rfid(SS_PIN, RST_PIN);

struct data
{
  const int angle;
  const bool level;
  bool state;
  const int UID;
};

data ID[4] = {{0, 0, 0, 36}, { 90, 1, 0, 106}, {180, 0, 0, 112}, {-90, 1, 0, 142}};

void setup()
{
  Serial.begin(9600);
  lcd.init();
  SPI.begin();
  rfid.PCD_Init();
  stepper1.begin(RPM1, MICROSTEPS);
  stepper2.begin(RPM2, MICROSTEPS);

  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SPEED, OUTPUT);
  pinMode(FWD,  OUTPUT);
  pinMode(BWD,  OUTPUT);
  pinMode(GL, OUTPUT);
  pinMode(RL, OUTPUT);

  digitalWrite(GL, LOW);
  digitalWrite(RL, LOW);

  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  lcd.setCursor(7, 1);
  lcd.print("TO");
  digitalWrite(GL, HIGH);
  delay(2000);
  digitalWrite(GL, LOW);
  digitalWrite(RL, HIGH);
  lcd.setCursor(3, 0);
  lcd.print("AUTOMATED");
  lcd.setCursor(2, 1);
  lcd.print("PARKING SYS");
  delay(2000);
  digitalWrite(RL, LOW);
  lcd.clear();
  digitalWrite(RL, HIGH);
}

void loop()
{
  digitalWrite(RL, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Slots filled:");
  char buff[4];
  sprintf(buff, "%d/7", slot);
  lcd.setCursor(13, 0);
  lcd.print(buff);
  lcd.setCursor(0, 1);
  lcd.print("PARK     RETRIVE");
  Serial.println("PARK OR RETRACT");

  Park_st = digitalRead(SW1);
  Retr_st = digitalRead(SW2);


  if (Park_st != PrevPark_st)
  {
    if (Park_st == LOW)
    {
      digitalWrite(RL, HIGH);
      Park();
      delay(500);
      digitalWrite(GL, LOW);
      digitalWrite(RL, LOW);
      
    }
  }
  if (Retr_st != PrevRetr_st)
  {
    if (Retr_st == LOW)
    {
      digitalWrite(RL, HIGH);
      Retrive();
      delay(500);
      digitalWrite(GL, LOW);
      digitalWrite(RL, LOW);
      
    }
  }
  PrevPark_st = Park_st;
  PrevRetr_st = Retr_st;
}
