/*
   hhugboy Game Boy emulator
   copyright 2013-2016 taizou
   Based on GEST
   Copyright (C) 2003-2010 TM
   Incorporating code from VisualBoyAdvance
   Copyright (C) 1999-2004 by Forgotten

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "MbcNinCamera.h"

byte MbcNinCamera::readMemory(register unsigned short address) {
    if(address >= 0xA000 && address < 0xC000)
    {
        if(cameraIO) // Camera I/O register in cart RAM area
        {
            if(address == 0xA000)
                return 0x00; // Hardware is ready
            else
                return 0xFF; // others write only
        }
    }

    return BasicMbc::readMemory(address);
}

void MbcNinCamera::writeMemory(unsigned short address, register byte data) {
    if(address < 0x2000)// Is it a RAM bank enable/disable?
    {
        RAMenable = ( (data&0x0A) == 0x0A ? 1 : 0);
        return;
    }

    if(address < 0x4000) // Is it a ROM bank switch?
    {
        if(data == 0)
            data = 1;
        if(data > maxROMbank[(*gbCartridge)->ROMsize])
            data = maxROMbank[(*gbCartridge)->ROMsize];

        rom_bank = data;

        int cadr = data<<14;
        gbMemMap[0x4] = &(*gbCartRom)[cadr];
        gbMemMap[0x5] = &(*gbCartRom)[cadr+0x1000];
        gbMemMap[0x6] = &(*gbCartRom)[cadr+0x2000];
        gbMemMap[0x7] = &(*gbCartRom)[cadr+0x3000];
        return;
    }

    if(address < 0x6000) // Is it a RAM bank switch?
    {
        if(data == 0x10)
        {
            cameraIO = 1;
            return;
        }
        else
            cameraIO = 0;

        data &= 0x0F;

        if(data > maxRAMbank[(*gbCartridge)->RAMsize])
            data = maxRAMbank[(*gbCartridge)->RAMsize];

        ram_bank = data;

        int madr = data<<13;
        gbMemMap[0xA] = &(*gbCartRam)[madr];
        gbMemMap[0xB] = &(*gbCartRam)[madr+0x1000];
        return;

    }

    if(address<0x8000)
        return;

    /*  if(address >= 0xA000 && address < 0xC000)
      {
         if(!RAMenable)
            return;
      }*/

    gbMemMap[address>>12][address&0x0FFF] = data;
}

MbcNinCamera::MbcNinCamera():
        cameraIO(0)
{}

void MbcNinCamera::resetVars(bool preserveMulticartState) {
    cameraIO = 0;
    AbstractMbc::resetVars(preserveMulticartState);
}
