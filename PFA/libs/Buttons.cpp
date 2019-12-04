/*
 * Buttons.cpp
 *
 *  Created on: 4 de dez de 2019
 *      Author: 158820
 */

#include "Bounce2.h"
#include "../libs/PFA.h"

const int P = 8;  //P button pin
const int UP = 9;  //+ button pin
const int DOWN = 10; //- button pin
const int SET = 11; //S button pin

void init_buttons() {
	pinMode(P, INPUT_PULLUP);
	pinMode(UP, INPUT);
	pinMode(DOWN, INPUT);
	pinMode(SET, INPUT);
}

Bounce setBTN = Bounce();
Bounce pBTN = Bounce();
Bounce upBTN = Bounce();
Bounce downBTN = Bounce();

void init_debouncer() {
	setBTN.attach(SET); //seta debouncer ao pino
	setBTN.interval(25); //intervalo
	pBTN.attach(P);
	pBTN.interval(25);
	upBTN.attach(UP);
	upBTN.interval(25);
	downBTN.attach(DOWN);
	downBTN.interval(25);
}

void update_buttons() {
	setBTN.update();
	pBTN.update();
	upBTN.update();
	downBTN.update();
}

bool p_button() {
	if (pBTN.fell())
		return true;
	else
		return false;
}

bool set_button() {
	if (setBTN.fell())
		return true;
	else
		return false;
}

bool up_button() {
	if (upBTN.fell())
		return true;
	else
		return false;
}

bool down_button() {
	if (downBTN.fell())
		return true;
	else
		return false;
}




