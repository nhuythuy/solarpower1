
#include "sensors.h"
#include "actuators.h"
#include "datetime.h"
#include "blynk.h"


#define MESSAGE_DELAY 50
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.


void setup()
{
  ESP.wdtDisable();
  Serial.begin(115200);
  delay(100);


  setupSensors();
  delay(100);

  setupActuators();
  delay(100);

  BlynkEdgent.begin();
  timer.setInterval(2000L, blynkTimerEvent);

  setupDateTime();

  autoLoadPower = (boolean)readState(ADDRESS_AUTO_LOAD_POWER);
  manualLoadPowerOn = (boolean)readState(ADDRESS_MANUAL_LOAD_POWER_ON);

  ESP.wdtEnable(5000); // msec
}

unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
long diffMillis = 0;

void loop() {
  currentMillis = millis();
  runtimeMinutes = currentMillis / 60000;
  diffMillis = currentMillis - previousMillis;
  if(abs(diffMillis) > 2000){  // sampling sensors every 2 sec
    previousMillis = currentMillis;             // save the last time  

    yield();
    getServerTime();

    yield();
    updateBattVolt();
    yield();
    updateTempHumid();
    yield();
    updateActuators();

    flipLed();
  }
  
  BlynkEdgent.run();

  delay(100);
}
