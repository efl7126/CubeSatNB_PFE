/*
 * pfe_packets.c
 *
 *  Created on: 3 avr. 2019
 *      Author: franc
 */


#include "upsat.h"
#include "services.h"
#include "system.h"
#include "stddef.h"
#include "stdbool.h"




SAT_returnState import_pkt_pfe(TC_TM_app_id app_id, struct uart_data *data) {

    tc_tm_pkt *pkt;
    uint16_t size = 0;

    SAT_returnState res;
    SAT_returnState res_deframe;

    /*
    res = HAL_uart_rx(app_id, data);
    if( res == SATR_EOT ) {

        size = data->uart_size;
        res_deframe = HLDLC_deframe(data->uart_unpkt_buf, data->deframed_buf, &size);
        if(res_deframe == SATR_EOT) {

            data->last_com_time = HAL_sys_GetTick();  //update the last communication time, to be used for timeout discovery

            pkt = get_pkt(size);

            if(!C_ASSERT(pkt != NULL) == true) { return SATR_ERROR; }
            if((res = unpack_pkt(data->deframed_buf, pkt, size)) == SATR_OK) {
                stats_inbound(pkt->type, pkt->app_id, pkt->dest_id, pkt);
                route_pkt(pkt); }
            else {
                stats_dropped_upack();
                pkt->verification_state = res;
            }
            verification_app(pkt);

            TC_TM_app_id dest = 0;

            if(pkt->type == TC)         { dest = pkt->app_id; }
            else if(pkt->type == TM)    { dest = pkt->dest_id; }

            if(dest == SYSTEM_APP_ID) {
                free_pkt(pkt);
            }
        }
        else {
            stats_dropped_hldlc();
        }
    }

    */

    return SATR_OK;
}
