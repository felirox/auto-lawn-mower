#define in 8
void setup() {
pinMode(in,OUTPUT);  // put your setup code here, to run once:

}

void loop() {
 digitalWrite(in,HIGH);
 delay(100);
 digitalWrite(in,LOW);
 delay(100);
 digitalWrite(in,HIGH);
 delay(70);
 digitalWrite(in,LOW);
 delay(50);
 digitalWrite(in,HIGH);
 delay(50);
 digitalWrite(in,LOW);
 delay(20);
 digitalWrite(in,HIGH);
 delay(300);
 digitalWrite(in,LOW);
 delay(100);// put your main code here, to run repeatedly:

}
