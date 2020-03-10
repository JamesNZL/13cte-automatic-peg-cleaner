int sensorPin = A0;
int sensorValue = 0;
int initialValue = 0;
int triggerValue = 0;
const armedValue = 1000;

int initial1 = 0;
int initial2 = 0;
int initial3 = 0;
int initial4 = 0;
int initial5 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  initial1 = analogRead(sensorPin);
  initial2 = analogRead(sensorPin);
  initial3 = analogRead(sensorPin);
  initial4 = analogRead(sensorPin);
  initial5 = analogRead(sensorPin);
  initialValue = (initial1 + initial2 + initial3 + initial4 + initial5) / 5;
  
  triggerValue = armedValue - (initialValue / 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  
  while (sensorValue >= triggerValue) {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
  }

  Serial.println("Triggered");
}
