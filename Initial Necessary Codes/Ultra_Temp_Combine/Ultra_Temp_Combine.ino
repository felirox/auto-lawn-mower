
const int E1=13; // low 1
const int E2=12; // low 2
const int E3=11; // mid
const int E4=10; //high 1
const int E5=4;  //high 2
const int E6=5;//base low
const int E7=9;//mode
const int pingPin = 7;  //ping
const int echoPin = 6;  //echo
const int resd = 8;
int i=1;//hahaha
int j;
int ir=1;
int co;
int temp;
int dar;
int pp=1;
int r=1;
//
#include <dht.h>
dht DHT;
#define DHT11_PIN 3
void setup() 
{
  Serial.begin(19200);
  pinMode(E1,OUTPUT);
  pinMode(E2,OUTPUT);
  pinMode(E3,OUTPUT);
  pinMode(E4,OUTPUT);
  pinMode(E5,OUTPUT);
  pinMode(E6,OUTPUT);
  pinMode(E7,OUTPUT);
  pinMode(resd,OUTPUT);
}

void loop() 
{
  temp=digitalRead(resd);
  if(temp==HIGH)
  {
  if(ir==1)
  {
    allone();
    delay(2000);
    alloff();
    delay(400);
    fun();
    fun();
    delay(80);
    allone();
    delay(100);
    alloff();
    delay(100);
    allone();
    delay(510);
    alloff();
    delay(500);
    ir++;
  }
  if(j%15==0)
  {
    if(co%2==0)
    {
      digitalWrite(E7,HIGH);
      co++;
    }
    else
    {
      digitalWrite(E7,LOW);
      co++;
    }
  }
  j++;
  
  long duration,cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if(cm<10)
  {
     allone();
    alloff();
    
    Serial.println("Output Sent: All LED ON");
  }
  else if(cm<15)
  {
     
    alloff();
    oneoff();
    Serial.println("Output Sent: ONE LED OFF");
  }
  else if(cm<23)
  {
     
    alloff();
    twooff();
    Serial.println("Output Sent: TWO LED'S OFF");
  }
  else if(cm<29)
  {
     
    alloff();
    threeoff();
    Serial.println("Output Sent: THREE LED'S OFF");
  }
  else if(cm<36)
  {
     
    alloff();
    fouroff();
    Serial.println("Output Sent: FOUR LED'S OFF");
  }
  else if(cm<70)
  {
    alloff();
    dar = 70-cm;
    dar = dar*5;
    analogWrite(E6,dar);
  }
  else
  {
    
    alloff();
    Serial.println("Output Sent: ALL LED'S OFF");
  }
  Serial.println("Loop Over");  
  //delay(500);
  //delay(1000);
}
else if(temp==LOW)                            //temp mode ativate!!!
{
  
  
  //
  
  if(j%5000==0)
  {
    if(co%2==0)
    {
      if(pp==1)
      {
        alloff();
        digitalWrite(E1,HIGH);
        digitalWrite(E6,HIGH);
        pp=2;
      }
      else if(pp==2)
      {
        alloff();
        digitalWrite(E2,HIGH);
        digitalWrite(E5,HIGH);
        if(r==1)
        {
           pp=3;
           r++;
        }
        else
        {
          pp=1;
          r--;
        }
      }
      else if(pp==3)
      {
        alloff();
        digitalWrite(E3,HIGH);
        digitalWrite(E4,HIGH);
        pp=2;
      }
      digitalWrite(E7,HIGH);
      co++;
    }
    else
    {
      digitalWrite(E7,LOW);
      co++;
       
    }
    if(i%15==0)
    {
    int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  i++;
    }
    else 
    {
      i++;
    }
}
j++;
}
}
//converter
long microsecondsToCentimeters(long microseconds) 
{
   return microseconds / 29 / 2;
}
// led controllers
void alloff()
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
  digitalWrite(E3,LOW);
  digitalWrite(E4,LOW);
  digitalWrite(E5,LOW);
  digitalWrite(E6,LOW);
}
void allone()
{
  digitalWrite(E1,HIGH);
  digitalWrite(E2,HIGH);
  digitalWrite(E3,HIGH);
  digitalWrite(E4,HIGH);
  digitalWrite(E5,HIGH);
  analogWrite(E6,170);
}
void oneoff()
{
  digitalWrite(E2,HIGH);
  digitalWrite(E3,HIGH);
  digitalWrite(E4,HIGH);
  digitalWrite(E5,HIGH);
  analogWrite(E6,170);
}
void twooff()
{
  digitalWrite(E3,HIGH);
  digitalWrite(E4,HIGH);
  digitalWrite(E5,HIGH);
  analogWrite(E6,170);
}
void threeoff()
{
  digitalWrite(E4,HIGH);
  digitalWrite(E5,HIGH);
  analogWrite(E6,170);
}
void fouroff()
{
  digitalWrite(E5,HIGH);
  analogWrite(E6,170);
}
void fun()
{
  analogWrite(E6,170);
  delay(600);
  alloff();
  digitalWrite(E5,HIGH);
  delay(600);
  alloff();
  digitalWrite(E4,HIGH);
  delay(600);
  alloff();
  digitalWrite(E3,HIGH);
  delay(600);
  alloff();
  digitalWrite(E2,HIGH);
  delay(600);
  alloff();
  digitalWrite(E1,HIGH);
  delay(600);
  alloff();
}
