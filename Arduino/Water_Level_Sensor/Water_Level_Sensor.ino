int waterValue = 0;
const int waterPin = A0;

void setup()
{
	pinMode(waterPin, INPUT);
}

void loop()
{
	waterValue = analogRead(waterPin);
}