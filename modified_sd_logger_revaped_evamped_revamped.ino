#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include <SD.h>

File myFile;
/*
 *
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 5, TXPin = 6;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
double lat1=0;
long lat2=0;
double lon1;
long lon2=0;

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  

}
void loop()
{
  Serial.println("lon2 is:  ");
  Serial.println(lon2);
  Serial.println("lat2 is   ");
  Serial.println(lat2);
  
      while (ss.available()>0){
      
      if (gps.encode(ss.read()))   
      {  
        Serial.print(F("Location: ")); 
       
  if (gps.location.isValid())
  {
    lat1=(gps.location.lat())*1000000; 
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    lon1=(gps.location.lng())*1000000;
    Serial.print(gps.location.lng(),6);
        
  }
  else
  {
    Serial.print(F("INVALID"));
      
  }

  Serial.print(F("  Date/Time: "));
   
   if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
    
  }

  Serial.print(F(" "));
   
 
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print((gps.time.hour())+5);
    
    Serial.print(F(":"));
    
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print((gps.time.minute())+30);
    
    Serial.print(F(":"));
    
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
   
    Serial.print(F("."));
   
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
    
    
  }
  else
  {
    Serial.print(F("INVALID"));
    
  }

  if((lat1!=lat2)||(lon1!=lon2))
  {     
     myFile = SD.open("test.txt", FILE_WRITE);
     if(myFile)
      {
      myFile.print("Location: ");
      myFile.print(gps.location.lat(),6);
      myFile.print(",");
      myFile.print(gps.location.lng(),6);
      myFile.print("  Date/Time: ");
      myFile.print(gps.date.month());
      myFile.print("/");
      myFile.print(gps.date.day());
      myFile.print("/");
      myFile.print(gps.date.year());
      myFile.print(" ");
      myFile.print("0");
      myFile.print(((gps.time.hour())+5)%24);
      myFile.print(":");
      myFile.print("0");
      myFile.print(((gps.time.minute())+30)%60);
      myFile.print(":");
      myFile.print("0");
      myFile.print(gps.time.second());
      myFile.print(".");
      myFile.print("0");
      myFile.print(gps.time.centisecond());
      myFile.println();
      Serial.println();
      myFile.close();
      Serial.println("data stored");
      lon2=lon1;
      lat2=lat1;
      }
      
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  }
}
}
}
