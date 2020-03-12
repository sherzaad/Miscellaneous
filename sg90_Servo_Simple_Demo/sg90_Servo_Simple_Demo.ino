/*the sg90 accepts 3 command pulse width
  1ms - CCW movement
  1.5ms - return to center position
  2ms - CW movement
  minimum time between pulses/steps - 20ms
  Servo can rotate approximately 180 degrees end-to-end

  This example used delay() to demonstrate servo operation.

*/

uint8_t DirectionInputPin = 9;
uint8_t sg90ControlPin = 8;

uint8_t CCWpulseWidth = 1;  // milliseconds
uint8_t CWpulseWidth = 2;  // milliseconds
int millisbetweenSteps = 60; // milliseconds - or try larger values for slower steps

uint8_t numberOfSteps = 100;

void move_servo(int Steps, uint8_t pulseWidth) {
  for (uint8_t n = 0; n < Steps; n++) {
    digitalWrite(sg90ControlPin, LOW);
    delay(millisbetweenSteps);
    digitalWrite(sg90ControlPin, HIGH);
    delay(pulseWidth);
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(DirectionInputPin, INPUT_PULLUP);
  pinMode(sg90ControlPin, OUTPUT);
  digitalWrite(sg90ControlPin, HIGH); //reduces chances of jitter on powerup/reset
                                      //a 1k pullup resistor between sg90ControlPin and VCC would also help

  Serial.println("Starting Sg90 Test");

  //servo initialisation
  //move servo to center positon
  digitalWrite(sg90ControlPin, LOW);
  delay(20);
  digitalWrite(sg90ControlPin, HIGH);
  delayMicroseconds(1500);
  digitalWrite(sg90ControlPin, LOW);
  delay(20);
  digitalWrite(sg90ControlPin, HIGH);
  delay(20);
  //move servo fully CounterClockwise (approximately 90 steps)
  move_servo(90, CCWpulseWidth);

  //abitrary delay
  delay(2000);
}

void loop() {
  //move servo Clockwise
  if (digitalRead(DirectionInputPin)) {
    move_servo(numberOfSteps, CWpulseWidth);
  }
  //move servo Counter-Clockwise
  else {
    move_servo(numberOfSteps, CCWpulseWidth);
  }
  
  delay(millisbetweenSteps);
}
