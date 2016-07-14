This MBR routine is based on TS' original bootloader.  It is loaded by
the bootrom stored in the companion FPGA, and chainloads an executable
located at the beginning of the first non-fs (0xda) partition.
