/*
 * Telas.h
 *
 *  Created on: 4 de dez de 2019
 *      Author: 158820
 */

#ifndef LIBS_TELAS_H_
#define LIBS_TELAS_H_

#define rs 40
#define en 41
#define d4 42
#define d5 43
#define d6 44
#define d7 45

void Init_Screen();
void Error_Screen();
void Ref_Screen();
void Pos_Screen(float speedNOW, long z_axis_pos, long x_axis_pos, long y_axis_pos);
void Z_Screen();
void X_Screen();
void Y_Screen();
void OT_Screen(char axis, char sinal);
void init_lcd();
void refresh_lcd();
void unset_cursor();

#endif /* LIBS_TELAS_H_ */
