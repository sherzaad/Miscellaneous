//PWM read using External Interrupts. Following code measures the time a PWM pulse is HIGH
#define INTR_2 2
#define MAX_SIZE 16 //"power of 2" buffer size is recommended to dramatically optimize all the modulo operations for ring buffers.

volatile uint32_t prev_time;
volatile uint8_t tail = 0;
uint32_t pwm_buf[MAX_SIZE];
uint8_t head = 0;

void rising() {
  attachInterrupt(digitalPinToInterrupt(INTR_2), falling, FALLING);
  prev_time = micros();
}

void falling() {
  attachInterrupt(digitalPinToInterrupt(INTR_2), rising, RISING);
  pwm_buf[tail] = micros() - prev_time;
  tail = (tail + 1) % MAX_SIZE;
}

void setup() {
  Serial.begin(115200);
  // when pin D2 goes LOW->HIGH, call the rising function
  attachInterrupt(digitalPinToInterrupt(INTR_2), rising, RISING);
}

void loop() {
  if (head != tail) {
    uint32_t pwm_value = pwm_buf[head];

    head = (head + 1) % MAX_SIZE;

    Serial.print("pulse width: ");
    Serial.print(pwm_value);
    Serial.println("us");
  }
}
