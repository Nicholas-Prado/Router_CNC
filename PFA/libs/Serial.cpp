/*
 * Serial.cpp
 *
 *  Created on: 4 de dez de 2019
 *      Author: 158820
 */

#include "Serial.h"

const char slow[] = "Lento";
const char med[] = "Medio";
const char fast[] = "Rapido";

String comando, s_valor, cw_valor, ccw_valor, f_valor, x_valor, y_valor, z_valor;
char recebe, termina = '0';
int flag=0;
int posicoes[8], s_posicao, cw_posicao, ccw_posicao, f_posicao, x_posicao, y_posicao, z_posicao, final_posicao;
long set_spindle_speed = 0;
long x_axis_pos = 0;
long y_axis_pos = 0;
long z_axis_pos = 0;
long last_x_axis_pos = 0;
long last_y_axis_pos = 0;
long last_z_axis_pos = 0;
int set_axis_speed = LOW_SPEED;
int set_spindle = off;

int qualquer (int atual_posicao, int *posicoes)
{
  int i, proximo;
  for (i = 7; i > 0; i--)
  {
    if (i == 7)
      proximo = posicoes[i];
    else if (atual_posicao < posicoes[i] && posicoes[i] < proximo)
      proximo = posicoes[i];
  }
  return proximo;
}

void entrada_serial()
{
  last_x_axis_pos = x_axis_pos;
  last_y_axis_pos = y_axis_pos;
  last_z_axis_pos = z_axis_pos;
  Serial.begin(115200);
  while(flag != 1)
  {
    int proximo;
    if (Serial.available() > 0)
    {
      recebe = Serial.read();
      comando.concat(recebe);
      if ((comando.startsWith("\n$") && comando.endsWith("#")) || (comando.startsWith("$") && comando.endsWith("#")) || (comando.startsWith("\0$") && comando.endsWith("#")))
      {
        s_posicao = comando.indexOf("S=");
        posicoes[0] = s_posicao;

        cw_posicao = comando.indexOf("M3");
        posicoes[1] = cw_posicao;

        ccw_posicao = comando.indexOf("M4");
        posicoes[2] = ccw_posicao;

        f_posicao = comando.indexOf("F=");
        posicoes[3] = f_posicao;

        x_posicao = comando.indexOf("X=");
        posicoes[4] = x_posicao;

        y_posicao = comando.indexOf("Y=");
        posicoes[5] = y_posicao;

        z_posicao = comando.indexOf("Z=");
        posicoes[6] = z_posicao;

        final_posicao = comando.indexOf("#");
        posicoes[7] = final_posicao;

        Serial.print("COMANDOS SERIAL: ");
        Serial.println(comando);

        if (s_posicao > 0)
        {
          proximo = qualquer(s_posicao, posicoes);
          Serial.print("VALOR DE S: ");
          s_valor = comando.substring(s_posicao + 2, proximo);
          Serial.println(s_valor);
          set_spindle_speed = s_valor.toInt();
          if(set_spindle_speed > S_RPM_SUP_LIMIT) set_spindle_speed = S_RPM_SUP_LIMIT;
          else if(set_spindle_speed < S_RPM_INF_LIMIT) set_spindle_speed = S_RPM_INF_LIMIT;
        }

        if (f_posicao > 0)
        {
          proximo = qualquer(f_posicao, posicoes);
          Serial.print("VALOR DE F: ");
          f_valor = comando.substring(f_posicao + 2, proximo);
          Serial.println(f_valor);
          if(f_valor.equals(slow)) set_axis_speed = LOW_SPEED;
          else if(f_valor.equals(med)) set_axis_speed = MED_SPEED;
          else if(f_valor.equals(fast)) set_axis_speed = HIGH_SPEED;
        }

        if (x_posicao > 0)
        {
          proximo = qualquer(x_posicao, posicoes);
          Serial.print("VALOR DE X: ");
          x_valor = comando.substring(x_posicao + 2, proximo);
          Serial.println(x_valor);
          x_axis_pos = x_valor.toInt();
          if(x_axis_pos > X_AXIS_SUP_LIMIT) x_axis_pos = X_AXIS_SUP_LIMIT;
          else if(x_axis_pos < X_AXIS_INF_LIMIT) x_axis_pos = X_AXIS_INF_LIMIT;
        }

        if (y_posicao > 0)
        {
          proximo = qualquer(y_posicao, posicoes);
          Serial.print("VALOR DE Y: ");
          y_valor = comando.substring(y_posicao + 2, proximo);
          Serial.println(y_valor);
          y_axis_pos = y_valor.toInt();
          if(y_axis_pos > Y_AXIS_SUP_LIMIT) y_axis_pos = Y_AXIS_SUP_LIMIT;
          else if(y_axis_pos < Y_AXIS_INF_LIMIT) y_axis_pos = Y_AXIS_INF_LIMIT;
        }

        if (z_posicao > 0)
        {
          proximo = qualquer(z_posicao, posicoes);
          Serial.print("VALOR DE Z: ");
          z_valor = comando.substring(z_posicao + 2, proximo);
          Serial.println(z_valor);
          z_axis_pos = z_valor.toInt();
          if(z_axis_pos > Z_AXIS_SUP_LIMIT) z_axis_pos = Z_AXIS_SUP_LIMIT;
          else if(z_axis_pos < Z_AXIS_INF_LIMIT) z_axis_pos = Z_AXIS_INF_LIMIT;
        }
        if(cw_posicao > 0)
        {
          Serial.println("ROTACAO SENTIDO CW: M3");
          set_spindle = cw;
        }
        if(ccw_posicao > 0)
        {
          Serial.println("ROTACAO SENTIDO CCW: M4");
          set_spindle = ccw;
        }
        if(cw_posicao <= 0 && ccw_posicao <= 0) set_spindle = off;
        Serial.flush();
        comando.remove(0);
        flag=1;
      }
    }
  }
  Serial.end();
}



