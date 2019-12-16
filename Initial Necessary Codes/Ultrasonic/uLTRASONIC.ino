const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int i=0;
void setup() {
   Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
   long duration, inches, cm;
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
   delay(400);

if(cm>=20)
  i++;
  else
  i=0;

if(i>17)
{
Serial.println("OFF");
delay(3000);
i=0;

}
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
