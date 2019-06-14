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

// Déclarations de fonctions

char * toArray(int number);
void sendOverUSB_weak(uint8_t* text);
void sendOverUSB_boucleInfinie(uint8_t* text);
uint8_t sendOverUSB_withNoBusy(uint8_t* text);
USBD_StatusTypeDef sendOverUSB(uint8_t* text);

void debugReset();


#endif /* PFE_FONCTIONSUTILISATEUR_H_ */
