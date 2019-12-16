#define A 7
#define B 6
#define C 5
#define D 4
int co=0;
void setup() {
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
   pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);

}


void loop() {
   digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  delay(5000);

  

  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  delay(1000);
}
