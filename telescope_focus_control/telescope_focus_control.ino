#define COIL1_PIN1 5
#define COIL1_PIN2 4
#define COIL2_PIN1 3
#define COIL2_PIN2 2

#define STEP_TIME_MS 100
#define FORWARD 1
#define BACKWARD 0
#define STOPPED 2

#define FORWARD_BTN 6
#define BACKWARD_BTN 7

#define BTN_ACTIVE LOW
#define BTN_INACTIVE HIGH

void setup() {
  pinMode(COIL1_PIN1, OUTPUT);
  pinMode(COIL1_PIN2, OUTPUT);
  pinMode(COIL2_PIN1, OUTPUT);
  pinMode(COIL2_PIN2, OUTPUT);

  pinMode(FORWARD_BTN, INPUT);
  pinMode(BACKWARD_BTN, INPUT);

  Serial.begin(9600);
}

void state1() {
  digitalWrite(COIL1_PIN1, HIGH);
  digitalWrite(COIL1_PIN2, LOW);
  digitalWrite(COIL2_PIN1, HIGH);
  digitalWrite(COIL2_PIN2, LOW);
}

void state2() {
  digitalWrite(COIL1_PIN1, LOW);
  digitalWrite(COIL1_PIN2, HIGH);
  digitalWrite(COIL2_PIN1, HIGH);
  digitalWrite(COIL2_PIN2, LOW);
}

void state3() {
  digitalWrite(COIL1_PIN1, LOW);
  digitalWrite(COIL1_PIN2, HIGH);
  digitalWrite(COIL2_PIN1, LOW);
  digitalWrite(COIL2_PIN2, HIGH);
}

void state4() {
  digitalWrite(COIL1_PIN1, HIGH);
  digitalWrite(COIL1_PIN2, LOW);
  digitalWrite(COIL2_PIN1, LOW);
  digitalWrite(COIL2_PIN2, HIGH);
}

void poweredDown() {
  digitalWrite(COIL1_PIN1, LOW);
  digitalWrite(COIL1_PIN2, LOW);
  digitalWrite(COIL2_PIN1, LOW);
  digitalWrite(COIL2_PIN2, LOW);
}

void (*STATE_LOOP[4]) () = {state1, state2, state3, state4};

int CURRENT_STATE_IDX = 0;
int DIRECTION = STOPPED;

void loop() {
  int btn_forward_state = digitalRead(FORWARD_BTN);
  int btn_backward_state = digitalRead(BACKWARD_BTN);

  if (btn_forward_state == BTN_ACTIVE && btn_backward_state == BTN_INACTIVE) {
    DIRECTION = FORWARD;
  }
  else if(btn_forward_state == BTN_INACTIVE && btn_backward_state == BTN_ACTIVE) {
    DIRECTION = BACKWARD;
  } else {
    DIRECTION = STOPPED;
  }

  if (DIRECTION == STOPPED) {
    poweredDown();
    return;
  }

  STATE_LOOP[CURRENT_STATE_IDX]();
  delay(STEP_TIME_MS);
  if (DIRECTION == FORWARD) {
    CURRENT_STATE_IDX++;
  } else {
    CURRENT_STATE_IDX--;
  }

  if (CURRENT_STATE_IDX == -1) {
    CURRENT_STATE_IDX = 3;
  }
  CURRENT_STATE_IDX %= 4;
}
