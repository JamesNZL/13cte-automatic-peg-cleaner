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
bool jetsEngaged = false;
bool waterDanger = false;
bool buttonPressed = false;
unsigned long currentTime;
unsigned long lastAction = 0;
unsigned long terminateTime = 180000;

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
		if (jetsEngaged == false) {
			lastAction = currentTime;
		}

		jetsEngaged = true;
		digitalWrite(jetGate, HIGH);
	} else {
		if (jetsEngaged == true) {
			lastAction = currentTime;
		}

		jetsEngaged = false;
		digitalWrite(jetGate, LOW);
	}

	waterValue = analogRead(waterPin);

	if (waterValue > waterMinimum) {
		if (waterDanger == false) {
			lastAction = currentTime;
		}

		waterDanger = true;
		digitalWrite(drainGate, HIGH);

		digitalWrite(redPin, HIGH);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, LOW);
	} else {
		if (waterDanger == true) {
			lastAction = currentTime;
		}

		waterDanger = false;
		digitalWrite(drainGate, LOW);

		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, HIGH);
		digitalWrite(bluePin, LOW);
	}

	drainInput = digitalRead(drainButton);

	if (drainInput == HIGH) {
		if (buttonPressed == false) {
			lastAction = currentTime;
		}

		buttonPressed = true;
		digitalWrite(drainGate, HIGH);

		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, HIGH);
	} else {
		if (buttonPressed == true) {
			lastAction = currentTime;
		}

		buttonPressed = false;
		digitalWrite(drainGate, LOW);

		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, HIGH);
		digitalWrite(bluePin, LOW);
	}

	offInput = digitalRead(offButton);

	if (offInput == HIGH) {
		digitalWrite(jetGate, LOW);
		digitalWrite(drainGate, LOW);
		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, LOW);
		digitalWrite(powerGate, LOW);
	}

	if lastAction >= terminateTime {
		digitalWrite(jetGate, LOW);
		digitalWrite(drainGate, LOW);
		digitalWrite(redPin, LOW);
		digitalWrite(greenPin, LOW);
		digitalWrite(bluePin, LOW);
		digitalWrite(powerGate, LOW);
	}
}