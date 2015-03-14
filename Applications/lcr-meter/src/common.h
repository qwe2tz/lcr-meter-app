/**
 * @brief Red Pitaya LCR common module.
 *
 * @Author Luka Golinar <luka.golinar@redpitaya.com>
 *         
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef __COMMON_H
#define __COMMON_H

/* Red Pitaya LCR meter control constants */
#define RP_OK		 0
#define RP_ERRNO	-1

typedef enum{
	RP_CH_1,
	RP_CH_2
}rp_channel_t;

#endif /*	__COMMON_H */