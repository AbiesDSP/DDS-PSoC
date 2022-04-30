/*
    Copyright (c) 2022 Frank Sodari

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_DMALUT_dma.h"
#include "`$INSTANCE_NAME`_DMAPhase_dma.h"
#include "`$INSTANCE_NAME`_PhaseAccum.h"

// Find log2 assuming that the input is a power of two.
static inline uint8_t quick_log2(uint16_t size)
{
    uint8_t base = 16;

    while (base--)
    {
        if (size >> base == 0x01)
        {
            break;
        }
    }

    return base;
}

static uint8_t `$INSTANCE_NAME`_lut_dma_ch;
static uint8_t `$INSTANCE_NAME`_lut_dma_td;
static uint8_t `$INSTANCE_NAME`_phase_dma_ch;
static uint8_t `$INSTANCE_NAME`_phase_dma_td;

void `$INSTANCE_NAME`_Start(uint8_t *lut, uint16_t size, uint32_t dest_addr)
{
    // Copying from sram to destination. Destination can be SRAM, peripheral, etc.
    `$INSTANCE_NAME`_lut_dma_ch = `$INSTANCE_NAME`_DMALUT_DmaInitialize(1, 1, HI16(CYDEV_SRAM_BASE), HI16(dest_addr));
    `$INSTANCE_NAME`_lut_dma_td = CyDmaTdAllocate();

    // The Phase DMA will write the lut address into the LUT DMA TD's source address.
    reg16 *td_src = (reg16 *)&CY_DMA_TDMEM_STRUCT_PTR[`$INSTANCE_NAME`_lut_dma_td].TD1[0u];

    // Copy from the phase accumulator to the TD source address.
    `$INSTANCE_NAME`_phase_dma_ch = `$INSTANCE_NAME`_DMAPhase_DmaInitialize(2, 1, HI16(CYDEV_PERIPH_BASE), HI16((uint32)td_src));
    `$INSTANCE_NAME`_phase_dma_td = CyDmaTdAllocate();

    // Every request transfers 1 byte.
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_lut_dma_td, 1, `$INSTANCE_NAME`_lut_dma_td, `$INSTANCE_NAME`_DMALUT__TD_TERMOUT_EN);
    CyDmaTdSetAddress(`$INSTANCE_NAME`_lut_dma_td, LO16((uint32)lut), LO16(dest_addr));
    CyDmaChSetInitialTd(`$INSTANCE_NAME`_lut_dma_ch, `$INSTANCE_NAME`_lut_dma_td);

    // Copy address from phase accumulator to the LUT DMA TD's source address.
    // The phase accumulator nrq will trigger the next dma transfer.
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_phase_dma_td, 2, `$INSTANCE_NAME`_phase_dma_td, `$INSTANCE_NAME`_DMAPhase__TD_TERMOUT_EN);
    CyDmaTdSetAddress(`$INSTANCE_NAME`_phase_dma_td, LO16((uint32)`$INSTANCE_NAME`_PhaseAccum_Accum_F1_PTR), LO16((uint32)td_src));
    CyDmaChSetInitialTd(`$INSTANCE_NAME`_phase_dma_ch, `$INSTANCE_NAME`_phase_dma_td);

    // Maximum LUT depth is 15 bits.
    uint8_t base = quick_log2(size);
    uint8_t shift_amount = 15 - base;

    `$INSTANCE_NAME`_PhaseAccum_Start();
    `$INSTANCE_NAME`_PhaseAccum_SetBaseAddress(LO16((uint32)lut));
    `$INSTANCE_NAME`_PhaseAccum_SetShiftAmount(shift_amount);

    CyDmaChEnable(`$INSTANCE_NAME`_lut_dma_ch, 1);
    CyDmaChEnable(`$INSTANCE_NAME`_phase_dma_ch, 1);
}

void `$INSTANCE_NAME`_SetPhaseInc(uint16_t phase_inc)
{
    `$INSTANCE_NAME`_PhaseAccum_SetPhaseInc(phase_inc);
}

void `$INSTANCE_NAME`_Enable()
{
    `$INSTANCE_NAME`_PhaseAccum_Enable(1);
}

void `$INSTANCE_NAME`_Disable()
{
    `$INSTANCE_NAME`_PhaseAccum_Enable(0);
}
