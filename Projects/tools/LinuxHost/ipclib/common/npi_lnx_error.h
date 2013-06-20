/**************************************************************************************************
  Filename:       npi_lnx_error.h
  Revised:        $Date: 2012-08-24 14:04:49 -0800 (Fri, 24 Aug 2012) $
  Revision:       $Revision: 108 $

  Description:    This file contains the Network Processor Interface (NPI),
                  which abstracts the physical link between the Application
                  Processor (AP) and the Network Processor (NP). The NPI
                  serves as the HAL's client for the SPI and UART drivers, and
                  provides API and callback services for its client.

  Copyright (C) {2012} Texas Instruments Incorporated - http://www.ti.com/


   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

     Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the
     distribution.

     Neither the name of Texas Instruments Incorporated nor the names of
     its contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************************************************/

#ifndef NPI_LNX_ERROR_H_
#define NPI_LNX_ERROR_H_


// Global error variable
extern int npi_ipc_errno;
extern int __BIG_DEBUG_ACTIVE;
extern int __DEBUG_TIME_ACTIVE;
#define st(x)      do { x } while (__LINE__ == -1)

// Global function to notify of error
int NPI_LNX_IPC_NotifyError(uint16 source, const char* errorMsg);

// Define RPC command type
#define RPC_CMD_NOTIFY_ERR						0xE0	//RPC_CMD_RES7

/*
 * Following are error codes for the NPI Server, 32-bit unsigned int
 * There are 4 bytes. Following is an explanation of the meaning of
 * the different nibbles. Starting with the short containing the least
 * significant nibble
 * 0-3:	Error code
 * 		0-1:	Special per error info
 * 				If nibble 0-1 == FF then a reset is requested
 * 		2-3:	Error ID
 * 4-5:	Function
 * 6-7:	Module (natural parent module)	 (Example: Serial Interface)
 */
#define NPI_LNX_SUCCESS												0x00000000
#define NPI_LNX_FAILURE												0xFFFFFFFF
#define NPI_LNX_UINT8_ERROR											0xFF
// Reserved error code. This must not be used as it is a valid return value.
#define NPI_LNX_ERROR_RESERVED										0x00000001

#define NPI_LNX_ERROR_RESET_REQUESTED(x)							((x & 0x000000FF) == 0x000000FF)

// Mask for module/thread
#define NPI_LNX_ERROR_MODULE_MASK(a)								((uint16)((a & 0xFFFF0000) >> 16))
#define NPI_LNX_ERROR_MODULE(a)										((uint8)((a & 0xFF00) >> 8))
#define NPI_LNX_ERROR_THREAD(a)										((uint8)(a & 0x00FF))

/*
 * Master errors
 */
#define NPI_LNX_ERROR_IPC_GENERIC									0x01000100
#define NPI_LNX_ERROR_IPC_OPEN_REMOTI_RNP_CFG						0x01010100
#define NPI_LNX_ERROR_IPC_SOCKET_GET_ADDRESS_INFO					0x01010200
#define NPI_LNX_ERROR_IPC_SOCKET_BIND								0x01010300
#define NPI_LNX_ERROR_IPC_SOCKET_SET_REUSE_ADDRESS					0x01010400
#define NPI_LNX_ERROR_IPC_SOCKET_LISTEN								0x01010500
#define NPI_LNX_ERROR_IPC_SOCKET_SELECT_CHECK_ERRNO					0x01010600
#define NPI_LNX_ERROR_IPC_SOCKET_ACCEPT								0x01010700
#define NPI_LNX_ERROR_IPC_SEND_DATA_SPECIFIC						0x01020100
#define NPI_LNX_ERROR_IPC_SEND_DATA_ALL								0x01020200
#define NPI_LNX_ERROR_IPC_SEND_DATA_SPECIFIC_CONNECTION_REMOVED		0x01020300
#define NPI_LNX_ERROR_IPC_RECV_DATA_CHECK_ERRNO						0x01030100
#define NPI_LNX_ERROR_IPC_RECV_DATA_DISCONNECT						0x01030200
#define NPI_LNX_ERROR_IPC_RECV_DATA_TOO_FEW_BYTES					0x01030300
#define NPI_LNX_ERROR_IPC_RECV_DATA_INCOMPATIBLE_CMD_TYPE			0x01030400
#define NPI_LNX_ERROR_IPC_RECV_DATA_INVALID_SREQ					0x01030500
#define NPI_LNX_ERROR_IPC_RECV_DATA_INVALID_GET_PARAM_CMD			0x01030600
#define NPI_LNX_ERROR_IPC_ADD_TO_ACTIVE_LIST_NO_ROOM				0x01040100
#define NPI_LNX_ERROR_IPC_REMOVE_FROM_ACTIVE_LIST_NOT_FOUND			0x01050100
#define NPI_LNX_ERROR_IPC_SERIAL_CFG_FILE_DOES_NOT_EXIST			0x01060100
#define NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_DEVICE_KEY			0x01070100
#define NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_DEVICE_PATH			0x01070200
#define NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_DEVICE_GPIO_ERR 	0x01070300
#define NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_LOG_PATH			0x01070400
#define NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_CAPSENSE_PATH		0x01070500
#define NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_DEVICE_GPIO(gpioIdx, gpioOrLevel, devIdx) \
	(NPI_LNX_ERROR_IPC_REMOTI_RNP_CFG_PARSER_DEVICE_GPIO_ERR | \
			((gpioOrLevel & 0x03)<<6) | \
			((gpioIdx & 0x07)<<3) | \
			(devIdx & 0x07))
/*
 * For reading GPIO configuration an array of errors can occur. They are indexed
 * as follows:
 * _________________________________________________
 * | GPIO:  0  |                 |                 |
 * | LEVEL: 1  | GPIO Index 0-2  |Device Index 1-2 |
 * |___________|_________________|_________________|
 * |     |     |     |     |     |     |     |     |
 * |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * |_____|_____|_____|_____|_____|_____|_____|_____|
 */
#define NPI_LNX_ERROR_IPC_NOTIFY_ERR_GET_ADDR_INFO					0x01080100
#define NPI_LNX_ERROR_IPC_NOTIFY_ERR_CREATE_SOCKET					0x01080200
#define NPI_LNX_ERROR_IPC_NOTIFY_ERR_CONNECT 						0x01080300
#define NPI_LNX_ERROR_IPC_NOTIFY_ERR_SET_SOCKET_OPTIONS				0x01080400

/*
 * Serial interface error codes
 */
// Error codes for UART
#define NPI_LNX_ERROR_UART_GENERIC									0x02000100
#define NPI_LNX_ERROR_UART_OPEN_GENERIC								0x02010100
#define NPI_LNX_ERROR_UART_OPEN_ALREADY_OPEN						0x02010200
#define NPI_LNX_ERROR_UART_OPEN_FAILED_DEVICE						0x02010300
#define NPI_LNX_ERROR_UART_OPEN_FAILED_ASYNCH_CB_THREAD				0x02010400
#define NPI_LNX_ERROR_UART_OPEN_FAILED_RX_THREAD					0x02010500
#define NPI_LNX_ERROR_UART_CLOSE_GENERIC							0x02020100
#define NPI_LNX_ERROR_UART_SEND_FRAME_FAILED_TO_WRITE				0x02030100
#define NPI_LNX_ERROR_UART_SEND_FRAME_FAILED_TO_ALLOCATE			0x02030200
#define NPI_LNX_ERROR_UART_SEND_SYNCH_TIMEDOUT						0x02040100
#define NPI_LNX_ERROR_UART_RX_THREAD								0x02050100
#define NPI_LNX_ERROR_UART_RX_THREAD_MAX_ATTEMPTS					0x02050200
#define NPI_LNX_ERROR_UART_ASYNCH_CB_PROC_THREAD					0x02060100

// Error codes for SPI
#define NPI_LNX_ERROR_SPI_GENERIC									0x03000100
#define NPI_LNX_ERROR_SPI_OPEN_GENERIC								0x03010100
#define NPI_LNX_ERROR_SPI_OPEN_ALREADY_OPEN							0x03010200
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_POLL_THREAD					0x03010300
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_EVENT_THREAD					0x03010400
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_POLL_LOCK_MUTEX				0x03010500
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_POLL_MUTEX					0x03010600
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_SRDY_MUTEX					0x03010700
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_POLL_COND						0x03010800
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_SRDY_COND						0x03010900
#define NPI_LNX_ERROR_SPI_OPEN_FAILED_SRDY_LOCK_MUTEX				0x03010A00
#define NPI_LNX_ERROR_SPI_CLOSE_GENERIC								0x03020100
#define NPI_LNX_ERROR_SPI_POLL_LOCK_VAR_ERROR						0x03030100
#define NPI_LNX_ERROR_SPI_POLL_DATA_SRDY_CLR_TIMEOUT_POSSIBLE_RESET	0x03040100
#define NPI_LNX_ERROR_SPI_POLL_THREAD_SREQ_CONFLICT					0x03050100
#define NPI_LNX_ERROR_SPI_POLL_THREAD_POLL_UNLOCK					0x03050200
#define NPI_LNX_ERROR_SPI_POLL_THREAD_POLL_LOCK						0x03050300
#define NPI_LNX_ERROR_SPI_EVENT_THREAD_OPEN_EVENT_FD				0x03060100
#define NPI_LNX_ERROR_SPI_EVENT_THREAD_POLL_FD_FAILED				0x03060200
#define NPI_LNX_ERROR_SPI_EVENT_THREAD_FAILED_POLL					0x03070100
#define NPI_LNX_ERROR_SPI_INT_THREAD_FAILED_POLL					0x03080100

// Error codes for HAL SPI
#define NPI_LNX_ERROR_HAL_SPI_GENERIC								0x04000100
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_OPEN_DEVICE			0x04010100
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_SET_MODE				0x04010200
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_GET_MODE				0x04010300
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_SET_BPW    			0x04010400
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_GET_BPW    			0x04010500
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_SET_MAX_SPEED			0x04010600
#define NPI_LNX_ERROR_HAL_SPI_INIT_FAILED_TO_GET_MAX_SPEED			0x04010700
#define NPI_LNX_ERROR_HAL_SPI_WRITE_FAILED							0x04020100
#define NPI_LNX_ERROR_HAL_SPI_WRITE_FAILED_INCORRECT_NUM_OF_BYTES	0x04020200

// Error codes for I2C
#define NPI_LNX_ERROR_I2C_GENERIC									0x05000100
#define NPI_LNX_ERROR_I2C_OPEN_GENERIC								0x05010100
#define NPI_LNX_ERROR_I2C_OPEN_ALREADY_OPEN							0x05010200
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_POLL_THREAD					0x05010300
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_EVENT_THREAD					0x05010400
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_POLL_LOCK_MUTEX				0x05010500
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_POLL_MUTEX					0x05010600
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_SRDY_MUTEX					0x05010700
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_POLL_COND						0x05010800
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_SRDY_COND						0x05010900
#define NPI_LNX_ERROR_I2C_OPEN_FAILED_SRDY_LOCK_MUTEX				0x05010A00
#define NPI_LNX_ERROR_I2C_CLOSE_GENERIC								0x05020100
#define NPI_LNX_ERROR_I2C_SEND_ASYNCH_FAILED_LOCK					0x05030100
#define NPI_LNX_ERROR_I2C_SEND_ASYNCH_FAILED_UNLOCK					0x05030200
#define NPI_LNX_ERROR_I2C_SEND_SYNCH_FAILED_LOCK					0x05040100
#define NPI_LNX_ERROR_I2C_SEND_SYNCH_FAILED_UNLOCK					0x05040200
#define NPI_LNX_ERROR_I2C_POLL_THREAD_FAILED_LOCK					0x05050100
#define NPI_LNX_ERROR_I2C_POLL_THREAD_FAILED_UNLOCK					0x05050200
#define NPI_LNX_ERROR_I2C_EVENT_THREAD_OPEN_EVENT_FD				0x05060100
#define NPI_LNX_ERROR_I2C_EVENT_THREAD_POLL_FD_FAILED				0x05060200
#define NPI_LNX_ERROR_I2C_EVENT_THREAD_FAILED_POLL					0x05070100
#define NPI_LNX_ERROR_I2C_EVENT_THREAD_FAILED_LOCK					0x05070200
#define NPI_LNX_ERROR_I2C_INT_THREAD_FAILED_POLL					0x05080100

// Error codes for HAL I2C
#define NPI_LNX_ERROR_HAL_I2C_GENERIC								0x06000100
#define NPI_LNX_ERROR_HAL_I2C_INIT_FAILED_TO_OPEN_DEVICE			0x06010100
#define NPI_LNX_ERROR_HAL_I2C_INIT_FAILED_TO_SET_ADDRESS			0x06010200
#define NPI_LNX_ERROR_HAL_I2C_CLOSE_GENERIC							0x06020100
#define NPI_LNX_ERROR_HAL_I2C_WRITE_TIMEDOUT						0x06030100
#define NPI_LNX_ERROR_HAL_I2C_WRITE_TIMEDOUT_PERFORM_RESET			0x060301FF
#define NPI_LNX_ERROR_HAL_I2C_READ_TIMEDOUT							0x06040100
#define NPI_LNX_ERROR_HAL_I2C_READ_TIMEDOUT_PERFORM_RESET			0x060401FF

// Error codes for the common HAL GPIO module
#define NPI_LNX_ERROR_HAL_GPIO_GENERIC								0x07000100
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_DIR_OPEN				0x07010100
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_DIR_WRITE				0x07010200
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_VAL_OPEN				0x07010300
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_LVLSHFT_VAL_WRITE				0x07010400
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_DIR_OPEN					0x07010500
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_DIR_WRITE					0x07010600
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_VAL_OPEN					0x07010700
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_VAL_WRITE					0x07010800
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_EDGE_OPEN					0x07010900
#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_EDGE_WRITE					0x07010A00

#define NPI_LNX_ERROR_HAL_GPIO_MRDY_LVLSHFT_DIR_OPEN				0x07020100
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_LVLSHFT_DIR_WRITE				0x07020200
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_LVLSHFT_VAL_OPEN				0x07020300
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_LVLSHFT_VAL_WRITE				0x07020400
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_DIR_OPEN					0x07020500
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_DIR_WRITE					0x07020600
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_VAL_OPEN					0x07020700
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_VAL_WRITE					0x07020800
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_VAL_READ					0x07020900

#define NPI_LNX_ERROR_HAL_GPIO_RESET_LVLSHFT_DIR_OPEN				0x07030100
#define NPI_LNX_ERROR_HAL_GPIO_RESET_LVLSHFT_DIR_WRITE				0x07030200
#define NPI_LNX_ERROR_HAL_GPIO_RESET_LVLSHFT_VAL_OPEN				0x07030300
#define NPI_LNX_ERROR_HAL_GPIO_RESET_LVLSHFT_VAL_WRITE				0x07030400
#define NPI_LNX_ERROR_HAL_GPIO_RESET_GPIO_DIR_OPEN					0x07030500
#define NPI_LNX_ERROR_HAL_GPIO_RESET_GPIO_DIR_WRITE					0x07030600
#define NPI_LNX_ERROR_HAL_GPIO_RESET_GPIO_VAL_OPEN					0x07030700
#define NPI_LNX_ERROR_HAL_GPIO_RESET_GPIO_VAL_WRITE					0x07030800

#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_VAL_WRITE_SET_LOW			0x07040100
#define NPI_LNX_ERROR_HAL_GPIO_MRDY_GPIO_VAL_WRITE_SET_HIGH			0x07040200

#define NPI_LNX_ERROR_HAL_GPIO_RESET_GPIO_VAL_WRITE_SET_HIGH		0x07050100
#define NPI_LNX_ERROR_HAL_GPIO_RESET_GPIO_VAL_WRITE_SET_LOW			0x07050200

#define NPI_LNX_ERROR_HAL_GPIO_SRDY_GPIO_VAL_READ_FAILED			0x07060100

#define NPI_LNX_ERROR_HAL_GPIO_WAIT_SRDY_CLEAR_POLL_TIMEDOUT		0x07070100
#define NPI_LNX_ERROR_HAL_GPIO_WAIT_SRDY_CLEAR_READ_FAILED			0x07070200

#define NPI_LNX_ERROR_HAL_GPIO_WAIT_SRDY_SET_POLL_TIMEDOUT			0x07080100
#define NPI_LNX_ERROR_HAL_GPIO_WAIT_SRDY_SET_READ_FAILED			0x07080200

#endif /* NPI_LNX_ERROR_H_ */