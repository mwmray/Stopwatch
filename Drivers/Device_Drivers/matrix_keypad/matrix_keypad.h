#ifndef CMSIS_DEVICE_DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_
#define CMSIS_DEVICE_DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>

/// @struct Keypad_str
/// @brief
///
typedef struct Keypad_str {
	///
	/// attribute : keypad rows
	uint8_t Rows;
	///
	/// attribute : keypad rows
	uint8_t Columns;
	///
	/// user data
	/// holds the status of button
	uint32_t Button_Status;
	///
	/// pheripheral configuration

	GPIO_TypeDef *Row_Port;
	uint8_t Row_Start_Pin;
	GPIO_TypeDef *Column_Port;
	uint8_t Column_Start_Pin;
	uint32_t Input_Mask;
	uint32_t Output_Mask;

} Keypad_Matrix_t;

/// @fn void Keypad_Matrix_init(Keypad_Matrix_t*)
/// @brief
///
/// @param kp
void Keypad_Matrix_init(Keypad_Matrix_t *kp);

/// @fn void Keypad_Matrix_Refresh(Keypad_Matrix_t*)
/// @brief
///
/// @param kp
void Keypad_Matrix_Refresh(Keypad_Matrix_t *kp);

/// @fn uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t*, uint8_t)
/// @brief
///
/// @param kp
/// @param key
/// @return
uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t *kp, uint8_t key);

#endif

