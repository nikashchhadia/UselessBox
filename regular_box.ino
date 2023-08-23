// enumerate state values
enum states {STOP = 0, FORWARD, REVERSE};

// saves our state between calls to loop()
int state = STOP;

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
  } else if (limitOn) {  // elif toggle is off and limit is on, stop motor
    stop();
  } else {  // else toggle is off and limit is off, reverse motor
    reverse();
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