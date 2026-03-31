#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include <PluggableUSBHID.h>
#include <USBKeyboard.h>

#if !defined(HALF_LEFT) && !defined(HALF_RIGHT)
#define HALF_LEFT
#endif

namespace {
constexpr uint8_t kRows = 6;
constexpr uint8_t kCols = 8;
constexpr uint8_t kMcpAddress = 0x20;
constexpr uint8_t kDebounceMs = 5;

constexpr uint8_t kBatterySensePin = A0;
constexpr uint8_t kBuzzerPin = D1;

constexpr float kBatteryDividerScale = (806.0f + 2000.0f) / 2000.0f;
constexpr float kBatteryEmptyV = 3.30f;
constexpr float kBatteryFullV = 4.20f;

constexpr uint8_t H_A = 0x04;
constexpr uint8_t H_B = 0x05;
constexpr uint8_t H_C = 0x06;
constexpr uint8_t H_D = 0x07;
constexpr uint8_t H_E = 0x08;
constexpr uint8_t H_F = 0x09;
constexpr uint8_t H_G = 0x0A;
constexpr uint8_t H_H = 0x0B;
constexpr uint8_t H_I = 0x0C;
constexpr uint8_t H_J = 0x0D;
constexpr uint8_t H_K = 0x0E;
constexpr uint8_t H_L = 0x0F;
constexpr uint8_t H_M = 0x10;
constexpr uint8_t H_N = 0x11;
constexpr uint8_t H_O = 0x12;
constexpr uint8_t H_P = 0x13;
constexpr uint8_t H_Q = 0x14;
constexpr uint8_t H_R = 0x15;
constexpr uint8_t H_S = 0x16;
constexpr uint8_t H_T = 0x17;
constexpr uint8_t H_U = 0x18;
constexpr uint8_t H_V = 0x19;
constexpr uint8_t H_W = 0x1A;
constexpr uint8_t H_X = 0x1B;
constexpr uint8_t H_Y = 0x1C;
constexpr uint8_t H_Z = 0x1D;
constexpr uint8_t H_1 = 0x1E;
constexpr uint8_t H_2 = 0x1F;
constexpr uint8_t H_3 = 0x20;
constexpr uint8_t H_4 = 0x21;
constexpr uint8_t H_5 = 0x22;
constexpr uint8_t H_6 = 0x23;
constexpr uint8_t H_7 = 0x24;
constexpr uint8_t H_8 = 0x25;
constexpr uint8_t H_9 = 0x26;
constexpr uint8_t H_0 = 0x27;
constexpr uint8_t H_ENTER = 0x28;
constexpr uint8_t H_ESC = 0x29;
constexpr uint8_t H_BKSP = 0x2A;
constexpr uint8_t H_TAB = 0x2B;
constexpr uint8_t H_SPACE = 0x2C;
constexpr uint8_t H_MINUS = 0x2D;
constexpr uint8_t H_EQUAL = 0x2E;
constexpr uint8_t H_LBKT = 0x2F;
constexpr uint8_t H_RBKT = 0x30;
constexpr uint8_t H_BSLS = 0x31;
constexpr uint8_t H_SCLN = 0x33;
constexpr uint8_t H_QUOT = 0x34;
constexpr uint8_t H_COMM = 0x36;
constexpr uint8_t H_DOT = 0x37;
constexpr uint8_t H_SLSH = 0x38;
constexpr uint8_t H_CAPS = 0x39;
constexpr uint8_t H_F7 = 0x40;
constexpr uint8_t H_F8 = 0x41;
constexpr uint8_t H_F9 = 0x42;
constexpr uint8_t H_F10 = 0x43;
constexpr uint8_t H_F11 = 0x44;
constexpr uint8_t H_F12 = 0x45;
constexpr uint8_t H_INS = 0x49;
constexpr uint8_t H_HOME = 0x4A;
constexpr uint8_t H_PGUP = 0x4B;
constexpr uint8_t H_DEL = 0x4C;
constexpr uint8_t H_END = 0x4D;
constexpr uint8_t H_PGDN = 0x4E;
constexpr uint8_t H_RIGHT = 0x4F;
constexpr uint8_t H_LEFT = 0x50;
constexpr uint8_t H_DOWN = 0x51;
constexpr uint8_t H_UP = 0x52;

struct KeyDef {
  uint8_t usage;
  uint8_t modifier;
};

constexpr KeyDef N = {0, 0};
constexpr KeyDef K(uint8_t usage) { return {usage, 0}; }
constexpr KeyDef M(uint8_t modifier) { return {0, modifier}; }

constexpr uint8_t kColPins[kCols] = {0, 1, 2, 3, 4, 5, 6, 7};
constexpr uint8_t kRowPins[kRows] = {8, 9, 10, 11, 12, 13};

const KeyDef kLeftKeymap[kRows][kCols] = {
  {K(H_ESC), K(H_1), K(H_2), K(H_3), K(H_4), K(H_5), K(H_6), K(H_7)},
  {K(H_TAB), K(H_Q), K(H_W), K(H_E), K(H_R), K(H_T), K(H_Y), K(H_U)},
  {K(H_CAPS), K(H_A), K(H_S), K(H_D), K(H_F), K(H_G), K(H_H), N},
  {M(arduino::KEY_SHIFT), K(H_Z), K(H_X), K(H_C), K(H_V), K(H_B), K(H_N), N},
  {M(arduino::KEY_CTRL), M(arduino::KEY_LOGO), M(arduino::KEY_ALT), K(H_SPACE), K(H_BKSP), K(H_ENTER), N, N},
  {K(H_LEFT), K(H_DOWN), K(H_UP), K(H_RIGHT), K(H_DEL), N, N, N}
};

const KeyDef kRightKeymap[kRows][kCols] = {
  {K(H_8), K(H_9), K(H_0), K(H_MINUS), K(H_EQUAL), K(H_LBKT), K(H_RBKT), K(H_BSLS)},
  {K(H_I), K(H_O), K(H_P), K(H_SCLN), K(H_QUOT), K(H_BKSP), K(H_PGUP), K(H_HOME)},
  {K(H_J), K(H_K), K(H_L), K(H_COMM), K(H_DOT), K(H_SLSH), K(H_ENTER), K(H_END)},
  {K(H_M), K(H_F7), K(H_F8), K(H_F9), K(H_F10), K(H_F11), K(H_F12), M(arduino::KEY_RSHIFT)},
  {M(arduino::KEY_RALT), M(arduino::KEY_RLOGO), M(arduino::KEY_RCTRL), K(H_INS), K(H_LEFT), K(H_DOWN), K(H_UP), K(H_RIGHT)},
  {K(H_SPACE), K(H_DEL), K(H_PGDN), K(H_HOME), K(H_END), K(H_ENTER), K(H_BKSP), K(H_TAB)}
};

const KeyDef (*activeKeymap)[kCols] =
#if defined(HALF_RIGHT)
  kRightKeymap;
#else
  kLeftKeymap;
#endif

Adafruit_MCP23X17 mcp;
arduino::USBKeyboard Keyboard;
bool rawState[kRows][kCols] = {};
bool debouncedState[kRows][kCols] = {};
uint32_t changedAt[kRows][kCols] = {};
uint32_t nextBatteryReportMs = 0;

float readBatteryVoltage() {
  analogReadResolution(12);
  const int raw = analogRead(kBatterySensePin);
  const float sensed = (static_cast<float>(raw) / 4095.0f) * 3.3f;
  return sensed * kBatteryDividerScale;
}

uint8_t batteryPercent(float vbat) {
  float pct = (vbat - kBatteryEmptyV) * 100.0f / (kBatteryFullV - kBatteryEmptyV);
  if (pct < 0.0f) pct = 0.0f;
  if (pct > 100.0f) pct = 100.0f;
  return static_cast<uint8_t>(pct + 0.5f);
}

void setAllRowsHigh() {
  for (uint8_t r = 0; r < kRows; ++r) {
    mcp.digitalWrite(kRowPins[r], HIGH);
  }
}

void sendKeyboardReport() {
  uint8_t modifierMask = 0;
  uint8_t usages[6] = {0, 0, 0, 0, 0, 0};
  uint8_t usageCount = 0;

  for (uint8_t r = 0; r < kRows; ++r) {
    for (uint8_t c = 0; c < kCols; ++c) {
      if (!debouncedState[r][c]) continue;
      const KeyDef key = activeKeymap[r][c];
      modifierMask |= key.modifier;
      if (key.usage != 0 && usageCount < 6) {
        usages[usageCount++] = key.usage;
      }
    }
  }

  HID_REPORT report;
  report.data[0] = 1;
  report.data[1] = modifierMask;
  report.data[2] = 0;
  report.data[3] = usages[0];
  report.data[4] = usages[1];
  report.data[5] = usages[2];
  report.data[6] = usages[3];
  report.data[7] = usages[4];
  report.data[8] = usages[5];
  report.length = 9;

  Keyboard.send(&report);
}

void scanMatrix() {
  const uint32_t now = millis();
  bool changed = false;

  for (uint8_t row = 0; row < kRows; ++row) {
    setAllRowsHigh();
    mcp.digitalWrite(kRowPins[row], LOW);
    delayMicroseconds(50);

    for (uint8_t col = 0; col < kCols; ++col) {
      const bool pressed = (mcp.digitalRead(kColPins[col]) == LOW);

      if (pressed != rawState[row][col]) {
        rawState[row][col] = pressed;
        changedAt[row][col] = now;
      }

      if ((now - changedAt[row][col]) >= kDebounceMs && debouncedState[row][col] != rawState[row][col]) {
        debouncedState[row][col] = rawState[row][col];
        changed = true;
      }
    }
  }
  setAllRowsHigh();

  if (changed) {
    sendKeyboardReport();
  }
}

void reportBatteryIfDue() {
  const uint32_t now = millis();
  if (now < nextBatteryReportMs) return;
  nextBatteryReportMs = now + 30000;

  const float vbat = readBatteryVoltage();
  const uint8_t pct = batteryPercent(vbat);
  Serial.print("Battery: ");
  Serial.print(pct);
  Serial.print("% (");
  Serial.print(vbat, 2);
  Serial.println("V)");
}
}

void setup() {
  Serial.begin(115200);
  delay(150);

  pinMode(kBuzzerPin, OUTPUT);
  digitalWrite(kBuzzerPin, LOW);

  Wire.begin();
  if (!mcp.begin_I2C(kMcpAddress, &Wire)) {
    Serial.println("MCP23017 not found at 0x20.");
    while (true) {
      digitalWrite(kBuzzerPin, HIGH);
      delay(80);
      digitalWrite(kBuzzerPin, LOW);
      delay(920);
    }
  }

  for (uint8_t c = 0; c < kCols; ++c) {
    mcp.pinMode(kColPins[c], INPUT_PULLUP);
  }
  for (uint8_t r = 0; r < kRows; ++r) {
    mcp.pinMode(kRowPins[r], OUTPUT);
  }
  setAllRowsHigh();

  digitalWrite(kBuzzerPin, HIGH);
  delay(40);
  digitalWrite(kBuzzerPin, LOW);

  Serial.println(
#if defined(HALF_RIGHT)
    "SplitKeyboard firmware: RIGHT half"
#else
    "SplitKeyboard firmware: LEFT half"
#endif
  );
}

void loop() {
  scanMatrix();
  reportBatteryIfDue();
  delay(2);
}
