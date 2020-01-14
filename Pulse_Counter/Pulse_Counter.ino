//Using Timer1 as a pulse counter to calculate RPM

#define T_1 5 //External clock source T1 pin for Timer1 (Check board datasheet and change accordingly) 
#define PERIOD 1000 //1000 ms = 1sec
#define TOOTH_CNT 16
#define RPM 60000.0 //60s (defined as a float as used in float calculation)

bool new_data = false;
uint32_t oldTime;

void setup(void)
{
  Serial.begin(115200);

  //---initialize Timer1 as external pulse counter---
  pinMode(T_1, INPUT_PULLUP); //or use analog comparator (ACIC=1)
  TCCR1A = 0x00;
  TCNT1 = 0x00;   //start counting from 0
  TCCR1B = 0x07;  //Start timer1
                  //set Clock Selet Bits (CS1 2:0). CS12=1, CS11=1, CS10=1 :- Clock on Rising Edge
                  //set Clock Selet Bits (CS1 2:0). CS12=1, CS11=1, CS10=0 :- Clock on Falling Edge

  oldTime = millis();
}

void loop()
{
uint16_t count;
uint32_t elapsed_time = millis() - oldTime;

  if (elapsed_time >= PERIOD) {
    TCCR1B = 0x00;  //Timer1 Stopped
    count = TCNT1;  //read Timer1/Counter1 Register
    TCNT1 = 0x00;   //reset counter
    TCCR1B = 0x07;  //restart timer1
    new_data = true;
    oldTime = millis();
  }

  if (new_data) {
    //calculate rpm and print to serial monitor
    float rpm = (count * RPM) / (elapsed_time * TOOTH_CNT);
    Serial.print("RPM: ");
    Serial.println(rpm, 2);
    new_data = false;
  }
}
