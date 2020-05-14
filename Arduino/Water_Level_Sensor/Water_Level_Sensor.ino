int waterValue = 0;
const int waterPin = A0;

void setup()
{
	pinMode(waterPin, INPUT);

	Serial.begin(9600);
}

void loop()
{
	waterValue = analogRead(waterPin);

	Serial.println(waterValue);
}