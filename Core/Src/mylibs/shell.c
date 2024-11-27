/*
 * shell.c
 *
 *  Created on: Oct 1, 2023
 *      Author: nicolas
 */
#include "usart.h"
#include "mylibs/shell.h"
#include "mylibs/pwm.h"
#include "adc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint8_t prompt[]="user@Nucleo-STM32G474RET6>>";
uint8_t started[]=
		"\r\n*-----------------------------*"
		"\r\n| Welcome on Nucleo-STM32G474 |"
		"\r\n*-----------------------------*"
		"\r\n";
uint8_t newline[]="\r\n";
uint8_t backspace[]="\b \b";
uint8_t cmdNotFound[]="Command not found\r\n";
uint8_t brian[]="Brian is in the kitchen\r\n";
uint8_t uartRxReceived;
uint8_t uartRxBuffer[UART_RX_BUFFER_SIZE];
uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE];

extern uint16_t value_adc1[];
extern uint16_t value_adc2;
extern float vitesse[];
int consigne =0;
float NewAlpha = 0.0;


char	 	cmdBuffer[CMD_BUFFER_SIZE];
int 		idx_cmd;
char* 		argv[MAX_ARGS];
int		 	argc = 0;
char*		token;
int 		newCmdReady = 0;

void Shell_Init(void){
	memset(argv, NULL, MAX_ARGS*sizeof(char*));
	memset(cmdBuffer, NULL, CMD_BUFFER_SIZE*sizeof(char));
	memset(uartRxBuffer, NULL, UART_RX_BUFFER_SIZE*sizeof(char));
	memset(uartTxBuffer, NULL, UART_TX_BUFFER_SIZE*sizeof(char));

	HAL_UART_Receive_IT(&huart2, uartRxBuffer, UART_RX_BUFFER_SIZE);
	HAL_UART_Transmit(&huart2, started, strlen((char *)started), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, prompt, strlen((char *)prompt), HAL_MAX_DELAY);
}

void Shell_Loop(void){

	int uartTxStringLength;

	if(uartRxReceived){
		switch(uartRxBuffer[0]){
		case ASCII_CR: // Nouvelle ligne, instruction à traiter
			HAL_UART_Transmit(&huart2, newline, sizeof(newline), HAL_MAX_DELAY);
			cmdBuffer[idx_cmd] = '\0';
			argc = 0;
			token = strtok(cmdBuffer, " ");
			while(token!=NULL){
				argv[argc++] = token;
				token = strtok(NULL, " ");
			}
			idx_cmd = 0;
			newCmdReady = 1;
			break;
		case ASCII_BACK: // Suppression du dernier caractère
			cmdBuffer[idx_cmd--] = '\0';
			HAL_UART_Transmit(&huart2, backspace, sizeof(backspace), HAL_MAX_DELAY);
			break;

		default: // Nouveau caractère
			cmdBuffer[idx_cmd++] = uartRxBuffer[0];
			HAL_UART_Transmit(&huart2, uartRxBuffer, UART_RX_BUFFER_SIZE, HAL_MAX_DELAY);
		}
		uartRxReceived = 0;
	}

	if(newCmdReady){
		if(strcmp(argv[0],"WhereisBrian?")==0){
			HAL_UART_Transmit(&huart2, brian, sizeof(brian), HAL_MAX_DELAY);
		}
		else if(strcmp(argv[0],"help")==0){
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Print all available functions here\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "help : Donne les fonctions disponibles\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "WhereisBrian? : dit ou se situe Brian\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "speed XXX : Set la speed\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "speedStart : Start les PWM\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "speedStop : Stop les PWM\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "adcValue : Recupere la valeure de l'adc\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "vitesse : Recupere la valeure de vitesse\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "asserv : Choisit une valeure de tr/min\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "asservPrint : Print la valeure d'alpha calculée par asserv\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
		}
		else if(strcmp(argv[0],"speed")==0){
			if(atoi(argv[1])>=0){
				if(atoi(argv[1])<=100){
					set_pwm_alpha(atoi(argv[1]));
					uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Nouveau alpha = %d\r\n",atoi(argv[1]));
					HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
				}else{
					set_pwm_alpha(100);
					uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Nouveau alpha = 100\r\n");
					HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
				}
			}else{
				uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Erreur alpha est pas entre 0 et 100\r\n",atoi(argv[1]));
				HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			}
		}else if(strcmp(argv[0],"speedStart")==0){
			pwm_start();
		}else if(strcmp(argv[0],"speedStop")==0){
			pwm_stop();

		}else if(strcmp(argv[0], "asservPrint")==0){

			int uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Nouvelle alpha = %d\r\n",(int)NewAlpha);
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);

		}else if(strcmp(argv[0],"asserv")==0){//Fonction permettant de lancer l'asservissement
			if((atoi(argv[1])>=-3000) & (atoi(argv[1])<=3000)){
				consigne = atoi(argv[1]);
				int uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Nouvelle consigne = %d\r\n",atoi(argv[1]));
				HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			}
			else{//Sécuritée permettant de ne pas avoir une vitesse inatteignable
				int uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Erreur consigne doit être comprise entre + ou - 3000 tour/min\r\n");
				HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
			}

		}else if(strcmp(argv[0],"vitesse")==0){//Fonction permettant d'éteindre les PWM

			int uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Vitesse : %d\r\n",(int)vitesse[0]);
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);


		}else if(strcmp(argv[0],"adcValue")==0){

			float adc1 = ((((float)value_adc1[0]/4095.0)*3.3)-1.65)/0.05;
			float adc2 = ((((float)value_adc1[1]/4095)*3.3)-1.65)/0.05;
			float adc3 = ((((float)value_adc2/4095)*3.3)-1.65)/0.05;

			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Valeur Source: %f \r\n", adc1);
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);

			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Valeur V: %f \r\n", adc2);
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);

			uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Valeur de U: %f \r\n", adc3);
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);

		}
		else{
			HAL_UART_Transmit(&huart2, cmdNotFound, sizeof(cmdNotFound), HAL_MAX_DELAY);
		}
		HAL_UART_Transmit(&huart2, prompt, sizeof(prompt), HAL_MAX_DELAY);
		newCmdReady = 0;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart){
	uartRxReceived = 1;
	HAL_UART_Receive_IT(&huart2, uartRxBuffer, UART_RX_BUFFER_SIZE);
}
