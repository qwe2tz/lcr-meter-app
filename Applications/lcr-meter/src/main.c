/** @file main.c
 *
 * @brief Red Pitaya LCR Main module.
 * @author Luka Golinar <luka.golinar@redpitaya.com>
 * @copyright Red Pitaya  http://www.redpitaya.com
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "worker.h"
#include "version.h"

/* Describe app. parameters with some info/limitations */
pthread_mutex_t lcr_main_params_mutex = PTHREAD_MUTEX_INITIALIZER;

static rp_app_params_t lcr_main_params[PARAMS_NUM+1] = {
	/* LCR parameters definiton */
	{ /* start_measure - General flag used for sending params from the RedPitaya browser.
   *   -1 - Application not loaded yet
   *    0 - negative
   *    1 - Frequency Sweep
   *    2 - Measurment sweep 
   *    3 - Other ( Change the max value for more states )
   *  - Setting max value to 2 for general purposes. Can be changed accordingly. 
   *  - Read only value set to 0, as the flag_button value can be changed from Javascript 
   *    code in index.html as well as from the C controller code. */
    "start_measure", -1, 1, 0, -1, 3 },
{ /* LCR amplitude. User defined.
   *    Min value - 0
   *    Max value - 2 */
    "gen_amp", 0, 1, 0, 0, 2 },
{ /* Averaging parameter.
   *    Min value - 0
   *    Max value - 10 */
    "gen_avg", 0, 1, 0, 0, 10 },
{ /* DC bias parameter.
   *    Min value - (-2)
   *    Max value -   2 */
    "gen_DC_bias", 0, 1, 0, -2, 2 },
{ /* DC bias parameter.
   *    Min value - (-2)
   *    Max value -   2  */
   "gen_R_shunt", 0, 1, 0, 0, 50000 },
{ /* Start frequency for frequency sweep.
   *    Min value - 200
   *    Max value - 1000000    */
   "start_freq", 200, 1, 0, 0, 1000000 },
{ /* End frequency for frequency sweep.
   * Min value - 200
   * Max value - 1000000 */
   "end_freq", 200, 1, 0, 0, 1000000 },
{ /* Plots different data depending on user choice
   * 0 - Plots amplitude
   * 1 - Plots phase
   * 5 - TODO: Adding multiple data acquisition. */
  "plot_y_scale_data", 0, 1, 0, 0, 15 },
{ /* Lcr scale type. Defined by user.
   * 0 - Linear scale
   * 1 - Logarithmic scale */
  "lcr_scale_type", 0 , 1, 0, 0, 1 },
{ /* Lcr LoadRE
   * */
  "gen_fs_LoadRe", 0, 1, 0, 0, 1 },

{ /* Lcr LoadIm
   * */
  "gen_fs_LoadIm", 0, 1, 0, 0, 1 },
{ /* Calibration type. Defined by user in browser.
   * 0 - Open calibration
   * 1 - Short alibration
   * 2 - Load calibration
   * 3 - None */
   "lcr_calibration", 0, 1, 0, 0, 3 },
{ /* LCR steps declared by user
   * Minimum value - 1
   * Maximum value - 1000
   * Default value - 100  */
  "lcr_steps", 1000, 1, 0, 0, 1000},
{ /* Lcr progress status. Used for progress bar while measuring.
   * 0 -   default/min val
   * 100 - max val */
   "lcr_progress", 0, 1, 0, 0, 100 },
{/* Lcr save/load data parameter 
  * -1 - Do not save any parameter data
  *  1 - Save parameter data */ 
   "lcr_save_data", -1, 1, 0, -1, 3 },
{ /* Must be last! */
    NULL, 0.0, -1, -1, 0.0, 0.0 }
};

/* params initialized */
//static int params_init = 0;

const char *rp_app_desc(void)
{
    return (const char *)"Red Pitaya LCR application.\n";
}

int lcr_app_init(void){

	fprintf(stderr, "Loading scope (with gen+pid extensions) version %s-%s.\n", VERSION_STR, REVISION_STR);
	lcr_set_params(&lcr_main_params[0], PARAMS_NUM);
	//TODO Init all the other required modules
	return 0;
}

int lcr_app_exit(void){
	fprintf(stderr, "Unloading lcr application version %s-%s.\n", VERSION_STR, REVISION_STR);
	//TODO Unload all the other required modules
	return 0;
}

int lcr_set_params(rp_app_params_t *params, int param_len){

	int i;
	TRACE("%s()\n", __FUNCTION__);

	if(param_len > PARAMS_NUM){
		fprintf(stderr, "Too many parameters, max=%d\n", PARAMS_NUM);
		return -1;
	}
	pthread_mutex_lock(&lcr_main_params_mutex);
	for (i = 0; i < param_len || params[i].name != NULL; i++){

		int j = 0;
		int p_idx = -1;

		while(params[i].name != NULL){
			int p_strlen = strlen(params[i].name);

			if(p_strlen != strlen(lcr_main_params[j].name)){
				p_idx++;
				j++;
				continue;
			}

			if(!strncmp(params[i].name, lcr_main_params[j].name, p_strlen)){
				p_idx = j;
				break;
			}
			j++;
		}

		if(p_idx == -1){
			fprintf(stderr, "Paramter %s not found, igoring it.\n", params[i].name);
			continue;

		}else if(params[p_idx].read_only == 1){
			continue;
		}

		if(lcr_main_params[p_idx].value != params[i].value){
			
			if(lcr_main_params[p_idx].min_val > params[i].value){
				fprintf(stderr, "Incorrect value. Param %s min val: %f\n", lcr_main_params[p_idx].name, lcr_main_params[i].min_val);
			}

			if(lcr_main_params[p_idx].max_val < params[i].value){
				fprintf(stderr, "Incorrect value. Param %s min val: %f\n", lcr_main_params[p_idx].name, lcr_main_params[i].max_val);
			}
		}

		lcr_main_params[p_idx].value = params[i].value;
		pthread_mutex_unlock(&lcr_main_params_mutex);
	}

	return 0;
}

