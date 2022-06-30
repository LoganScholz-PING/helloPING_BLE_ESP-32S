#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.print("HEY WE ARE IN THE BLECharacteristCallbacks()");

        if(value == "<1>") { Serial.print("We have received <1>"); } // HERE, BETWEEN THE "{}" IS WHERE THE ACTION HAPPENS WHEN YOU PRESS A BUTTON ON THE DEVICE
        value = "";
      }
    }
};

void setup() 
{
  Serial.begin(9600);

  BLEDevice::init("PING_TEST_BLE_DEVICE");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("PING_HELLO_BLE");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() 
{
  /* just let the bluetooth stuff do the callbacks */
}