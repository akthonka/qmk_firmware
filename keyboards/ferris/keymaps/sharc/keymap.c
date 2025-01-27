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
#define REDO LCTL(KC_Y)
#define LMON LGUI(LSFT(KC_LEFT))
#define RMON RGUI(LSFT(KC_RIGHT))
#define LSEL LCTL(LSFT(KC_LEFT))
#define RSEL LCTL(LSFT(KC_RIGHT))
#define RDSKTP LCTL(LGUI(KC_RIGHT))
#define LDSKTP LCTL(LGUI(KC_LEFT))
#define RTAB LCTL(KC_TAB)
#define LTAB LCTL(LSFT(KC_TAB))
#define WRDDEL LCTL(KC_BSPC)


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
    LBRC_LT,
    RBRC_GT,
	SHFT_CPS,
    CTRL_WIN,
    TO_ONE,
    TO_TWO,
    SLSH_UND,
    COMM_SEM,
    PLS_MINS
};

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void dotexcl_finished(qk_tap_dance_state_t *state, void *user_data);
void dotexcl_reset(qk_tap_dance_state_t *state, void *user_data);
void lbrclt_finished(qk_tap_dance_state_t *state, void *user_data);
void lbrclt_reset(qk_tap_dance_state_t *state, void *user_data);
void rbrcgt_finished(qk_tap_dance_state_t *state, void *user_data);
void rbrcgt_reset(qk_tap_dance_state_t *state, void *user_data);
void ctrlwin_finished(qk_tap_dance_state_t *state, void *user_data);
void ctrlwin_reset(qk_tap_dance_state_t *state, void *user_data);
void toone_finished(qk_tap_dance_state_t *state, void *user_data);
void toone_reset(qk_tap_dance_state_t *state, void *user_data);
void totwo_finished(qk_tap_dance_state_t *state, void *user_data);
void totwo_reset(qk_tap_dance_state_t *state, void *user_data);
void slshund_finished(qk_tap_dance_state_t *state, void *user_data);
void slshund_reset(qk_tap_dance_state_t *state, void *user_data);
void commsem_finished(qk_tap_dance_state_t *state, void *user_data);
void commsem_reset(qk_tap_dance_state_t *state, void *user_data);
void plsmins_finished(qk_tap_dance_state_t *state, void *user_data);
void plsmins_reset(qk_tap_dance_state_t *state, void *user_data);


enum custom_keycodes {
    CLINE = SAFE_RANGE, // copies the line to clipboard
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CLINE:
        if (record->event.pressed) {
            // when keycode CLINE is pressed
            tap_code(KC_HOME);
            register_code(KC_LSFT);
            tap_code(KC_END);
            unregister_code(KC_LSFT);
        } else {
            // when keycode QMKBEST is released
            register_code(KC_LEFT_CTRL);
            tap_code(KC_C);
            unregister_code(KC_LEFT_CTRL);
        }
        break;
    }
    return true;
};

// NOTE: Avoid tap dance functions between "fast swapping" (i.e. within the hold window time period) layers!
//       This leads to a bug where qmk has permanently stuck hold-function keys, even with clear_keyboard()

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
		KC_Y, 	    KC_C, 	    KC_L, 		KC_M, 		KC_K, 						KC_Z, 	    KC_F, 		KC_U,	 	    TD(COMM_SEM), 	KC_QUOTE,
		KC_I, 	    KC_S, 	    KC_R,	    KC_T, 	    KC_G,						KC_P, 	    KC_N,		KC_E,		    KC_A, 			KC_O,
		KC_Q, 	    KC_V, 	    KC_W, 		KC_D, 		KC_J, 						KC_B, 	    KC_H, 		TD(SLSH_UND), 	TD(DOT_EXCL), 	KC_X,

			  				    TD(SHFT_CPS),     TD(TO_ONE),	    			    TD(CTRL_WIN),       KC_SPACE),

																																			//.

	[1] = LAYOUT_split_3x5_2(
		KC_ESC, 	KC_EXLM,    KC_AT, 	    KC_HASH,    KC_DLR, 			        KC_PERC,    KC_CIRC, 	KC_AMPR, 	    KC_ASTR, 	    KC_BSPC,
		KC_TAB, 	ALL, 		COPY, 		PASTE,      KC_F2, 				        KC_EQL, 	KC_MINS,    KC_LPRN,        KC_RPRN, 	    KC_ENT,
		UNDO, 		REDO, 	    CUT, 	    KC_F4,      TO(2), 				        WRDDEL,     KC_BSLS,	TD(LBRC_LT), 	TD(RBRC_GT),    KC_DEL,

								KC_LALT, 	     TD(CTRL_WIN),			            TO(0),      KC_LSFT),
																																			//

	[2] = LAYOUT_split_3x5_2(
		KC_ESC,     LSEL, 	    KC_UP, 		RSEL, 		KC_NO, 				        TD(PLS_MINS),   KC_7, 	    KC_8, 	    KC_9, 	    KC_BSPC,
		KC_TAB,     KC_LEFT,    KC_DOWN, 	KC_RGHT, 	TO(3),				        KC_EQL,         KC_4, 	    KC_5, 	    KC_6, 	    KC_ENT,
		KC_NO,      KC_HOME,    CLINE, 	    KC_END, 	KC_NO, 				        KC_DOT, 	    KC_1, 	    KC_2, 	    KC_3, 	    KC_DEL,

							    KC_LSFT, 	     TD(CTRL_WIN), 				        TO(0), 	        KC_0),
							 																												//

            
	[3] = LAYOUT_split_3x5_2(
		KC_GESC, 	LDSKTP, 	KC_MS_U, 	RDSKTP, 	KC_PSCR, 					KC_WH_U, 	KC_BTN3, 	LTAB, 	    RTAB,	    KC_BSPC,
		KC_TAB, 	KC_MS_L, 	KC_MS_D, 	KC_MS_R, 	KC_F5, 						KC_WH_D, 	KC_ACL0, 	KC_ACL1, 	KC_ACL2, 	KC_ENT,
		LMON, 	    KC_WH_L, 	KC_NO, 		KC_WH_R, 	RMON, 						KC_NO, 		KC_BTN2, 	KC_BTN4, 	KC_BTN5, 	KC_DEL, 

                                KC_LALT,         TD(CTRL_WIN), 						TO(0), 	    KC_BTN1),
																																			//.


    // German Keyboard Layout 
    [4] = LAYOUT_split_3x5_2(
        KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO, 					    KC_NO, 	    KC_NO, 	    KC_LBRC,    KC_NO, 	    KC_NO,
        KC_NO, 	    KC_MINS,    KC_NO, 	    KC_NO, 	    KC_NO, 					    KC_NO,	    KC_NO, 	    KC_NO, 	    KC_QUOT,    KC_SCLN,
        KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO, 					    KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO, 	    KC_NO,

                                            KC_NO,      KC_NO, 					    TO(0), 	    KC_NO)
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

void dotexcl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_DOT); break;
        case TD_SINGLE_HOLD: register_code16(KC_EXLM); break;
		case TD_DOUBLE_TAP: register_code16(KC_COLN); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_COLN); break;
		case TD_TRIPLE_TAP: tap_code(KC_DOT); register_code(KC_DOT); register_code(KC_DOT); break;
        case TD_TRIPLE_SINGLE_TAP: tap_code(KC_DOT); register_code(KC_DOT); register_code(KC_DOT); break;
		default: break;
    }
}

void dotexcl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_DOT); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_EXLM); break;
		case TD_DOUBLE_TAP: unregister_code16(KC_COLN); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_COLN); break;
		case TD_TRIPLE_TAP: unregister_code(KC_DOT); break;
        case TD_TRIPLE_SINGLE_TAP: unregister_code(KC_DOT); break;
		default: break;
    }
}

void lbrclt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: register_code16(KC_LT); break;
        case TD_DOUBLE_TAP: register_code16(KC_LCBR); break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_LCBR); break;
		default: break;
    }
}

void lbrclt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_LT); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_LCBR); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LCBR); break;
		default: break;
    }
}

void rbrcgt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_RBRC); break;
        case TD_SINGLE_HOLD: register_code16(KC_GT); break;
        case TD_DOUBLE_TAP: register_code16(KC_RCBR); break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_RCBR); break;
		default: break;
    }
}

void rbrcgt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code16(KC_RBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GT); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_RCBR); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RCBR); break;
		default: break;
    }
}

void shftcps_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
		case TD_DOUBLE_TAP: register_code(KC_CAPS); break;
		default: break;
    }
}

void shftcps_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
		case TD_DOUBLE_TAP: unregister_code(KC_CAPS); break;
		default: break;
    }
}

void ctrlwin_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_RIGHT_CTRL); break;
        case TD_SINGLE_HOLD: register_code(KC_RIGHT_CTRL); break;
		case TD_DOUBLE_TAP: register_code(KC_LGUI); break;
        case TD_DOUBLE_SINGLE_TAP: register_code(KC_LGUI); break;
        case TD_DOUBLE_HOLD: register_code(KC_LGUI); break;
		default: break;
    }
}

void ctrlwin_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_RIGHT_CTRL); break;
        case TD_SINGLE_HOLD: unregister_code(KC_RIGHT_CTRL); break;
		case TD_DOUBLE_TAP: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LGUI); break;
		default: break;
    }
}

void toone_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: layer_move(1); break;
        case TD_SINGLE_HOLD:
            register_code16(LGUI(KC_SPACE));
            unregister_code(KC_SPACE);
            layer_move(4);
            break;
        default: break;
    }
}

void toone_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: clear_keyboard(); break;
        case TD_SINGLE_HOLD:
            register_code16(LGUI(KC_SPACE));
            unregister_code(KC_SPACE);
            layer_move(0);
            break;
        case TD_DOUBLE_TAP: clear_keyboard(); break;
		default: break;
    }
}

void totwo_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: layer_move(2); break;
        case TD_SINGLE_HOLD: register_code(KC_LALT); break;
		default: break;
    }
}

void totwo_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: clear_keyboard(); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
		default: break;
    }
}

void slshund_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_SLSH); break;
        case TD_SINGLE_HOLD: register_code16(KC_UNDS); break;
        case TD_DOUBLE_TAP: tap_code16(KC_SLSH); register_code16(KC_SLSH); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_SLSH); register_code16(KC_SLSH); break;
		default: break;
    }
}

void slshund_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_SLSH); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_UNDS); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_SLSH); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_SLSH); break;
		default: break;
    }
}

void commsem_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_COMMA); break;
        case TD_DOUBLE_TAP: register_code16(KC_SCLN); break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_SCLN); break;
		default: break;
    }
}

void commsem_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_COMMA); break;
        case TD_DOUBLE_TAP: unregister_code(KC_SCLN); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SCLN); break;
		default: break;
    }
}

void plsmins_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_MINS); break;
        case TD_DOUBLE_TAP: register_code16(KC_PLUS); break;
        case TD_DOUBLE_SINGLE_TAP: register_code16(KC_PLUS); break;
		default: break;
    }
}

void plsmins_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_MINS); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_PLUS); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_PLUS); break;
		default: break;
    }
}

// Associate tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [DOT_EXCL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dotexcl_finished, dotexcl_reset),
    [LBRC_LT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbrclt_finished, lbrclt_reset),
    [RBRC_GT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbrcgt_finished, rbrcgt_reset),
	[SHFT_CPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shftcps_finished, shftcps_reset),
    [CTRL_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrlwin_finished, ctrlwin_reset),
    [TO_ONE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, toone_finished, toone_reset),
    [TO_TWO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, totwo_finished, totwo_reset),
    [SLSH_UND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slshund_finished, slshund_reset),
    [COMM_SEM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, commsem_finished, commsem_reset),
    [PLS_MINS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, plsmins_finished, plsmins_reset),
};