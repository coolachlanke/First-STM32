#include <stdint.h>

int main(void) {
    // Enable GPIOC clock
    volatile uint32_t *rcc_apb2enr = (volatile uint32_t *)0x40021018;
    *rcc_apb2enr |= (1 << 4); // Set IOPCEN (bit 4)

    // Configure PC13 as output push-pull, 10 MHz
    volatile uint32_t *gpioc_crh = (volatile uint32_t *)0x40011004;
    *gpioc_crh &= ~(0xF << 20); // Clear MODE13 and CNF13
    *gpioc_crh |= (0x1 << 20); // MODE13 = 01 (output 10 MHz), CNF13 = 00 (push-pull)

    // Main loop: toggle PC13
    volatile uint32_t *gpioc_odr = (volatile uint32_t *)0x4001100C;
    while(1) {
        *gpioc_odr |= (1 << 13);  // Set PC13 (LED ON)
        for (uint32_t i = 0; i < 50000; ++i) {}    // Pseudo-delay function
        *gpioc_odr &= ~(1 << 13);  // Reset PC13 (LED OFF)
        for (uint32_t i = 0; i < 50000; ++i) {}    // Pseudo-delay function
    }
}
