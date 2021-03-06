/*
 * Additional mapper support for hhugboy emulator
 * by taizou 2016
 * This file released under Creative Commons CC0 https://creativecommons.org/publicdomain/zero/1.0/legalcode
 *
 * As part of the hhugboy project it is also licensed under the GNU General Public License v2
 * See "license.txt" in the project root
 */


#ifndef HHUGBOY_MBCUNLDBZTRN_H
#define HHUGBOY_MBCUNLDBZTRN_H


#include "MbcNin5.h"

class MbcUnlDbzTrans : public MbcNin5 {
    public:
        virtual void writeMemory(unsigned short address, register byte data) override;
    private:
        bool waitingForOtherHalf = false;
};


#endif //HHUGBOY_MBCUNLDBZTRN_H
