/*
  0-30 Counter Using Two 7-Segment Displays
  Board : Arduino Uno
  Parts : 2 x CD4511 (BCD to 7-segment decoder), 2 x common cathode 7-segment display,
          14 x 330 ohm resistors (one per segment line)

  Wiring summary
  --------------
  Units CD4511 : D2 -> pin 7 (A, LSB), D3 -> pin 1 (B), D4 -> pin 2 (C), D5 -> pin 6 (D, MSB)
  Tens  CD4511 : D6 -> pin 7 (A, LSB), D7 -> pin 1 (B), D8 -> pin 2 (C), D9 -> pin 6 (D, MSB)
  Both CD4511  : pin 16 (VDD), pin 3 (LT), pin 4 (BI) -> 5V
                 pin 8 (VSS), pin 5 (LE)              -> GND
  Outputs      : pins 13, 12, 11, 10, 9, 15, 14 (a to g) -> 330 ohm -> display segments
  Display COM  : pins 3 and 8 of each display -> GND
*/

// Arduino pins connected to the BCD inputs of each decoder
// Index 0 = bit A (LSB) ... index 3 = bit D (MSB)
const int unitsPins[4] = {2, 3, 4, 5};
const int tensPins[4]  = {6, 7, 8, 9};

const unsigned long STEP_MS = 1000;   // time each number stays on the display
const int MAX_COUNT = 30;             // counter runs from 0 to MAX_COUNT

int count = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(unitsPins[i], OUTPUT);
    pinMode(tensPins[i], OUTPUT);
  }
  showNumber(count);                  // show 00 at power-on
}

// Writes one decimal digit (0-9) as 4-bit BCD on the given pins
void writeBCD(const int pins[], int digit) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], (digit >> i) & 0x01);
  }
}

// Splits a number into tens and units and sends each to its decoder
void showNumber(int n) {
  int tens  = n / 10;
  int units = n % 10;
  writeBCD(tensPins, tens);
  writeBCD(unitsPins, units);
}

void loop() {
  showNumber(count);
  delay(STEP_MS);

  count++;
  if (count > MAX_COUNT) {
    count = 0;                        // wrap around after 30
  }
}
