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


// Structs ================================================


// Structure utilisee pour recevoir les trames AX.25, par
// communication UART, qui devront etre transmises
typedef struct {
	uint8_t data[AX25_PAYLOAD_MAXLEN];
	uint8_t valide; // Lorsque valide est mis a 1, la trame n'a pas ete envoyee
					// Lorsque valide est mis a 0, la trame a deja ete envoyee.
					// Il faut alors attendre pour une prochaine trame recue sur UART.
} payload_data_t;



// Déclarations de fonctions ===============================

char * toArray(int number);
void sendOverUSB_weak(uint8_t* text);
void sendOverUSB_boucleInfinie(uint8_t* text);
uint8_t sendOverUSB_withNoBusy(uint8_t* text);
USBD_StatusTypeDef sendOverUSB(uint8_t* text);

void debugReset();



#endif /* PFE_FONCTIONSUTILISATEUR_H_ */
