#define pi 3.141593

struct real_solutions_t {
  uint8_t number_of_solutions;
  float solutions[3];
};

uint8_t solve_cubic(float a, float b, float c, float d, struct real_solutions_t *soln)
{
  float _a, _b, _c;
  float half = 1.0 / 2;
  float third = 1.0 / 3;

  if (a != 0) {
    _a = b / a;
    _b = c / a;
    _c = d / a;
  }
  else {
    return 0;  //not a cubic funtions
  }

  float p = _b - ((_a * _a) / 3);
  float q = ((2 * _a * _a * _a) / 27) - ((_a * _b) / 3) + _c;
  float disciminant = ((q * q) / 4) + ((p * p * p) / 27);

  if (disciminant > 0.000001) { //inplace of 'disciminant > 0' to due to floating point computation accuracy.
								//else may result in incorrect output if 'disciminant = 0'
    soln->number_of_solutions = 1; //one real solution
    soln->solutions[0] = pow((pow(disciminant, half) - (q / 2)), third) + pow((-1 * (pow(disciminant, half)) - (q / 2)), third) - (_a / 3);
  }
  else if (disciminant < 0 ) {
    p = pow((-1 * p), half);
    float r = pow(3, half);
    float f = (2 / r) * p;
    float g = 1.5 * r;
    soln->number_of_solutions = 3; //3 real solutions
    soln->solutions[0] = f * sin(third * asin((g * q) / (p * p * p))) - (_a / 3);
    soln->solutions[1] = f * sin(third * asin(((g * q) / (p * p * p))) + (pi / 3)) - (_a / 3);
    soln->solutions[2] = f * cos(third * asin(((g * q) / (p * p * p))) + (pi / 6)) - (_a / 3);
  }
  else { //assumes 'disciminant = 0'
    soln->number_of_solutions = 2; //2 real solutions (x2 = x3, repeated root)
    if (q < 0) {
      q *= -1;
      soln->solutions[0] = (2 * pow((q / 2), third)) - (_a / 3);
      soln->solutions[1] = (-1 * pow((q / 2), third)) - (_a / 3);
    }
    else {
      soln->solutions[0] = (-2 * pow((q / 2), third)) - (_a / 3);
      soln->solutions[1] = pow((q / 2), third) - (_a / 3);
    }
  }

  return 1;

}

void setup() {
  struct real_solutions_t real_solutions;

  Serial.begin(115200);

  uint8_t i = solve_cubic(1, -4, 5, -2, &real_solutions);

  if (i) {
    Serial.print(F("Number of Real Solutions: "));
    Serial.println(real_solutions.number_of_solutions);

    if (real_solutions.number_of_solutions == 1) {
      Serial.print(F("x = "));
      Serial.println(real_solutions.solutions[0]);
    }
    else if (real_solutions.number_of_solutions == 2) {
      Serial.print(F("x1 = "));
      Serial.println(real_solutions.solutions[0]);
      Serial.print(F("x2 = x3 = "));
      Serial.println(real_solutions.solutions[1]);
    }
    else {
      Serial.print(F("x1 = "));
      Serial.println(real_solutions.solutions[0]);
      Serial.print(F("x2 = "));
      Serial.println(real_solutions.solutions[1]);
      Serial.print(F("x3 = "));
      Serial.println(real_solutions.solutions[2]);
    }
  }
  else {
    Serial.println(F("NOT A CUBIC EQUATION!"));
  }
}

void loop() {
  //nothing here
}
