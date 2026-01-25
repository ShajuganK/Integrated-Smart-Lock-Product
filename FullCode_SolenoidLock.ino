#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// ------------------ PIN DEFINITIONS ------------------
const int knockSensor = A0;         // Piezo sensor on pin A0
const int programSwitch = 2;        // If this is high, we program a new code
const int redLED = 4;               // Red LED
const int greenLED = 5;             // Green LED
const int relayPin = 3;             // Relay module controlling solenoid lock

// ------------------ LCD ------------------
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C Address may vary (0x27 or 0x3F)

// ------------------ KEYPAD SETUP ------------------
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};     // Connect to the row pinouts of keypad
byte colPins[COLS] = {12, 11, 10};     // Connect to the column pinouts of keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ------------------ CONSTANTS ------------------
const int threshold = 3;
const int rejectValue = 25;
const int averageRejectValue = 15;
const int knockFadeTime = 150;
const int lockTurnTime = 3000;        // Door unlock duration (adjust as needed)
const int maximumKnocks = 4;
const int knockComplete = 1200;

int secretCode[maximumKnocks] = {100, 100, 100, 100};
int knockReadings[maximumKnocks];
bool programButtonPressed = false;
int knockFails = 0;

// ------------------ KEYPAD PASSWORD ------------------
String password = "123";
String entered = "";

// ------------------ SETUP ------------------
void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(programSwitch, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // keep solenoid OFF initially

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Welcome to G36");
  delay(1500);
  lcd.clear();
  lcd.print("Ready for Knock");
  digitalWrite(greenLED, HIGH);
}

// ------------------ LOOP ------------------
void loop() {
  if (knockFails < 3) {
    knockMode();
  } else {
    keypadMode();
  }
}

// ------------------ KNOCK MODE ------------------
void knockMode() {
  int knockSensorValue = analogRead(knockSensor);

  if (digitalRead(programSwitch) == HIGH) {
    programButtonPressed = true;
    digitalWrite(redLED, HIGH);
  } else {
    programButtonPressed = false;
    digitalWrite(redLED, LOW);
  }

  if (knockSensorValue >= threshold) {
    if (listenToSecretKnock()) {
      triggerDoorUnlock();
      knockFails = 0; // reset fails
    } else {
      knockFails++;
      lcd.clear();
      lcd.print("Wrong Knock!");
      blinkLED(redLED, 3);
      delay(1000);
      lcd.clear();
      lcd.print("Tries: ");
      lcd.print(3 - knockFails);
      delay(1000);
      if (knockFails >= 3) {
        lcd.clear();
        lcd.print("Switching ->");
        lcd.setCursor(0, 1);
        lcd.print("Keypad Mode");
        delay(1500);
      } else {
        lcd.clear();
        lcd.print("Try Again");
      }
    }
  }
}

// ------------------ LISTEN TO KNOCK ------------------
boolean listenToSecretKnock() {
  for (int i = 0; i < maximumKnocks; i++) knockReadings[i] = 0;
  int currentKnockNumber = 0;
  long startTime = millis();
  long now = millis();

  do {
    int sensorVal = analogRead(knockSensor);
    if (sensorVal >= threshold) {
      now = millis();
      knockReadings[currentKnockNumber] = now - startTime;
      currentKnockNumber++;
      startTime = now;
      blinkLED(greenLED, 1);
    }
    now = millis();
  } while ((now - startTime < knockComplete) && (currentKnockNumber < maximumKnocks));

  if (programButtonPressed) {
    for (int i = 0; i < maximumKnocks; i++) {
      secretCode[i] = map(knockReadings[i], 0, knockReadings[maximumKnocks - 1], 0, 100);
    }
    lcd.clear();
    lcd.print("Pattern Saved");
    delay(1000);
    return false;
  } else {
    return validateKnock();
  }
}

// ------------------ VALIDATE KNOCK ------------------
boolean validateKnock() {
  int i;
  int currentKnockCount = 0;
  int secretKnockCount = 0;
  int maxKnockInterval = 0;

  for (i = 0; i < maximumKnocks; i++) {
    if (knockReadings[i] > 0) currentKnockCount++;
    if (secretCode[i] > 0) secretKnockCount++;
    if (knockReadings[i] > maxKnockInterval) maxKnockInterval = knockReadings[i];
  }

  if (currentKnockCount != secretKnockCount) return false;

  int totalDiff = 0;
  for (i = 0; i < maximumKnocks; i++) {
    knockReadings[i] = map(knockReadings[i], 0, maxKnockInterval, 0, 100);
    int diff = abs(knockReadings[i] - secretCode[i]);
    if (diff > rejectValue) return false;
    totalDiff += diff;
  }

  if (totalDiff / secretKnockCount > averageRejectValue) return false;
  return true;
}

// ------------------ KEYPAD MODE ------------------
void keypadMode() {
  lcd.clear();
  lcd.print("Enter Password:");
  entered = "";

  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        if (entered == password) {
          lcd.clear();
          lcd.print("Access Granted");
          triggerDoorUnlock();
          knockFails = 0; // reset for next time
          delay(1000);
          lcd.clear();
          lcd.print("Ready for Knock");
          return;
        } else {
          lcd.clear();
          lcd.print("Access Denied");
          blinkLED(redLED, 3);
          delay(1000);
          lcd.clear();
          lcd.print("Try Again");
          entered = "";
        }
      } else if (key == '*') {
        entered = "";
        lcd.clear();
        lcd.print("Cleared");
        delay(500);
        lcd.clear();
        lcd.print("Enter Password:");
      } else {
        entered += key;
        lcd.setCursor(0, 1);
        lcd.print(entered);
      }
    }
  }
}

// ------------------ UNLOCK FUNCTION (Modified for Relay) ------------------
void triggerDoorUnlock() {
  lcd.clear();
  lcd.print("Door Unlocked!");
  digitalWrite(relayPin, HIGH);   // Activate relay → energize solenoid
  digitalWrite(greenLED, HIGH);
  delay(lockTurnTime);            // Keep open for a few seconds
  digitalWrite(relayPin, LOW);    // Deactivate relay → lock again
  blinkLED(greenLED, 3);
  lcd.clear();
  lcd.print("Locked Again");
  delay(1000);
}

// ------------------ LED BLINK HELPER ------------------
void blinkLED(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin, LOW);
    delay(150);
  }
}
