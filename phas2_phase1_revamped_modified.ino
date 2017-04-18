#define trigPin1 3
#define echoPin1 2
#define trigPin2 4
#define echoPin2 5
#define trigPin3 7
#define echoPin3 8
#define buzzerPin 11
#define vibratorPin 12
#define trigPin4 13
#define echoPin4 6

long duration, distance;
long pinvalue1,pinvalue2;
void setup()
{
Serial.begin (9600);
Serial.print("start");
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT);
pinMode(9, OUTPUT);//CONNECT 9-6 OF SECOND ARDUINO
pinMode(10, OUTPUT);//CONNECT 10-7 OF SECOND ARDUINO
pinMode(buzzerPin, OUTPUT);
pinMode(vibratorPin, OUTPUT);
}

long SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
return (distance);
}

void beep(unsigned char delayms) 
{
  //creating function
  analogWrite(buzzerPin, 20); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
}

void vibrate(int vib) 
{
  if (vib==1)
    {
     digitalWrite(vibratorPin,HIGH); //Setting pin to high
    }
  else if (vib==2)
    {
     digitalWrite(vibratorPin,LOW); //Setting pin to low
    }
  
}

void loop() 
{
 
 do
 {
  if((SonarSensor(trigPin3, echoPin3)<=100)&&((SonarSensor(trigPin2, echoPin2)>50)||(SonarSensor(trigPin1, echoPin1)>50)))
  {
  do 
    {
      if(SonarSensor(trigPin1, echoPin1)<=50)
      {
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);//GO LEFT
      Serial.println("OBSTACLE NEAR FRONT AND RIGHT SENSOR");
      vibrate(1);
      beep(50);
      }
      else
      {
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);//GO RIGHT
      Serial.println("OBSTACLE NEAR FRONT AND LEFT SENSOR");
      vibrate(1);
      beep(50);
      }
    }while((SonarSensor(trigPin3, echoPin3)<=100)&&((SonarSensor(trigPin2, echoPin2)>50)||(SonarSensor(trigPin1, echoPin1)>50)));
  }
  else if((SonarSensor(trigPin1, echoPin1)<=50)&&((SonarSensor(trigPin2, echoPin2)>50)&&(SonarSensor(trigPin3, echoPin3)>100)))
  {
    do
    {
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);//GO LEFT
      Serial.println("OBSTACLE RIGHT SENSOR");
      vibrate(1);
      beep(50);
    }while((SonarSensor(trigPin1, echoPin1)<=50)&&((SonarSensor(trigPin2, echoPin2)>50)&&(SonarSensor(trigPin3, echoPin3)>100)));
  }
  else if((SonarSensor(trigPin2, echoPin2)<=50)&&((SonarSensor(trigPin1, echoPin1)>50)&&(SonarSensor(trigPin3, echoPin3)>100)))
  {
    do
    {
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);//GO RIGHT
      Serial.println("OBSTACLE NEAR LEFT SENSOR");
      vibrate(1);
      beep(50);
    }while((SonarSensor(trigPin2, echoPin2)<=50)&&((SonarSensor(trigPin1, echoPin1)>50)&&(SonarSensor(trigPin3, echoPin3)>100)));
  }
   else if(((SonarSensor(trigPin2, echoPin2)<=50)&&(SonarSensor(trigPin1, echoPin1)<=50)&&(SonarSensor(trigPin3, echoPin3)<=100))||(SonarSensor(trigPin4, echoPin4)>40))
  {
     digitalWrite(9,LOW);
     digitalWrite(10,LOW);
     Serial.println("OBSTACLE NEAR FRONT,LEFT AND RIGHT SENSOR OR POTHOLE DETECTED");
     vibrate(1);
     beep(50);
  }
   else
   {
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    Serial.println("NO OBSTACLES");
    vibrate(2);
   }
 }while(true);
}
  
 
