#include<Servo.h>
String voice;

const int TRIG_PIN = 5; //Define 5 as the Trigger Pin for Ultrasonic Sensor
const int ECHO_PIN = 3; //Define 3 as the Echo Pin for Ultrasonic Sensor
const int Buzzer = 2; //Define 2 as the buzzer pin
const int led1 = 4; //Define 4 as led 1
const int led2 = 7; //Define 7 as led 2

long duration;
int distance;
Servo myServo;

int lm1 = 9;
int lm2 =8;
int rm1=10;
int rm2=11;

int readPing() 
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW); 
  int cm;
  duration = pulseIn(ECHO_PIN, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  cm=(duration*0.034)/2;
  return cm;
}

void Buzzer_on()
{
  digitalWrite(Buzzer, HIGH);
}

void Buzzer_off()
{
  digitalWrite(Buzzer, LOW);
}

void Lights_on()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH); 
}

void Lights_off()
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
}

void forward ()
{
 /*distance = readPing();
 Serial.print("Distance: ");
 Serial.println(distance);
 if(distance>150)
 {*/
  digitalWrite(lm1,HIGH); 
  digitalWrite(lm2,LOW); 
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);  
 /*}
 else
 {
  Buzzer_on();
  delay(2000);
  Buzzer_off();
 }*/
}

/*void backward()
{
 digitalWrite(lm1,LOW); 
 digitalWrite(lm2,HIGH); 
 digitalWrite(rm1,LOW);
 digitalWrite(rm2,HIGH); 
}*/

void left()
{
  myServo.write(180);
  
  delay(1000);
  distance=readPing();
  myServo.write(90);
  delay(1000);
  Serial.print("Distance: ");
 Serial.println(distance);
  if(distance>30)
  {
    digitalWrite(lm1,LOW); 
    digitalWrite(lm2,LOW); 
    digitalWrite(rm1,HIGH);
    digitalWrite(rm2,LOW);
  }
  else
  {
    Buzzer_on();
    delay(2000);
    Buzzer_off();
  }
}
 
void right()
{
  myServo.write(0);
  
  delay(1000);
  distance=readPing();
  myServo.write(90);
  delay(1000);
  Serial.print("Distance: ");
 Serial.println(distance);
  if(distance>30)
  {
    digitalWrite(lm1,HIGH); 
    digitalWrite(lm2,LOW); 
    digitalWrite(rm1,LOW);
    digitalWrite(rm2,LOW);
  }
  else
  {
    Buzzer_on();
    delay(2000);
    Buzzer_off();
  }
}

void finish()
{
 digitalWrite(lm1,LOW); 
 digitalWrite(lm2,LOW); 
 digitalWrite(rm1,LOW);
 digitalWrite(rm2,LOW); 
}

void setup()
{
  Serial.begin(9600);
  myServo.attach(6); //define our servo pin to 6
  myServo.write(0); //servo position is 0 degrees
  myServo.write(90); //servo position is 90 degrees
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT); //5 is output pin
  pinMode(ECHO_PIN, INPUT); //3 is input pin
  pinMode(Buzzer, OUTPUT); //2 is output pin
  pinMode(led1, OUTPUT); //4 is output pin
  pinMode(led2, OUTPUT); //7 is output pin
}

void loop()
{
 
      while(Serial.available())
      {
      delay(10);
      char c=Serial.read();
      if(c=='#')
      {break;}

      voice += c;
      }
      
      distance = readPing();
      if(distance<30)
        finish();

  if(voice.length() > 0)
  {
   Serial.println(voice);
   if (voice == "*go ahead")
   {
    if(distance>30)
    {
      forward();
    }
    else
    {
      Buzzer_on();
      delay(2000);
      Buzzer_off();
    }
   }
   /*else if(voice == "*backward")
   {backward() ;}*/
   else if (voice == "*turn right")
   {
    /*myServo.write(0);
    distance=readPing();
    delay(1000);
    myServo.write(90);
    delay(1000);
    if(distance>30)
    {*/
      right();
      delay(500);
      finish();
    /*}
    else
    {
      Buzzer_on();
      delay(2000);
      Buzzer_off();
    }*/
   }
   else if(voice == "*turn left")
   {
    /*myServo.write(180);
    distance=readPing();
    delay(1000);
    myServo.write(90);
    delay(1000);
    if(distance>30)
    {*/
    left();
    delay(500);
    finish();
    /*}
    else
    {
      Buzzer_on();
      delay(2000);
      Buzzer_off();
    } */
   }
   else if(voice=="*lights on")
   {Lights_on();}
   else if(voice=="*lights off")
   {Lights_off();}
   else if(voice == "*stop")
   {finish() ;}
   voice="";
  }

}
