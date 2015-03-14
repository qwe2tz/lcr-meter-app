/**
 * @brief Red Pitaya LCR main module.
 *
 * @Author Luka Golinar <luka.golinar@redpitaya.com>
 *         
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef DEBUG
#  define TRACE(args...) fprintf(stderr, args)
#else
#  define TRACE(args...) {}
#endif

/* Parameters description structure - must be the same for all RP controllers */
typedef struct rp_app_params_s {
    char  *name;
    float  value;
    int    fpga_update;
    int    read_only;
    float  min_val;
    float  max_val;
} rp_app_params_t;

/* Parameters indexes - these defines should be in the same order as 
 * rp_app_params_t structure defined in main.c */

/* LCR parameters */
#define PARAMS_NUM 				15
#define LCR_START_MEASURE		0
#define LCR_GEN_AMP				1
#define LCR_GEN_AVG  			2
#define LCR_GEN_DC_BIAS			3
#define LCR_GEN_R_SHUNT			4
#define LCR_START_FREQ			5
#define LCR_END_FREQ			6
#define LCR_Y_SCALE_DATA		7
#define LCR_SCALE_TYPE			8
#define LCR_GEN_LRE				9
#define LCR_GEN_LIM				10
#define LCR_CALIB				11
#define LCR_STEPS				12
#define LCR_PROG				13
#define LCR_SAVE				14

/* Output signals */
#define SIGNALS_NUM   			3

/* module entry points */
const char *rp_app_desc(void);
int lcr_app_init(void);
int lcr_app_exit(void);
int lcr_set_params(rp_app_params_t *params, int param_len);
int lcr_copy_params(rp_app_params_t *src, rp_app_params_t **dst);
int lcr_get_params(rp_app_params_t **p);
int lcr_get_signals(float ***s, int *sig_num, int *sig_len);

#endif /*  __MAIN_H */