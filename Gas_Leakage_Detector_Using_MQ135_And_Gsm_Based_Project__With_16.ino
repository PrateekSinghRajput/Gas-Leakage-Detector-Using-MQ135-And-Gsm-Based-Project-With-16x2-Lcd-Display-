#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(9,8);
 
int gasValue = A0; 
int data = 0;
int relay = 6; 
int pir_Status; 
int buzzerPin = 5;

void setup()
{
randomSeed(analogRead(0));
mySerial.begin(9600); 
Serial.begin(9600); 
 lcd.init();
 lcd.backlight();
pinMode(gasValue, INPUT);
pinMode(relay, OUTPUT);
pinMode(buzzerPin, OUTPUT);
lcd.setCursor(2,0);
lcd.print ("WELCOME TO  ");
lcd.setCursor(2,1);
lcd.print ("JUSTDOELECTRONICS");
lcd.setCursor(6,2);
lcd.print ("DESIGN By :-");
lcd.setCursor(6,3);
lcd.print ("PRATEEK");
delay(3000);
lcd.clear();
}
 
void loop(){
data = analogRead(gasValue);
 
Serial.print("Gas Level: ");
Serial.println(data);
lcd.clear();
lcd.setCursor(1,0);
lcd.print ("Exhaust fan :- OFF");
lcd.setCursor(2,1);
lcd.print("Gas Level: ");
lcd.print(data);
delay(1000);
 
if ( data > 700) 
{
SendMessage();
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(1,0);
lcd.print ("Exhaust fan :- ON");
lcd.setCursor(2,2);
lcd.print("Gas Level Exceed");
lcd.setCursor(2,3);
lcd.print("SMS Sent");
delay(1000);
 digitalWrite(buzzerPin, HIGH);
 digitalWrite(relay, HIGH);

}
else
{
 
Serial.print("Gas Level Low");
lcd.clear();
lcd.setCursor(2,3);
lcd.print("Gas Level Normal");
delay(1000);
digitalWrite(buzzerPin, LOW);
 digitalWrite(relay, LOW);

}
 
//lcd.clear();
}
 
void SendMessage()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"+918830584864\"\r"); 
delay(1000);
mySerial.println("Excess Gas Detected. Open Windows");
delay(100);
mySerial.println((char)26);
delay(1000);
}
