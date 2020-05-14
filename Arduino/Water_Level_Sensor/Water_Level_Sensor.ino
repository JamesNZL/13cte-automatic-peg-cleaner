int waterValue = 0;
unsigned long currentTime;
unsigned long lastPrint = 0;
const int waterPin = A0;
const unsigned long printDelay = 500;

void setup()
{
	pinMode(waterPin, INPUT);

	Serial.begin(9600);
}

void loop()
{
	waterValue = analogRead(waterPin);
	currentTime = millis();

	if((currentTime - lastPrint) >= printDelay) {
	    Serial.println(waterValue);
	    lastPrint = currentTime;
	}
}