#include "libs/PFA.h"
#include "libs/Buttons.h"
#include "libs/Serial.h"
#include "libs/Telas.h"

//PINOS
const int Coverpin = 21;
const int HomeXpin = 24;
const int HomeYpin = 26;
const int HomeZpin = 28;
const int blinkpin = 13;
const int mxs1 = A1;
const int mxs2 = A2;
const int mxs3 = A3;
const int mxs4 = A4;
const int mys1 = A5;
const int mys2 = A6;
const int mys3 = A7;
const int mys4 = A8;
const int mzs1 = 4;
const int mzs2 = 5;
const int mzs3 = 6;
const int mzs4 = 7;
const int spindleA = 2;
const int spindleB = 12;
const int DriveEnpin = 3;
const int interruptPin = 18; //18/19/20

int conta_tela = 0;
bool ref_axis = 0;
char now_axis = '0';

//TEMPO
const int period = 500;
unsigned long time_now = 0;

//controle Spindle Encoder
int Encount = 0;
const float FA = 2.0; //freq de amostragem 2Hz (atualiza cada 500ms)
const float nPPR = 20.0; //100.0 para testar no proteus
const float minut = 60.0; //quantidade de segundos em um minuto
const float K_RPM = minut*FA/nPPR;
float nRPM = 0;
float speedNOW = 0;

//CONTROLE HEART BEAT
bool troca=0;

int StateAtual = inite;

const int stepsPerRevolution = 10;  // change this to fit the number of steps per revolution
bool controlspindle = 0;

Stepper StepperX(stepsPerRevolution, mxs1, mxs2, mxs3, mxs4);
Stepper StepperY(stepsPerRevolution, mys1, mys2, mys3, mys4);
Stepper StepperZ(stepsPerRevolution, mzs1, mzs2, mzs3, mzs4);

void HeartBeat()
{
  //realiza verificação a cada 500ms
  if(millis() >= (time_now + period))
  {
    if(digitalRead(DriveEnpin)==0)
    {
	  digitalWrite(blinkpin, troca);
	  troca=!troca;
    }else{
      //envia sinal contrário ao atual
    	digitalWrite(blinkpin, HIGH);
    }

    //calculo de velocidade spindle
    nRPM = K_RPM*Encount;
    speedNOW = nRPM;
    Encount = 0;

    time_now = millis();
  }
}

void rotinaISR()
{
	Encount++;
}

void ISRA()
{
  StepperX.setSpeed(0);
  StepperY.setSpeed(0);
  StepperZ.setSpeed(0);
  analogWrite(spindleA, 0);
  analogWrite(spindleB, 0);
	Error_Screen();
	StateAtual = inite;
}


void cncMove(int x_steps, int y_steps, int resto_x, int resto_y)
{
  char axis;
  char sign;
  int i=0;
  //fazer o spindle antes....
  switch (set_spindle)
  {
    case off:
      if(controlspindle)
      {
        detachInterrupt(digitalPinToInterrupt(interruptPin));
        controlspindle=0;
      }
      analogWrite(spindleB, 0);
      analogWrite(spindleA, 0);
    break;

    case cw:
      analogWrite(spindleB, 0);
      analogWrite(spindleA, 0);
      if(controlspindle==0)
      {
        attachInterrupt(digitalPinToInterrupt(interruptPin), rotinaISR, RISING);
        controlspindle=1;
      }
      while(speedNOW != set_spindle_speed)
      {
        analogWrite(spindleA, i);

        HeartBeat();

        if(speedNOW < set_spindle_speed)
        {
          i++;
          if(i > 0) i = 255;
        }
        if(speedNOW > set_spindle_speed)
        {
          i--;
          if(i < 0) i = 0;
        }
      }
    break;

    case ccw:
      analogWrite(spindleB, 0);
      analogWrite(spindleA, 0);
      if(controlspindle==0)
      {
        attachInterrupt(digitalPinToInterrupt(interruptPin), rotinaISR, RISING);
        controlspindle=1;
      }
      while(speedNOW != set_spindle_speed)
      {
        analogWrite(spindleB, i);

        HeartBeat();

        if(speedNOW < set_spindle_speed)
        {
          i++;
          if(i > 0) i = 255;
        }
        if(speedNOW > set_spindle_speed)
        {
          i--;
          if(i < 0) i = 0;
        }
      }
    break;
  }

  //MOVE Z
  axis = 'Z';
  StepperZ.setSpeed(set_axis_speed);
  if(z_axis_pos < last_z_axis_pos)
  {//quer voltar
	sign = '-';
    while(last_z_axis_pos > z_axis_pos)
    {
      HeartBeat();
      StepperZ.step(-stepsPerRevolution);
      last_z_axis_pos--;
    }
    if(last_z_axis_pos == Z_AXIS_INF_LIMIT) OT_Screen(axis, sign);
  }else{//quer ir ou é idem
	sign = '+';
    while(last_z_axis_pos < z_axis_pos)
    {
      HeartBeat();
      StepperZ.step(stepsPerRevolution);
      last_z_axis_pos++;
    }
    if(last_z_axis_pos == Z_AXIS_SUP_LIMIT) OT_Screen(axis, sign);
  }

  //MOVE X e/ou Y
  StepperX.setSpeed(set_axis_speed);
  StepperY.setSpeed(set_axis_speed);
  while(last_x_axis_pos != (x_axis_pos-resto_x) && last_y_axis_pos != (y_axis_pos-resto_y))
  {
    HeartBeat();

    if(last_x_axis_pos != (x_axis_pos-resto_x))
    {
        StepperX.step(stepsPerRevolution*x_steps);
        last_x_axis_pos += x_steps;
    }

    if(last_y_axis_pos != (y_axis_pos-resto_y))
    {
      StepperY.step(stepsPerRevolution*y_steps);
      last_y_axis_pos += y_steps;
    }
  }
  x_steps = 0;
  y_steps = 0;
  StepperX.step(stepsPerRevolution*resto_x);
  last_x_axis_pos += resto_x;
  resto_x = 0;
  StepperY.step(stepsPerRevolution*resto_y);
  last_y_axis_pos += resto_y;
  resto_y = 0;
  axis = 'X';
  sign = '-';
  if(last_x_axis_pos == X_AXIS_INF_LIMIT) OT_Screen(axis, sign);
  sign = '+';
  if(last_x_axis_pos == X_AXIS_SUP_LIMIT) OT_Screen(axis, sign);
  axis = 'Y';
  sign = '-';
  if(last_y_axis_pos == Y_AXIS_INF_LIMIT) OT_Screen(axis, sign);
  sign = '+';
  if(last_y_axis_pos == Y_AXIS_SUP_LIMIT) OT_Screen(axis, sign);

}

void Interpolate()
{
  int x_dif, y_dif; //se negativo, andar em sentido oposto
  bool flagx = 0;//negativo?
  bool flagy = 0;
  int resto_x = 0;
  int resto_y = 0;
  int x_steps = 0;
  int y_steps = 0;

  if(abs(x_axis_pos - last_x_axis_pos) > 0)
  {
      x_dif = x_axis_pos - last_x_axis_pos;
      if(x_dif < 0)
      {
        flagx=1;
      }
  }
  if(abs(y_axis_pos - last_y_axis_pos) > 0)
  {
      y_dif = y_axis_pos - last_y_axis_pos;
      if(y_dif < 0)
      {
        flagy=1;
      }
  }
  if(flagx==1 && flagy==1){//ambos voltam
    if(abs(x_dif)>abs(y_dif)){//x>y
      x_steps = -(abs(x_dif)/abs(y_dif));
      y_steps = -1;
      resto_x = -(abs(x_dif)%abs(y_dif));
    }else{//y>x
      y_steps = -(abs(y_dif)/abs(x_dif));
      x_steps = -1;
      resto_y = -(abs(y_dif)%abs(x_dif));
    }
  }else if(flagx==1 && flagy==0){//x volta, y avança
    if(abs(x_dif)>abs(y_dif)){//x>y
      x_steps = -(abs(x_dif)/abs(y_dif));
      y_steps = 1;
      resto_x = -(abs(x_dif)%abs(y_dif));
    }else{//y>x
      y_steps = (abs(y_dif)/abs(x_dif));
      x_steps = -1;
      resto_y = (abs(y_dif)%abs(x_dif));
    }
  }else if(flagy==1 && flagx == 0){//y volta, x avança
    if(abs(x_dif)>abs(y_dif)){//x>y
      x_steps = (abs(x_dif)/abs(y_dif));
      y_steps = -1;
      resto_x = (abs(x_dif)%abs(y_dif));
    }else{//y>x
      y_steps = -(abs(y_dif)/abs(x_dif));
      x_steps = 1;
      resto_y = -(abs(y_dif)%abs(x_dif));
    }
  }else{//ambos avançam
    if(abs(x_dif)>abs(y_dif)){//x>y
      x_steps = (abs(x_dif)/abs(y_dif));
      y_steps = 1;
      resto_x = (abs(x_dif)%abs(y_dif));
    }else{//y>x
      y_steps = (abs(y_dif)/abs(x_dif));
      x_steps = 1;
      resto_y = (abs(y_dif)%abs(x_dif));
    }
  }

  cncMove(x_steps, y_steps, resto_x, resto_y);
}

//The setup function is called once at startup of the sketch
void setup()
{
	 //define entradas e saidas
	  pinMode(Coverpin, INPUT);
	  pinMode(HomeXpin, INPUT);
	  pinMode(HomeYpin, INPUT);
	  pinMode(HomeZpin, INPUT);
	  pinMode(interruptPin, INPUT);
	  pinMode(blinkpin, OUTPUT);
	  pinMode(DriveEnpin, OUTPUT);
	  pinMode(mxs1, OUTPUT);
	  pinMode(mxs2, OUTPUT);
	  pinMode(mxs3, OUTPUT);
	  pinMode(mxs4, OUTPUT);
	  pinMode(mys1, OUTPUT);
	  pinMode(mys2, OUTPUT);
	  pinMode(mys3, OUTPUT);
	  pinMode(mys4, OUTPUT);
	  pinMode(mzs1, OUTPUT);
	  pinMode(mzs2, OUTPUT);
	  pinMode(mzs3, OUTPUT);
	  pinMode(mzs4, OUTPUT);
	  pinMode(spindleA, OUTPUT);
	  pinMode(spindleB, OUTPUT);
	  pinMode(blinkpin, HIGH);
	  pinMode(DriveEnpin, HIGH);
	  init_buttons();
	  init_debouncer();
	  init_lcd();
}

// The loop function is called in an endless loop
void loop()
{
	HeartBeat();

	  //INTERFACE - troca de estados
	  switch(StateAtual)
	  {

		case inite:
	      Init_Screen();
	      update_buttons();
	  		if(set_button()){
	  			  switch (digitalRead(Coverpin))
	  			  {
					  case 1:
						  StateAtual = referencia;
					  break;

					  case 0:
						  Error_Screen();

						  for(int i = 0; i < 30; i++)
						  {
							  delay(100);
							  HeartBeat();
						  }
						  refresh_lcd();
					  break;
	  			  }
	  		  }
		break;

		case referencia:
	  		Ref_Screen();
	  		if(digitalRead(Coverpin)==0)
	  		{
	  			Error_Screen();
	  			StateAtual = inite;
	  		}
	  		else{
	        if(ref_axis==0){
	    			attachInterrupt(digitalPinToInterrupt(Coverpin), ISRA, FALLING); //habilita interrupção do coverPin
	    			StepperX.setSpeed(LOW_SPEED); // seta para velocidade de rotação baixa
	    			StepperY.setSpeed(LOW_SPEED); // seta para velocidade de rotação baixa
	    			StepperZ.setSpeed(LOW_SPEED); // seta para velocidade de rotação baixa

	    			//se travar aqui, rever programação de motores
	    			while(digitalRead(HomeXpin==0)){
						HeartBeat();
						StepperX.step(stepsPerRevolution);
	    			}

	    			while(digitalRead(HomeYpin)==0){
						HeartBeat();
						StepperY.step(stepsPerRevolution);
	    			}

	    			while(digitalRead(HomeZpin)==0){
	    				HeartBeat();
	    				StepperZ.step(stepsPerRevolution);
	    			}
	    			ref_axis = 1;
	        }

	        StateAtual = manual;
	        refresh_lcd();
	        Pos_Screen(speedNOW, z_axis_pos, x_axis_pos, y_axis_pos);
	  		}

		break;

		case manual:
			update_buttons();
			if(p_button()){
				conta_tela++;
				switch (conta_tela)
				{
					case 1:
						Z_Screen();
						now_axis = 'Z';
					break;

					case 2:
						X_Screen();
						now_axis = 'Y';
					break;

					case 3:
						Y_Screen();
						now_axis = 'X';
					break;

					default:
						now_axis = '0';
						conta_tela = 0;
						StateAtual = automatico;
						refresh_lcd();
						Pos_Screen(speedNOW, z_axis_pos, x_axis_pos, y_axis_pos);
				}
			}
			switch (now_axis)
			{
				case 'Z':
					update_buttons();
					if(up_button())
					{
						//gira z em cw
						z_axis_pos++;
						if(z_axis_pos == Z_AXIS_SUP_LIMIT)
						{
							StepperZ.step(stepsPerRevolution);
							OT_Screen(now_axis, '+');
						}else if(z_axis_pos > Z_AXIS_SUP_LIMIT)
						{
							z_axis_pos--;
							OT_Screen(now_axis, '+');
						}else{
							StepperZ.step(stepsPerRevolution);
						}
					}else if(down_button())
					{
						//gira z em ccw
						z_axis_pos--;
						if(z_axis_pos == Z_AXIS_INF_LIMIT)
						{
							StepperZ.step(-stepsPerRevolution);
							OT_Screen(now_axis, '-');
						}else if(z_axis_pos < Z_AXIS_INF_LIMIT)
						{
							z_axis_pos++;
							OT_Screen(now_axis, '-');
						}else{
							StepperZ.step(-stepsPerRevolution);
						}
					}
					Z_Screen();
				break;

				case 'Y':
					update_buttons();
					if(up_button())
					{
						//gira y em cw
						y_axis_pos++;
					  if(y_axis_pos == Y_AXIS_SUP_LIMIT)
					  {
						  StepperY.step(stepsPerRevolution);
						  OT_Screen(now_axis, '+');
					  }else if(y_axis_pos > Y_AXIS_SUP_LIMIT)
					 {
						  y_axis_pos--;
						  OT_Screen(now_axis, '+');
					 }else{
						 StepperY.step(stepsPerRevolution);
					 }
					}else if(down_button())
					{
						//gira y em ccw
						y_axis_pos--;
					  if(y_axis_pos == Y_AXIS_INF_LIMIT)
					  {
						  StepperY.step(-stepsPerRevolution);
						  OT_Screen(now_axis, '-');
					  }else if(y_axis_pos < Y_AXIS_INF_LIMIT)
					 {
						  y_axis_pos++;
						  OT_Screen(now_axis, '-');
					 }else{
						 StepperY.step(-stepsPerRevolution);
					 }
					}
					Y_Screen();
				break;

				case 'X':
					update_buttons();
					if(up_button())
					{
						//gira x em cw
						x_axis_pos++;
					  if(x_axis_pos == X_AXIS_SUP_LIMIT)
					  {
						  StepperX.step(stepsPerRevolution);
						  OT_Screen(now_axis, '+');
					  }else if(x_axis_pos > X_AXIS_SUP_LIMIT)
					 {
						  x_axis_pos--;
						  OT_Screen(now_axis, '+');
					 }else{
						 StepperX.step(stepsPerRevolution);
					 }
					}else if(down_button())
					{
						//gira x em ccw
						x_axis_pos--;
					  if(x_axis_pos == X_AXIS_INF_LIMIT)
					  {
						  StepperX.step(-stepsPerRevolution);
						  OT_Screen(now_axis, '-');
					  }else if(x_axis_pos < X_AXIS_INF_LIMIT)
					 {
						  x_axis_pos++;
						  OT_Screen(now_axis, '-');
					 }else{
						 StepperZ.step(-stepsPerRevolution);
					 }
					}
					X_Screen();
				break;
			}

			update_buttons();
			if(set_button()){
			  if(controlspindle==0)//desligado, vai ligar
			  {
				//habilita/desabilita spindle em 500rpm sentido
				analogWrite(spindleB, 0);
				analogWrite(spindleA, SPINDLE_RPM);

				//habilita interrupção para medir velocidade do encoder
				attachInterrupt(digitalPinToInterrupt(interruptPin), rotinaISR, RISING);
				controlspindle=1;
			  }else{//ligado, vai desligar
				analogWrite(spindleB, 0);
				analogWrite(spindleA, 0);
				detachInterrupt(digitalPinToInterrupt(interruptPin));
				controlspindle=0;
			  }
			}
		break;

	  case automatico:
	    update_buttons();
	    if(p_button())
	    {
	      conta_tela++;
	      now_axis = 'Z';
	      StateAtual = manual;
	      Pos_Screen(speedNOW, z_axis_pos, x_axis_pos, y_axis_pos);
	    }else{
	      entrada_serial();
	      Interpolate();
	    }
	  break;
	  }

	  delay(1);
}
