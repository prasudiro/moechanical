/* MIT License

Copyright (c) 2019 Mattia Dal Ben

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_keycodes {
    KC_DBL0 = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  [0] = LAYOUT(
              KC_KP_7,  KC_KP_8,  KC_KP_9,
    KC_VOLU,  KC_KP_4,  KC_KP_5,  KC_KP_6,
    KC_VOLD,  KC_KP_1,  KC_KP_2,  KC_KP_3,
    KC_MPLY,  TO(1),    KC_KP_0,  KC_ENTER
  ),

  [1] = LAYOUT(
             MACRO07, MACRO08,  MACRO09,
    KC_VOLU, MACRO04, MACRO05,  MACRO06,
    KC_VOLD, MACRO01, MACRO02,  MACRO03,
    KC_MPLY, TO(2),   MACRO00,  KC_ENTER
  ),

  [2] = LAYOUT(
             KC_NO,   KC_NO,    KC_BSPC,
    KC_VOLU, MACRO14, MACRO15,  KC_NO,
    KC_VOLD, MACRO11, MACRO12,  MACRO13,
    KC_MPLY, TO(3),   MACRO10,  KC_ENTER
  ),

  [3] = LAYOUT(
             KC_F7, KC_F8,  KC_F9,
    KC_BTN5, KC_F4, KC_F5,  KC_F6,
    KC_BTN4, KC_F1, KC_F2,  KC_F3,
    KC_F12,  TO(0), KC_F10, KC_F11
  ),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
//new

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

bool oled_task_user(void) {
  
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("ZERO"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("ONE"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("TWO"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("THREE"), false);
            break;
        default:
            oled_write_ln_P(PSTR("ZERO"), false);
    }

    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false); 

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(dynamic_keymap_get_keycode(biton32(layer_state),1,0));
        } else {
            tap_code(dynamic_keymap_get_keycode(biton32(layer_state),2,0));
        }
    }
    return false;
}
#endif
