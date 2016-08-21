//
// Created by Alex on 18/08/2016.
//
#ifndef HHUGBOY_GB_MBC_H_H
#define HHUGBOY_GB_MBC_H_H

#include "mbc/AbstractMbc.h"
#include "mbc/MbcLicHuc3.h"

enum memoryaccess
{
    MEMORY_DEFAULT = 0,
    MEMORY_MBC1,
    MEMORY_MBC2,
    MEMORY_MBC3,
    MEMORY_MBC5,
    MEMORY_CAMERA,
    MEMORY_HUC3,
    MEMORY_MBC7,
    MEMORY_TAMA5,
    MEMORY_ROCKMAN8,
    MEMORY_BC,
    MEMORY_8IN1,
    MEMORY_MMM01,
    MEMORY_MK12,
    MEMORY_POKE,
    MEMORY_NIUTOUDE,
    MEMORY_SINTAX,
    MEMORY_ROMONLY
};

class gb_mbc {

public:
    gb_mbc(byte** gbMemMap, byte** gbCartridge, GBrom** gbRom, byte** gbCartRam, byte* romBankXor, int* rumbleCounter, byte** gbMemory);

    void setMemoryReadWrite(memoryaccess memory_type);

    int getRomBank();
    int getRamBank();

    byte readmemory_cart(register unsigned short address);
    void writememory_cart(unsigned short address,register byte data);
    void resetMbcVariables();
    void resetRomMemoryMap(bool resetOffset);

    void writeMbcSpecificStuffToSaveFile(FILE *savefile);
    void readMbcSpecificStuffFromSaveFile(FILE *savefile);

    void readMbcBanksFromStateFile(FILE *statefile);
    void readMbcMoreCrapFromStateFile(FILE *statefile);
    void writeMbcBanksToStateFile(FILE *statefile);
    void writeMbcOtherStuffToStateFile(FILE *statefile);

    void writeNewerCartSpecificVarsToStateFile(FILE *statefile);
    void writeCartSpecificVarsToStateFile(FILE *statefile);
    void readCartSpecificVarsFromStateFile(FILE *statefile);
    void readNewerCartSpecificVarsFromStateFile(FILE *statefile);

private:

    AbstractMbc *mbc;

    byte** gbMemMap;
    GBrom** gbRom;
    byte** gbCartRam;
    byte** gbCartridge;
    byte* gbRomBankXor;
    int* gbRumbleCounter;
    byte** gbMemory;

    memoryaccess mbcType;

    int superaddroffset;

    void rtc_update();

    // MBC R/W methods
    void writememory_MBC1(unsigned short address,register byte data);
    void writememory_MBC2(unsigned short address,register byte data);
    void writememory_MBC3(unsigned short address,register byte data);
    void writememory_MBC5(unsigned short address,register byte data, bool isNiutoude, bool isSintax);
    void writememory_Camera(unsigned short address,register byte data);
    void writememory_TAMA5(register unsigned short address,register byte data);
    void writememory_Rockman8(register unsigned short address,register byte data);
    void writememory_BC(register unsigned short address,register byte data);
    void writememory_8in1(register unsigned short address,register byte data);
    void writememory_MMM01(register unsigned short address,register byte data);
    void writememory_MK12(register unsigned short address,register byte data);
    void writememory_poke(register unsigned short address,register byte data);
    void setXorForBank(byte bankNo);

};

#endif //HHUGBOY_GB_MBC_H_H
