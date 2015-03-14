/**
 * @brief Red Pitaya LCR worker module.
 *
 * @Author Luka Golinar <luka.golinar@redpitaya.com>
 *         
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef __WORKER_H
#define __WORKER_H

#include "main.h"
#include "common.h"

typedef enum {
	lcr_osc_idle_state = 0, /* do nothing */
    lcr_osc_quit_state, /* shutdown worker */
    lcr_osc_meas_state /* Start lcr measure*/
} lcr_worker_state_machine;

int lcr_worker_init(rp_app_params_t *params);
int lcr_worker_exit(void);

#endif /* __WORKER_H*/