/* =
 * matrix_keypad.c
 *
 *  Created on: Feb 17, 2024
 *      Author: M.W Laptop
 */
#include "../matrix_keypad/matrix_keypad.h"

static void Hardware_Interface_Initialize(Keypad_Matrix_t *kp) {
	GPIO_InitTypeDef GP = { .Mode = GPIO_MODE_OUTPUT_PP, // Output Push Pull Mode
			.Speed = GPIO_SPEED_LOW };
	uint32_t Pins = 0;
	for (int x = 0; x < kp->Rows; x++) {
		Pins |= 1 << ((kp->Row_Start_Pin) + x);
	};
	GP.Pin = Pins;
	HAL_GPIO_Init(kp->Row_Port, &GP);

	kp->Output_Mask = Pins;
	GP.Mode = GPIO_MODE_INPUT;
	GP.Pull = GPIO_PULLDOWN;
	Pins = 0;
	for (int x = 0; x < kp->Columns; x++) {
		Pins |= 1 << ((kp->Column_Start_Pin) + x);
	};
	GP.Pin = Pins;
	HAL_GPIO_Init(kp->Column_Port, &GP);
	kp->Input_Mask = Pins;
}

static void Hardware_Generate_Delay(uint16_t delay) {
	HAL_Delay(delay);
}

static uint8_t Hardware_Get_Inputs(Keypad_Matrix_t *kp) {
	uint32_t m = kp->Column_Port->IDR & kp->Input_Mask;
	m >>= kp->Column_Start_Pin;
	return (uint8_t) m;

}

static void Hardware_Set_Outputs(Keypad_Matrix_t *kp, uint8_t OutputStatus) {
	kp->Row_Port->ODR &= ~(kp->Output_Mask);
	kp->Row_Port->ODR |= ((uint32_t) OutputStatus) << kp->Row_Start_Pin;
}

void Keypad_Matrix_init(Keypad_Matrix_t *kp) {
	Hardware_Interface_Initialize(kp);
	Hardware_Set_Outputs(kp, 0);
}

void Keypad_Matrix_Refresh(Keypad_Matrix_t *kp) {
	kp->Button_Status = 0;
	uint8_t scan = 0b00000001;
	for (uint8_t x = 0; x < kp->Rows; x++) {
		Hardware_Set_Outputs(kp, scan);
		Hardware_Generate_Delay(1);
		kp->Button_Status |= Hardware_Get_Inputs(kp) << (x * kp->Columns);
		scan <<= 1;
	}
}

uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t *kp, uint8_t key) {
	if (kp->Button_Status & (1 << key)) {
		return 1;
	} else {
		return 0;
	}
}

