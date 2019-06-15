/*
 * pfe_FonctionsUtilisateur.c
 *
 *  Created on: 30 janv. 2019
 *      Author: franc
 */


#include "pfe_fonctionsUtilisateur.h"
#include "usbd_def.h"
#include "usbd_cdc_if.h"
#include "usbd_cdc.h"
#include <string.h>
uint8_t* rccGetResetReason(void);




extern USBD_HandleTypeDef hUsbDeviceFS;


typedef enum{
	  RESET_REASON_LOW_POWER,
	  RESET_REASON_WINDOW_WATCHDOG,
	  RESET_REASON_INDEPENDENT_WATCHDOG,
	  RESET_REASON_SOFTWARE,
	  RESET_REASON_POWER_ON,
	  RESET_REASON_PIN,
	  RESET_REASON_UNKNOWN,
}rccResetReason_t;


// Fonctions utilisateur ==================================================================

// Convertit un int vers un array de char
char * toArray(int number)
{
	int n = log10(number) + 1;
	int i;
      char *numberArray = calloc(n, sizeof(char));
        for ( i = 0; i < n; ++i, number /= 10 )
        {
            numberArray[i] = number % 10;
        }

    return numberArray;
}

USBD_StatusTypeDef sendOverUSB(uint8_t* text)
{
	USBD_StatusTypeDef status = USBD_FAIL;

	HAL_Delay(10); // Attendre 10 mS pour s'assurer que la derniere transmission USB soit completee
	status = CDC_Transmit_FS(text, strlen((char *)text));

	return status;
}

void sendOverUSB_weak(uint8_t* text)
{
	USBD_StatusTypeDef status = CDC_Transmit_FS(text, strlen((char *)text));
}

uint8_t sendOverUSB_withNoBusy(uint8_t* text)
{

	  uint8_t result = USBD_OK;
	  /* USER CODE BEGIN 7 */
	  // USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
/*	  if (hcdc->TxState != 0){
	    return USBD_BUSY;
	  }*/
	  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, text, strlen((char *)text));
	  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
	  /* USER CODE END 7 */
	  return result;
}

// Envoi d'un texte par USB. La fonction contient une boucle infinie qui termine seulement
// lorsque le port USB n'est plus occupé. Cela peut être nécessaire pour éviter qu'au prochain
// envoi USB, le port soit occupé et que la transmission ne fonctionne pas.
void sendOverUSB_boucleInfinie(uint8_t* text)
{
	while(1)
	{
		USBD_StatusTypeDef status = CDC_Transmit_FS(text, strlen((char *)text));
		if(status != USBD_BUSY)
			break;
	};
}


uint8_t* rccGetResetReason(void)
{

/*	// test the reset flags in order because the pin reset is always set.
	if  (RCC_GetFlagStatus(RCC_FLAG_SFTRST)){
	  sendOverUSB("SFT ");
	} else if  (RCC_GetFlagStatus(RCC_FLAG_PORRST)){
	  sendOverUSB("PWR ");
	} else if  (RCC_GetFlagStatus(RCC_FLAG_PINRST)){
	  sendOverUSB("PIN ");
	} else {
	  sendOverUSB("?RST");
	}
	// The flags must be cleared manually after use
	RCC_ClearFlag();*/


	    if(RCC->CSR & RCC_CSR_LPWRRSTF)
	      return "RESET_REASON_LOW_POWER";
	    else if(RCC->CSR & RCC_CSR_WWDGRSTF)
	      return "RESET_REASON_WINDOW_WATCHDOG";
	    else if(RCC->CSR & RCC_CSR_WDGRSTF)
	      return "RESET_REASON_INDEPENDENT_WATCHDOG";
	    else if(RCC->CSR & RCC_CSR_SFTRSTF)
	      return "RESET_REASON_SOFTWARE";
	    else if(RCC->CSR & RCC_CSR_PORRSTF)
	      return "RESET_REASON_POWER_ON";
	    else if(RCC->CSR & RCC_CSR_PADRSTF)
	      return "RESET_REASON_PIN";
	    else
	      return "RESET_REASON_UNKNOWN";

}
