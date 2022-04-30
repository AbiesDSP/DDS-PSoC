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

void `$INSTANCE_NAME`_Start(void)
{
    `$INSTANCE_NAME`_Count7_Start();
}

void `$INSTANCE_NAME`_Enable(uint8_t state)
{
    `$INSTANCE_NAME`_Ctl_Write(state);
}

void `$INSTANCE_NAME`_SetPhaseInc(uint16_t phase_inc)
{
    CY_SET_REG16(`$INSTANCE_NAME`_Accum_D0_PTR, phase_inc);
}

void `$INSTANCE_NAME`_SetShiftAmount(uint8_t amount)
{
    `$INSTANCE_NAME`_Count7_WritePeriod(amount);
}

void `$INSTANCE_NAME`_SetBaseAddress(uint16_t address)
{
    // Setting the base address resets the register.
    CY_SET_REG16(`$INSTANCE_NAME`_Accum_D1_PTR, address);
    CY_SET_REG16(`$INSTANCE_NAME`_Accum_A1_PTR, address);
}

void `$INSTANCE_NAME`_SetPhase(uint16_t phase)
{
    CY_SET_REG16(`$INSTANCE_NAME`_Accum_A0_PTR, phase);
}