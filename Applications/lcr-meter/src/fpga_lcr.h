 /* @brief Red Pitaya LCR FPGA Interface.
 *
 * @Author Luka Golinar <luka.golinar@redpitaya.com>
 *         
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef __FPGA_LCR_H
#define __FPGA_LCR_H

#include <stdint.h>

/* LCR meter uses the very same addresses as does the Oscilloscope module */

/** Starting address of FPGA registers handling Oscilloscope module. */
#define OSC_FPGA_BASE_ADDR 	0x40100000
/** The size of FPGA registers handling Oscilloscope module. */
#define OSC_FPGA_BASE_SIZE 0x30000
/** Size of data buffer into which input signal is captured , must be 2^n!. */
#define OSC_FPGA_SIG_LEN   (16*1024)

/** Offset to the memory buffer where signal on channel A is captured. */
#define OSC_FPGA_CHA_OFFSET    0x10000
/** Offset to the memory buffer where signal on channel B is captured. */
#define OSC_FPGA_CHB_OFFSET    0x20000


/** @brief FPGA registry structure for Oscilloscope core module.
 *
 * This structure is direct image of physical FPGA memory. It assures
 * direct read/write FPGA access when it is mapped to the appropriate memory address
 * through /dev/mem device.
 */
typedef struct osc_fpga_reg_mem_s {
    /** @brief  Configuration:
     * bit     [0] - arm_trigger
     * bit     [1] - rst_wr_state_machine
     * bits [31:2] - reserved 
     */
    uint32_t conf;

    /** @brief  Trigger source:
     * bits [ 2 : 0] - trigger source:
     *   1 - trig immediately
     *   2 - ChA positive edge
     *   3 - ChA negative edge
     *   4 - ChB positive edge 
     *   5 - ChB negative edge
     *   6 - External trigger 0
     *   7 - External trigger 1 
     * bits [31 : 3] -reserved
     */
    uint32_t trig_source;

    /** @brief  ChA threshold:
     * bits [13: 0] - ChA threshold
     * bits [31:14] - reserved
     */
    uint32_t cha_thr;

    /** @brief  ChB threshold:
     * bits [13: 0] - ChB threshold
     * bits [31:14] - reserved
     */
    uint32_t chb_thr;

    /** @brief  After trigger delay:
     * bits [31: 0] - trigger delay 
     * 32 bit number - how many decimated samples should be stored into a buffer.
     * (max 16k samples)
     */
    uint32_t trigger_delay;

    /** @brief  Data decimation
     * bits [16: 0] - decimation factor, legal values:
     *   1, 8, 64, 1024, 8192 65536
     *   If other values are written data is undefined 
     * bits [31:17] - reserved
     */
    uint32_t data_dec;

    /** @brief  Write pointers - both of the format:
     * bits [13: 0] - pointer
     * bits [31:14] - reserved
     * Current pointer - where machine stopped writing after trigger
     * Trigger pointer - where trigger was detected 
     */
    uint32_t wr_ptr_cur;
    uint32_t wr_ptr_trigger;

    /** @brief  ChA & ChB hysteresis - both of the format:
     * bits [13: 0] - hysteresis threshold
     * bits [31:14] - reserved
     */
    uint32_t cha_hystersis;
    uint32_t chb_hystersis;

    /** @brief
     * bits [0] - enable signal average at decimation
     * bits [31:1] - reserved
     */
    uint32_t other;
    
    uint32_t reseved;
    
    /** @brief ChA Equalization filter
     * bits [17:0] - AA coefficient (pole)
     * bits [31:18] - reserved
     */
    uint32_t cha_filt_aa;    
    
    /** @brief ChA Equalization filter
     * bits [24:0] - BB coefficient (zero)
     * bits [31:25] - reserved
     */
    uint32_t cha_filt_bb;    
    
    /** @brief ChA Equalization filter
     * bits [24:0] - KK coefficient (gain)
     * bits [31:25] - reserved
     */
    uint32_t cha_filt_kk;  
    
    /** @brief ChA Equalization filter
     * bits [24:0] - PP coefficient (pole)
     * bits [31:25] - reserved
     */
    uint32_t cha_filt_pp;     
    
    /** @brief ChB Equalization filter
     * bits [17:0] - AA coefficient (pole)
     * bits [31:18] - reserved
     */
    uint32_t chb_filt_aa;    
    
    /** @brief ChB Equalization filter
     * bits [24:0] - BB coefficient (zero)
     * bits [31:25] - reserved
     */
    uint32_t chb_filt_bb;    
    
    /** @brief ChB Equalization filter
     * bits [24:0] - KK coefficient (gain)
     * bits [31:25] - reserved
     */
    uint32_t chb_filt_kk;  
    
    /** @brief ChB Equalization filter
     * bits [24:0] - PP coefficient (pole)
     * bits [31:25] - reserved
     */
    uint32_t chb_filt_pp;            
    
    
    /** @brief  ChA & ChB data - 14 LSB bits valid starts from 0x10000 and
     * 0x20000 and are each 16k samples long */
} osc_fpga_reg_mem_t;

/* function declarations, detailed descriptions is in apparent implementation file  */
int   lcr_fpga_init(void);
int   lcr_fpga_exit(void);

int   lcr_fpga_reset(void);
static int __lcr_fpga_cleanup_mem(void);

#endif /* __FPGA_H_LCR */
