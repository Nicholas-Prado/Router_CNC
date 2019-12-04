/*
 * PFA.h
 *
 *  Created on: 4 de dez de 2019
 *      Author: 158820
 */

#ifndef LIBS_PFA_H_
#define LIBS_PFA_H_

#include "Arduino.h"
#include "stdio.h"
#include "stdlib.h"
#include "Stepper.h"

//MAQUINA DE ESTADOS
typedef enum
{
  inite = 1,
  referencia,
  manual,
  automatico,

}Estados;

#endif /* LIBS_PFA_H_ */
