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

// #include <print.h>


#include QMK_KEYBOARD_H
// #include "keymap_extras/keymap_german_ch.h"

// #include "keymap_extras/muse.h"
// #include "keymap_extras/keymap_spanish.h"



/* Ideas from: https://github.com/gkbd/qmk_firmware/tree/one/keyboards/idobo/keymaps */

#define MIN_PROXIMITY 500

#define PRENASAL(code) (KC_A <= (code) && (code) <= KC_Z &&    code != KC_T && code != KC_S && code != KC_C && code != KC_P && code != KC_G && code != KC_W && code != KC_X)
#define PREANAL(code)  (KC_A <= (code) && (code) <= KC_Z &&    code != KC_H && code != KC_A && code != KC_B && code != KC_D && code != KC_E && code != KC_F && code != KC_I && code != KC_J && code != KC_K && code != KC_L && code != KC_M && code != KC_O && code != KC_Q && code != KC_R && code != KC_U && code != KC_V && code != KC_Y && code != KC_Z && code != KC_N)

uint16_t predecessor_key = KC_NO;
uint16_t adaptive_key = KC_NO;

static uint16_t prenasal_proximity;

// MacOS based definitions.
#define K_SPCFN LT(SYMB, KC_SPACE) // Tap for space, hold for symbols layer
#define K_SCRN  LSFT(LGUI(KC_4))
#define K_PRVWD LALT(KC_LEFT)      // Previous word
#define K_NXTWD LALT(KC_RIGHT)     // Next word
#define K_LSTRT LGUI(KC_LEFT)      // Start of line
#define K_LEND  LGUI(KC_RIGHT)     // End of line
#define UNDO    LGUI(KC_Z)         // UNDO
#define CUT     LGUI(KC_X)         // CUT
#define COPY    LGUI(KC_C)         // COPY
#define PASTE   LGUI(KC_V)         // PASTE
#define SUPTAB  LGUI(KC_TAB)


#define GUI_LBRC    GUI_T(KC_LBRC)               // Tap for [, hold for Alt
#define GUI_RBRC    GUI_T(KC_RBRC)               // Tap for ], hold for Alt

/* These don't actually work, cause other probs */
enum unicode_names {
    U_E1,
    U_E2,
    U_E3,
    U_E4,
    U_E5,
    U_E6
};
const uint32_t PROGMEM unicode_map[] = {
    [U_E1]  = 0x00B0,  // é
    [U_E2]  = 0x00B1,  //
    [U_E3]  = 0x00B2,  //
    [U_E4]  = 0x00B3,  //
    [U_E5]  = 0x00B4,  //
    [U_E6]  = 0x00B5,  //
};

// Combos

const uint16_t PROGMEM test_combo1[] =  {KC_L,    KC_R,    COMBO_END};
// const uint16_t PROGMEM test_combo2[] = {KC_J,    KC_B,    COMBO_END};
const uint16_t PROGMEM test_combo3[] =  {KC_K,    KC_G,    COMBO_END};
const uint16_t PROGMEM test_combo4[] =  {KC_DOT,  KC_COMM, COMBO_END};
const uint16_t PROGMEM test_combo5[] =  {KC_C,    KC_D,    COMBO_END};
const uint16_t PROGMEM test_combo6[] =  {KC_G,    KC_Q,    COMBO_END};
const uint16_t PROGMEM test_combo7[] =  {KC_B,    KC_F,    COMBO_END};
const uint16_t PROGMEM test_combo8[] =  {KC_F,    KC_P,    COMBO_END};
const uint16_t PROGMEM test_combo9[] =  {KC_DQUO, KC_R,    COMBO_END};
const uint16_t PROGMEM test_combo10[] = {KC_P,    KC_X,    COMBO_END};
const uint16_t PROGMEM test_combo11[] = {KC_COMM, KC_MINS, COMBO_END};
const uint16_t PROGMEM test_combo12[] = {KC_L,    KC_R,    COMBO_END};
const uint16_t PROGMEM test_combo13[] = {KC_SLSH, KC_DOT,  COMBO_END};
const uint16_t PROGMEM test_combo14[] = {KC_DQUO, KC_B,    COMBO_END};
const uint16_t PROGMEM test_combo15[] = {KC_F,    KC_S,    COMBO_END};
const uint16_t PROGMEM test_combo16[] = {KC_P,    KC_X,    COMBO_END};
const uint16_t PROGMEM test_combo17[] = {KC_V,    KC_M,    COMBO_END};
const uint16_t PROGMEM test_combo18[] = {KC_X,    KC_M,    COMBO_END};
const uint16_t PROGMEM test_combo19[] = {KC_T,    KC_D,    COMBO_END};
const uint16_t PROGMEM test_combo20[] = {KC_K,    KC_D,    COMBO_END};
const uint16_t PROGMEM test_combo21[] = {KC_B,    KC_DQUO, COMBO_END};
const uint16_t PROGMEM test_combo22[] = {KC_N,    KC_H,    COMBO_END};
const uint16_t PROGMEM test_combo23[] = {KC_H,    KC_SLSH, COMBO_END};
const uint16_t PROGMEM test_combo24[] = {KC_T,    KC_M,    COMBO_END};
const uint16_t PROGMEM test_combo25[] = {KC_W,    KC_Y,    COMBO_END};
combo_t key_combos[] = {
    COMBO(test_combo1, KC_TAB),
    // COMBO(test_combo2, LCTL(KC_W)),
    COMBO(test_combo3,  KC_Z),
    COMBO(test_combo4,  KC_DQUO),
    COMBO(test_combo5,  KC_J),
    COMBO(test_combo6,  LCTL(LGUI(KC_V))),
    COMBO(test_combo7,  LCTL(KC_TAB)),
    COMBO(test_combo8,  KC_EQL),
    COMBO(test_combo9,  LCTL(KC_W)),
    /* COMBO(test_combo10, LCTL(KC_V)), */
    COMBO(test_combo10, KC_AT),
    COMBO(test_combo11, KC_GRV),
    COMBO(test_combo13, KC_QUES),
    /* COMBO(test_combo13, KC_QUES), */ // TODO
    /* COMBO(test_combo2, LClrTL(KC_Z)), // keycodes with modifiers are possible too! */
    COMBO(test_combo16, KC_PIPE),
    COMBO(test_combo17, LCTL(KC_V)),
    COMBO(test_combo18, LCTL(KC_X)),
    COMBO(test_combo20, LCTL(KC_C)),
    /* COMBO(test_combo21, KC_), */
    COMBO(test_combo22, KC_ASTR),
    COMBO(test_combo23, KC_UNDS),
    COMBO(test_combo24, KC_COLN),
    COMBO(test_combo25, KC_COLN),
};


#define IS_MOD(code) (KC_LEFT_CTRL <= (code) && (code) <= KC_RIGHT_GUI)



enum layer_names {
    BASE,
    NUMB,
    EURO,
    SYMB,
    /* CURS, */
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  HN = SAFE_RANGE,
  OM = SAFE_RANGE,
  QMKBEST = SAFE_RANGE,
  QMKURL
};

bool prenasal(void) {
  /* return predecessor_key == KC_A && timer_elapsed(prenasal_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG); */
  return predecessor_key == KC_T && timer_elapsed(prenasal_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG);
};


/* bool prenasal2(void) { */
/*   return predecessor_key == KC_X && timer_elapsed(prenasal_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG); */
/* }; */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_1_a(
    LT(NUMB,KC_GRV),   _______, K_SCRN,  GUI_RBRC,SC_RAPC, KC_SPC,    KC_BSPC, KC_Z,         OSM(MOD_LSFT),QK_REP,  SC_LAPO, GUI_LBRC,SUPTAB,   _______, LT(NUMB,KC_BSLS),
    KC_MINS,           KC_COMM, KC_DOT,  KC_SLSH, KC_H,    KC_N,      KC_PLUS,               KC_EXLM,      KC_V,    KC_D,    KC_C,    KC_K,     KC_G,    KC_Q,
    CTL_T(KC_ENT),     KC_A,    KC_I,    KC_E,    HN,      LCTL(KC_C),KC_RABK,               KC_LABK,      KC_M,    KC_T,    KC_S,    KC_R,     KC_L,    CTL_T(KC_TAB),
    KC_F5,             KC_QUOT, KC_U,    KC_O,    KC_W,    KC_Y,      KC_AT,   OSM(MOD_LCTL),KC_HASH,      KC_X,    KC_P,    KC_F,    KC_B,     KC_APP,  LT(EURO,KC_GRV),
    KC_ESC,            KC_RCBR, KC_DQUO, KC_SCLN, KC_ASTR,                     CW_TOGG,                    KC_DLR,  KC_PERC, KC_TILD, KC_CIRC,  KC_LCBR, KC_APP
  ),
  [NUMB] = LAYOUT_1_a(
    _______,           _______, CW_TOGG, _______, KC_0,    _______, _______, DF(0),   _______, _______, _______, _______, _______, _______, _______,
    _______,           KC_SLSH, KC_3,    KC_2,    KC_1,    KC_GT,   _______,          _______, KC_LT,   KC_PIPE, KC_F11,     _______, KC_LCBR, _______,
    _______,           KC_DOT,  KC_6,    KC_5,    KC_4,    KC_RCBR, _______,          _______, KC_LCBR, KC_DLR,  KC_BSLS, _______, KC_AMPR, _______,
    _______,           KC_GRV,  KC_9,    KC_8,    KC_7,    KC_CIRC, _______, _______, _______, KC_PERC, KC_PERC, KC_HASH, KC_AT,   KC_EXLM, _______,
    _______,           _______, _______, _______,          _______, KC_P0,   _______,       _______, _______, _______, _______, _______
  ),

  [EURO] = LAYOUT_1_a(
    _______,           _______, _______, U_E6,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,           KC_E,    _______, U_E1,    _______, _______, _______,          _______, _______, K_PRVWD, KC_UP,   K_NXTWD, _______, _______,
    _______,           _______, KC_LCTL, U_E2,    KC_LSFT, KC_DEL,  _______,          _______, KC_BSPC, KC_RGHT, KC_DOWN, KC_LEFT, KC_PGDN, _______,
    _______,           UNDO,    CUT,     U_E3,    PASTE,   KC_INS,  _______, _______, _______, _______, KC_END,  KC_UP,   KC_HOME, KC_PGUP, _______,
    _______,           _______, KC_GRV,  U_E4,    _______,                   _______,          _______, _______, _______, KC_TILD, KC_CIRC, _______
  ),
  [SYMB] = LAYOUT_1_a(
    KC_DOWN,           KC_END,  KC_F12,  KC_F11,    KC_F10,  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, _______,
    KC_UP,             KC_S,    KC_F3,   KC_F2,   KC_F1,   _______, _______,          _______, _______, _______, _______, KC_MUTE, KC_VOLU, _______,
    _______,           KC_PGUP, KC_F6,   KC_F5,   KC_F4,   KC_DEL,  _______,          _______, _______, KC_RGHT, KC_DOWN, KC_LEFT, KC_PGDN, _______,
    _______,           KC_HOME, KC_F9,   KC_F8,   KC_F7,   KC_INS,  _______, _______, _______, _______, KC_END,  KC_UP,   KC_HOME, KC_PGUP, _______,
    _______,           _______, _______, _______,                _______,    _______,    KC_DEL,        _______, _______, _______, _______, _______
  ),
  /* [CURS] = LAYOUT_1_a( */
  /*   _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
  /*   _______,           KC_X,    _______, _______, _______, _______, _______,          _______, _______, K_PRVWD, KC_UP,   K_NXTWD, _______, _______, */
  /*   _______,           _______, KC_LCTL, KC_LALT, KC_LSFT, _______, _______,          _______, KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  _______, */
  /*   _______,           UNDO,    CUT,     COPY,    PASTE,   _______, _______, _______, _______, _______, K_LSTRT, _______, K_LEND,  _______, _______, */
  /*   _______,           _______, _______, _______, _______,                   _______,          _______, _______, _______, _______, _______, _______ */
  /* ) */

};

/* Enable the CURS layer, pressing both the other layers together. */
/* https://docs.splitkb.com/hc/en-us/articles/360018614379-Using-tri-state-layers */
/* https://docs.qmk.fm/#/ref_functions?id=update_tri_layer_statestate-x-y-z */
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, NUMB, EURO, SYMB);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // switch (keycode) {
  //     // case KC_F11:  SEND_STRING(SS_TAP(X_F12) SS_DELAY(10) "~"); return false;
  //     case KC_F11:  SEND_STRING(SS_TAP(X_APP)  "'"); return true;
  // }

  // print("string");
  // dprintf("%s", keycode);

  // if (is_caps_word_on()) return true;

  if (keycode == KC_F12) {
    /* SEND_STRING("../"); predecessor_key = keycode; */
    return false;
  }

  else {

  /* adaptive keys */
  if (keycode == HN) {
    if (record->event.pressed) {
      keycode = prenasal()?KC_H:KC_N;
      //keycode = prenasal()?KC_N:KC_H;
      //keycode = preanal()?KC_H:KC_N;
      //keycode = (!prenasal())?KC_H:KC_N;
      register_code(keycode);
      adaptive_key = keycode; }
    else { unregister_code(adaptive_key); }
  }

  /* if (keycode == OM) { */
  /*   if (record->event.pressed) { */
  /*     keycode = prenasal()?KC_M:KC_O; */
  /*     /\* keycode = KC_M; *\/ */
  /*     register_code(keycode); */
  /*     adaptive_key = keycode; } */
  /*   else { unregister_code(adaptive_key); } */
  /* } */

  if (! IS_MOD(keycode) && keycode != OSM(MOD_LSFT) && record->event.pressed) {
    //if (PRENASAL(keycode)) {
    if (PREANAL(keycode)) {
      /* predecessor_key = KC_A; */
      predecessor_key = KC_T;
      prenasal_proximity = timer_read();
    }
    else { predecessor_key = keycode; }
    /* predecessor_key = keycode; */


    /* repeat/magic */
    int rep_count = get_repeat_key_count();
    if (rep_count > 0) {
      switch (keycode) {
      // case KC_F11:  SEND_STRING(SS_TAP(X_F12) "~"); return false;
        //case KC_F11:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING(SS_TAP(KC_TILD)); return false;
      case KC_SPC:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("and"); return false;
      case KC_BSLS: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("``"); return false;
      case KC_COMM: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING(" but"); return false;
      case KC_DOT:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING(".."); return false;
      case KC_QUOT: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bI'"); return false;
      case KC_CIRC: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bback"); return false;
      case KC_TILD: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bforward"); return false;
      case KC_DQUO: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bonly"); return false;
      case KC_SCLN: unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bwithout"); return false;
      /* case KC_GRV:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("```"); return false; */
        /* case KC_DOT:  unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("and"); return false; */
      case KC_A:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ny"); return false;
      case KC_B:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("etween"); return false;
        /* case KC_B:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\broblem"); return false; */
        /* case KC_C:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ontrol"); return false; */
        /* case KC_D:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("epend"); return false; */
        /* case KC_E:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING(""); return false; */
        /* case KC_F:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("rom"); return false; */ // too many doubles
        /* case KC_F:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("orward"); return false; */
        /* case KC_F:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("l"); return false; */
      case KC_G:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("l"); return false;
      case KC_H:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ow"); return false; // how show however
      case KC_I:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ous"); return false; // interest, instrument, industry,
      case KC_J:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bdj"); return false;
      case KC_K:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\b TODO"); return false;
        /* case KC_N:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("umber"); return false; */
      /* case KC_O:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ne"); return false; // ope */
        /* case KC_P:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("e"); return false; // ope */
      /* case KC_Q:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ui"); return false; */
      case KC_Q:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bprob"); return false;
        /* case KC_R:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("emember"); return false; // round, real, remember */
        /* case KC_R:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("ly"); return false; */
      case KC_U:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("i"); return false;
      case KC_X:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\bexcept"); return false;
      case KC_W:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("hy"); return false;
      case KC_V:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("\btogether"); return false;
      case KC_Y:    unregister_weak_mods(MOD_MASK_CSAG); SEND_STRING("eah"); return false;
      }
      /* return true; */
    }

    else switch (keycode) {
    /* case U_E1: SEND_STRING(SS_TAP(X_APP) "'"  SS_DELAY(10) "e"); return false; */

    /* case U_E1: SEND_STRING(SS_TAP(X_APP) "'e"); return false; */
    /* case U_E2: SEND_STRING(SS_TAP(X_APP) "~e"); return false; */
    /* case U_E3: SEND_STRING(SS_TAP(X_APP) "^e"); return false; */
    /* case U_E4: SEND_STRING(SS_TAP(X_APP) "\"e"); return false; */
    /* case U_E5: SEND_STRING(SS_TAP(X_APP) "^e"); return false; */

      /* SEND_STRING("../"); return false; */
    }


  }


  return true;
  }
}
