#ifndef __INCLUDE_H
#define __INCLUDE_H
#if 0
#include "common.h"
#include "systick.h"
#include "wdog.h"
#include "gpio.h"
#include "rtc.h"
#include "ftm.h"
#include "pit.h"
#include "uart.h"
#include "kbi.h"
#include "mscan.h"
#include "adc.h"
#include "flash.h"
#include "ics.h"
#include "sim.h"
#include "pmc.h"
#include "sysinit.h"
#else

#include "adc.h"
#include "usart.h"
#include "spi.h"



///=====================================================
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>

#include "config.h"
#include "sch_config.h"
#include "sch_printf.h"

#include "bsp.h"
#include "system.h"
#include "app_task.h"

///#include "uicc_def.h"
#include "app_debug.h"


#include <math.h>

///#include "mw_rtc.h"
#include "mw_uart.h"
///#include "mw_can.h"
#include "mw_gpio.h"
#include "mw_i2c.h"
#include "mw_adc.h"
///#include "mw_time.h"
#include "mw_flash.h"
#include "mw_spi.h"

#include "app_connect.h"
#include "app_at.h"
#include "app_led.h"
#include "app_start.h"
#include "app_mute.h"
///#include "app_can.h"
#include "app_power.h"
#include "app_voltage.h"
///#include "app_panel.h"
#include "app_updata.h"
#include "app_lowpower.h"
#include "app_amp.h"
#include "app_tdf8541.h" ///AMP
#include "app_bt.h"
#include "app_dsp_adau1452.h"
#include "app_dspdata_access.h"
#include "app_dsp_driver.h"
#include "app_dsp_eq.h"
#include "app_dsp_filter.h"
#include "app_dsp_readback.h"
#include "app_dsp_single_mute.h"
#include "app_dsp_mix.h"
#include "app_ad1938.h"

#include "dsp_defines.h"
#include "dsp_IC_1_PARAM.h"
#include "dsp_IC_1_REG.h"
//#include "dsp_IC_1.h"

#include "app_eprom.h"
#endif
#endif///
