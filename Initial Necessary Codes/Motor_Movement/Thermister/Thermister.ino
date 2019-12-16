w float analogTemp, digitalTemp, temp;
int in1=A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1,INPUT); //to set the pin mode
  Serial.begin(9600); //set baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  analogTemp=analogRead(in1); //read analog temp value
  digitalTemp=analogTemp/1024*5000;  //converting analog value to digital value
  digitalTemp=digitalTemp/10; //every 10mv corresponds to 1 degree celsius
  Serial.print("Temperature in degree Celsius: "); //to print the temperature in a new or next line
  Serial.print(digitalTemp); //printing the temperature value with the statement above
  Serial.println();
  delay(1000);
}
