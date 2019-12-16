//Motor A
const int ip1=11;
const int ip2=10;
const int ip3=9;
const int ip4=8;
const int ip5=7;
const int ip6=6;
const int ip7=5;
const int ip8=4;
int tp1=A2;
int ep1=A3;
int tp2=12;
int ep2=13;
int ir1=A0;
int ir2=A4;
void setup()
{
  pinMode(ip1,OUTPUT);
  pinMode(ip2,OUTPUT);
   pinMode(ip3,OUTPUT);
  pinMode(ip4,OUTPUT);
  pinMode(ip5,OUTPUT);
  pinMode(ip6,OUTPUT);
   pinMode(ip7,OUTPUT);
  pinMode(ip8,OUTPUT);
  pinMode(tp1,OUTPUT);
  pinMode(ep1,INPUT);
   pinMode(tp2,OUTPUT);
  pinMode(ep2,INPUT);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  Serial.begin(9600);
}
 void firsen()
 {
  long duration,cm;
  //pinMode(pingPin, OUTPUT);
  digitalWrite(tp1, LOW);
  delayMicroseconds(2);
  digitalWrite(tp1, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp1, LOW);
  //pinMode(echoPin, INPUT);
  duration = pulseIn(ep1, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(5);

  if(cm<5)
  
 {
  digitalWrite(ip1,LOW);
 }
 else
 {
  digitalWrite(ip1,HIGH);
 }
 }
 void secsen()
 {
   long duration,cm;
  //pinMode(pingPin, OUTPUT);
  digitalWrite(tp2, LOW);
  delayMicroseconds(2);
  digitalWrite(tp2, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp2, LOW);
  //pinMode(echoPin, INPUT);
  duration = pulseIn(ep2, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print("Distance = ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(5);

 if(cm<5)
 {
  digitalWrite(ip3,LOW);
 }
 else
 {
  digitalWrite(ip3,HIGH);
 }
 }
 void thisen()
 {
  if(digitalRead(ir1)==HIGH)
  {
    digitalWrite(ip5,LOW);
    
  }
 else
 {
  digitalWrite(ip5,HIGH);
 }
 }
 void fousen()
 {
  if(digitalRead(ir2)==HIGH)
  {
    digitalWrite(ip7,LOW);  
  }
 else
 {
  digitalWrite(ip7,HIGH);
 }
 }
 void loop ()
 {
  Serial.println("/n");
 firsen();
delay(100);
secsen();
delay(100);
thisen();
delay(100);
fousen();
delay(100);

  
  
 }
 
long microsecondsToCentimeters(long microseconds) 
{
   return microseconds / 29 / 2;
}
