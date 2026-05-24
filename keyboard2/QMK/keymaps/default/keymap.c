// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"
#include "quantum.h"

#define ARROWS MO(4)
#define NUMPAD MO(5)

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   3

// Add the behaviour of this new keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CYCLE_LAYERS:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

      uint8_t current_layer = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
      return false;

    // Process other keycodes normally
    default:
      return true;
  }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
    // Set cursor position
    oled_set_cursor(0, 1);
    
    // Get the highest active layer
    uint8_t current_layer = get_highest_layer(layer_state);

    oled_write("Current Layer: ", false);

    // Display the corresponding layer number
    switch (current_layer) {
        case 0:
            oled_write("0\n(Default)  ", false);
            break;
        case 1:
            oled_write("1\n(Gaming)   ", false);
            break;
        case 2:
            oled_write("2\n(Normal)   ", false);
            break;
        case 3:
            oled_write("3\n(Native)   ", false);
            break;

        case 4:
            // Shows when you hold your ARROWS modifier
            oled_write("4\n(Arrows)   ", false); 
            break;
        case 5:
            // Shows when you hold your NUMPAD modifier
            oled_write("5\n(Numpad)   ", false); 
            break;
        default:
            oled_write("?            ", false);
            break;
    }
    } 
    
    if(!is_keyboard_left()){
        // --- SLAVE OLED (Right Half) ---
        oled_set_cursor(0, 1);
        oled_write("Hello World! ", false);
        
        // If you ever want to add that QMK logo back, 
        // the else block is a great place to put it!
    }
    
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(//default layer
    
          HU_0,   KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
          HU_ODAC,  KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_ESC,
          KC_V,   KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
          KC_B,   HU_IACU,         HU_Y,    KC_X,    KC_C,    HU_UACU, KC_B,
                KC_LEFT_CTRL,    KC_TAB,   NUMPAD, KC_SPACE, KC_ENTER, KC_P4,
                                                   KC_LSFT, ARROWS, KC_LEFT_ALT,    

        // right half down
        KC_NO,           KC_7,           KC_8,           KC_9,               HU_ODIA, HU_UDIA,           HU_OACU,  
        KC_NO,           HU_Z,           KC_U,           KC_I,                KC_O,    KC_P,             HU_ODAC, 
        HU_SCLN,         KC_H,           KC_J,           KC_K,                 KC_L,    HU_EACU,         HU_AACU, 
        KC_KP_ASTERISK,  KC_N,           KC_M,           KC_COMM,             KC_DOT,  KC_SLSH,          HU_UDAC, 
      KC_CYCLE_LAYERS,             KC_NO,        KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),   KC_DEL	,   KC_RIGHT_CTRL, 
         KC_P6,          KC_P7,       KC_RSFT
    ),
    [1] = LAYOUT(//gaming layer, each button is different
        HU_0,   KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
          KC_NO,  KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
          KC_V,   KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
          KC_B,   KC_UP,         HU_Y,    KC_X,    KC_C,    HU_UACU, KC_B,
                KC_LEFT_CTRL,    KC_F12,   KC_LSFT, KC_SPACE, KC_ENTER, KC_P4,
                                                   KC_RIGHT, KC_LEFT_ALT, KC_F11,    

        // right half down
        KC_NO,           KC_7,           KC_8,           KC_9,               HU_ODIA, HU_UDIA,           HU_OACU,  
        KC_NO,           HU_Z,           KC_U,           KC_I,                KC_O,    KC_P,             HU_ODAC, 
        HU_SCLN,         KC_H,           KC_J,           KC_K,                 KC_L,    HU_EACU,         HU_AACU, 
        KC_KP_ASTERISK,  KC_N,           KC_M,           KC_COMM,             KC_DOT,  KC_SLSH,          HU_UDAC, 
        KC_CYCLE_LAYERS,             KC_NO,        KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),   KC_DEL	,   KC_RIGHT_CTRL, 
        KC_P6,          KC_P7,       KC_RSFT
    ),
   [2]= LAYOUT(//backspace works like normal
    
          HU_0,   KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
          KC_NO,  KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
          KC_V,   KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
          KC_B,   HU_IACU,         HU_Y,    KC_X,    KC_C,    HU_UACU, KC_B,
                KC_LEFT_CTRL,    KC_P2,   KC_P3, KC_SPACE, KC_ENTER, KC_P4,
                                                   KC_LSFT, KC_1, KC_LEFT_ALT,    

        // right half down
        KC_NO,           KC_7,           KC_8,           KC_9,               HU_ODIA, HU_UDIA,           HU_OACU,  
        KC_NO,           HU_Z,           KC_U,           KC_I,                KC_O,    KC_P,             HU_ODAC, 
        HU_SCLN,         KC_H,           KC_J,           KC_K,                 KC_L,    HU_EACU,         HU_AACU, 
        KC_KP_ASTERISK,  KC_N,           KC_M,           KC_COMM,             KC_DOT,  KC_SLSH,          HU_UDAC, 
      KC_CYCLE_LAYERS,             KC_NO,        KC_BACKSPACE,   LCTL(KC_BACKSPACE),   KC_DEL	,   KC_RIGHT_CTRL, 
         KC_P6,          KC_P7,       KC_RSFT
    ),
       [3]= LAYOUT(//native IHKL layer 
    
          HU_0,   KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
          KC_NO,  HU_OACU,        KC_U,    HU_AACU, HU_Y,    HU_IACU, KC_NO,
          HU_ODIA,KC_I,           KC_O,    KC_E,    KC_A,    HU_ODAC, KC_LEFT_ALT,
          KC_C,   HU_UDIA,        KC_DOT, KC_COMM,  HU_EACU, HU_UDAC, HU_UACU, 
                  KC_LEFT_CTRL,    KC_TAB,   NUMPAD, KC_SPACE, KC_ENTER, KC_P4,
                                                   KC_LSFT, KC_1, KC_LEFT_ALT,    

        // right half down
        KC_NO,           KC_7,           KC_8,           KC_9,               KC_W,      KC_X,           KC_Q,  
        KC_NO,           KC_F,           HU_Z,           KC_K,                KC_D,    KC_H,             HU_UACU, 
        HU_SCLN,         KC_B,           KC_L,           KC_T,                 KC_S,    KC_N,         KC_P, 
        KC_KP_ASTERISK,  KC_V,           KC_R,           KC_M,             KC_G,  KC_J,         KC_SLSH, 
      KC_CYCLE_LAYERS,             KC_NO,        KC_BACKSPACE,   LCTL(KC_BACKSPACE),   KC_DEL	,   KC_RIGHT_CTRL, 
         KC_P6,          KC_P7,       KC_RSFT
    ),

 [4] = LAYOUT(//arrow layer and brackets
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,
    
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_HOME, KC_END, _______,
        _______, _______, KC_LEFT, KC_RIGHT,KC_UP,   KC_DOWN, _______,
        _______, _______,HU_LCBR, HU_RCBR, HU_LBRC, HU_RBRC, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    [5] =LAYOUT(//numpad layer
    
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,
    
        _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, KC_P7,   KC_P8,     KC_P9,   KC_PSLS, _______,
        _______, _______, KC_P4,   KC_P5,     KC_P6,   KC_PMNS, _______,
        _______, _______, KC_P1,   KC_P2,     KC_P3,   KC_PPLS, _______,
        _______, _______, _______, KC_P0,     KC_PENT, _______,
        _______, _______, _______
    ),

};
