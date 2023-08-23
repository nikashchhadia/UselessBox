// enumerate state values
enum states {STOP = 0, FORWARD, REVERSE};

// saves our state between calls to loop()
int state = STOP;

// keeps track of whether the arm is currently angry
bool angered = false;

// instantiate pin numbers for inputs/outputs
const int inverter1 = 6;
const int inverter2 = 9;
const int toggle = 10;
const int limit = 12;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup complete");

  // intialize input and output pins
  pinMode(inverter1, OUTPUT);
  pinMode(inverter2, OUTPUT);
  pinMode(toggle, INPUT_PULLUP);
  pinMode(limit, INPUT_PULLUP);

  // intialize initial state
  state = STOP;
}

void loop() {
  // read input pins to get status of toggle and limit
  bool toggleOn = (digitalRead(toggle) == 1);
  bool limitOn = (digitalRead(limit) == 1);

  if (toggleOn) { // if toggle is on, move motor forward
    forward();
    angered = true; // toggle has been flipped, so the arm gets angry
  } else if (limitOn) {  // elif toggle is off and limit is on, stop motor
      stop();
  } else {  // else toggle is off and limit is off, reverse motor
    if (angered) {
      angryArm(); // if the arm is angry, call angryMotor before reversing
      angered = false;  // and get rid of anger until the toggle is flipped again
    }
    reverse();
  }
}

// makes the arm angrily go back and forth (random 3 to 7 times)
void angryArm() {
  int count = random(3, 8);
  for (int i = 0; i < count; i++) {
    reverse();
    delay(150);
    forward();
    delay(200);
    stop();
  }
}

// spins the motor forward
void forward() {
  digitalWrite(inverter1, LOW);
  digitalWrite(inverter2, HIGH);
}

// spins the motor backward
void reverse() {
  digitalWrite(inverter1, HIGH);
  digitalWrite(inverter2, LOW);
}

// stops the motor
void stop() {
  digitalWrite(inverter1, LOW);
  digitalWrite(inverter2, LOW);
}