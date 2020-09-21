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
const int alertDelay = 500;
bool jetsEngaged = false;
bool waterDanger = false;
bool buttonPressed = false;
unsigned long currentTime;
unsigned long lastAction = 0;
unsigned long terminateTime = 180000;

void setup() 
{
	pinMode(batteryPin, INPUT);
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

	for (int i = 0; i < testIterations; i++) {
		testTotal += analogRead(ldrValue);
	}

	digitalWrite(laserPin, HIGH);
	lastAction = currentTime;

	disarmedValue = testTotal / testIterations;
	triggerAt = (maximumValue + disarmedValue) / 2;

	ldrValue = analogRead(ldrPin);

	if (ldrValue < triggerAt) {
		indicatorAlert();
		digitalWrite(powerGate, LOW);
	}
	
	else if (ldrValue > triggerAt) {
		indicatorControl(LOW, HIGH, LOW);
	}
}

void loop() 
{
	currentTime = millis();
	ldrValue = analogRead(ldrPin);
	waterValue = analogRead(waterPin);
	drainInput = digitalRead(drainButton);
	offInput = digitalRead(offButton);
	
	if (ldrValue >= triggerAt) {
		jetsEngaged = timeOut(jetsEngaged, false);
		digitalWrite(jetGate, HIGH);
	} else {
		jetsEngaged = timeOut(jetsEngaged, true);
		digitalWrite(jetGate, LOW);
	}

	if (waterValue > waterMinimum || drainInput == HIGH) {
		waterDanger = timeOut(waterDanger, false);
		buttonPressed = timeOut(buttonPressed, false);

		digitalWrite(jetGate, LOW);
		digitalWrite(drainGate, HIGH);

		if (drainInput == HIGH) {
			indicatorControl(LOW, LOW, HIGH);
		} else {
			indicatorControl(HIGH, LOW, LOW);
		}
	} else {
		waterDanger = timeOut(waterDanger, true);
		buttonPressed = timeOut(buttonPressed, true);

		digitalWrite(drainGate, LOW);

		indicatorControl(LOW, HIGH, LOW);
	}

	if (offInput == HIGH) {
		shutDown();
	}

	if ((currentTime - lastAction) >= terminateTime) {
		shutDown();
	}
}

void indicatorControl(byte redOutput, byte greenOutput, byte blueOutput)
{
	digitalWrite(redPin, redOutput);
	digitalWrite(greenPin, greenOutput);
	digitalWrite(bluePin, blueOutput);
}

void indicatorAlert()
{
	for (int i = 0; i < 5; i++) {
		indicatorAlert(HIGH, LOW, LOW);
		delay(alertDelay);
		indicatorAlert(LOW, LOW, LOW);
		delay(alertDelay);
	}
}

void timeOut(bool previousState, bool testFor)
{
	if (previousState == testFor) {
		lastAction = currentTime;
	}

	return !testFor;
}

void shutDown()
{
	digitalWrite(jetGate, LOW);
	digitalWrite(drainGate, LOW);
	indicatorControl(LOW, LOW, LOW);
	digitalWrite(powerGate, LOW);
}