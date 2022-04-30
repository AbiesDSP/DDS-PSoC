# Direct Digital Synthesis

This project implements direct digital synthesis using a PSoC 5LP device.
This can be used as an arbitrary waveform genrator.

The DDS component operates entirely in hardware. CPU intervention is only required for configuration.

It consists of a UDB-based phase accumulator and uses DMA transfers to transfer data from an SRAM table to a peripheral.
