// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"

// Define the keycode, `QK_USER` avoids collisions with existing keycodes
enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   2

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

#define ARROW_LAYER_KEY MO(3)
#define NUMPAD_LAYER_KEY MO(4)

// Place `KC_CYCLE_LAYERS` as a keycode in your keymap
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
        KC_ESC,          KC_F1,   KC_F2,          KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,
        KC_ALGR,         HU_0,    KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_TAB,          KC_NO,  KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
        KC_CAPS_LOCK,    KC_V,    KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
        KC_LEFT_GUI,     KC_B,    HU_IACU,         HU_Y,    KC_X,    KC_C,    HU_UACU,    KC_B,
        ARROW_LAYER_KEY,           KC_NO,   KC_LEFT_CTRL,   KC_NO,   NUMPAD_LAYER_KEY, KC_SPACE, KC_LSFT, KC_ENTER,
        // right half down
        KC_F8,           KC_F9,          KC_F10,         KC_F11,             KC_F12,  KC_F13,            KC_F14,   KC_CYCLE_LAYERS,
        KC_NO,           KC_7,           KC_8,           KC_9,               HU_ODIA, HU_UDIA,           HU_OACU,  KC_NO,
        KC_NO,           HU_Z,           KC_U,           KC_I,                KC_O,    KC_P,             HU_ODAC, HU_UACU,
        HU_SCLN,         KC_H,           KC_J,           KC_K,                 KC_L,    HU_EACU,         HU_AACU, HU_UDAC,
        KC_KP_ASTERISK,  KC_N,           KC_M,           KC_COMM,             KC_DOT,  KC_SLSH,          HU_UDAC, KC_LEFT_ALT,
        KC_NO,           KC_RSFT,        KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),   KC_DEL	,   KC_RIGHT_CTRL,   KC_NO,   KC_NO
    ),
     [1] = LAYOUT(//gaming layer, each button is different
        KC_ESC,          KC_F1,   KC_F2,          KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,
        KC_NO,           HU_0,    KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_TAB,          KC_F8,   KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_F9,
        KC_CAPS_LOCK,    KC_V,    KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,
        KC_LEFT_GUI,     KC_B,    KC_UP,         HU_Y,    KC_X,    KC_C,    HU_UACU,    KC_B,
        KC_LEFT_ALT	,           KC_F11,   KC_LEFT_CTRL,   KC_F12,   KC_LSFT, KC_SPACE, KC_RGHT, KC_ENTER,
        // right half down
        KC_F8,  KC_F9,          KC_F10,         KC_F11,             KC_F12,  KC_F13,            KC_F14,   KC_CYCLE_LAYERS,
        KC_NO,  KC_7,           KC_8,           KC_9,               HU_ODIA, HU_UDIA,           HU_OACU,  KC_NO,
        KC_NO,  HU_Z,           KC_U,           KC_I,                KC_O,    KC_P,             HU_ODAC, HU_UACU,
        KC_SEMICOLON,  KC_H,           KC_J,           KC_K,                 KC_L,    HU_EACU,         HU_AACU, HU_UDAC,
        KC_KP_ASTERISK,  KC_N,           KC_M,           KC_COMM,             KC_DOT,  KC_SLSH,          HU_UDAC, KC_NO,
        KC_NO,  KC_RSFT,        KC_CAPS_LOCK,   LCTL(KC_CAPS_LOCK),   KC_NO,   KC_RIGHT_CTRL,   KC_NO,   KC_NO
    ),
[2] = LAYOUT(//backspace works like normal
        KC_ESC,          KC_F1,   KC_F2,          KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,
        KC_ALGR,         HU_0,    KC_1,           KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_TAB,          KC_NO,  KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
        KC_CAPS_LOCK,    KC_V,    KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT_ALT,
        KC_LEFT_GUI,     KC_B,    HU_IACU,         HU_Y,    KC_X,    KC_C,    HU_UACU,    KC_B,
        ARROW_LAYER_KEY,           KC_NO,   KC_LEFT_CTRL,   KC_NO,   NUMPAD_LAYER_KEY, KC_SPACE, KC_LSFT, KC_ENTER,
        // right half down
        KC_F8,           KC_F9,          KC_F10,         KC_F11,             KC_F12,  KC_F13,            KC_F14,   KC_CYCLE_LAYERS,
        KC_NO,           KC_7,           KC_8,           KC_9,               HU_ODIA, HU_UDIA,           HU_OACU,  KC_NO,
        KC_NO,           HU_Z,           KC_U,           KC_I,                KC_O,    KC_P,             HU_ODAC, HU_UACU,
        HU_SCLN,         KC_H,           KC_J,           KC_K,                 KC_L,    HU_EACU,         HU_AACU, HU_UDAC,
        KC_KP_ASTERISK,  KC_N,           KC_M,           KC_COMM,             KC_DOT,  KC_SLSH,          HU_UDAC, KC_LEFT_ALT,
        KC_NO,           KC_RSFT,        KC_BACKSPACE,   LCTL(KC_BACKSPACE),   KC_DEL	,   KC_RIGHT_CTRL,   KC_NO,   KC_NO
    ),




     [3] = LAYOUT(//arrow layer and brackets
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        // right half down
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_LEFT, KC_RIGHT,KC_UP,   KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, HU_LCBR, HU_RCBR, HU_LBRC, HU_RBRC, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
        [4] = LAYOUT( // Numpad layer on right; J/K/L = 4/5/6 (4th row from top)
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        // right half down
        KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS,     KC_TRNS,     KC_P7,       KC_P8,       KC_P9,      KC_PSLS,    KC_TRNS, KC_TRNS, // 3rd row: 7 8 9 /
        KC_TRNS,     KC_TRNS,     KC_P4,       KC_P5,       KC_P6,      KC_PAST,    KC_TRNS, KC_TRNS, // 4th row: 4 5 6 *
        KC_TRNS,     KC_TRNS,     KC_P1,       KC_P2,       KC_P3,      KC_PMNS,    KC_TRNS, KC_TRNS, // 5th row: 1 2 3 -
        KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_P0,     KC_PENT,    KC_PPLS,    KC_TRNS, KC_TRNS  // 6th row: 0 . Enter +
    )
};

