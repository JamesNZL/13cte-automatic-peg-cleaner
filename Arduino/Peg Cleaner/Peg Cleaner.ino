int batteryValue;
int waterValue;
int ldrValue;
int offInput;
int drainInput;
int disarmedValue;
int triggerAt;
int testTotal;
int waterMinimum = 200;
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
unsigned long currentTime;
unsigned long lastAction = 0;
bool waterDanger = false;

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
		testTotal += analogRead(ldrValue);
	}

	digitalWrite(laserPin, HIGH);
	lastAction = currentTime;

	disarmedValue = testTotal / testIterations;
	triggerAt = (maximumValue + disarmedValue) / 2;

	ldrValue = analogRead(ldrPin);

	if (ldrValue < triggerAt) {
		digitalWrite(redPin, HIGH);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, LOW);

		digitalWrite(powerGate, LOW);
	}
	
	else if (ldrValue > triggerAt) {
		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, HIGH);
		digitalWrite(bluePin, LOW);
	}
}

void loop() 
{
	currentTime = millis();
	ldrValue = analogRead(ldrPin);
	
	if (ldrValue >= triggerAt) {
		digitalWrite(jetGate, HIGH);
		lastAction = currentTime;
	} else {
		digitalWrite(jetGate, LOW);
	}

	waterValue = analogRead(waterPin);

	if (waterValue > waterMinimum) {
		digitalWrite(drainGate, HIGH);

		digitalWrite(redPin, HIGH);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, LOW);
	} else {
		digitalWrite(drainGate, LOW);

		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, HIGH);
		digitalWrite(bluePin, LOW);
	}
}