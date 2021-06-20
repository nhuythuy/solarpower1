
#include "sensors.h"
#include "datetime.h"
#include "blynk.h"


#define MESSAGE_DELAY 50
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

//void blynkTimerEvent()
//{  
//  runtimeMinutes++;
//  getServerTime();
//  updateTempHumid();
//  
//  // You can send any value at any time.
//  // Please don't send more that 10 values per second.
//  yield();
//  Serial.println("Blynk timer triggered...");
//  // for all signals to be sent at once
//  Serial.println("Counter: " + String(runtimeMinutes));
//  Serial.println("Clock: " + String(systemClock));
//  Serial.println("Batt. Volt.: " + String(ssBatteryVolt));
//  Serial.println("Temperature: " + String(temp));
//  Serial.println("Humidity: " + String(humidity));
//  Serial.println("Error Counter: " + String(sensorErrorCounter));
//
//
//  Blynk.virtualWrite(VP_LR_RUNTIME, runtimeMinutes);
//  delay(MESSAGE_DELAY);
//  Blynk.virtualWrite(VP_CLOCK, systemClock);
//  delay(MESSAGE_DELAY);
//  Blynk.virtualWrite(VP_BATT_VOLT, ssBatteryVolt);
//  delay(MESSAGE_DELAY);
//  Blynk.virtualWrite(VP_LR_TEMPERATURE, temp);
//  delay(MESSAGE_DELAY);
//  Blynk.virtualWrite(VP_LR_HUMIDITY, humidity);
//  delay(MESSAGE_DELAY);
//
//  Blynk.virtualWrite(VP_ERROR_COUNTER, sensorErrorCounter);
//  delay(MESSAGE_DELAY);
//}

void setup()
{
  Serial.begin(115200);
  delay(100);

  setupSensors();
  delay(100);


  BlynkEdgent.begin();

  timer.setInterval(2000L, blynkTimerEvent);

  setupDateTime();
}

void loop() {
  BlynkEdgent.run();

}
