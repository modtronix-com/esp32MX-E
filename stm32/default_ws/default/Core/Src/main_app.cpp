/*
 * main_app.cpp
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"         //Must be first include! Contains many includes required by other code
#include "main_app.h"
#include "usart.h"



/* Defines -------------------------------------------------------------------*/
#define TX_BUF_SIZE 128

// Enable test LED on port F0
// IMPORTANT: When enabling the test LED:
// - Ensure pin F0 is configured an an output using the visual "Device Configurator Tool"
// - Set pin F0 label to "testLED" using the visual "Device Configurator Tool"
//#define ENABLE_TEST_LED

// Enable UART debug output.
// IMPORTANT: When enabling this line, ensure USART1 is enables in "Asynchronous"
// mode via the visual "Device Configurator Tool", and configured for 115200
//#define ENABLE_DEBUG_UART


/* Private variables ---------------------------------------------------------*/
uint8_t smPhyReset = 0;
/* Buffer used for reception */
uint8_t txBuf[TX_BUF_SIZE];


/**
 * Converts the upper nibble of a binary value to a hexadecimal ASCII byte.
 * For example, nzHighNibbleToAsciiHex(0xAE) will return 'A'.
 * Same as Microchip "btohexa_high()" function
 *
 * @param b The byte containing the nibble to convert
 *
 * @return The converted ASCII hex character for the given nibble
 */
__STATIC_INLINE uint8_t high_nibble_to_ascii_hex(uint8_t b) {
  b >>= 4;
  return (b > 0x9u) ? b + 'A' - 10 : b + '0';
}

/**
 * Converts the lower nibble of a binary value to a hexadecimal ASCII byte.
 * For example, nzLowNibbleToAsciiHex(0xAE) will return 'E'.
 * Same as Microchip "btohexa_low()" function
 *
 * @param b The byte containing the nibble to convert
 *
 * @return The converted ASCII hex character for the given nibble
 */
__STATIC_INLINE uint8_t low_nibble_to_ascii_hex(uint8_t b) {
  b &= 0x0F;
  return (b > 9u) ? b + 'A' - 10 : b + '0';
}


/**
 * Initialization called before HAL init
 */
void mainAppInitPreHAL(void) {

 // Debug initialization before HAL init
 //My_Debug_Init_Pre_HAL();
}


/**
 * Initialization called after HAL init
 */
void mainAppInit() {
	smPhyReset = 0;						// PHY reset state

	// Reset PHY
	HAL_GPIO_WritePin(resetPHY_GPIO_Port, resetPHY_Pin, GPIO_PIN_RESET);
}

/**
 * Called just before main loop. This will be called after
 * all other initialization.
 */
void mainAppPreLoop() {
	// Turn test LED on
#ifdef ENABLE_TEST_LED
	HAL_GPIO_WritePin(testLED_GPIO_Port, testLED_Pin, GPIO_PIN_SET);
#endif

#ifdef ENABLE_DEBUG_UART
	txBuf[0] = 'H';
	txBuf[1] = 'i';
	txBuf[2] = '\r';
	txBuf[3] = '\n';
	HAL_UART_Transmit(&huart1, &txBuf[0], 4, 100);
#endif
}

/* My Main Loop */
void mainAppLoop() {
	static uint32_t senseCnt = 0;
	static uint32_t tmrSense = 0;
	static uint32_t tmrTemp = 0;

	// Refresh IWDG watchdog down-counter to default value
	//LL_IWDG_ReloadCounter(IWDG);

	// A reset signal is applied to the ESP32
	if (HAL_GPIO_ReadPin(resetESP_GPIO_Port, resetESP_Pin) == 0) {
		smPhyReset = 0;
		senseCnt = 0;

		// Reset PHY
		HAL_GPIO_WritePin(resetPHY_GPIO_Port, resetPHY_Pin, GPIO_PIN_RESET);

		// Turn test LED on
		#ifdef ENABLE_TEST_LED
		HAL_GPIO_WritePin(testLED_GPIO_Port, testLED_Pin, GPIO_PIN_SET);
		#endif
	}
	// No reset signal is applied to the ESP32
	else {
		// Just came out of reset, set state to start looking for toggling GPIO0
		if (smPhyReset == 0) {
			// To save code space, do not use "tmrSense = HAL_GetTick() + 3;". Will be done below on first check of tmrSense
			tmrSense = 0;

			smPhyReset++;
		}
	}

	// Look for toggling GPIO0, which will be when the ESP32 start outputting PHY clock on it
	// If we find 200 pulses within 3ms, we take the PHY out of reset
	if (smPhyReset == 1) {

		// If we have been in this state for longer than tmrSense(10ms), reset
		if (HAL_GetTick() >= tmrSense) {
			#ifdef ENABLE_DEBUG_UART
			txBuf[0] = 'R';	// Fail
			txBuf[1] = 'S';	// Fail
			txBuf[2] = 'T';	// Fail
			txBuf[3] = '\n';
			HAL_UART_Transmit(&huart1, &txBuf[0], 4, 100);
			#endif

			// Put this AFTER UART output above, because it will delay for a long time
			tmrSense = HAL_GetTick() + 3;	// Check again in 3ms
			senseCnt = 0;	// Reset
		}

		// If we have been looking for longer than 1ms
		if(__HAL_GPIO_EXTI_GET_IT(phyOscSense_Pin) != 0) {
			__HAL_GPIO_EXTI_CLEAR_IT(phyOscSense_Pin);
			senseCnt++;

			// Look for 200 clock cycles, should take less than 1ms
			if (senseCnt > 200) {
				// Turn test LED off
				#ifdef ENABLE_TEST_LED
				HAL_GPIO_WritePin(testLED_GPIO_Port, testLED_Pin, GPIO_PIN_RESET);
				#endif

				// Enable PHY
				HAL_GPIO_WritePin(resetPHY_GPIO_Port, resetPHY_Pin, GPIO_PIN_SET);

				#ifdef ENABLE_DEBUG_UART
				txBuf[0] = 'P';
				txBuf[1] = 'H';
				txBuf[2] = 'Y';
				txBuf[3] = '\n';
				HAL_UART_Transmit(&huart1, &txBuf[0], 4, 100);
				#endif

				smPhyReset++;
			}
		}
	}
	else if (smPhyReset == 2) {

		if(__HAL_GPIO_EXTI_GET_IT(phyOscSense_Pin) != 0) {
			__HAL_GPIO_EXTI_CLEAR_IT(phyOscSense_Pin);
			senseCnt++;
		}

		if (HAL_GetTick() > tmrTemp) {
			tmrTemp = HAL_GetTick() + 250;	// Every second

			#ifdef ENABLE_DEBUG_UART
			txBuf[0] = high_nibble_to_ascii_hex((uint8_t)senseCnt);
			txBuf[1] = low_nibble_to_ascii_hex((uint8_t)senseCnt);
			txBuf[2] = '\n';
			HAL_UART_Transmit(&huart1, &txBuf[0], 3, 100);
			#endif
		}
	}
}



