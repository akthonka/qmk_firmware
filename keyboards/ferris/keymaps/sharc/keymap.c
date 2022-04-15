/* Flashing commands
 *
 *  qmk flash -kb ferris/sweep -km sharc -bl dfu-split-left
 *  qmk flash -kb ferris/sweep -km sharc -bl dfu-split-right
 */

#include QMK_KEYBOARD_H
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define ALL LCTL(KC_A)
#define CUT LCTL(KC_X)
#define UNDO LCTL(KC_Z)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
	TD_TRIPLE_SINGLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    DOT_EXCL,
    APO_GRV,
	SHFT_CPS
};

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void dotexcl_finished(qk_tap_dance_state_t *state, void *user_data);
void dotexcl_reset(qk_tap_dance_state_t *state, void *user_data);
void apogrv_finished(qk_tap_dance_state_t *state, void *user_data);
void apogrv_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
		KC_Y, 	KC_C, 	KC_L, 			KC_M, 			KC_K, 						KC_Z, 	KC_F, 			KC_U,	 	KC_COMMA, 		TD(APO_GRV),
		KC_I, 	KC_S, 	LCTL_T(KC_R),	LGUI_T(KC_T), 	KC_G,						KC_P, 	KC_N,			KC_E,		KC_A, 			KC_O,
		KC_Q, 	KC_V, 	KC_W, 			KC_D, 			KC_J, 						KC_B, 	KC_H, 			KC_SLSH, 	TD(DOT_EXCL), 	KC_X,

			  							TD(SHFT_CPS), 	TO(1), 						KC_RIGHT_CTRL, 	KC_SPACE),
																																			//.

	[1] = LAYOUT_split_3x5_2(
		KC_GESC, 	KC_AT, 		KC_HASH, 	KC_DLR, 	KC_PERC, 					KC_CIRC, 	KC_AMPR, 	KC_ASTR, 	KC_DEL, 	KC_BSPC,
		KC_TAB, 	UNDO, 		COPY, 		PASTE, 		KC_NO, 						KC_MINS, 	KC_LPRN, 	KC_RPRN, 	KC_SCLN, 	KC_ENT,
		ALL, 		CUT, 		KC_HOME, 	KC_END, 	TO(3), 						KC_DQUO, 	KC_LCBR, 	KC_RCBR, 	KC_BSLS, 	KC_QUES,

								MT(MOD_LALT, KC_ENT), 	TO(2),						TO(0), KC_RCTL),
																																			//.

	[2] = LAYOUT_split_3x5_2(
		KC_NO, KC_NO, 	KC_UP, 		KC_NO, 		KC_NO, 				KC_EQL, 	KC_7, 	KC_8, 	KC_9, 	KC_BSPC,
		KC_NO, KC_LEFT, KC_DOWN, 	KC_RGHT, 	KC_NO,				KC_MINS, 	KC_4, 	KC_5, 	KC_6, 	KC_ENT,
		KC_NO, KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 				KC_DOT, 	KC_1, 	KC_2, 	KC_3, 	KC_NO,

								 	KC_SFTENT, 	KC_NO, 				TO(0), 	KC_0),
							 																												//.


	[3] = LAYOUT_split_3x5_2(
		KC_NO, 	KC_NO, 		KC_MS_U, 	KC_NO, 		KC_NO, 						KC_WH_U, 	KC_WH_L, 	KC_WH_R, 	KC_NO, 		KC_NO,
		KC_NO, 	KC_MS_L, 	KC_MS_D, 	KC_MS_R, 	KC_NO, 						KC_WH_D, 	KC_BTN1, 	KC_BTN2, 	KC_BTN3, 	KC_BTN4,
		KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 						KC_NO, 		KC_ACL0, 	KC_ACL1, 	KC_ACL2, 	KC_BTN5,

										KC_NO, 		TO(4), 						TO(0), 	KC_NO),
																																			//.


	[4] = LAYOUT_split_3x5_2(
		DEBUG, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 					KC_MPLY, 	KC_VOLU, 	KC_NO, 		KC_NO, 		KC_BRIU,
		KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 					KC_MSTP,	KC_VOLD, 	KC_MRWD, 	KC_MFFD, 	KC_BRID,
		KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 					KC_NO, 		KC_MUTE, 	KC_NO, 		KC_NO, 		KC_NO,

							 	KC_NO, 	KC_NO, 					TO(0), 		KC_NO)
								 																											//.
};


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted) return TD_TRIPLE_SINGLE_TAP;
        else if (state->pressed) return TD_TRIPLE_HOLD;
        else return TD_TRIPLE_TAP;
    } else return TD_UNKNOWN;
}


// Individual tap dance definitons

// Functions that control what our tap dance key does
void dotexcl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_DOT);break;
        case TD_SINGLE_HOLD: register_code16(KC_EXLM); break;
		case TD_DOUBLE_TAP: register_code(KC_MINS); break;
        case TD_DOUBLE_HOLD: register_code16(KC_UNDS); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_DOT); register_code(KC_DOT); break;
		case TD_TRIPLE_TAP: tap_code(KC_DOT); register_code(KC_DOT); register_code(KC_DOT); break;
		default: break;
    }
}

void dotexcl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_DOT); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_EXLM); break;
		case TD_DOUBLE_TAP: unregister_code(KC_MINS); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_UNDS); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_DOT); break;
		case TD_TRIPLE_TAP: unregister_code(KC_DOT); break;
		default: break;
    }
}

void apogrv_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_QUOT);break;
        case TD_SINGLE_HOLD: register_code16(KC_GRV); break;
		default: break;
    }
}

void apogrv_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GRV); break;
		default: break;
    }
}

void shftcps_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_ENTER);break;
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(KC_LSFT)); break;
		case TD_DOUBLE_TAP: register_code(KC_CAPS); break;
		default: break;
    }
}

void shftcps_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_ENTER); break;
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(KC_LSFT)); break;
		case TD_DOUBLE_TAP: unregister_code(KC_CAPS); break;
		default: break;
    }
}

// Associate tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [DOT_EXCL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dotexcl_finished, dotexcl_reset),
	[APO_GRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, apogrv_finished, apogrv_reset),
	[SHFT_CPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shftcps_finished, shftcps_reset)
};