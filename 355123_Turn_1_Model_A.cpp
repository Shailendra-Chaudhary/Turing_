
#include <stm32f10x.h>

// Define the address for persistent memory in flash
#define PERSISTENT_MEMORY_ADDRESS   (0x08010000)  // Starting address of flash page 1 (assuming page 0 is bootloader)

// Example data to be stored persistently
const uint16_t DEFAULT_VALUE = 1000;
uint16_t savedData = DEFAULT_VALUE;

void readPersistentData() {
    FLASH_Unlock();
    // Erase the sector if it contains data (Note: This is a slow operation and should be optimized in production code)
    if (*(uint16_t *)PERSISTENT_MEMORY_ADDRESS != 0) {
        FLASH_ErasePage(PERSISTENT_MEMORY_ADDRESS >> 12);
    }
    FLASH_ProgramHalfWord(PERSISTENT_MEMORY_ADDRESS, savedData);
    FLASH_Lock();
    // Read the data back
    savedData = *(uint16_t *)PERSISTENT_MEMORY_ADDRESS;
}

void writePersistentData() {
    FLASH_Unlock();
    // Erase the sector if it contains data (Note: This is a slow operation and should be optimized in production code)
    if (*(uint16_t *)PERSISTENT_MEMORY_ADDRESS != savedData) {
        FLASH_ErasePage(PERSISTENT_MEMORY_ADDRESS >> 12);
    }
    FLASH_ProgramHalfWord(PERSISTENT_MEMORY_ADDRESS, savedData);
    FLASH_Lock();
}

int main() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Check if data exists in persistent memory
    readPersistentData();

    // Example data modification
    savedData++;

    // Write the modified data to persistent memory
    writePersistentData();

    // Blink LED to indicate data save
    while (1) {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        HAL_Delay(500);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        HAL_Delay(500);
    }

    return 0;
}
