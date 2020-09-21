int sensorValue;
int disarmedValue;
int triggerAt;
int testTotal;
const int batteryPin = A0;
const int waterPin = A1;
const int ldrPin = A2;
const int powerGate = 2;
const int offButton = 3;
const int drainButton = 4;
const int jetGate = 6;
const int drainGate = 8;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int laserPin = 12;
const int testIterations = 5;
const int maximumValue = 1023;

void setup() 
{
	pinMode(batterPin, INPUT);
	pinMode(waterPin, INPUT);
	pinMode(ldrPin, INPUT);
	pinMode(offButton, INPUT);
	pinMode(drainButton, INPUT);
	pinMode(powerGate, OUTPUT);
	pinMode(jetGate, OUTPUT);
	pinMode(powerGate, OUTPUT);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	pinMode(laserPin, OUTPUT);
	
	digitalWrite(powerGate, HIGH);

	Serial.begin(9600);

	digitalWrite(laserPin, LOW);

	for (int i = 0; i <= (testIterations - 1); i++) {
		testTotal += analogRead(sensorValue);
	}

	digitalWrite(laserPin, HIGH);

	disarmedValue = testTotal / testIterations;
	triggerAt = (maximumValue + disarmedValue) / 2;

	sensorValue = analogRead(sensorPin);

	if (sensorValue < triggerAt) {
		digitalWrite(redPin, HIGH);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, LOW);
	}
	
	else if (sensorValue > triggerAt) {
		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, HIGH);
		digitalWrite(bluePin, LOW);
	}
}

void loop() 
{
	sensorValue = analogRead(sensorPin);
	
	while (sensorValue >= triggerAt) {
		sensorValue = analogRead(sensorPin);
		Serial.println(sensorValue);
	}

	Serial.print("Triggered @ ");
	Serial.println(sensorValue);
}
