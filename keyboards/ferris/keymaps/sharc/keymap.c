#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
		KC_Y, 	KC_C, 	KC_L, 	KC_M, 	KC_K, 					KC_Z, 	KC_F, 	KC_U,	 	KC_LSPO, 	KC_GESC,
		KC_I, 	KC_S, 	KC_R, 	KC_T, 	KC_G,					KC_P, 	KC_N, 	KC_E, 	 	KC_A, 		KC_O,
		KC_Q, 	KC_V, 	KC_W, 	KC_D, 	KC_J, 					KC_B, 	KC_H, 	KC_SLSH, 	KC_DOT, 	KC_X,

			  			KC_SFTENT, 	LT(1,KC_NO), 				KC_SPC, 	KC_LCPO),
																														//.

	[1] = LAYOUT_split_3x5_2(
		KC_GESC, 	KC_AT, 		KC_HASH, 	KC_DLR, 	KC_PERC, 					KC_CIRC, 	KC_AMPR, 	KC_ASTR, 	KC_DEL, 	KC_BSPC,
		KC_TAB, 	KC_APP, 	KC_UP, 		KC_HOME, 	KC_END, 					KC_MINS, 	KC_LPRN, 	KC_RPRN, 	KC_SCLN, 	KC_ENT,
		KC_PSCR, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	LT(3,KC_NO), 				KC_DQUO, 	KC_LCBR, 	KC_RCBR, 	KC_BSLS, 	KC_QUES,

											KC_RSPC, 	LT(1,KC_NO),				LT(0,KC_NO), KC_RCTL),
																														//.


	[2] = LAYOUT_split_3x5_2(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_EQL, 	KC_7, 	KC_8, 	KC_9, 	KC_BSPC,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,				KC_MINS, 	KC_4, 	KC_5, 	KC_6, 	KC_ENT,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_DOT, 	KC_1, 	KC_2, 	KC_3, 	KC_NO,

							 KC_NO, KC_NO, 				LT(0,KC_NO), 	KC_0),
							 																							//.


	[3] = LAYOUT_split_3x5_2(
		KC_NO, 	KC_NO, 		KC_MS_U, 	KC_NO, 		KC_WH_U, 					KC_NO, 		KC_MS_L, 	KC_MS_R, 	KC_NO, 		KC_NO,
		KC_NO, 	KC_MS_L, 	KC_MS_D, 	KC_MS_R, 	KC_WH_D, 					KC_NO, 		KC_ACL0, 	KC_ACL1, 	KC_ACL2, 	KC_NO,
		KC_NO, 	KC_WH_L, 	KC_NO, 		KC_WH_R, 	KC_NO, 						KC_BTN1, 	KC_BTN2, 	KC_BTN3, 	KC_BTN4, 	KC_BTN5,

										KC_NO, 		LT(3,KC_NO), 				LT(0,KC_NO), 	KC_NO),
																														//.


	[4] = LAYOUT_split_3x5_2(
		DEBUG, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 					KC_MPLY, 	KC_VOLU, 	KC_NO, 		KC_NO, 		KC_BRIU,
		KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 					KC_MSTP,	KC_VOLD, 	KC_MRWD, 	KC_MFFD, 	KC_BRID,
		KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 					KC_NO, 		KC_MUTE, 	KC_NO, 		KC_NO, 		KC_NO,

							 	KC_NO, 	KC_NO, 					KC_NO, 		KC_NO)
								 																						//.
};

