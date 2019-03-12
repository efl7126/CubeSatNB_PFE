/*
 * upsat-comms-software: Communication Subsystem Software for UPSat satellite
 *
 *  Copyright (C) 2016, Libre Space Foundation <http://librespacefoundation.org/>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#undef __FILE_ID__
#define __FILE_ID__ 25

#include <stdint.h>
#include "comms_manager.h"
#include "stm32f4xx_hal.h"
#include "ax25.h"
#include "cw.h"
#include "status.h"
#include "tx_manager.h"

static uint8_t interm_buf[AX25_PREAMBLE_LEN + AX25_POSTAMBLE_LEN + AX25_MAX_FRAME_LEN + 2];
static uint8_t spi_buf[AX25_PREAMBLE_LEN
		       + AX25_POSTAMBLE_LEN
		       + AX25_MAX_FRAME_LEN + AX25_MAX_ADDR_LEN];
static uint8_t recv_buffer[AX25_MAX_FRAME_LEN];
static uint8_t send_buffer[AX25_MAX_FRAME_LEN];


// Notifies the communication mode over USB
uint8_t charArray_text[30] = "test \r\n";

/**
 * Timer that keeps track of the Command and Control phase
 */

/**
 * Used to delay the update of the internal statistics and save some cycles
 */
static uint32_t stats_tick;
static uint32_t rx_fifo_tick;

/**
 * Disables the TX RF
 */

/**
 * Make all the necessary initializations for the COMMS subsystem
 */
void
comms_init ()
{
  uint8_t cc_id_tx;
  uint8_t cc_id_rx;
  volatile uint8_t codeRetour = 10;
//
  /* fetch TX ID */
  codeRetour = cc_tx_rd_reg (0x2F8F, &cc_id_tx);

  /* fetch RX ID */
//  cc_rx_rd_reg (0x2F8F, &cc_id_rx);
//
  /* Configure TX CC1120 */
  tx_registerConfig ();

  HAL_Delay (10);
  codeRetour = cc_tx_rd_reg (0x2f8F, &cc_id_tx);
//
//  /* Configure RX CC1120 */
//	rx_register_config (); // Comment out for now
//	HAL_Delay (10);
//	cc_rx_rd_reg (0x2f8F, &cc_id_rx);
//
//  /* Calibrate TX */
  	// tx_manualCalibration ();
cc_tx_rd_reg (0x2f8F, &cc_id_tx);
//
//  /* Calibrate RX */
// rx_manual_calibration ();
// cc_rx_rd_reg (0x2f8F, &cc_id_tx);
//
  /* Initialize the TX and RX routines */
//  rx_init();
  cw_init();
//
//  // Comment Add to remove error
//  // large_data_init();
//
//  /*Initialize the COMMS statistics mechanism */
//  comms_rf_stats_init(&comms_stats);
//
//  /* Initialize the CC1120 in RX mode */
// cc_rx_cmd(SRX);
//
//  // Comment Add to remove error
//  //pkt_pool_INIT ();
//
// comms_wod_init();
// comms_ex_wod_init();
//
//  /* Initialize all the time counters */
stats_tick = HAL_GetTick();
rx_fifo_tick = stats_tick;
// set_cmd_and_ctrl_period(0);
}


/**
 * Sends a payload using CW Morse code
 * @param in the payload buffer
 * @param len the length of the payload in bytes
 * @return the number of bytes sent or an appropriate error code
 */
int32_t
send_payload_cw(const uint8_t *in, size_t len)
{

  //sendOverUSB("Fonction send_payload_cw \r\n");

  int32_t ret;

  if(len > AX25_MAX_FRAME_LEN) {
    return COMMS_STATUS_BUFFER_OVERFLOW;
  }

  /* Check if the TX is enabled */
/*  if(!is_tx_enabled()){
    return COMMS_STATUS_RF_OFF;
  }*/

  ret = tx_data_cw(in, len);
  return ret;
}

/**
 * Sends a CW beacons based on the internal COMMS statistics tracking mechanism
 * @return a negative number in case of error
 */
int32_t
send_cw_beacon()
{
  size_t i = 0;

  /* Check if the satellite is during command and control phase */
  /*if(is_cmd_ctrl_enabled()) {
    return 0;
  }*/

  memset(send_buffer, 0, AX25_MAX_FRAME_LEN);
  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
//  send_buffer[i++] = 'Y';
 /* send_buffer[i++] = cw_get_bat_voltage_char(&comms_stats);
  send_buffer[i++] = cw_get_bat_current_char(&comms_stats);
  send_buffer[i++] = cw_get_temp_char(&comms_stats);
  send_buffer[i++] = cw_get_uptime_hours_char(&comms_stats);
  send_buffer[i++] = cw_get_uptime_mins_char(&comms_stats);
  send_buffer[i++] = cw_get_cont_errors_char(&comms_stats);
  send_buffer[i++] = cw_get_last_error_char(&comms_stats);*/
  return send_payload_cw(send_buffer, i);
}




