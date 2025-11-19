/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum {
  TD_ALT_GUI = 0,
  TD_MT_TG3 = 1,
  TD_PR_TG4 = 2
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_ALT_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
  [TD_MT_TG3] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_MUTE, 3),
  [TD_PR_TG4] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_PSCR, 4)
};

enum custom_keycodes {
  S_SZ = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t s_sz_timer;  // Timer to measure the key press time

    switch(keycode) {
        case S_SZ:
            if(record->event.pressed) {
                // When the key is pressed, start the timer.
                s_sz_timer = timer_read();
            } else {
                // Key released. Check the elapsed time.
                if (timer_elapsed(s_sz_timer) < 200) {
                    // Tap: output 's'
                    register_code(KC_S);
                    unregister_code(KC_S);
                } else {
                    // Hold: output 'ß' (ANSI -)
                    register_code(KC_MINS);
                    unregister_code(KC_MINS);
                }
            }
            return false; // We've handled this keycode completely.
    }
    return true; // Process all other keycodes normally.
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(
  //,   -----------------------------------------------------------------------------|     |--------------------------------------------------------------.
       KC_TAB,       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,    KC_VOLU, TD(TD_PR_TG4),       KC_Y,       KC_U,       KC_I,       KC_O,      KC_P,     KC_LBRC,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|     |--------+-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LCTL,       KC_A,       KC_S,       KC_D,       KC_F,       KC_G,    KC_VOLD, TD(TD_MT_TG3),       KC_H,       KC_J,       KC_K,       KC_L,    KC_SCLN,    KC_QUOT,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|     |--------+-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LSFT,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                                  KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,    KC_RSFT,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|     |--------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                 MO(2),    TD(TD_ALT_GUI),     KC_ENT,        KC_SPC,    KC_BSPC,       MO(1)
                                      //`--------------------------------------------'     `--------------------------------------------'

  ),

    [1] = LAYOUT_split_3x6_3_ex2(
  //,   -----------------------------------------------------------------------------|  |-----------------------------------------------------------------------------------.
       KC_ESC,       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,    XXXXXXX,       XXXXXXX,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,    KC_MINS,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      KC_CAPS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    KC_LEFT,    KC_DOWN,      KC_UP,   KC_RIGHT,    XXXXXXX,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LSFT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                               XXXXXXX,    KC_MUTE,    XXXXXXX,    XXXXXXX,    KC_BSLS,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                 MO(3),    TD(TD_ALT_GUI),     KC_ENT,        KC_SPC,    KC_BSPC,    _______
                                      //`--------------------------------------------'  `-----------------------------------------------'
  ),

    [2] = LAYOUT_split_3x6_3_ex2(
  //,   -----------------------------------------------------------------------------|  |-----------------------------------------------------------------------------------.
       KC_ESC,    KC_EXLM,      KC_AT,    KC_HASH,     KC_DLR,    KC_PERC,    XXXXXXX,       XXXXXXX,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,     KC_DEL,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LCTL,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,     KC_EQL,    KC_MINS,    KC_PLUS,    KC_LBRC,    KC_RBRC, S(KC_QUOT),
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      KC_LSFT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                               KC_TILD,    KC_UNDS,     KC_GRV,    KC_LCBR,    KC_RCBR,    KC_PIPE,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                      _______,    KC_LALT,     KC_ENT,        KC_SPC,    _______,      MO(3)
                                      //`---------------------------------------------'  ````-------------------------------------------'
  ),
  //, Mouse layer
    [3] = LAYOUT_split_3x6_3_ex2(
  //,   -----------------------------------------------------------------------------|  |-----------------------------------------------------------------------------------.
      XXXXXXX,    MS_ACL0,    MS_ACL1,    MS_ACL2,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    MS_WHLL,    MS_WHLD,    MS_WHLU,    MS_WHLR,    XXXXXXX,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, TD(TD_MT_TG3),    MS_LEFT,    MS_DOWN,      MS_UP,    MS_RGHT,    XXXXXXX,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    MS_BTN1,    XXXXXXX,                               MS_BTN3,    MS_BTN1,    MS_BTN2,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                      KC_LGUI,    KC_LALT,     KC_ENT,        KC_SPC,    _______,    _______
                                      //`--------------------------------------------'  `-----------------------------------------------'
  ),
  //, Function Key / RGB layer
    [4] = LAYOUT_split_3x6_3_ex2(
  //,   -----------------------------------------------------------------------------|  |-----------------------------------------------------------------------------------.
        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,    XXXXXXX,         TG(4),      KC_F7,      KC_F8,      KC_F9,     KC_F10,     KC_F11,     KC_F12,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      RM_TOGG,    RM_HUEU,    RM_SATU,    RM_VALU,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      RM_NEXT,    RM_HUED,    RM_SATD,    RM_VALD,    XXXXXXX,    XXXXXXX,                               XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|--------+-----------+-----------+-----------+-----------+-----------+-----------|  |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                      KC_LGUI,    KC_LALT,     KC_ENT,        KC_SPC,    _______,    KC_RALT
                                      //`--------------------------------------------'  `-----------------------------------------------'
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD,    KC_VOLU),    ENCODER_CCW_CW(KC_MPRV,    KC_MNXT),    ENCODER_CCW_CW(RM_VALD,    RM_VALU),    ENCODER_CCW_CW(KC_RGHT,    KC_LEFT),    },
  [1] = { ENCODER_CCW_CW(KC_VOLD,    KC_VOLU),    ENCODER_CCW_CW(KC_MPRV,    KC_MNXT),    ENCODER_CCW_CW(RM_VALD,    RM_VALU),    ENCODER_CCW_CW(KC_RGHT,    KC_LEFT),    },
  [2] = { ENCODER_CCW_CW(KC_VOLD,    KC_VOLU),    ENCODER_CCW_CW(KC_MPRV,    KC_MNXT),    ENCODER_CCW_CW(RM_VALD,    RM_VALU),    ENCODER_CCW_CW(KC_RGHT,    KC_LEFT),    },
  [3] = { ENCODER_CCW_CW(KC_VOLD,    KC_VOLU),    ENCODER_CCW_CW(KC_MPRV,    KC_MNXT),    ENCODER_CCW_CW(RM_VALD,    RM_VALU),    ENCODER_CCW_CW(KC_RGHT,    KC_LEFT),    },
};
#endif
