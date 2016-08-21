//
// Created by Alex on 20/08/2016.
//

#ifndef HHUGBOY_BASICMBC_H
#define HHUGBOY_BASICMBC_H


#include "../../types.h"
#include "AbstractMbc.h"
#include "RomOnly.h"

//-------------------------------------------------------------------------
// Write: for undocumented/unknown MBCs
//-------------------------------------------------------------------------
class BasicMbc : public RomOnly {
public:
    virtual void writeMemory(unsigned short address, register byte data) override;
};


#endif //HHUGBOY_BASICMBC_H
