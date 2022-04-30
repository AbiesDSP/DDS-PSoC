#include "project.h"
#include <math.h>
#include <stdlib.h>

#define ever (;;)

// The size of the Look-Up-Table must be a power of two.
#define LUT_SIZE 2048
uint8_t lut[LUT_SIZE];

CY_ISR_PROTO(phase_update_isr);

int main(void)
{
    CyGlobalIntEnable;

    // Fill the table with one period of cosine.
    double tscale = (2.0 * M_PI) / LUT_SIZE;
    for (int i = 0; i < LUT_SIZE; i++)
    {
        lut[i] = (-1 * cos(i * tscale) + 1) * 127.5;
    }

    // dds frequency = fsclk * phase_inc / 65536
    uint32_t fbus = 24e6;
    uint32_t fsclk = 10e3;

    // Target frequency.
    double dds_frequency = 1;

    // Configure sample clock.
    uint16_t clkdiv = fbus / fsclk;
    fsclk = fbus / clkdiv; // Set it to actual value.
    SclkClk_SetDivider(clkdiv);

    // Configure phase increment.
    uint16_t phase_inc = (dds_frequency * 65536) / fsclk;

    PWM_Start();

    // Write the dds output to the PWM compare register.
    DDS_Start(lut, LUT_SIZE, (uint32)PWM_COMPARE1_LSB_PTR);
    DDS_SetPhaseInc(phase_inc);

    DDS_Enable();

    for ever
    {
    }
}

CY_ISR(phase_update_isr)
{
}
