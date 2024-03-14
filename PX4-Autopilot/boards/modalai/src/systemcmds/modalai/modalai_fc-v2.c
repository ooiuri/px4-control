#include <px4_platform_common/module.h>


#include "chip.h"
#include "stm32_gpio.h"
#include "board_config.h"

#include <nuttx/board.h>
#include <arch/board/board.h>

// v2
#ifdef CONFIG_ARCH_CHIP_STM32H753II		// chip on M0087


#include "modalai_fc-v2.h"

void modalai_print_usage_v2(void)
{
	PRINT_MODULE_DESCRIPTION("ModalAI Test utility\n");

	PRINT_MODULE_USAGE_NAME_SIMPLE("modalai", "command");

	PRINT_MODULE_USAGE_COMMAND_DESCR("led", "LED Test");
	PRINT_MODULE_USAGE_COMMAND_DESCR("con", "Connector Output Test (as GPIO)");
	PRINT_MODULE_USAGE_COMMAND_DESCR("buzz", "Automated buzz out test");
	PRINT_MODULE_USAGE_COMMAND_DESCR("detect", "Detect board type");
	return;
}
void modalai_print_usage_con_gpio_test_v2(void)
{
	return;
}
int modalai_con_gpio_test_v2(uint8_t con, uint8_t pin, bool state)
{
	return 0;
}
int modalai_led_test_v2(void)
{
	PX4_INFO("Running led test");

	stm32_configgpio(GPIO_nLED_RED);
	stm32_configgpio(GPIO_nLED_GREEN);
	stm32_configgpio(GPIO_nLED_BLUE);

	int i = 0;

	for (i = 0; i < 3; i++) {
		usleep(1000 * 100);
		stm32_gpiowrite(GPIO_nLED_RED, false);

		usleep(1000 * 100);
		stm32_gpiowrite(GPIO_nLED_RED, true);

		usleep(1000 * 100);
		stm32_gpiowrite(GPIO_nLED_GREEN, false);
		usleep(1000 * 100);
		stm32_gpiowrite(GPIO_nLED_GREEN, true);

		usleep(1000 * 100);
		stm32_gpiowrite(GPIO_nLED_BLUE, false);
		usleep(1000 * 100);
		stm32_gpiowrite(GPIO_nLED_BLUE, true);
	}

	return 0;
}

bool test_pair(uint32_t output_pin, uint32_t input_pin)
{

	bool state = false;

	stm32_gpiowrite(output_pin, true);
	usleep(1000 * 10);
	state = stm32_gpioread(input_pin);

	if (state != true) {
		return false;
	}

	usleep(1000 * 10);

	stm32_gpiowrite(output_pin, false);
	usleep(1000 * 10);
	state = stm32_gpioread(input_pin);

	if (state != false) {
		return false;
	}

	return true;
}

int modalai_buzz_test_v2(eHW_TYPE hw_type)
{
	PX4_INFO("test: buzz");
	usleep(1000 * 100 * 10);

	if (hw_type == eM0079) {
		PX4_INFO("Using M0079 config");

	} else if (hw_type == eM0087) {
		PX4_INFO("Using M0087 config");

	} else {
		return -1;

	}

	if (hw_type == eM0079) {
		//
		//
		//
		PX4_INFO(">> Testing J1");
		stm32_configgpio(M0079_J1_PIN_2_OUT); // 2-3
		stm32_configgpio(M0079_J1_PIN_3_IN);  // 3-2
		stm32_configgpio(M0079_J1_PIN_4_OUT); // 4-5
		stm32_configgpio(M0079_J1_PIN_5_IN);  // 5-4

		if (test_pair(M0079_J1_PIN_2_OUT, M0079_J1_PIN_3_IN)) {
			PX4_INFO("PASS: M0079_J1_PIN_2_OUT M0079_J1_PIN_3_IN");

		} else {
			PX4_ERR("FAIL: M0079_J1_PIN_2_OUT M0079_J1_PIN_3_IN");
		}

		if (test_pair(M0079_J1_PIN_4_OUT, M0079_J1_PIN_5_IN)) {
			PX4_INFO("PASS: M0079_J1_PIN_4_OUT M0079_J1_PIN_5_IN");

		} else {
			PX4_ERR("FAIL: M0079_J1_PIN_4_OUT M0079_J1_PIN_5_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J5");
		stm32_configgpio(M0079_J5_PIN_2_OUT); // 2-4
		stm32_configgpio(M0079_J5_PIN_3_OUT); // 3-5
		stm32_configgpio(M0079_J5_PIN_4_IN);  // 4-2
		stm32_configgpio(M0079_J5_PIN_5_IN);  // 5-3

		if (test_pair(M0079_J5_PIN_2_OUT, M0079_J5_PIN_4_IN)) {
			PX4_INFO("PASS: M0079_J5_PIN_2_OUT M0079_J5_PIN_4_IN");

		} else {
			PX4_ERR("FAIL: M0079_J5_PIN_2_OUT M0079_J5_PIN_4_IN");
		}

		if (test_pair(M0079_J5_PIN_3_OUT, M0079_J5_PIN_5_IN)) {
			PX4_INFO("PASS: M0079_J5_PIN_3_OUT M0079_J5_PIN_5_IN");

		} else {
			PX4_ERR("FAIL: M0079_J5_PIN_3_OUT M0079_J5_PIN_5_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J7");
		stm32_configgpio(M0079_J7_PIN_2_OUT); // 2-6
		stm32_configgpio(M0079_J7_PIN_3_OUT); // 3-7
		stm32_configgpio(M0079_J7_PIN_4_OUT); // 4-8
		stm32_configgpio(M0079_J7_PIN_5_OUT); // 5-9
		stm32_configgpio(M0079_J7_PIN_6_IN); // 6-2
		stm32_configgpio(M0079_J7_PIN_7_IN); // 7-3
		stm32_configgpio(M0079_J7_PIN_8_IN); // 8-4
		stm32_configgpio(M0079_J7_PIN_9_IN); // 9-5

		if (test_pair(M0079_J7_PIN_2_OUT, M0079_J7_PIN_6_IN)) {
			PX4_INFO("PASS: M0079_J7_PIN_2_OUT M0079_J7_PIN_6_IN");

		} else {
			PX4_ERR("FAIL: M0079_J7_PIN_2_OUT M0079_J7_PIN_6_IN");
		}

		if (test_pair(M0079_J7_PIN_3_OUT, M0079_J7_PIN_7_IN)) {
			PX4_INFO("PASS: M0079_J7_PIN_3_OUT M0079_J7_PIN_7_IN");

		} else {
			PX4_ERR("FAIL: M0079_J7_PIN_3_OUT M0079_J7_PIN_7_IN");
		}

		if (test_pair(M0079_J7_PIN_4_OUT, M0079_J7_PIN_8_IN)) {
			PX4_INFO("PASS: M0079_J7_PIN_4_OUT M0079_J7_PIN_8_IN");

		} else {
			PX4_ERR("FAIL: M0079_J7_PIN_4_OUT M0079_J7_PIN_8_IN");
		}

		if (test_pair(M0079_J7_PIN_5_OUT, M0079_J7_PIN_9_IN)) {
			PX4_INFO("PASS: M0079_J7_PIN_5_OUT M0079_J7_PIN_9_IN");

		} else {
			PX4_ERR("FAIL: M0079_J7_PIN_5_OUT M0079_J7_PIN_9_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J10");
		stm32_configgpio(M0079_J10_PIN_2_OUT); // 2-4
		stm32_configgpio(M0079_J10_PIN_3_OUT); // 3-5
		stm32_configgpio(M0079_J10_PIN_4_IN);  // 4-2
		stm32_configgpio(M0079_J10_PIN_5_IN);  // 5-3

		if (test_pair(M0079_J10_PIN_2_OUT, M0079_J10_PIN_4_IN)) {
			PX4_INFO("PASS: M0079_J10_PIN_2_OUT M0079_J10_PIN_4_IN");

		} else {
			PX4_ERR("FAIL: M0079_J10_PIN_2_OUT M0079_J10_PIN_4_IN");
		}

		if (test_pair(M0079_J10_PIN_3_OUT, M0079_J10_PIN_5_IN)) {
			PX4_INFO("PASS: M0079_J10_PIN_3_OUT M0079_J10_PIN_5_IN");

		} else {
			PX4_ERR("FAIL: M0079_J10_PIN_3_OUT M0079_J10_PIN_5_IN");
		}


		//
		//
		//
		PX4_INFO(">> Testing J13");
		stm32_configgpio(M0079_J12_PIN_2_OUT); // 2-3
		stm32_configgpio(M0079_J12_PIN_3_IN);  // 3-2

		if (test_pair(M0079_J12_PIN_2_OUT, M0079_J12_PIN_3_IN)) {
			PX4_INFO("PASS: M0079_J12_PIN_2 M0079_J12_PIN_3");

		} else {
			PX4_ERR("FAIL: M0079_J12_PIN_2 M0079_J12_PIN_3");
		}


	} else if (hw_type == eM0087) {
		//
		//
		//
		PX4_INFO(">> Testing J1");
		stm32_configgpio(M0087_J1_PIN_2_IN);    // 2-4
		stm32_configgpio(M0087_J1_PIN_3_OUT);   // 3-5
		stm32_configgpio(M0087_J1_PIN_4_OUT);   // 4-2
		stm32_configgpio(M0087_J1_PIN_5_IN);    // 5-3

		if (test_pair(M0087_J1_PIN_4_OUT, M0087_J1_PIN_2_IN)) {
			PX4_INFO("PASS: M0087_J1_PIN_4_OUT M0087_J1_PIN_2_IN");

		} else {
			PX4_ERR("FAIL: M0087_J1_PIN_4_OUT M0087_J1_PIN_2_IN");
		}

		if (test_pair(M0087_J1_PIN_3_OUT, M0087_J1_PIN_5_IN)) {
			PX4_INFO("PASS: M0087_J1_PIN_3_OUT M0087_J1_PIN_5_IN");

		} else {
			PX4_ERR("FAIL: M0087_J1_PIN_3_OUT M0087_J1_PIN_5_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J5");
		stm32_configgpio(M0087_J5_PIN_2_OUT); // 2-4
		stm32_configgpio(M0087_J5_PIN_3_OUT); // 3-5
		stm32_configgpio(M0087_J5_PIN_4_IN);  // 4-2
		stm32_configgpio(M0087_J5_PIN_5_IN);  // 5-3

		if (test_pair(M0087_J5_PIN_2_OUT, M0087_J5_PIN_4_IN)) {
			PX4_INFO("PASS: M0087_J5_PIN_2_OUT M0087_J5_PIN_4_IN");

		} else {
			PX4_ERR("FAIL: M0087_J5_PIN_2_OUT M0087_J5_PIN_4_IN");
		}

		if (test_pair(M0087_J5_PIN_3_OUT, M0087_J5_PIN_5_IN)) {
			PX4_INFO("PASS: M0087_J5_PIN_3_OUT M0087_J5_PIN_5_IN");

		} else {
			PX4_ERR("FAIL: M0087_J5_PIN_3_OUT M0087_J5_PIN_5_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J7");
		stm32_configgpio(M0087_J7_PIN_2_OUT); // 2-6
		stm32_configgpio(M0087_J7_PIN_3_OUT); // 3-7
		stm32_configgpio(M0087_J7_PIN_4_OUT); // 4-8
		stm32_configgpio(M0087_J7_PIN_5_OUT); // 5-9
		stm32_configgpio(M0087_J7_PIN_6_IN); // 6-2
		stm32_configgpio(M0087_J7_PIN_7_IN); // 7-3
		stm32_configgpio(M0087_J7_PIN_8_IN); // 8-4
		stm32_configgpio(M0087_J7_PIN_9_IN); // 9-5

		if (test_pair(M0087_J7_PIN_2_OUT, M0087_J7_PIN_6_IN)) {
			PX4_INFO("PASS: M0087_J7_PIN_2_OUT M0087_J7_PIN_6_IN");

		} else {
			PX4_ERR("FAIL: M0087_J7_PIN_2_OUT M0087_J7_PIN_6_IN");
		}

		if (test_pair(M0087_J7_PIN_3_OUT, M0087_J7_PIN_7_IN)) {
			PX4_INFO("PASS: M0087_J7_PIN_3_OUT M0087_J7_PIN_7_IN");

		} else {
			PX4_ERR("FAIL: M0087_J7_PIN_3_OUT M0087_J7_PIN_7_IN");
		}

		if (test_pair(M0087_J7_PIN_4_OUT, M0087_J7_PIN_8_IN)) {
			PX4_INFO("PASS: M0087_J7_PIN_4_OUT M0087_J7_PIN_8_IN");

		} else {
			PX4_ERR("FAIL: M0087_J7_PIN_4_OUT M0087_J7_PIN_8_IN");
		}

		if (test_pair(M0087_J7_PIN_5_OUT, M0087_J7_PIN_9_IN)) {
			PX4_INFO("PASS: M0087_J7_PIN_5_OUT M0087_J7_PIN_9_IN");

		} else {
			PX4_ERR("FAIL: M0087_J7_PIN_5_OUT M0087_J7_PIN_9_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J10");
		stm32_configgpio(M0087_J10_PIN_2_OUT); // 2-4
		stm32_configgpio(M0087_J10_PIN_3_OUT); // 3-5
		stm32_configgpio(M0087_J10_PIN_4_IN);  // 4-2
		stm32_configgpio(M0087_J10_PIN_5_IN);  // 5-3

		if (test_pair(M0087_J10_PIN_2_OUT, M0087_J10_PIN_4_IN)) {
			PX4_INFO("PASS: M0087_J10_PIN_2_OUT M0087_J10_PIN_4_IN");

		} else {
			PX4_ERR("FAIL: M0087_J10_PIN_2_OUT M0087_J10_PIN_4_IN");
		}

		if (test_pair(M0087_J10_PIN_3_OUT, M0087_J10_PIN_5_IN)) {
			PX4_INFO("PASS: M0087_J10_PIN_3_OUT M0087_J10_PIN_5_IN");

		} else {
			PX4_ERR("FAIL: M0087_J10_PIN_3_OUT M0087_J10_PIN_5_IN");
		}


		//
		//
		//
		PX4_INFO(">> Testing J12");
		stm32_configgpio(M0087_J12_PIN_2_OUT); // 2-3
		stm32_configgpio(M0087_J12_PIN_3_IN);  // 3-2

		if (test_pair(M0087_J12_PIN_2_OUT, M0087_J12_PIN_3_IN)) {
			PX4_INFO("PASS: M0087_J12_PIN_2_OUT M0087_J12_PIN_3_IN");

		} else {
			PX4_ERR("FAIL: M0087_J12_PIN_2_OUT M0087_J12_PIN_3_IN");
		}

		//
		//
		//
		PX4_INFO(">> Testing J14");
		stm32_configgpio(M0087_J14_PIN_2_OUT);
		stm32_configgpio(M0087_J14_PIN_3_OUT);
		stm32_configgpio(M0087_J14_PIN_4_OUT);
		stm32_configgpio(M0087_J14_PIN_5_OUT);
		stm32_configgpio(M0087_J14_PIN_6_OUT);
		stm32_configgpio(M0087_J14_PIN_7_IN);
		stm32_configgpio(M0087_J14_PIN_8_IN);
		stm32_configgpio(M0087_J14_PIN_9_IN);
		stm32_configgpio(M0087_J14_PIN_10_IN);
		stm32_configgpio(M0087_J14_PIN_11_IN);

		if (test_pair(M0087_J14_PIN_2_OUT, M0087_J14_PIN_7_IN)) {
			PX4_INFO("PASS: M0087_J14_PIN_2_OUT M0087_J14_PIN_7_IN");

		} else {
			PX4_ERR("FAIL: M0087_J14_PIN_2_OUT M0087_J14_PIN_7_IN");
		}

		if (test_pair(M0087_J14_PIN_3_OUT, M0087_J14_PIN_8_IN)) {
			PX4_INFO("PASS: M0087_J14_PIN_3_OUT M0087_J14_PIN_8_IN");

		} else {
			PX4_ERR("FAIL: M0087_J14_PIN_3_OUT M0087_J14_PIN_8_IN");
		}

		if (test_pair(M0087_J14_PIN_4_OUT, M0087_J14_PIN_9_IN)) {
			PX4_INFO("PASS: M0087_J14_PIN_4_OUT M0087_J14_PIN_9_IN");

		} else {
			PX4_ERR("FAIL: M0087_J14_PIN_4_OUT M0087_J14_PIN_9_IN");
		}

		if (test_pair(M0087_J14_PIN_5_OUT, M0087_J14_PIN_10_IN)) {
			PX4_INFO("PASS: M0087_J14_PIN_5_OUT M0087_J14_PIN_10_IN");

		} else {
			PX4_ERR("FAIL: M0087_J14_PIN_5_OUT M0087_J14_PIN_10_IN");
		}

		if (test_pair(M0087_J14_PIN_6_OUT, M0087_J14_PIN_11_IN)) {
			PX4_INFO("PASS: M0087_J14_PIN_6_OUT M0087_J14_PIN_11_IN");

		} else {
			PX4_ERR("FAIL: M0087_J14_PIN_6_OUT M0087_J14_PIN_11_IN");
		}

	}

	return 0;
}

int modalai_hw_detect_v2(eHW_TYPE hw_type)
{
	int result = -1;

	if (hw_type == eM0079) {
		PX4_INFO("V230 - M0079");
		result = 0;

	} else if (hw_type == eM0087) {
		PX4_INFO("V230 - M0087");
		result = 0;

	} else {
		PX4_ERR("Unknown hardware");
	}

	return result;
}

#endif //CONFIG_ARCH_CHIP_STM32H753II
