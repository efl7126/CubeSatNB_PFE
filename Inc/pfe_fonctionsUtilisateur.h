/*
 * pfe_fonctionsUtilisateur.h
 *
 *  Created on: 30 janv. 2019
 *      Author: franc
 */

#ifndef PFE_FONCTIONSUTILISATEUR_H_
#define PFE_FONCTIONSUTILISATEUR_H_

#include "stdint.h"
#include "usbd_def.h"

#define AX25_PAYLOAD_MAXLEN 206

// Déclarations de fonctions

char * toArray(int number);
void sendOverUSB_weak(uint8_t* text);
void sendOverUSB_boucleInfinie(uint8_t* text);
uint8_t sendOverUSB_withNoBusy(uint8_t* text);
USBD_StatusTypeDef sendOverUSB(uint8_t* text);

void debugReset();



typedef struct {
  uint8_t data[AX25_PAYLOAD_MAXLEN];
  uint8_t valide;
} payload_data_t;



#endif /* PFE_FONCTIONSUTILISATEUR_H_ */
