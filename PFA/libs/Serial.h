/*
 * Serial.h
 *
 *  Created on: 4 de dez de 2019
 *      Author: 158820
 */

#ifndef LIBS_SERIAL_H_
#define LIBS_SERIAL_H_

#include "Arduino.h"

//defs velocidade em RPM
#define LOW_SPEED 50
#define MED_SPEED 100
#define HIGH_SPEED 200
#define SPINDLE_RPM 100 //modificar na hora de testes finais

#define X_AXIS_INF_LIMIT 0
#define X_AXIS_SUP_LIMIT 200
#define Y_AXIS_INF_LIMIT 0
#define Y_AXIS_SUP_LIMIT 300
#define Z_AXIS_INF_LIMIT 0
#define Z_AXIS_SUP_LIMIT 150
#define S_RPM_SUP_LIMIT 2000
#define S_RPM_INF_LIMIT 200

#define SRPM 500 //velocidade de rotação de spindle fixa, em rpm

typedef enum
{
  off = 0,
  cw,
  ccw,
}Sentidos;

int qualquer (int atual_posicao, int *posicoes);
void entrada_serial();

extern long set_spindle_speed;
extern long x_axis_pos;
extern long y_axis_pos;
extern long z_axis_pos;
extern long last_x_axis_pos;
extern long last_y_axis_pos;
extern long last_z_axis_pos;
extern int set_axis_speed;
extern int set_spindle;

#endif /* LIBS_SERIAL_H_ */
