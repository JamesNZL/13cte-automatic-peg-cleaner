int sensorPin = A0;
int sensorValue = 0;
int disarmedValue = 0;
int triggerAt = 0;
int testTotal = 0;
const testIterations = 5;
const armedValue = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // TURN LASER MODULE OFF

  for (int i = 0; i <= (testIterations - 1); i++) {
    testTotal += analogRead(sensorValue);
  }

  disarmedValue = testTotal / testIterations;
  triggerAt = armedValue - (disarmedValue / 2);

  // TURN LASER MODULE ON
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
