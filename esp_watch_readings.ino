#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEAdvertisedDevice.h>
int ctr=0 ;
int i=0;
int scanTime = 1; // In seconds
BLEScan *pBLEScan;
std::string targetDeviceAddress = "C8:C9:A3:CF:2B:C2"; // Replace with the MAC address of the target device
std::string targetDeviceAddress2 = "FE:23:62:2D:CD:0F"; // Replace with the MAC address of the target device

int rssiValue = 0;
int rssiValue1 = 0;

int arr[120];
int arr1[120];

bool targetDeviceFound = false; // Track if the target device is found
bool targetDeviceFound1 = false; // Track if the target device is found

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice *advertisedDevice)
    {if (advertisedDevice->getAddress().equals(targetDeviceAddress2))
        {
         
            Serial.println("Found the target device!");
            Serial.print("Device name: ");
            Serial.println(advertisedDevice->getName().c_str());
            Serial.println(" | RSSI: ");
        rssiValue1 = advertisedDevice->getRSSI();
            
           
            if (advertisedDevice->haveServiceUUID())
            {
                BLEUUID devUUID = advertisedDevice->getServiceUUID();
                Serial.print("Service UUID: ");
                Serial.println(devUUID.toString().c_str());
            }

            if (advertisedDevice->haveManufacturerData())
            {
                std::string strManufacturerData = advertisedDevice->getManufacturerData();

                if (strManufacturerData.length() == 25 && strManufacturerData[0] == 0x4C && strManufacturerData[1] == 0x00)
                {
                    Serial.println("Found an iBeacon!");
                    // Handle iBeacon data here if needed
                }
                else
                {
                    Serial.println("Found another manufacturer's beacon!");
                    // Handle other manufacturer data here if needed
                }
            }

            // Set the flag to stop scanning after the target device is found
            targetDeviceFound1 = false;
        }

        if (advertisedDevice->getAddress().equals(targetDeviceAddress))
        {
         
            Serial.println("Found the target device!");
            Serial.print("Device name: ");
            Serial.println(advertisedDevice->getName().c_str());
            Serial.println(" | RSSI: ");
        rssiValue = advertisedDevice->getRSSI();
            
           
            if (advertisedDevice->haveServiceUUID())
            {
                BLEUUID devUUID = advertisedDevice->getServiceUUID();
                Serial.print("Service UUID: ");
                Serial.println(devUUID.toString().c_str());
            }

            if (advertisedDevice->haveManufacturerData())
            {
                std::string strManufacturerData = advertisedDevice->getManufacturerData();

                if (strManufacturerData.length() == 25 && strManufacturerData[0] == 0x4C && strManufacturerData[1] == 0x00)
                {
                    Serial.println("Found an iBeacon!");
                    // Handle iBeacon data here if needed
                }
                else
                {
                    Serial.println("Found another manufacturer's beacon!");
                    // Handle other manufacturer data here if needed
                }
            }

            // Set the flag to stop scanning after the target device is found
            targetDeviceFound = false;
        }
    }

};

void setup()
{
    Serial.begin(115200);
    


    Serial.println("Scanning for the target device...");

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);

    Serial.print("Scanning for device with MAC address: ");
    Serial.println(targetDeviceAddress.c_str());
        Serial.println(targetDeviceAddress2.c_str());

}

void loop() 
{
/*********************************************/


/*******************************************/
    if (!targetDeviceFound || !targetDeviceFound1)
    {
        BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
        Serial.print("Devices found: ");
        Serial.println(foundDevices.getCount());
        Serial.println("Scan done!");

        // Clear results to release memory
        pBLEScan->clearResults();
        //Serial.println("target device is found");
      Serial.print("RSSI0 in loop: ");
    Serial.println(rssiValue);
    Serial.print("RSSI1 in loop: ");
    Serial.println(rssiValue1);
    Serial.print("counter:");
        Serial.println(ctr);

    arr[ctr]=rssiValue;
   arr1[ctr]=rssiValue1;
   
    ctr++;
    if (ctr==120){
            Serial.println("esp Readings");
      Serial.print("{");
     for ( i=0; i<120;i++){

      Serial.print(arr[i]); 
      Serial.print(",");
              targetDeviceFound=true; 

     }
     Serial.println("}");
       Serial.println("Watch Readings");
      Serial.print("{");
     for ( i=0; i<120;i++){

      Serial.print(arr1[i]); 
      Serial.print(",");
              
 targetDeviceFound1=true;
     }
     Serial.print("}");
    
    
     
     


    }
    
   


    }


}

String intToString(int number) {
  // Use the String class to convert the integer to a string
  return String(number);
  }


