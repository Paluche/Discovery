/*
 *  ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/*
 * This program turn the Discovery board into a serial to USB device.
 */
#include "ch.h"
#include "hal.h"
#include "test.h"

#include "chprintf.h"
#include "shell.h"

#include "usbcfg.h"

/*===========================================================================*/
/* Serial configuration                                                      */
/*===========================================================================*/
/* Virtual serial port over USB.*/
SerialUSBDriver SDU1;

// USART1 configuration
static const SerialConfig sdconfig = {
    9600,
    0,
    0,
    0
};


// Serial RX to USB thread
static int toggle_rx = 0;
static WORKING_AREA(waRX_Thread,256);
__attribute__((noreturn))
    static msg_t RX_Thread(__attribute__((unused)) void *arg)
{
    for(;;) {
        chSequentialStreamPut(&SDU1, sdGet(&SD1));
        if (toggle_rx)
            palSetPad(GPIOG, GPIOG_LED4_RED);
        else
            palClearPad(GPIOG, GPIOG_LED4_RED);
        toggle_rx = ~toggle_rx;
    }
}

// USB to Serial TX thread
static int toggle_tx = 0;
static WORKING_AREA(waTX_Thread,256);
__attribute__((noreturn))
    static msg_t TX_Thread(__attribute__((unused)) void *arg)
{
    for(;;) {
        char received = chSequentialStreamGet(&SDU1);
        // Echo what we received in USB
        chSequentialStreamPut(&SDU1, received);
        if (received == '\n')
            chSequentialStreamPut(&SDU1, '\r');
        if (received == '\r')
            chSequentialStreamPut(&SDU1, '\n');
        // Transfer to the serial
        sdPut(&SD1, received);
        if (toggle_tx)
            palSetPad(GPIOG, GPIOG_LED3_GREEN);
        else
            palClearPad(GPIOG, GPIOG_LED3_GREEN);
        toggle_tx = ~toggle_tx;
    }
}

/*===========================================================================*/
/* Initialization and main thread.                                           */
/*===========================================================================*/

/*
 * Application entry point.
 */
int main(void) {
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device i
     *   drivers and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    /*
     * Initializes a serial-over-USB CDC driver.
     */
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    /*
     * Initializes the USART1 Serial Driver 1
     */
    sdStart(&SD1, &sdconfig);

    /*
     * Launch RX and TX thread
     */
    chThdCreateStatic(waRX_Thread, sizeof(waRX_Thread),
                      NORMALPRIO + 10, RX_Thread, NULL);

    chThdCreateStatic(waTX_Thread, sizeof(waTX_Thread),
                      NORMALPRIO + 10, TX_Thread, NULL);

    for (;;) {
//        palSetPad(GPIOG, GPIOG_LED3_GREEN);
        chThdSleepMilliseconds(1000);
  //      palClearPad(GPIOG, GPIOG_LED3_GREEN);
        chThdSleepMilliseconds(1000);
    }
}
