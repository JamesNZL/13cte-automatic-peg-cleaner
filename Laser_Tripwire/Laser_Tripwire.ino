int sensorValue = 0;                                        // variable for current analogue reading from LDR
int disarmedValue = 0;                                      // variable that records the analogue reading from LDR when laser is disengaged ('disarmed' value)
int triggerAt = 0;                                          // variable for what LDR reading to 'trigger' tripwire at (Let 'disarmed' value be 500, 'armed' value be max of 1000, triggerAt would be 1000 - 500/2 = 1000 - 250 = 750)
int testTotal = 0;                                          // iterative variable to record total of (testIterations) readings from LDR when initialising
const int sensorPin = A0;                                   // LDR 'signal' pin
const int testIterations = 5;                               // number of readings to perform when initialising
const int armedValue = 1023;                                // maximum reading possible from LDR, therefore reading when laser is 'armed'

void setup() {
  Serial.begin(9600);                                       // initialise serial monitor at 9600 baud

  // TURN LASER MODULE OFF

  for (int i = 0; i <= (testIterations - 1); i++) {         // perform the following actions (testIterations) times
    testTotal += analogRead(sensorValue);                   // add current analogue reading from LDR to existing (testTotal) value
  }

  disarmedValue = testTotal / testIterations;               // set (disarmedValue) equal to average of the (testIterations) tests
  triggerAt = armedValue - (disarmedValue / 2);             // set (triggerAt) to mid point between 'armed' and 'disarmed' / 'triggered'

  // TURN LASER MODULE ON
}

void loop() {
  sensorValue = analogRead(sensorPin);                      // update (sensorValue) to analogue reading from LDR now that the tripwire is armed
  
  while (sensorValue >= triggerAt) {                        // until the analogue reading has dropped below 'activation' threshold, do the following
    sensorValue = analogRead(sensorPin);                    // update (sensorValue)
    Serial.println(sensorValue);                            // print current value to serial monitor (for debugging)
  }

  Serial.print("Triggered @ ");                              // if tripwire is broken, print 'Triggered' to serial monitor
  Serial.println(sensorValue);
}
