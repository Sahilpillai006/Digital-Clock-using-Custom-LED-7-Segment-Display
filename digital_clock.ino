// ======================================================
//      4 DIGIT CLOCK (HH:MM)
//      Arduino Nano + 3 Buttons
//      Common Anode Display
//
// MODE button:
//   Normal -> Edit Hours -> Edit Minutes -> Normal
//
// UP button:
//   Increase selected value
//
// DOWN button:
//   Decrease selected value
//
// Clock pauses while editing
// ======================================================


// ---------------- DIGIT PINS ----------------
int d1 = 2;
int d2 = 3;
int d3 = 4;
int d4 = 5;

// ---------------- SEGMENT PINS ----------------
int a = 6;
int b = 7;
int c = 8;
int d = 9;
int e = 10;
int f = 11;
int g = 12;

// ---------------- COLON ----------------
int colonPin = 13;

// ---------------- BUTTONS ----------------
int btnMode = A5;
int btnUp   = A4;
int btnDown = A3;

// ---------------- TIME ----------------
int hours = 12;
int minutes = 0;

unsigned long prevTime = 0;
unsigned long prevBlink = 0;

bool colonState = false;

// ---------------- MODES ----------------
// 0 = Normal
// 1 = Edit Hours
// 2 = Edit Minutes
int mode = 0;

// ---------------- BUTTON STATES ----------------
bool lastModeState = HIGH;
bool lastUpState = HIGH;
bool lastDownState = HIGH;


// ======================================================
// SETUP
// ======================================================

void setup() {

  // Digit pins
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);

  // Segment pins
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  // Colon
  pinMode(colonPin, OUTPUT);

  // Buttons
  pinMode(btnMode, INPUT_PULLUP);
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);

  Serial.begin(9600);
}


// ======================================================
// TURN ALL DIGITS OFF
// Common Anode:
// LOW = OFF
// ======================================================

void allDigitsOff() {

  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
}


// ======================================================
// TURN ALL SEGMENTS OFF
// Common Anode:
// HIGH = OFF
// ======================================================

void allSegmentsOff() {

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}


// ======================================================
// SHOW DIGIT
// Common Anode
// ======================================================

void showDigit(int num) {

  switch (num) {

    case 0:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;

    case 1:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 2:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;

    case 3:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;

    case 4:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 5:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 6:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 7:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 8:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 9:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
  }
}


// ======================================================
// DISPLAY TIME
// ======================================================

void displayTime() {

  int h1 = hours / 10;
  int h2 = hours % 10;

  int m1 = minutes / 10;
  int m2 = minutes % 10;


  // -------- Digit 1 --------
  allDigitsOff();
  allSegmentsOff();

  // Blink hours while editing
  if (!(mode == 1 && colonState == false)) {
    digitalWrite(d1, HIGH);
    showDigit(h1);
  }

  delay(2);


  // -------- Digit 2 --------
  allDigitsOff();
  allSegmentsOff();

  if (!(mode == 1 && colonState == false)) {
    digitalWrite(d2, HIGH);
    showDigit(h2);
  }

  delay(2);


  // -------- Colon --------
  digitalWrite(colonPin, colonState);


  // -------- Digit 3 --------
  allDigitsOff();
  allSegmentsOff();

  // Blink minutes while editing
  if (!(mode == 2 && colonState == false)) {
    digitalWrite(d3, HIGH);
    showDigit(m1);
  }

  delay(2);


  // -------- Digit 4 --------
  allDigitsOff();
  allSegmentsOff();

  if (!(mode == 2 && colonState == false)) {
    digitalWrite(d4, HIGH);
    showDigit(m2);
  }

  delay(2);
}


// ======================================================
// LOOP
// ======================================================

void loop() {

  // ---------------- BLINK TIMER ----------------
  if (millis() - prevBlink >= 500) {

    prevBlink = millis();
    colonState = !colonState;
  }


  // ==================================================
  // MODE BUTTON
  // ==================================================

  bool currentMode = digitalRead(btnMode);

  if (lastModeState == HIGH && currentMode == LOW) {

    mode++;

    if (mode > 2) {

      mode = 0;

      // Resume clean timing
      prevTime = millis();
    }

    delay(200);
  }

  lastModeState = currentMode;


  // ==================================================
  // UP BUTTON
  // ==================================================

  bool currentUp = digitalRead(btnUp);

  if (lastUpState == HIGH && currentUp == LOW) {

    // Edit Hours
    if (mode == 1) {

      hours++;

      if (hours >= 24) {
        hours = 0;
      }
    }

    // Edit Minutes
    else if (mode == 2) {

      minutes++;

      if (minutes >= 60) {
        minutes = 0;
      }
    }

    delay(200);
  }

  lastUpState = currentUp;


  // ==================================================
  // DOWN BUTTON
  // ==================================================

  bool currentDown = digitalRead(btnDown);

  if (lastDownState == HIGH && currentDown == LOW) {

    // Edit Hours
    if (mode == 1) {

      hours--;

      if (hours < 0) {
        hours = 23;
      }
    }

    // Edit Minutes
    else if (mode == 2) {

      minutes--;

      if (minutes < 0) {
        minutes = 59;
      }
    }

    delay(200);
  }

  lastDownState = currentDown;


  // ==================================================
  // CLOCK TIMER
  // Runs ONLY in normal mode
  // ==================================================

  if (mode == 0) {

    if (millis() - prevTime >= 60000) {

      prevTime = millis();

      minutes++;

      if (minutes >= 60) {

        minutes = 0;
        hours++;
      }

      if (hours >= 24) {

        hours = 0;
      }

      // Serial Debug
      Serial.print("Time: ");

      if (hours < 10) Serial.print("0");
      Serial.print(hours);

      Serial.print(":");

      if (minutes < 10) Serial.print("0");
      Serial.println(minutes);
    }
  }


  // ==================================================
  // DISPLAY REFRESH
  // ==================================================

  displayTime();
}
