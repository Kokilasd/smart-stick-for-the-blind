//*****************************Arduino Code for Transmitter***********************
//This sketch is from a tutorial video on the ForceTronics YouTube Channel. The tutorial discusses how to build a 
//shield and a prototyping board for the nRF24L01 Transceiver Module.
//the code was leverage from Ping pair example at http://tmrh20.github.io/RF24/pingpair_ack_8ino-example.html
//This sketch is free to the public to use and modify at your own risk

#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
RF24 wirelessSPI(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
const uint64_t pAddress = 0xB00B1E5000LL;   // Radio pipe addresses for the 2 nodes to communicate.

long pinvalue1,pinvalue2;

#include "SIM900.h"
#include <SoftwareSerial.h>

#include "sms.h"
SMSGSM sms;

boolean started=false;
int count=0;

const int buttonPin = 4;     // the number of the pushbutton pin

int buttonState = 0;         // variable for reading the pushbutton status

void setup()  
{
  Serial.begin(9600);   //start serial to communicate process
  wirelessSPI.begin();            //Start the nRF24 module
  wirelessSPI.setAutoAck(1);                    // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
  wirelessSPI.setRetries(5,15);                 // Sets up retries and timing for packets that were not ack'd, current settings: smallest time between retries, max no. of retries
  wirelessSPI.openWritingPipe(pAddress);        // pipe address that we will communicate over, must be the same for each nRF24 module
  wirelessSPI.stopListening();
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.println("GSM Shield testing.");
  //Start configuration of shield with baudrate.
  //For http uses is raccomanded to use 4800 or slower.
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true;  
  }
  else Serial.println("\nstatus=IDLE");
  
}

void loop()  
{
   
    pinvalue1=digitalRead(6);
    pinvalue2=digitalRead(7);



    if (pinvalue1== HIGH && pinvalue2== HIGH)
{
  byte t = 1; 
  wirelessSPI.write(&t, 1 );
 }

else if (pinvalue1== HIGH && pinvalue2== LOW)
{
byte t = 2; 
  wirelessSPI.write(&t, 1 );
}

else if (pinvalue1== LOW && pinvalue2== HIGH)
{
byte t = 3; 
  wirelessSPI.write(&t, 1 );
}

else if (pinvalue1== LOW && pinvalue2== LOW)
{
byte t = 4; 
  wirelessSPI.write(&t, 1 );
}


buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) 
  {
    Serial.println("ON");
    while(count!=1)
     {
       if(started)
        {
           if (sms.SendSMS("08547889564", "SOS"))
           Serial.println("\nSMS sent OK");
           count++;
        }
     }
  }
  else
  {
   Serial.println("OFF");
  }
}
