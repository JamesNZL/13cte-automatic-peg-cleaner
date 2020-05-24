int sensorValue;                                            // variable for current analogue reading from LDR
int disarmedValue;                                          // variable that records the analogue reading from LDR when laser is disengaged ('disarmed' value)
int triggerAt;                                              // variable for what LDR reading to 'trigger' tripwire at (Let 'disarmed' value be 500, 'armed' value be max of 1000, triggerAt would be 1000 - 500/2 = 1000 - 250 = 750)
int testTotal;                                              // iterative variable to record total of (testIterations) readings from LDR when initialising
const int sensorPin = A0;                                   // LDR 'signal' pin
const int laserPin = 12;                                    // laser pin
const int redPin = 9;                                       // rgb module red pin
const int greenPin = 10;                                    // rgb module blue pin
const int bluePin = 11;                                     // rgb module blue pin
const int testIterations = 5;                               // number of readings to perform when initialising
const int maximumValue = 1023;                              // maximum reading possible from LDR, therefore maximum reading when laser is 'armed'

void setup() {
	pinMode(sensorPin, INPUT);                                // defines (sensorPin) as an input pin
	pinMode(laserPin, OUTPUT);                                // defines (laserPin) as an output pin
	pinMode(redPin, OUTPUT);                                  // defines (redPin) as an output pin
	pinMode(greenPin, OUTPUT);                                // defines (greenPin) as an output pin
	pinMode(bluePin, OUTPUT);                                 // defines (bluePin) as an output pin
	
	Serial.begin(9600);                                       // initialise serial monitor at 9600 baud

	digitalWrite(laserPin, LOW);                              // disengage laser for preliminary sensor reading

	for (int i = 0; i <= (testIterations - 1); i++) {         // perform the following actions (testIterations) times
		testTotal += analogRead(sensorValue);                   // add current analogue reading from LDR to existing (testTotal) value
	}

	digitalWrite(laserPin, HIGH);                             // engage laser tripwire

	disarmedValue = testTotal / testIterations;               // set (disarmedValue) equal to average of the (testIterations) tests
	triggerAt = (maximumValue + disarmedValue) / 2;           // set (triggerAt) to mid point between 'armed' and 'disarmed' / 'triggered'

	sensorValue = analogRead(sensorPin);                      // read current value from LDR

	if (sensorValue < triggerAt) {                            // if analogue reading from LDR indicates the tripwire is disarmed, do the following
		digitalWrite(redPin, HIGH);                             // turn red LED on
		digitalWrite(greenPin, LOW);                            // turn green LED off
		digitalWrite(bluePin, LOW);                             // turn blue LED off
	}
	
	else if (sensorValue > triggerAt) {                       // if analogue reading from LDR indicates the tripwire is armed, do the following
		digitalWrite(redPin, LOW);                              // turn red LED off
		digitalWrite(greenPin, HIGH);                           // turn green LED on
		digitalWrite(bluePin, LOW);                             // turn blue LED off
	}
}

void loop() {
	sensorValue = analogRead(sensorPin);                      // update (sensorValue) to analogue reading from LDR now that the tripwire is armed
	
	while (sensorValue >= triggerAt) {                        // until the analogue reading has dropped below 'activation' threshold, do the following
		sensorValue = analogRead(sensorPin);                    // update (sensorValue)
		Serial.println(sensorValue);                            // print current value to serial monitor (for debugging)
	}

	Serial.print("Triggered @ ");                             // if tripwire is broken, print 'Triggered' to serial monitor
	Serial.println(sensorValue);
}
