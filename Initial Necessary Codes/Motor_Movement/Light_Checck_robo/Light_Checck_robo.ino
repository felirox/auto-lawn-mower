#define A 8 //Motor Pin 1
#define B 7 //Motor Pin 2
#define C 6 //Motor Pin 3
#define D 5      //Motor Pin 4
int tp1=11; //Ultrasonic Sensor 1 Trigger Pin
int ep1=10; //Ultrasonic Sensor 1 Echo Pin
int tp2=A1; //Ultrasonic Sensor 2 Trigger Pin
int ep2=A2; //Ultrasonic Sensor 2 Echo Pin
int ir1=9; //IR Sensor 1
int ir2=A3; //IR Sensor 2
int th1=A0; //Thermister
int re=A4; //Relay
int most=0;
//int buc=8; //Buzzer
int moo=0;
int dema=0;
#define l1 13 //LED 1
#define l2 12 //LED 2
#define l3 2 //LED 3
#define l4 3 //LED 4
int templight =0;
//#define respin A5 //Reset Pin
int an1,an2,an3,an4,ch5;
float analogTemp, digitalTemp, temp;

void setup() 
{
  pinMode(l1,OUTPUT); //LED 1
  pinMode(l2,OUTPUT); //LED 2
  pinMode(l3,OUTPUT); //LED 3
  pinMode(l4,OUTPUT); //LED 4
  pinMode(re,OUTPUT); //Relay
  pinMode(A,OUTPUT); //Motor Pin 1
  pinMode(B,OUTPUT); //Motor Pin 2
  pinMode(C,OUTPUT); //Motor Pin 3
  pinMode(D,OUTPUT); //Motor Pin 4
  pinMode(tp1,OUTPUT); //Ultrasonic Sensor 1 Trigger Pin
  pinMode(tp2,OUTPUT);//Ultrasonic Sensor 2 Trigger Pin
  //pinMode(respin,OUTPUT);//Reset
   
  pinMode(ep1,INPUT); //Ultrasonic Sensor 1 Echo Pin
  pinMode(ep2,INPUT); //Ultrasonic Sensor 2 Echo Pin
  pinMode(ir1,INPUT); //IR Sensor 1
  pinMode(ir2,INPUT); //IR Sensor 2
  pinMode(th1,INPUT); //Thermister
  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
}


float thermoa() //Thermostat Temperature Reading
{
  analogTemp=analogRead(th1); //read analog temp value
  digitalTemp=analogTemp/1024*3500;  //converting analog value to digital value
  digitalTemp=digitalTemp/10; //every 10mv corresponds to 1 degree celsius
  Serial.print("Temperature in degree Celsius: "); //to print the temperature in a new or next line
  Serial.print(digitalTemp); //printing the temperature value with the statement above
  Serial.println();
  return digitalTemp;
}



long uta() //Reading the Values from Ultrasonic Temperature 1
 {
  long duration,cm;
  digitalWrite(tp1, LOW);
  delayMicroseconds(2);
  digitalWrite(tp1, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp1, LOW);
  duration = pulseIn(ep1, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance 1 = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(5);
  return cm; //Retuen US  Value
}

long utb() //Reading the Values from Ultrasonic Temperature 2
{
  long duration,cm;
  digitalWrite(tp2, LOW);
  delayMicroseconds(2);
  digitalWrite(tp2, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp2, LOW);
  duration = pulseIn(ep2, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance 2 = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(5);
  return cm;
}

int ina() //Read Vaalue from Infrared 1
{
  int detect=digitalRead(ir1);
  Serial.print(" Distance 3 = ");
  Serial.println(ir1);
  return detect;
}

int inb() //Read Vaalue from Infrared 2
{
  int detect=digitalRead(ir2);
  Serial.print(" Distance 4 = ");
  Serial.println(ir1);
  return detect;
}

void buzz() //Relay turned ON to switch off motors and ring buzzer if temp gets high
{
  if(moo!=0)
  {
    fulloff();
    while(true)
    {
      digitalWrite(re,HIGH);
      dance2();
    }
  }
}

void motfow() //Front ok. //Go Front.
{
  frontlight();
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  
}

void motrig() //Front not ok, right ok. //Go right.
{
  rightlight();
  Serial.println("Turning Right....");
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  delay(2600);
  void();
}

void motlef() //Front not ok, right not ok, ,left ok. //Go left.
{
  leftlight();
  Serial.println("Turning LEft....");
  digitalWrite(A,HIGH);//turn left
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  delay(2000);
  void();
}
void revrig() // Front, Right, Left not ok. //Reverse and take right.
{
  while(an4>=1) //Perform until Obstacle is found
  {
    backlight();
    an1= uta(); //Ultrasonic Front
    an2= utb(); //Ultrasonic Back
    an3= ina(); //IR Left
    an4= inb(); //IR Right
    stoppa();
   digitalWrite(A,HIGH); //Motors are reversed
   digitalWrite(B,LOW);
   digitalWrite(C,HIGH);
   digitalWrite(D,LOW);
   nolight();
   if(an2<35)
   {
     condlev();
   }
  }delay(1000);
    motrig();
  
}

void stoppa() //Check if all sides are bloked and if yes, stop moving.
{
  an1= uta(); //Ultrasonic Front Value
  an2= utb(); //Ultrasonic Back Value
  an3= ina(); //IR Left Value
  an4= inb(); //IR Right Value
  if(an1<=22&&an3==1&&an4==1&&an2<=22)
  {
    fulloff();
    dance1();
  }
}

long condlev() //Specisl case if all sides are blocked and only if Left is free
{
  an1= uta(); //Ultrasonic Front
  an2= utb(); //Ultrasonic Back
  an3= ina(); //IR Left
  an4= inb(); //IR Right
  if(an1<=22&&an4==1&&an2<30&&an3==0) // Front, Right, Back not ok. Left ok. //Take left.
  {  
    leftlight();
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);
    delay(4800);
    most=1;
  }
}

void fulloff() //Switch off all the motors
{
  digitalWrite(A,LOW); //Motor Pin values set to stop
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
}
void nolight()
{
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  digitalWrite(l3,LOW);
  digitalWrite(l4,LOW);
}

void frontlight()
{
  
 
    digitalWrite(l1,HIGH);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,LOW);
    digitalWrite(l4,LOW);
}
void leftlight ()
{

    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(l3,HIGH);
    digitalWrite(l4,LOW);
  
}

void rightlight ()
{
  
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,LOW);
    digitalWrite(l4,HIGH);
}

void backlight ()
{
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    digitalWrite(l3,HIGH);
    digitalWrite(l4,HIGH);
}
void dance1()
{ 
    if(dema%80==0)
    {
      digitalWrite(l1,HIGH);
      delay(300);
    }
    else if(dema%60==0)
    {
      digitalWrite(l2,HIGH);
      delay(300);
    }
    else if(dema%40==0)
    {
      digitalWrite(l3,HIGH);
      delay(300);
    }
    else if(dema%20==0)
    {
      digitalWrite(l4,HIGH);
      delay(300);
    }
    else
    {
      dema++;
      nolight();
    }

  }
  void dance2()
  {
    digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(50);
  nolight();
  delay(50);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(50);
  nolight();
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(50);
  nolight();
  delay(150);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(250);
  nolight();
  delay(350);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(450);
  nolight();
  delay(250);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(350);
  nolight();
  delay(250);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(150);
  nolight();
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(850);
  nolight();
  digitalWrite(l1,HIGH);
  digitalWrite(l2,HIGH);
  digitalWrite(l3,HIGH);
  digitalWrite(l4,HIGH);
  delay(150);
  nolight();
}
long microsecondsToCentimeters(long microseconds)  //Conversion of Microsecinds to Centimetres
{
   return microseconds / 29 / 2;
}

//This project was created by Niran N in PC://Felirox by an open source platform Arduino IDE 1.8.7 
//The program being viewed has it's Copyright Accreditation for Niran N and in no circumstances  can this program be 
//used for mass replication without the consent of the creator. However, it can be used for any individual's non-profitable personal work
//Non-Organizational work. Contact the owner of this project <niran@live.co.uk> for any other further clarifications.
