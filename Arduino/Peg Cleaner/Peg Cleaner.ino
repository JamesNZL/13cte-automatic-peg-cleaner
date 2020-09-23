float batteryValue;

int waterValue;
int ldrValue;
int offInput;
int drainInput;
int disarmedValue;
int triggerAt;
int testTotal;
int waterMinimum = 200;

const float batteryLow = 3.9;
const float batteryCritical = 3.7;

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
unsigned long terminateNotify = 15000;

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

	indicatorControl(HIGH, LOW, LOW);
	batteryCheck();
	tripwireSetup();
	tripwireCheck();
}

void loop() 
{
	currentTime = millis();
	
	tripwireEngage();
	drainEngage();
	checkTurnOff();
}

void batteryCheck()
{
	batteryValue = analogRead(batteryPin) * (5.0 / 1023.0);

	if (batteryValue < batteryLow) {
		indicatorAlert(HIGH, LOW, LOW);
	}

	else if (batteryValue < batteryCritical) {
		indicatorAlert(HIGH, LOW, LOW);

		digitalWrite(powerGate, LOW);
	}
}

void tripwireSetup()
{
	digitalWrite(laserPin, LOW);

	for (int i = 0; i < testIterations; i++) {
		testTotal += analogRead(ldrValue);
	}

	digitalWrite(laserPin, HIGH);

	disarmedValue = testTotal / testIterations;
	triggerAt = (maximumValue + disarmedValue) / 2;
}

void tripwireCheck()
{
	ldrValue = analogRead(ldrPin);

	while (ldrValue < triggerAt) {
		ldrValue = analogRead(ldrPin);

		indicatorAlert(HIGH, LOW, LOW);
		checkTurnOff();

		Serial.println(ldrValue);
		Serial.println(triggerAt);
	}
	
	if (ldrValue > triggerAt) {
		indicatorControl(LOW, HIGH, LOW);
	}
}

void tripwireEngage()
{
	ldrValue = analogRead(ldrPin);

	if (ldrValue >= triggerAt) {
		jetsEngaged = timeOut(jetsEngaged, false);
		
		digitalWrite(jetGate, HIGH);

		indicatorControl(LOW, HIGH, HIGH);
	} 

	else {
		jetsEngaged = timeOut(jetsEngaged, true);
		
		digitalWrite(jetGate, LOW);

		indicatorControl(LOW, HIGH, LOW);
	}
}

void drainEngage()
{
	waterValue = analogRead(waterPin);
	drainInput = digitalRead(drainButton);

	if (waterValue > waterMinimum || drainInput == HIGH) {
		waterDanger = timeOut(waterDanger, false);
		buttonPressed = timeOut(buttonPressed, false);

		digitalWrite(jetGate, LOW);
		digitalWrite(drainGate, HIGH);

		if (drainInput == HIGH) {
			indicatorControl(LOW, LOW, HIGH);
		} 

		else {
			indicatorControl(HIGH, LOW, LOW);
		}
	} 

	else {
		waterDanger = timeOut(waterDanger, true);
		buttonPressed = timeOut(buttonPressed, true);

		digitalWrite(drainGate, LOW);

		indicatorControl(LOW, HIGH, LOW);
	}
}

void indicatorControl(byte redOutput, byte greenOutput, byte blueOutput)
{
	digitalWrite(redPin, redOutput);
	digitalWrite(greenPin, greenOutput);
	digitalWrite(bluePin, blueOutput);
}

void indicatorAlert(byte redOutput, byte greenOutput, byte blueOutput)
{
	for (int i = 0; i < 5; i++) {
		indicatorControl(redOutput, greenOutput, blueOutput);
		delay(alertDelay);
		indicatorControl(LOW, LOW, LOW);
		delay(alertDelay);
	}
}

bool timeOut(bool previousState, bool testFor)
{
	if (previousState == testFor) {
		lastAction = currentTime;
	}

	return !testFor;
}

void checkTurnOff()
{
	currentTime = millis();
	offInput = digitalRead(offButton);

	if (offInput == HIGH) {
		shutDown();
	}

	if ((currentTime - lastAction) >= (terminateTime - terminateNotify)) {
		indicatorAlert(HIGH, HIGH, LOW);
		indicatorControl(HIGH, HIGH, LOW);
	}

	else if ((currentTime - lastAction) >= terminateTime) {
		shutDown();
	}
}

void shutDown()
{
	indicatorControl(LOW, LOW, LOW);
	digitalWrite(jetGate, LOW);
	digitalWrite(drainGate, LOW);
	digitalWrite(powerGate, LOW);
}