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

ENTRY(mbrboot)

MEMORY
{
	ram (rwx) : ORIGIN = 0x96000000, LENGTH = 446
	bss (rwx) : ORIGIN = 0x96000200, LENGTH = 0x80
}
SECTIONS {
	.text : AT(0x0) {
		mbrboot.o(.text.mbrboot);
		*(.text);
		*(.text.*);
		*(.glue_7 .glue_7t);
		*(.got .got.*);
		*(.rodata);
		*(.rodata.*);
		*(.data);
		*(.data.*);
	} > ram

	.bss : {
		bss_start = .;
		*(.bss);
		*(.bss.*);
		*(COMMON);
		bss_end = .;
	} > bss
}
