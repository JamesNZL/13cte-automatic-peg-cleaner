const int redPin = 8;
const int greenPin = 10;
const int bluePin = 12;

void setup() {
	// put your setup code here, to run once:
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	digitalWrite(redPin, HIGH);
	digitalWrite(greenPin, LOW);
	digitalWrite(bluePin, LOW);
}
