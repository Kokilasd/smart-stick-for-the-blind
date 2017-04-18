// Motor 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 6;
int dir2PinB = 4;
int speedPinB = 7; // Needs to be a PWM pin to be able to control motor speed
long pinvalue1,pinvalue2;
void setup() {  // Setup runs once per reset
// initialize serial communication @ 9600 baud:
Serial.begin(9600);

//Define L298N Dual H-Bridge Motor Controller Pins

pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(speedPinB,OUTPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);

}

void loop() {

pinvalue1=digitalRead(10);
pinvalue2=digitalRead(11);
Serial.print("pin value 1:");
Serial.print(pinvalue1);
Serial.print("pin value 2:");
Serial.print(pinvalue2);

if (pinvalue1== HIGH && pinvalue2== HIGH)
{
  Serial.println("GO STRAIGHT");
analogWrite(speedPinA, 255);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 255);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
}

else if (pinvalue1== HIGH && pinvalue2== LOW)
{
  Serial.println("GO LEFT");
analogWrite(speedPinA, 255);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 16);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
}

else if (pinvalue1== LOW && pinvalue2== HIGH)
{
  Serial.println("GO RIGHT");
analogWrite(speedPinA, 16);
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 255);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
}

else if (pinvalue1== LOW && pinvalue2== LOW)
{
  Serial.println("STOP");
analogWrite(speedPinA, 0);
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB, 0);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, LOW);
}
  
      }
