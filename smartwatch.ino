#define BLYNK_PRINT Serial
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX
#include <Wire.h>
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "796e766502954e42a258268a96e44d55";
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial SerialBLE(10, 11); // RX, TX

BlynkTimer timer;
String t1,d1;
String t;
WidgetRTC rtc;

// Digital clock display of the time
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
   
  String currentTime = String(hour()) + ":" + String(minute());
  delay(10);
  String currentDate = String(day()) + "/" + String(month()) + "/" + String(year());
  delay(10);
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  // Send time to the App
  Blynk.virtualWrite(V1, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V2, currentDate);
  t1= currentTime;
  d1= currentDate;
}

void displaytime()
{ //displayTempHumid();
  display.display();
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(35,0);
  display.print(t1);
  display.setTextSize(1);
  display.setCursor(35,20);
  display.print(d1);
  //display.setCursor(0,25);
  //display.setTextSize(0.5);
 // display.print("Temp: "); 
  //display.print(t);
  //display.print(" C");
  }
void displayTempHumid(){
delay(10);
t = dht.readTemperature();
display.display();
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(35,0);
display.print(t);

}
void setup()
{
  // Debug console
  display.clearDisplay();
  dht.begin();
  Wire.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C
  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth);
  digitalWrite(5,LOW);
  digitalWrite(7,LOW);
  Serial.println("Waiting for connections...");

  // Begin synchronizing time
  rtc.begin();

  timer.setInterval(5000L, clockDisplay);
  display.display();
}
void stopwatch()
{
  display.display();
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(35,0);
display.print(millis()/3600000);
display.print(':');
display.print(millis()/60000);
display.print(':');
display.print(millis()/1000);
Serial.print(millis()/3600000);
Serial.print(':');
Serial.print(millis()/60000);
Serial.print(':');
Serial.print(millis()/1000);
  }

void loop()
{
 Blynk.run();
  while(digitalRead(5)==HIGH) displayTempHumid();
 display.display();
timer.run();
displaytime();
 while(digitalRead(7)==HIGH) stopwatch();
 delay(10); 
}


