#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
int Send = 7;

int Turned = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  rtc.begin();

  // Uncomment the following line if the DS3231 is not already set to the correct time.
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the current time on the RTC.

  pinMode(Send, OUTPUT);
  // digitalWrite(Send, HIGH);
  // delay(15000);
  // digitalWrite(Send, LOW);
  
}

void loop() {
  DateTime now = rtc.now();

  // Get the current hour and minute.
  int currentHour = now.hour();
  int currentMinute = now.minute();

  // Calculate the minutes since the last hour.
  int minutesSinceLastHour = currentMinute % 60;

  // Calculate the minutes to the next hour.
  int minutesToNextHour = 60 - minutesSinceLastHour;

  // Check if the current time is the start of a new hour.
  if (minutesSinceLastHour == 0 && Turned == 0) {
    // Turn on the LED for 10 seconds.
    digitalWrite(Send, HIGH);
    delay(20000);
    digitalWrite(Send, LOW);
    Turned = 1;
  }
  Turned = 0;
  // Wait until the next hour.
  delay(minutesToNextHour * 60000); // 1 minute = 60000 milliseconds
}