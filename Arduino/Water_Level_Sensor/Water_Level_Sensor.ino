int waterValue = 0;
unsigned long currentTime;
unsigned long lastPrint = 0;
bool waterDanger = false;
const int waterPin = A0;
const int minimumValue = 250;
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

	if (waterValue > minimumValue) {
	    waterDanger = true;
	} else {
		waterDanger = false;
	}

	if ((currentTime - lastPrint) >= printDelay) {
	    if (waterDanger == true) {
	    	Serial.print("Danger @");
	    } else {
	    	Serial.print("Safe @");
	    }

	    Serial.println(waterValue);
	    
	    lastPrint = currentTime;
	}
}