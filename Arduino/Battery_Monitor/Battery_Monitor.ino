int batteryValue;
const int batteryPin = A0;

void setup()
{
	pinMode(batteryPin, INPUT);
}

void loop()
{
	batteryValue = analogRead(batteryPin);
}