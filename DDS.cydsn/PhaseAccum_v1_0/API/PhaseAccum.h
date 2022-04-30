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

#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_defs.h"

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Enable(uint8_t state);
void `$INSTANCE_NAME`_SetPhaseInc(uint16_t phase_inc);
void `$INSTANCE_NAME`_SetShiftAmount(uint8_t amount);
void `$INSTANCE_NAME`_SetBaseAddress(uint16_t address);
void `$INSTANCE_NAME`_SetPhase(uint16_t phase);

#endif
