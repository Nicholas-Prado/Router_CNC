/*
 * Telas.cpp
 *
 *  Created on: 4 de dez de 2019
 *      Author: 158820
 */
#include "LiquidCrystal.h"
#include "Telas.h"

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//mensagens constantes da interface
const char TelaInL1[] = "   CNC Router";
const char TelaInL2[] = "Home Ret? <S>";
const char TelaErrL1[] = "Erro: Please";
const char TelaErrL2[] = "Close the Cover!";
const char TelaRefL1[] = "Machine Home";
const char TelaRefL2[] = "in progress...";
const char TelaPosL1[] = "S:        Z:";
const char TelaPosL2[] = "X:        Y:";
const char TelaOTL1[] = "  Over  Travel";
const char TelaOTL2[] = "    Axis:";

void refresh_lcd() {
	lcd.clear();
}

void init_lcd() {
	lcd.begin(16, 2);
	lcd.clear();
}

void Init_Screen() {
  //lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(TelaInL1);
  lcd.setCursor(0, 1);
  lcd.print(TelaInL2);
}

void Error_Screen() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(TelaErrL1);
  lcd.setCursor(0, 1);
  lcd.print(TelaErrL2);
}

void Ref_Screen() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(TelaRefL1);
  lcd.setCursor(0, 1);
  lcd.print(TelaRefL2);

}

void Pos_Screen(float speedNOW, long z_axis_pos, long x_axis_pos, long y_axis_pos) {
  //lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(TelaPosL1);
  lcd.setCursor(6, 0);
  lcd.print(speedNOW);
  lcd.setCursor(15, 0);
  lcd.print(z_axis_pos);
  lcd.setCursor(0, 1);
  lcd.print(TelaPosL2);
  lcd.setCursor(6, 1);
  lcd.print(x_axis_pos);
  lcd.setCursor(15, 1);
  lcd.print(y_axis_pos);

}

void Z_Screen(){
  lcd.setCursor(10, 0);
  lcd.cursor();
}

void X_Screen(){
  lcd.setCursor(0, 1);
  lcd.cursor();
}

void Y_Screen(){
  lcd.setCursor(10, 1);
  lcd.cursor();
}

void unset_cursor() {
	lcd.noCursor();
}

void OT_Screen(char axis, char sinal) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(TelaOTL1);
  lcd.setCursor(0, 1);
  lcd.print(TelaOTL2);
  lcd.setCursor(10, 1);
  lcd.print(axis);
  lcd.setCursor(11, 1);
  lcd.print(sinal);
}

