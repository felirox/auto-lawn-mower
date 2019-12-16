int sensorValue;
int GasSensorPin = A0; //Gas Sensor Connection
void setup()
{
 Serial.begin(9600);      // sets the serial port to 9600
 pinMode(GasSensorPin,INPUT);
}

void loop()
{
 sensorValue = analogRead(GasSensorPin);       // read analog input pin 0
 Serial.println(sensorValue, DEC); 
 Serial.println(sensorValue);// prints the value read
 delay(2000);                        // wait 100ms for next reading
}
