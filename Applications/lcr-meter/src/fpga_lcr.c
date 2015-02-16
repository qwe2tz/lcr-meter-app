/* @brief Red Pitaya Oscilloscope FPGA Interface.
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
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "fpga_lcr.h"

/* @brief Pointer to FPGA control registers. */
static osc_fpga_reg_mem_t *g_osc_fpga_reg_mem = NULL;

/* @brief Pointer to data buffer where signal on channel A is captured.  */
static uint32_t           *g_osc_fpga_cha_mem = NULL;

/* @brief Pointer to data buffer where signal on channel B is captured.  */
static uint32_t           *g_osc_fpga_chb_mem = NULL;

/* @brief The memory file descriptor used to mmap() the FPGA space. */
static int                 g_osc_fpga_mem_fd = -1;

/* @brief Number of ADC acquisition bits.  */
const int                  c_osc_fpga_adc_bits = 14;

/* @brief Sampling frequency = 125Mspmpls (non-decimated). */
const float                c_osc_fpga_smpl_freq = 125e6;

/* @brief Sampling period (non-decimated) - 8 [ns]. */
const float                c_osc_fpga_smpl_period = (1. / 125e6);


static int __lcr_fpga_cleanup_mem(void){

	if(g_osc_fpga_reg_mem){

		if(munmap(g_osc_fpga_reg_mem, OSC_FPGA_BASE_SIZE) < 0){
			fprintf(stderr, "Unmapping of Oscilloscope registers failed!%s\n", strerror(errno));
			return -1;
		}

		g_osc_fpga_reg_mem = NULL;
		g_osc_fpga_cha_mem = NULL;
		g_osc_fpga_chb_mem = NULL;
	}

	/* Close file descriptor */
	if(g_osc_fpga_mem_fd >= 0){
		close(g_osc_fpga_mem_fd);
		g_osc_fpga_mem_fd = -1;
	}

	return 0;
}

int lcr_fpga_init(void){

	void *page_ptr;
	long page_addr, page_off, page_size = sysconf(_SC_PAGESIZE);

	/* Cleanup FPGA address if needed */
	if(__lcr_fpga_cleanup_mem < 0){
		return -1;
	}

	g_osc_fpga_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(g_osc_fpga_mem_fd < 0) {
        fprintf(stderr, "open(/dev/mem) failed: %s\n", strerror(errno));
        return -1;
    }

    page_addr = OSC_FPGA_BASE_ADDR & (~(page_size-1));
    page_off  = OSC_FPGA_BASE_ADDR - page_addr;

    page_ptr = mmap(NULL, OSC_FPGA_BASE_SIZE, PROT_READ | PROT_WRITE,
                          MAP_SHARED, g_osc_fpga_mem_fd, page_addr);

    if((void *)page_ptr == MAP_FAILED){
    	fprintf(stderr, "Mmap function failed with error: %s\n", strerror(errno));
    	__lcr_fpga_cleanup_mem();
        return -1;
    }

    g_osc_fpga_reg_mem = page_ptr + page_off;
    g_osc_fpga_cha_mem = (uint32_t *)g_osc_fpga_reg_mem + 
        (OSC_FPGA_CHA_OFFSET / sizeof(uint32_t));
    g_osc_fpga_chb_mem = (uint32_t *)g_osc_fpga_reg_mem + 
        (OSC_FPGA_CHB_OFFSET / sizeof(uint32_t));

    return 0;
}

int lcr_fpga_exit(void){
	__lcr_fpga_cleanup_mem();
	return 0;
}