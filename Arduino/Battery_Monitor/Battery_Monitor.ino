float batteryValue;
const int batteryPin = A0;
const float batteryLow = 3.9;
const float batteryCritical = 3.7;
const float readVoltage = 5.0/1023.0;

void setup()
{
	pinMode(batteryPin, INPUT);

	Serial.begin(9600);
}

void loop()
{
	batteryValue = analogRead(batteryPin) * readVoltage;

	if (batteryValue < batteryCritical) {
		Serial.print("Critical @ ");
	} else if (batteryValue < batteryLow) {
		Serial.print("Low @");
	}

	Serial.println(batteryValue);

	delay(100);
}