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

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "common.h"
#include "worker.h"

pthread_t *rp_osc_thread_handler = NULL;
void *rp_osc_worker_thread(void *args);

pthread_mutex_t       rp_osc_ctrl_mutex = PTHREAD_MUTEX_INITIALIZER;
rp_app_params_t *lcr_params = NULL;

/* Signals directly pointing at the FPGA mem space */
int *rp_fpga_cha_signal, *rp_fpga_chb_signal;


/*----------------------------------------------------------------------------------*/
int lcr_worker_init(rp_app_params_t *params){

	lcr_copy_params(params, &lcr_params);

	return RP_OK;
}

