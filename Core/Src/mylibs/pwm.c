#include "mylibs/pwm.h"
#include "tim.h"

int aTemp;

void pwm_start(void){

	aTemp=50;

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);


}


void pwm_stop(void){
	set_pwm_alpha(50);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
}

/*
 * TP1
 */
//void set_pwm_alpha(int alpha){
//	int a1=alpha_MAX*alpha/100;
//	int a2=alpha_MAX*(100-alpha)/100;
//	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,a1);
//	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,a2);
//}

/*
 * TP2
 */

void set_pwm_alpha(int alpha){
	int a1;
	int a2;
	int aTransi=aTemp;

	if (alpha > aTransi){
		while(aTransi != alpha){

			aTransi++;
			a1=alpha_MAX*aTransi/PWM_MAX;
			a2=alpha_MAX*(PWM_MAX-aTransi)/PWM_MAX;
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,a1);
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,a2);
			HAL_Delay(100);
		}
	}

	if (alpha < aTransi){
		while(aTransi != alpha){

			aTransi--;
			a1=alpha_MAX*aTransi/PWM_MAX;
			a2=alpha_MAX*(PWM_MAX-aTransi)/PWM_MAX;
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,a1);
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,a2);

			HAL_Delay(100);
		}
	}
	aTemp = alpha;
}
