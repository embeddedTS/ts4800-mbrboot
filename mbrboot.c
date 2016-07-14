/*
 *     Copyright (C) 2009, Technologic Systems Inc.
 *     Copyright (C) 2016, Savoir-faire Linux Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define MBR_LOAD_ADDR 0x96000000
#define OS_LOAD_ADDR 0x90008000

#define PARTITION_TABLE_OFFSET (MBR_LOAD_ADDR + 446)
#define PARTITION_TABLE_ENTRY_N 4
#define PARTITION_TABLE_ENTRY_LEN 16
#define PARTITION_TYPE_NONFS_DATA 0xda

void mbrboot(void *(unsigned int, char*, int),
		void *(char *),
		void __attribute__((unused)) *(void))
		__attribute__((noreturn));

void mbrboot(void *read(unsigned int, char*, int),
		void *ser_puts(char *),
		void __attribute__((unused)) *clock_max_func(void))
{
	void (*os)(void) = (void *) OS_LOAD_ADDR;
	unsigned char *part = (unsigned char *) PARTITION_TABLE_OFFSET;
	int i;

	ser_puts("ts4800-mbrboot: searching for boot partition.. ");

	for (i = 0; i < PARTITION_TABLE_ENTRY_N; i++) {
		if (part[4] == PARTITION_TYPE_NONFS_DATA) {
			/* get partition offset and size from entry and load */
			unsigned short *p = (unsigned short *) &part[8];
			unsigned int start = p[0] + (p[1] << 16);
			unsigned int size = p[2] + (p[3] << 16);
			read(start, (char *) OS_LOAD_ADDR, size);
			break;
		}
		part += PARTITION_TABLE_ENTRY_LEN;
	}

	if (i < PARTITION_TABLE_ENTRY_N)
		ser_puts("found\r\n");
	else
		ser_puts("\r\nts4800-mbrboot: fatal: partition type 0xda not found\r\n");

	os();

	__builtin_unreachable();
}
