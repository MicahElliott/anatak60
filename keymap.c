/* Copyright 2019 rominronin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// MacOS based definitions.
#define K_SPCFN LT(SYMB, KC_SPACE) // Tap for space, hold for symbols layer
#define K_PRVWD LALT(KC_LEFT)      // Previous word
#define K_NXTWD LALT(KC_RIGHT)     // Next word
#define K_LSTRT LGUI(KC_LEFT)      // Start of line
#define K_LEND  LGUI(KC_RIGHT)     // End of line
#define UNDO    LGUI(KC_Z)         // UNDO
#define CUT     LGUI(KC_X)         // CUT
#define COPY    LGUI(KC_C)         // COPY
#define PASTE   LGUI(KC_V)         // PASTE


#define GUI_LBRC    GUI_T(KC_LBRC)               // Tap for [, hold for Alt
#define GUI_RBRC    GUI_T(KC_RBRC)               // Tap for ], hold for Alt


enum layer_names {
    BASE,
    NUMB,
    SYMB,
    CURS,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_1_a(/* Base */
    LT(NUMB,KC_ESC),   _______, _______, GUI_RBRC,SC_RAPC, KC_SPC,  KC_PLUS, KC_TILD, KC_PIPE, KC_MINS, SC_LAPO, GUI_LBRC,_______, _______, LT(NUMB,KC_BSLS),
    SFT_T(KC_GRV),     KC_SLSH, KC_DOT,  KC_COMM, KC_H,    KC_K,    KC_F12,           KC_F12,  KC_V,    KC_D,    KC_C,    KC_X,    KC_Z,    SFT_T(KC_SCLN),
    CTL_T(KC_ENT),     KC_O,    KC_I,    KC_E,    KC_N,    KC_M,    KC_RABK,          KC_LABK, KC_G,    KC_T,    KC_S,    KC_R,    KC_A,    CTL_T(KC_TAB),
    LT(SYMB,KC_BSPC),  KC_QUOT, KC_Y,    KC_U,    KC_L,    KC_J,    KC_CIRC, KC_F12,  KC_HASH, KC_B,    KC_P,    KC_F,    KC_W,    KC_Q,    LT(SYMB,KC_EQL),
    KC_HASH,           KC_RCBR, KC_UNDS, KC_ASTR, KC_AMPR,                   _______,          KC_AT,   KC_PERC, KC_COLN, KC_DLR,  KC_LCBR, KC_EXLM
  ),
  [NUMB] = LAYOUT_1_a(
    _______,           _______, _______, _______, _______, _______, _______, DF(0),   _______, _______, _______, _______, _______, _______, _______,
    _______,           KC_SLSH, KC_3,    KC_2,    KC_1,    KC_GT,   _______,          _______, KC_LT,   KC_PIPE, KC_LBRC, _______, KC_LCBR, _______,
    _______,           KC_DOT,  KC_6,    KC_5,    KC_4,    KC_RCBR, _______,          _______, KC_LCBR, KC_DLR,  KC_BSLS, _______, KC_AMPR, _______,
    _______,           KC_0,    KC_9,    KC_8,    KC_7,    KC_CIRC, _______, _______, _______, KC_PERC, KC_PERC, KC_HASH, KC_AT,   KC_EXLM, _______,
    _______,           _______, _______, _______,          _______, KC_P0,   _______,       _______, _______, _______, _______, _______
  ),
  [SYMB] = LAYOUT_1_a(
    KC_DOWN,           KC_END,  KC_F12,  KC_F11,  KC_F10,  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, _______,
    KC_UP,             KC_PGDN, KC_F3,   KC_F2,   KC_F1,   _______, _______,          _______, _______, _______, _______, KC_MUTE, KC_VOLU, _______,
    _______,           KC_PGUP, KC_F6,   KC_F5,   KC_F4,   KC_DEL,  _______,          _______, _______, KC_RGHT, KC_DOWN, KC_LEFT, KC_PGDN, _______,
    _______,           KC_HOME, KC_F9,   KC_F8,   KC_F7,   KC_INS,  _______, _______, _______, _______, KC_END,  KC_UP,   KC_HOME, KC_PGUP, _______,
    _______,           _______, _______, _______,                _______,    _______,    KC_DEL,        _______, _______, _______, _______, _______
  ),
  [CURS] = LAYOUT_1_a(
    _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,           _______, _______, _______, _______, _______, _______,          _______, _______, K_PRVWD, KC_UP,   K_NXTWD, _______, _______,
    _______,           _______, KC_LCTL, KC_LALT, KC_LSFT, _______, _______,          _______, KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  _______,
    _______,           UNDO,    CUT,     COPY,    PASTE,   _______, _______, _______, _______, _______, K_LSTRT, _______, K_LEND,  _______, _______,
    _______,           _______, _______, _______, _______,                   _______,          _______, _______, _______, _______, _______, _______
  )
};

/* Enable the CURS layer, pressing both the other layers together. */
/* https://docs.splitkb.com/hc/en-us/articles/360018614379-Using-tri-state-layers */
/* https://docs.qmk.fm/#/ref_functions?id=update_tri_layer_statestate-x-y-z */
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, NUMB, SYMB, CURS);
}
