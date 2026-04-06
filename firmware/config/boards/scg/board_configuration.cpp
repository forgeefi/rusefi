/**
 * @file board_configuration.cpp
 */

#include "pch.h"
#include "board_overrides.h"

static void setDefaultFrankensoStepperIdleParameters() {
	engineConfiguration->idle.stepperDirectionPin = Gpio::C9;
	engineConfiguration->idle.stepperStepPin = Gpio::C8;
	engineConfiguration->stepperEnablePin = Gpio::A8;
	engineConfiguration->idleStepperReactionTime = 10;
	engineConfiguration->idleStepperTotalSteps = 150;
}

static void setCanFrankensoDefaults() {
	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;
}

Gpio getWarningLedPin() {
	return Gpio::C11;
}

Gpio getCommsLedPin() {
	return Gpio::C10;
}

Gpio getRunningLedPin() {
	return Gpio::C12;
}

/**
 * @brief	Hardware board-specific default configuration (GPIO pins, ADC channels, SPI configs etc.)
 */
static void scg_DefaultConfiguration() {
	setDefaultFrankensoStepperIdleParameters();
	setCanFrankensoDefaults();

        engineConfiguration->clt.config.bias_resistor = 2490;
        engineConfiguration->iat.config.bias_resistor = 2490;

	engineConfiguration->binarySerialTxPin = Gpio::Unassigned;
	engineConfiguration->binarySerialRxPin = Gpio::Unassigned;

        // Disable ETBs
        engineConfiguration->etbFunctions[0] = dc_function_e::DC_None;
        engineConfiguration->etbFunctions[1] = dc_function_e::DC_None;

	engineConfiguration->vbattAdcChannel = EFI_ADC_0;
	engineConfiguration->vbattDividerCoeff = 7.2f;
	engineConfiguration->adcVcc = 3.3f;
	engineConfiguration->analogInputDividerCoefficient = 1.66f;

	engineConfiguration->map.sensor.hwChannel = EFI_ADC_1;
	engineConfiguration->clt.adcChannel = EFI_ADC_2;
	engineConfiguration->iat.adcChannel = EFI_ADC_3;
	engineConfiguration->afr.hwChannel = EFI_ADC_4;

	engineConfiguration->triggerSimulatorPins[0] = Gpio::Unassigned;
	engineConfiguration->triggerSimulatorPins[1] = Gpio::Unassigned;

	//engineConfiguration->triggerInputPins[0] = Gpio::C6;
//	engineConfiguration->triggerInputPins[1] = Gpio::A5;

	// set this to SPI_DEVICE_3 to enable stimulation
	//engineConfiguration->digitalPotentiometerSpiDevice = SPI_DEVICE_3;
	engineConfiguration->digitalPotentiometerChipSelect[0] = Gpio::Unassigned;
	engineConfiguration->digitalPotentiometerChipSelect[1] = Gpio::Unassigned;
	engineConfiguration->digitalPotentiometerChipSelect[2] = Gpio::Unassigned;
	engineConfiguration->digitalPotentiometerChipSelect[3] = Gpio::Unassigned;

	engineConfiguration->spi1mosiPin = Gpio::B5;
	engineConfiguration->spi1misoPin = Gpio::B4;
	engineConfiguration->spi1sckPin = Gpio::B3; // please note that this pin is also SWO/SWD - Single Wire debug Output

	engineConfiguration->spi2mosiPin = Gpio::B12;
	engineConfiguration->spi2misoPin = Gpio::B11;
	engineConfiguration->spi2sckPin = Gpio::B10;

	engineConfiguration->spi3mosiPin = Gpio::B5;
	engineConfiguration->spi3misoPin = Gpio::B4;
	engineConfiguration->spi3sckPin = Gpio::B3;



#if EFI_FILE_LOGGING
	setDefaultSdCardParameters();
#endif /* EFI_FILE_LOGGING */

	engineConfiguration->is_enabled_spi_1 = true;
	engineConfiguration->is_enabled_spi_2 = true;
	engineConfiguration->is_enabled_spi_3 = false;
}

void scg_boardInitHardware() {
#ifndef EFI_BOOTLOADER
	// todo: add to more appropriate location?
	addConsoleAction("injinfo", [](){
	    efiPrintf("injinfo index=%d", engine->fuelComputer.brokenInjector);
	});
#endif // EFI_BOOTLOADER
}

void setup_custom_board_overrides() {
	custom_board_InitHardware = scg_boardInitHardware;
	custom_board_DefaultConfiguration = scg_DefaultConfiguration;
}
