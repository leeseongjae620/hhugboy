//
// Created by Alex on 18/08/2016.
//
#ifndef HHUGBOY_GB_MBC_H_H
#define HHUGBOY_GB_MBC_H_H

#include "mbc/Mbc.h"
#include "mbc/Huc3.h"

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
    MEMORY_SINTAX
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

    Mbc *mbc;

    byte** gbMemMap;
    GBrom** gbRom;
    byte** gbCartRam;
    byte** gbCartridge;
    byte* gbRomBankXor;
    int* gbRumbleCounter;
    byte** gbMemory;

    memoryaccess mbcType;

    int rom_bank;
    int ram_bank;

    unsigned short MBChi;
    unsigned short MBClo;

    int RAMenable;

    int superaddroffset;

    void rtc_update();
    void update_HuC3time();

    // MBC R/W methods
    void writememory_default(unsigned short address,register byte data);
    void writememory_MBC1(unsigned short address,register byte data);
    void writememory_MBC2(unsigned short address,register byte data);
    void writememory_MBC3(unsigned short address,register byte data);
    void writememory_MBC5(unsigned short address,register byte data, bool isNiutoude, bool isSintax);
    void writememory_Camera(unsigned short address,register byte data);
    void writememory_HuC3(register unsigned short address,register byte data);
    void writememory_MBC7(unsigned short address,register byte data);
    void writememory_TAMA5(register unsigned short address,register byte data);
    void writememory_Rockman8(register unsigned short address,register byte data);
    void writememory_BC(register unsigned short address,register byte data);
    void writememory_8in1(register unsigned short address,register byte data);
    void writememory_MMM01(register unsigned short address,register byte data);
    void writememory_MK12(register unsigned short address,register byte data);
    void writememory_poke(register unsigned short address,register byte data);
    void setXorForBank(byte bankNo);

    void readRtcVarsFromStateFile(FILE *statefile);
    void readHuc3VarsFromStateFile(FILE *statefile);
    void readMbc7VarsFromStateFile(FILE *statefile);
    void readTama5VarsFromStateFile(FILE *statefile);
    void readMoreTama5VarsFromStateFile(FILE *statefile);
    void writeRtcVarsToStateFile(FILE *statefile);
    void writeHuc3VarsToStateFile(FILE *statefile);
    void writeMbc7VarsToStateFile(FILE *statefile);
    void writeTama5VarsToStateFile(FILE *statefile);
    void writeMoreTama5VarsToStateFile(FILE *statefile);

};

#endif //HHUGBOY_GB_MBC_H_H
