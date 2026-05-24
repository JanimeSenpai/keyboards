// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"
#include "keymap_german.h"
#include "keymap_finnish.h"
#include "keymap_italian.h"
#include "quantum.h"

#define ARROWS MO(7)
#define NUMPAD MO(8)

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   6

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
            oled_write("4\n(German)   ", false);
            break;    
        case 5:
            oled_write("5\n(Finnish)   ", false);
            break;  
            case 6:
            oled_write("6\n(Italian)   ", false);
            break;  
        case 7:
            // Shows when you hold your ARROWS modifier
            oled_write("7\n(Arrows)   ", false); 
            break;
        case 8:
            // Shows when you hold your NUMPAD modifier
            oled_write("8\n(Numpad)   ", false); 
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


[0] = LAYOUT( // default layer
        // Left Half
        KC_ESC,        KC_F1,         KC_F2,    KC_F3,    KC_F4,         KC_F5,      KC_F6,    KC_F7,       // Row 1 (New Top)
        KC_ALGR,       HU_0,          KC_1,     KC_2,     KC_3,          KC_4,       KC_5,     KC_6,        // Row 2 
        KC_TAB,        HU_ODAC,       KC_Q,     KC_W,     KC_E,          KC_R,       KC_T,     KC_ESC,      // Row 3
        KC_BACKSPACE,  KC_V,          KC_A,     KC_S,     KC_D,          KC_F,       KC_G,     KC_LEFT_ALT, // Row 4
        KC_CAPS_LOCK,  KC_B,          HU_IACU,  HU_Y,     KC_X,          KC_C,       HU_UACU,  KC_B,        // Row 5
        KC_LEFT_GUI,   KC_LEFT_CTRL,  KC_TAB,   NUMPAD,   KC_SPACE,      KC_ENTER,   KC_P4,                 // Row 6
        KC_NO,         KC_NO,         KC_NO,    KC_LSFT,  KC_LEFT_ALT,                                      // Row 7 (5 keys)
        KC_NO,         ARROWS,                                                                              // Row 8 (2 keys)

        // Right Half
        KC_F8,            KC_F9,    KC_F10,         KC_F11,               KC_F12,    KC_F13,          KC_F14,   KC_CYCLE_LAYERS, // Row 1 (New Top)
        KC_NO,            KC_7,     KC_8,           KC_9,                 HU_ODIA,   HU_UDIA,         HU_OACU,  KC_NO,           // Row 2
        KC_NO,            HU_Z,     KC_U,           KC_I,                 KC_O,      KC_P,            HU_ODAC,  KC_NO,           // Row 3
        HU_SCLN,          KC_H,     KC_J,           KC_K,                 KC_L,      HU_EACU,         HU_AACU,  HU_UDAC,          // Row 4
        KC_KP_ASTERISK,   KC_N,     KC_M,           KC_COMM,              KC_DOT,    KC_SLSH,         HU_UDAC,  KC_NO,           // Row 5
        KC_CYCLE_LAYERS,  KC_NO,    KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),   KC_DEL,    KC_RIGHT_CTRL,   KC_NO,                     // Row 6
        KC_P6,            KC_RSFT,  KC_NO,          KC_NO,                KC_NO,                                                 // Row 7 (5 keys)
        KC_NO,            KC_NO                                                                                                  // Row 8 (2 keys)
    ),

    [1] = LAYOUT( // gaming layer, each button is different
        // Left Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, HU_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        _______, KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
        _______, KC_V,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
        _______, KC_B,    KC_UP,   HU_Y,    KC_X,    KC_C,    HU_UACU, KC_B,
        _______,          KC_LEFT_CTRL, KC_F12,  KC_LSFT, KC_SPACE, KC_ENTER, KC_P4,
        _______, _______, KC_RIGHT, KC_LEFT_ALT, KC_F11, 
        _______, _______,

        // Right Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        KC_NO,   KC_7,    KC_8,    KC_9,    HU_ODIA, HU_UDIA, HU_OACU, _______,
        KC_NO,   HU_Z,    KC_U,    KC_I,    KC_O,    KC_P,    HU_ODAC, _______,
        HU_SCLN, KC_H,    KC_J,    KC_K,    KC_L,    HU_EACU, HU_AACU, _______,
        KC_KP_ASTERISK, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, HU_UDAC, _______,
        KC_CYCLE_LAYERS, KC_NO, KC_CAPS_LOCK, LCTL(KC_CAPS_LOCK), KC_DEL, KC_RIGHT_CTRL, _______, 
        KC_P6,   KC_P7,   KC_RSFT, _______, _______,
        _______, _______
    ),

    [2] = LAYOUT( // backspace works like normal
        // Left Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, HU_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        _______, KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
        _______, KC_V,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
        _______, KC_B,    HU_IACU, HU_Y,    KC_X,    KC_C,    HU_UACU, KC_B,
        _______,          KC_LEFT_CTRL, KC_P2,   KC_P3,   KC_SPACE, KC_ENTER, KC_P4,
        _______, _______, KC_LSFT, KC_1,    KC_LEFT_ALT, 
        _______, _______,

        // Right Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        KC_NO,   KC_7,    KC_8,    KC_9,    HU_ODIA, HU_UDIA, HU_OACU, _______,
        KC_NO,   HU_Z,    KC_U,    KC_I,    KC_O,    KC_P,    HU_ODAC, _______,
        HU_SCLN, KC_H,    KC_J,    KC_K,    KC_L,    HU_EACU, HU_AACU, _______,
        KC_KP_ASTERISK, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, HU_UDAC, _______,
        KC_CYCLE_LAYERS, KC_NO, KC_BACKSPACE, LCTL(KC_BACKSPACE), KC_DEL, KC_RIGHT_CTRL, _______, 
        KC_P6,   KC_P7,   KC_RSFT, _______, _______,
        _______, _______
    ),

[3] = LAYOUT( // native IHKL layer 
        // Left Half
        KC_ESC,        KC_F1,    KC_F2,         KC_F3,    KC_F4,    KC_F5,      KC_F6,    KC_F7,
        KC_ALGR,       HU_0,     KC_1,          KC_2,     KC_3,     KC_4,       KC_5,     KC_6,
        KC_TAB,        HU_UACU,  HU_OACU,       KC_U,     HU_AACU,  HU_Y,       HU_IACU,  KC_NO,
        KC_CAPS_LOCK,  HU_ODIA,  KC_I,          KC_O,     KC_E,     KC_A,       HU_ODAC,  KC_LEFT_ALT,
        KC_BACKSPACE,  KC_C,     HU_UDIA,       KC_DOT,   KC_COMM,  HU_EACU,    HU_UDAC,  HU_UACU,
        KC_LEFT_GUI, KC_LEFT_CTRL,  KC_TAB,   NUMPAD,   KC_SPACE,   KC_ENTER, KC_P4,
        KC_NO,         KC_NO,         KC_NO,    KC_LSFT,  KC_LEFT_ALT,  
        KC_NO,         ARROWS,

        // Right Half
        KC_F8,            KC_F9,    KC_F10,         KC_F11,              KC_F12,  KC_F13,         KC_F14,  KC_CYCLE_LAYERS,
        KC_NO,            KC_7,     KC_8,           KC_9,                KC_W,    KC_X,           KC_Q,    _______,
        KC_NO,            KC_F,     HU_Z,           KC_K,                KC_D,    KC_H,           HU_UACU, _______,
        HU_SCLN,          KC_B,     KC_L,           KC_T,                KC_S,    KC_N,           KC_P,    _______,
        KC_KP_ASTERISK,   KC_V,     KC_R,           KC_M,                KC_G,    KC_J,           KC_SLSH, _______,
        KC_CYCLE_LAYERS,  KC_NO,    KC_BACKSPACE,   LCTL(KC_BACKSPACE),  KC_DEL,  KC_RIGHT_CTRL,  _______, 
        KC_P6,            KC_RSFT,  KC_NO,          KC_NO,                KC_NO,
        KC_NO,            _______
    ),

    [4] = LAYOUT( // german layer
         // Left Half
        KC_ESC,        KC_F1,    KC_F2,         KC_F3,    KC_F4,    KC_F5,      KC_F6,    KC_F7,
        KC_ALGR,       HU_0,     KC_1,          KC_2,     KC_3,     KC_4,       KC_5,     KC_6,
        KC_TAB,        HU_UACU,  HU_OACU,       KC_U,     HU_AACU,  HU_Y,       HU_IACU,  KC_NO,
        KC_CAPS_LOCK,  DE_ODIA,  KC_I,          KC_O,     KC_E,     KC_A,       DE_ADIA,  KC_LEFT_ALT,
        KC_BACKSPACE,  KC_C,     DE_UDIA,       KC_DOT,   KC_COMM,  HU_EACU,    HU_UDAC,  HU_UACU,
        KC_LEFT_GUI, KC_LEFT_CTRL,  KC_TAB,   NUMPAD,   KC_SPACE,   KC_ENTER, KC_P4,
        KC_NO,         KC_NO,         KC_NO,    KC_LSFT,  KC_LEFT_ALT,  
        KC_NO,         ARROWS,

        // Right Half
        KC_F8,            KC_F9,    KC_F10,         KC_F11,              KC_F12,  KC_F13,         KC_F14,  KC_CYCLE_LAYERS,
        KC_NO,            KC_7,     KC_8,           KC_9,                KC_W,    KC_X,           KC_Q,    _______,
        KC_NO,            KC_F,     HU_Z,           KC_K,                KC_D,    KC_H,           DE_SS, _______,
        HU_SCLN,          KC_B,     KC_L,           KC_T,                KC_S,    KC_N,           KC_P,    _______,
        KC_KP_ASTERISK,   KC_V,     KC_R,           KC_M,                KC_G,    KC_J,           KC_SLSH, _______,
        KC_CYCLE_LAYERS,  KC_NO,    KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),  KC_DEL,  KC_RIGHT_CTRL,  _______, 
        KC_P6,            KC_RSFT,  KC_NO,          KC_NO,                KC_NO,
        KC_NO,            _______                                                                                                // Row 8 (2 keys)
    ),
        [5] = LAYOUT( // finnish layer
         // Left Half
        KC_ESC,        KC_F1,    KC_F2,         KC_F3,    KC_F4,    KC_F5,      KC_F6,    KC_F7,
        KC_ALGR,       HU_0,     KC_1,          KC_2,     KC_3,     KC_4,       KC_5,     KC_6,
        KC_TAB,        HU_UACU,  HU_OACU,       KC_U,     FI_ARNG,  FI_Y,       HU_IACU,  KC_NO,
        KC_CAPS_LOCK,  FI_ODIA,  KC_I,          KC_O,     KC_E,     KC_A,       FI_ADIA,  KC_LEFT_ALT,
        KC_BACKSPACE,  KC_C,     DE_UDIA,       KC_DOT,   KC_COMM,  HU_EACU,    HU_UDAC,  HU_UACU,
        KC_LEFT_GUI, KC_LEFT_CTRL,  KC_TAB,   NUMPAD,   KC_SPACE,   KC_ENTER, KC_P4,
        KC_NO,         KC_NO,         KC_NO,    KC_LSFT,  KC_LEFT_ALT,  
        KC_NO,         ARROWS,

        // Right Half
        KC_F8,            KC_F9,    KC_F10,         KC_F11,              KC_F12,  KC_F13,         KC_F14,  KC_CYCLE_LAYERS,
        KC_NO,            KC_7,     KC_8,           KC_9,                KC_W,    KC_X,           KC_Q,    _______,
        KC_NO,            KC_F,     FI_Z,           KC_K,                KC_D,    KC_H,           DE_SS, _______,
        HU_SCLN,          KC_B,     KC_L,           KC_T,                KC_S,    KC_N,           KC_P,    _______,
        KC_KP_ASTERISK,   KC_V,     KC_R,           KC_M,                KC_G,    KC_J,           KC_SLSH, _______,
        KC_CYCLE_LAYERS,  KC_NO,    KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),  KC_DEL,  KC_RIGHT_CTRL,  _______, 
        KC_P6,            KC_RSFT,  KC_NO,          KC_NO,                KC_NO,
        KC_NO,            _______                                                                                                // Row 8 (2 keys)
    ),
    [6] = LAYOUT( // Italian layer
        // Left Half
        KC_ESC,        KC_F1,    KC_F2,         KC_F3,    KC_F4,    KC_F5,      KC_F6,    KC_F7,
        KC_ALGR,       HU_0,     KC_1,          KC_2,     KC_3,     KC_4,       KC_5,     KC_6,
        KC_TAB,        IT_UGRV,  IT_OGRV,       KC_U,     IT_AGRV,  IT_Y,       HU_IACU,  KC_NO,
        KC_CAPS_LOCK,  HU_ODIA,  KC_I,          KC_O,     KC_E,     KC_A,       HU_ODAC,  KC_LEFT_ALT,
        KC_BACKSPACE,  KC_C,     HU_UDIA,       KC_DOT,   KC_COMM,  IT_EGRV,    HU_UDAC,  HU_UACU,
        KC_LEFT_GUI, KC_LEFT_CTRL,  KC_TAB,   NUMPAD,   KC_SPACE,   KC_ENTER, KC_P4,
        KC_NO,         KC_NO,         KC_NO,    KC_LSFT,  KC_LEFT_ALT,  
        KC_NO,         ARROWS,

        // Right Half
        KC_F8,            KC_F9,    KC_F10,         KC_F11,              KC_F12,  KC_F13,         KC_F14,  KC_CYCLE_LAYERS,
        KC_NO,            KC_7,     KC_8,           KC_9,                KC_W,    KC_X,           KC_Q,    _______,
        KC_NO,            KC_F,     IT_Z,           KC_K,                KC_D,    KC_H,           HU_UACU, _______,
        HU_SCLN,          KC_B,     KC_L,           KC_T,                KC_S,    KC_N,           KC_P,    _______,
        KC_KP_ASTERISK,   KC_V,     KC_R,           KC_M,                KC_G,    KC_J,           KC_SLSH, _______,
        KC_CYCLE_LAYERS,  KC_NO,    KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),  KC_DEL,  KC_RIGHT_CTRL,  _______, 
        KC_P6,            KC_RSFT,  KC_NO,          KC_NO,                KC_NO,
        KC_NO,            _______                                                                                           // Row 8 (2 keys)
    ),


    [7] = LAYOUT( // arrow layer and brackets
        // Left Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, 
        _______, _______,

        // Right Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_HOME, KC_END, _______, _______,
        _______, _______, KC_LEFT, KC_RIGHT, KC_UP,   KC_DOWN, _______, _______,
        _______, _______, HU_LCBR, HU_RCBR, HU_LBRC, HU_RBRC, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______,
        _______, _______
    ),

    [8] = LAYOUT( // numpad layer
        // Left Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, 
        _______, _______,

        // Right Half
        _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  KC_NUM, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______, _______,
        _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______, _______,
        _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______, _______,
        _______, _______, _______, KC_P0,   KC_PENT, _______, _______, 
        _______, _______, _______, _______, _______,
        _______, _______
    ),
};