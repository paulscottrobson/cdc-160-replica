// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_debug_cdc160.cpp
//		Purpose:	Debugger Code (System Dependent)
//		Created:	29th June 2016
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gfx.h"
#include "sys_processor.h"
#include "sys_debug_system.h"
#include "debugger.h"

static const char *_mnemonics[] = 
#include "_cdc160_mnemonics.h"	

#define DBGC_ADDRESS 	(0x0F0)														// Colour scheme.
#define DBGC_DATA 		(0x0FF)														// (Background is in main.c)
#define DBGC_HIGHLIGHT 	(0xFF0)

// *******************************************************************************************************************************
//												Reset the 8008
// *******************************************************************************************************************************

void DBGXReset(void) {
	CPUReset();
}

// *******************************************************************************************************************************
//											This renders the debug screen
// *******************************************************************************************************************************

char buffer[32];

void DBGXRender(int *address,int showDisplay) {
	int n;

	GFXSetCharacterSize(24,25);

	CPUSTATUS *s = CPUGetStatus();													// Get the CPU Status


	const char *labels[] = { "A","P","Z","HLT","","BRK","CYC","","IMO","IOP" };
	n = 0;
	while (labels[n] != NULL) {
		GFXString(GRID(16,n),labels[n],GRIDSIZE,DBGC_ADDRESS,-1);
		n++;
	}
	n = 0;

	#define DD(value,width)	GFXNumber(GRID(20,n++),value,8,width,GRIDSIZE,DBGC_DATA,-1)
	#define DDC(value) GFXNumber(GRID(20,n++),value,8,1,GRIDSIZE,DBGC_DATA,-1)

	DD(s->a,4);DD(s->p,4);DD(s->z,4);DD(s->halt,1);
	n++;
	DD(address[3],4);DD(s->cycles,4);
	n++;
	DD(s->ioMode,2);DD(s->ioOpcode,2);

	n = address[1];																	// Dump memory.
	for (int row = 14;row < 24;row++) {
		GFXNumber(GRID(0,row),n & 0xFFF,8,4,GRIDSIZE,DBGC_ADDRESS,-1);			// Head of line
		GFXCharacter(GRID(4,row),':',GRIDSIZE,DBGC_HIGHLIGHT,-1);
		for (int col = 0;col < 8;col++) {											// Data on line
			GFXNumber(GRID(5+col*5,row),CPURead(n & 0xFFF),8,4,GRIDSIZE,DBGC_DATA,-1);
			n++;
		}
	}
																					// Output text labels.																					// Macros to simplify dump drawing.

	n = address[0]; 																// Dump code.
	for (int row = 0;row < 12;row++) {
		int isPC = (n & 0xFFF) == (s->p);											// Check for breakpoint and being at PC
		int isBrk = ((n & 0xFFF) == address[3]);
		GFXNumber(GRID(0,row),n & 0xFFF,8,4,GRIDSIZE,isPC ? DBGC_HIGHLIGHT : DBGC_ADDRESS,isBrk ? 0xF00 : -1);
		int opcode = CPURead(n & 0xFFF);
		strcpy(buffer,_mnemonics[(opcode >> 6) & 0x3F]);							// Get mnemonic
		n++;
		GFXString(GRID(5,row),buffer,GRIDSIZE,isPC ? DBGC_HIGHLIGHT : DBGC_DATA,-1);
	}

	if (showDisplay == 0) return;
}	
