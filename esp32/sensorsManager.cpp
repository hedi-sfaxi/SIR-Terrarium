#include "sensorsManager.h"

SensorsManager::SensorsManager() : lightSensor(), dhtSensor(DHTPIN, DHTTYPE) {
  Wire.begin();
  // lightSensor.begin();
  dhtSensor.begin();
}