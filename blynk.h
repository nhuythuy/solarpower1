// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL41K1Al5C"
#define BLYNK_DEVICE_NAME "PowerStation"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD

#include "BlynkEdgent.h"

#include "wifi_cloud.h"
#include "global_vars.h"

int blynkCounter = 0;

#ifndef BLYNK
#define BLYNK

#define MESSAGE_DELAY                       100

#define VP_RUNTIME                          V0
#define VP_CLOCK                            V1
#define VP_BATT_VOLTAGE                     V2
#define VP_TEMPERATURE                      V3
#define VP_HUMIDITY                         V4

#define VP_AC_MAIN_DOOR_LIGHT_ON            V44   // status

// control signals, only available on Blynk
#define VP_AC_MAIN_DOOR_LIGHT               V45
#define VP_AC_LED_HEART_MODE                V46

// digital states
#define VP_AUTO_LOAD_POWER                  V51
#define VP_MANUAL_LOAD_POWER_ON             V52


#define BLYNK_PRINT Serial


BLYNK_WRITE(VP_AUTO_LOAD_POWER){
  autoLoadPower = (boolean)param.asInt();
  storeState(ADDRESS_AUTO_LOAD_POWER, autoLoadPower);
}

BLYNK_WRITE(VP_MANUAL_LOAD_POWER_ON){
  manualLoadPowerOn = (boolean)param.asInt();
  storeState(ADDRESS_MANUAL_LOAD_POWER_ON, manualLoadPowerOn);
}

BLYNK_WRITE(VP_AC_LED_HEART_MODE){
  heartLedMode = param.asInt();
}

BLYNK_WRITE(VP_AC_MAIN_DOOR_LIGHT){
  mainDoorLightMode = param.asInt();
}

void blynkTimerEvent()
{
  yield();  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(VP_AC_MAIN_DOOR_LIGHT_ON, (mainDoorLightOn ? 255 : 0));
  delay(MESSAGE_DELAY);

  yield();
  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once
  Serial.println("Counter: " + String(runtimeMinutes));
  Serial.println("Clock: " + String(systemClock));
  Serial.println("Batt. Volt.: " + String(ssBatteryVolt));
  Serial.println("Temperature: " + String(temp));
  Serial.println("Humidity: " + String(humidity));


  Blynk.virtualWrite(VP_RUNTIME, runtimeMinutes);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_CLOCK, systemClock);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_BATT_VOLTAGE, ssBatteryVolt);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_TEMPERATURE, temp);
  delay(MESSAGE_DELAY);
  Blynk.virtualWrite(VP_HUMIDITY, humidity);
  delay(MESSAGE_DELAY);

  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once
}

void blynkSetup(){
  timer.setInterval(1000L, blynkTimerEvent);
  delay(100);
}


#endif
