#define in 12
#define in1 11
void setup() {
 pinMode(in,OUTPUT);
 pinMode(in1,OUTPUT);// put your setup code here, to run once:

}

void loop() {
  digitalWrite(in,HIGH);
  delay(500);
  digitalWrite(in,LOW);
  digitalWrite(in1,HIGH);
  delay(500);
  digitalWrite(in1,LOW);
  // put your main code here, to run repeatedly:

}
