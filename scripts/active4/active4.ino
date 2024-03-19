#include <cmdline_defs.h>
#include <TrinketHidComboAbsoluteMouse.h>
#include <TrinketHidComboC.h>
#include <usbconfig.h>

// DESIGNED FOR ACTIVE 4 - 2024 JAN SECURITY PATCH, ONE UI 6.0 LIKELY ALL EQUAL
char knox_user[] = "";
char knox_pwd[] = "";

long t_last_ctrl = 0;
long t_ctrl_gap_ms = 10000;

void keystroke(uint8_t modifiers, uint8_t keycode) {
  TrinketHidCombo.pressKey(modifiers, keycode);
  TrinketHidCombo.pressKey(0, 0);
  my_delay(10);
}

void repeat(uint8_t times, uint8_t modifiers, uint8_t keycode) {
  for (int i = 0; i < times; i++) {
    keystroke(modifiers, keycode);
  }
}

void text(char string[]) {
  // implemented for "abcdefghijklmnopqrstuvwxyz @0123456789.ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  for (int i = 0; i < strlen(string); i++) {
    char c = string[i];
    if (c == '@') keystroke(KEYCODE_MOD_LEFT_SHIFT, KEYCODE_2);
    else if (c == '.') keystroke(0, KEYCODE_PERIOD);
    else if (c == ' ') keystroke(0, KEYCODE_SPACE);
    // numeric keycodes are 1-9,0 and ascii is 0-9
    else if (c <= '9') keystroke(0, (c - '0' + 9) % 10 + KEYCODE_1);
    else if (c <= 'Z') keystroke(KEYCODE_MOD_LEFT_SHIFT, c - 'A' + KEYCODE_A);
    else keystroke(0, c - 'a' + KEYCODE_A);
  }
}

void my_delay(long msec) {
  long t0 = millis();
  t_last_ctrl = t0;
  while (millis() < t0 + msec) {
    if (millis() > (t_last_ctrl + t_ctrl_gap_ms)) {
      digitalWrite(1, HIGH);
      keystroke(KEYCODE_MOD_LEFT_CONTROL, 0);
      t_last_ctrl = millis();
      digitalWrite(1, LOW);
    }
    TrinketHidCombo.poll();
  }
}

void loop() {
  if (millis() > (t_last_ctrl + t_ctrl_gap_ms)) {
    keystroke(KEYCODE_MOD_LEFT_CONTROL, 0);
    t_last_ctrl = millis();
  }
  TrinketHidCombo.poll();
}

void setup() {
  pinMode(1, OUTPUT); // LED
  TrinketHidCombo.begin();
  my_delay(1000);

  // terms and conditions
  keystroke(0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  my_delay(500);
  repeat(2, 0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  my_delay(500);
  repeat(5, 0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);

  my_delay(45000);
  // (fully managed) or work profile
  repeat(2, 0, KEYCODE_SPACE);

  my_delay(2000);
  // knox eula page
  repeat(4, 0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);

  my_delay(15000);
  // google services page - new in Android 14?
  // may only be 4 tabs in landscape mode so must be kept portrait
  repeat(5, 0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  my_delay(500);
  repeat(3, 0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  my_delay(500);
  // first 2 tabs cause a scroll so pause a bit more
  keystroke(0, KEYCODE_TAB);
  my_delay(500);
  keystroke(0, KEYCODE_TAB);
  my_delay(500);
  repeat(2, 0, KEYCODE_TAB);
  my_delay(500);
  keystroke(0, KEYCODE_SPACE);

  my_delay(25000);
  // knox login page
  keystroke(0, KEYCODE_TAB);
  my_delay(500);
  text(knox_user);
  keystroke(0, KEYCODE_ENTER);
  // reloads the page with a password field
  my_delay(15000);
  keystroke(0, KEYCODE_TAB);
  my_delay(500);
  text(knox_pwd);
  keystroke(0, KEYCODE_ENTER);

  my_delay(120000); // usually 2 mins is fine but may be up to 7
  // home screen
  // android 14: kiosk says this app was built for an earlier version of android
  keystroke(0, KEYCODE_SPACE);
  my_delay(1000);
  // install app
  keystroke(0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  my_delay(1000);
  keystroke(0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);

  my_delay(45000);
  // run app - activate admin
  keystroke(0, KEYCODE_SPACE);
  my_delay(3000);
  repeat(3, 0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);

  my_delay(10000);
  // app permissions - manage all files, appear on top, change system settings
  keystroke(0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  keystroke(KEYCODE_MOD_LEFT_GUI, KEYCODE_ARROW_LEFT);
  my_delay(5000);
  repeat(2, KEYCODE_MOD_LEFT_SHIFT, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  keystroke(KEYCODE_MOD_LEFT_GUI, KEYCODE_ARROW_LEFT);
  my_delay(5000);
  keystroke(0, KEYCODE_TAB);
  keystroke(0, KEYCODE_SPACE);
  keystroke(KEYCODE_MOD_LEFT_GUI, KEYCODE_ARROW_LEFT);

  // finished, enter device ID
  digitalWrite(1, HIGH);
}

