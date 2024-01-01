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
  [BASE] = LAYOUT_1_a(
    KC_RSFT,           _______, _______, GUI_RBRC,SC_RAPC, KC_SPC,  KC_BSPC, KC_TILD, KC_RSFT, KC_N,    SC_LAPO, GUI_LBRC,_______, _______, LT(NUMB,KC_BSLS),
    QK_REP,            KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, KC_Z,    KC_PIPE,          KC_PLUS, KC_K,    KC_D,    KC_C,    KC_X,    KC_W,    KC_M,
    CTL_T(KC_ENT),     KC_A,    KC_I,    KC_E,    KC_H,    KC_SCLN, KC_RABK,          KC_LABK, KC_G,    KC_T,    KC_S,    KC_R,    KC_L,    CTL_T(KC_TAB),
    KC_DQUO,           KC_QUOT, KC_Y,    KC_O,    KC_U,    KC_J,    KC_CIRC, KC_F12,  KC_HASH, KC_Q,    KC_P,    KC_F,    KC_B,    KC_V,    LT(SYMB,KC_EQL),
    KC_PLUS,           KC_RCBR, KC_UNDS, KC_ASTR, KC_AMPR,                   _______,          KC_AT,   KC_PERC, KC_COLN, KC_DLR,  KC_LCBR, KC_ESC
  ),
  [NUMB] = LAYOUT_1_a(
    _______,           _______, _______, _______, KC_0,    _______, _______, DF(0),   _______, _______, _______, _______, _______, _______, _______,
    _______,           KC_SLSH, KC_3,    KC_2,    KC_1,    KC_GT,   _______,          _______, KC_LT,   KC_PIPE, KC_LBRC, _______, KC_LCBR, _______,
    _______,           KC_DOT,  KC_6,    KC_5,    KC_4,    KC_RCBR, _______,          _______, KC_LCBR, KC_DLR,  KC_BSLS, _______, KC_AMPR, _______,
    _______,           KC_GRV,  KC_9,    KC_8,    KC_7,    KC_CIRC, _______, _______, _______, KC_PERC, KC_PERC, KC_HASH, KC_AT,   KC_EXLM, _______,
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
      int rep_count = get_repeat_key_count();
      if (rep_count > 0) {
        switch (keycode) {
        case KC_SPC:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("the"); return false;
        case KC_COMM: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING(" but"); return false;
        /* case KC_DOT:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("and"); return false; */
        case KC_A:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\b TODO"); return false;
        case KC_B:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\b TODO"); return false;
        /* case KC_C:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ontrol"); return false; */
        /* case KC_D:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("epend"); return false; */
        /* case KC_E:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING(""); return false; */
        /* case KC_F:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("rom"); return false; */ // too many doubles
        /* case KC_F:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("orward"); return false; */
        /* case KC_F:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("l"); return false; */
        case KC_G:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ood"); return false;
        case KC_H:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("owever"); return false;
        case KC_I:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ous"); return false; // interest, instrument, industry,
        case KC_J:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("oin"); return false;
        case KC_K:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("eep"); return false;
        /* case KC_N:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("umber"); return false; */
        /* case KC_P:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("e"); return false; // ope */
        case KC_Q:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ui"); return false;
        /* case KC_R:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("emember"); return false; // round, real, remember */
        /* case KC_R:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ly"); return false; */
        case KC_U:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("i"); return false; // TODO
        case KC_V:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ery"); return false; // village
        /* case KC_:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("that"); return false; */
        case KC_W:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ith"); return false;
        case KC_X:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ce"); return false;
        case KC_Y:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bope"); return false;
        case KC_Z:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\b TODO"); return false;
        }
      }
    }
    return true;
}
