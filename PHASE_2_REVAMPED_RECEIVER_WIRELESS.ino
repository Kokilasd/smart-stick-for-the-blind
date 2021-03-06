

 //This sketch is from a tutorial video on the ForceTronics YouTube Channel. The tutorial discusses how to build a 
//shield and a prototyping board for the nRF24L01 Transceiver Module.
//the code was leverage from Ping pair example at http://tmrh20.github.io/RF24/pingpair_ack_8ino-example.html
//This sketch is free to the public to use and modify at your own risk

#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
byte bVal; //used to store ADC value payload from transmit module, the ADC value will be < 256 so it will fit in a byte
RF24 wirelessSPI(pinCE, pinCSN); // Declare object from nRF24 library (Create your wireless SPI) 
const uint64_t pAddress = 0xB00B1E5000LL;  //Create a pipe addresses for the 2 nodes to communicate over, the "LL" is for LongLong type

void setup()   
{
  Serial.begin(9600);  //start serial to communicate process
  wirelessSPI.begin();  //Start the nRF24 module
  wirelessSPI.setAutoAck(1);                    // Ensure autoACK is enabled, this means rec send acknowledge packet to tell xmit that it got the packet with no problems
  wirelessSPI.openReadingPipe(1,pAddress);      //open pipe o for recieving meassages with pipe address
  wirelessSPI.startListening();                 // Start listening for messages
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop()  
{  
  while(wirelessSPI.available())
    { 
     wirelessSPI.read( &bVal, 1 ); //read one byte of data and store it in bVal variable
     Serial.println("RECEIVED: "); 
     Serial.println(bVal); 

  if(bVal==1)
  {
  do 
    {
      do{
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        wirelessSPI.read( &bVal, 1 );
      }while(!wirelessSPI.available());
    }while(bVal==1);
  }
  else if(bVal==2)
  {
    do
    {
       do{
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        wirelessSPI.read( &bVal, 1 );
      }while(!wirelessSPI.available());
    }while(bVal==2);
  }
  else if(bVal==3)
  {
    do
    {
       do{
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        wirelessSPI.read( &bVal, 1 );
      }while(!wirelessSPI.available());
    }while(bVal==3);
  }
   else if(bVal==4)
  {
     do
    {
       do{
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        wirelessSPI.read( &bVal, 1 );
      }while(!wirelessSPI.available());
    }while(bVal==4);
  }
    }    
 }



