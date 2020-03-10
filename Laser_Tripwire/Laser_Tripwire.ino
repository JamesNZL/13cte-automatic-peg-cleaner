int sensorPin = A0;
int sensorValue = 0;
int initialValue = 0;
int triggerValue = 0;
const armedValue = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  initialValue = analogRead(sensorPin);
  triggerValue = armedValue - (initialValue / 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (sensorValue >= triggerValue) {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
  }
}
