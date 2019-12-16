#define A 8 //Motor Pin 1
#define B 7 //Motor Pin 2
#define C 6 //Motor Pin 3
#define D 5      //Motor Pin 4
int tp1=11; //Ultrasonic Sensor 1 Trigger Pin
int ep1=10; //Ultrasonic Sensor 1 Echo Pin
int tp2=A1; //Ultrasonic Sensor 2 Trigger Pin
int ep2=A2; //Ultrasonic Sensor 2 Echo Pin
int countqw=0;
int tp3=9;
int ep3=A3;
int ir1=A5; //IR Sensor 1
//int ir2=A3; //IR Sensor 2
int th1=A0; //Thermister
int re=A4; //Relay
int most=0;
//int buc=8; //Buzzer
int moo=0;
int mik=0;
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
  pinMode(tp3,OUTPUT);
  //pinMode(respin,OUTPUT);//Reset
   
  pinMode(ep1,INPUT); //Ultrasonic Sensor 1 Echo Pin
  pinMode(ep2,INPUT); //Ultrasonic Sensor 2 Echo Pin
  pinMode(ep3,INPUT);
 pinMode(ir1,INPUT); //IR Sensor 1
  //pinMode(ir2,INPUT); //IR Sensor 2
  pinMode(th1,INPUT); //Thermister
  Serial.begin(9600);
}

void loop() 
{
  
  most=0;
  buzz(); //Check Buzzer Condition
  
  an1= uta(); //Ultrasonic Front Value
  an2= utb(); //Ultrasonic Left Value
  an3=utc();//Ultrasonic Right Value
  //an3= ina(); //IR Left Value
  an4= ina(); //IR Back Value
  
  ch5=thermoa(); //Thermostat Reading
  Serial.print(ch5);
  if(ch5>35) //buzz and turn off
  {
    moo=1;
    buzz();
   
  }
 if(an1>=18) //Front ok. //Go Front.
 {
  motfow();
  correct();
 }
 else if(an1<=18&&an3>=18) //Front not ok, right ok. //Go right.
  motrig();
 else if(an1<=18&&an3<18&&an2>=18) //Front not ok, right not ok, ,left ok. //Go left.
  motlef();
 else if(an1<=18&&an3<18&&an2<18) // Front, Right, Left not ok. //Reverse and take right.
  revrig();  
//else if(an1<=20&&an3<15&&an2<15&&an4>=1) // All sides bloaked
//{
 //  fulloff();
  // dance2();
//}
}

void correct()
{
  if(an1>=18)//&&an3>=15)
{
  countqw++;
  if(countqw== 30 )//Trial and Error
  {
    countqw=0;
    Serial.println("Correcting Right....");
    rightlight();
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
    delay(5.5);
  }
}
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
long utc() //Reading the Values from Ultrasonic Temperature 2
{
  long duration,cm;
  digitalWrite(tp3, LOW);
  delayMicroseconds(2);
  digitalWrite(tp3, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp3, LOW);
  duration = pulseIn(ep3, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance 3 = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(5);
  return cm;
}

int ina() //Read Vaalue from Infrared 1
{
  int detect=analogRead(ir1);
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
     
      
      if(mik==0)
    { 
   digitalWrite(A,HIGH); //Motors are reversed
   digitalWrite(B,LOW);
   digitalWrite(C,HIGH);
   digitalWrite(D,LOW);
   delay(1200);
  fulloff();
   mik++;
    }
    
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
  fulloff();
  delay(3000);
  rightlight();
  countqw=0;
  Serial.println("Turning Right....");
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  delay(2400);
  void();
}

void motlef() //Front not ok, right not ok, ,left ok. //Go left.
{
  fulloff();
  delay(3000);
  leftlight();
  countqw=0;
  Serial.println("Turning LEft....");
  digitalWrite(A,HIGH);//turn left
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  delay(2000);
  
}
void revrig() // Front, Right, Left not ok. //Reverse and take right.
{
  countqw=0;
  while(an3<=18) //Perform until Obstacle is found
  {
    countqw=0;
    backlight();
    an1= uta(); //Ultrasonic Front
    an2= utb(); //Ultrasonic Back
    an3= utc(); //IR Left
    an4= ina(); //IR Right
    //stoppa();
   digitalWrite(A,HIGH); //Motors are reversed
   digitalWrite(B,LOW);
   digitalWrite(C,HIGH);
   digitalWrite(D,LOW);
   nolight();
  //if(an4>=1)
   //{
   //condlev();
  // }
  }delay(2000);
    digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  delay(2300);
  
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
  nolight();
    digitalWrite(l1,HIGH);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,LOW);
    digitalWrite(l4,LOW);
}
void leftlight ()
{
    nolight();
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(l3,HIGH);
    digitalWrite(l4,LOW);
  
}

void rightlight ()
{
    nolight();
    digitalWrite(l1,LOW);
    digitalWrite(l2,HIGH);
    digitalWrite(l3,LOW);
    digitalWrite(l4,HIGH);
}

void backlight ()
{
    nolight();
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
