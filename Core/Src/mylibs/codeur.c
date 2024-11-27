
#include "mylibs/pwm.h"
#include "tim.h"
#include "mylibs/codeur.h"

uint32_t counter = 0;    //Valeur absolue du compteur
int16_t pos = 0;         //position du codeur (négative ou positive)
int16_t oldpos = 0;      //position du codeur à l'instant précédent
float vitesse[3] ={0};   //vitesse du moteur (le signe donne le sens)
int dt=100; 			 //mesure de la vitesse toutes les 100ms
float resolution = 4096; //nombre d'incrément du compteur pour un tour du moteur


void codeur_start(void){
	HAL_TIM_Encoder_Start_IT(&htim3,TIM_CHANNEL_ALL);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	counter = __HAL_TIM_GET_COUNTER(&htim3); //valeur du compteur absolue
	pos = (int16_t)counter; 				 //valeur du compteur avec les valeurs négatives
}

void calc_speed(){
	vitesse[0]=vitesse[1];
	vitesse[1]=vitesse[2];
	vitesse[2] = (((pos - oldpos)/dt)/resolution)*ms_To_s*10;
	oldpos = pos;
}


