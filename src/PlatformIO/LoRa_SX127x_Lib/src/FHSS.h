#include <Arduino.h>

volatile uint8_t FHSSptr = 0;

void ICACHE_RAM_ATTR FHSSsetCurrIndex(uint8_t value)
{ // get the current index of the FHSS pointer
    FHSSptr = value;
}

uint8_t ICACHE_RAM_ATTR FHSSgetCurrIndex()
{ // get the current index of the FHSS pointer
    return FHSSptr;
}

//const uint32_t FHSSfreqs433[5] = {
//    433420000,
//    433670000,
//    433920000,
//    434170000,
//    434420000};

const uint32_t FHSSfreqs433[5] = {
    433420000,
    433920000,
    434420000};

const uint32_t FHSSfreqs915[32] = {
    918000000,
    918250000,
    918500000,
    918750000,

    919000000,
    919250000,
    919500000,
    919750000,

    920000000,
    920250000,
    920500000,
    920750000,

    921000000,
    921250000,
    921500000,
    921750000,

    922000000,
    922250000,
    922500000,
    922750000,

    923000000,
    923250000,
    923500000,
    923750000,

    924000000,
    924250000,
    924500000,
    924750000,

    925000000,
    925250000,
    925500000,
    925750000};

uint8_t FHSSsequence[255] = {0};

uint32_t ICACHE_RAM_ATTR GetInitialFreq()
{
#ifdef Regulatory_Domain_AU_915
    return FHSSfreqs915[0];
#elif defined Regulatory_Domain_AU_433
    return FHSSfreqs433[0];
#endif
}

uint32_t ICACHE_RAM_ATTR FHSSgetCurrFreq()
{
#ifdef Regulatory_Domain_AU_915
    return FHSSfreqs915[FHSSsequence[FHSSptr]];
#elif defined Regulatory_Domain_AU_433
    return FHSSfreqs433[FHSSsequence[FHSSptr]];
#endif
    return 0;
}

uint32_t ICACHE_RAM_ATTR FHSSgetNextFreq()
{
    FHSSptr++;

    return FHSSgetCurrFreq();
}

uint32_t ICACHE_RAM_ATTR FHSSrandomiseFHSSsequence()
{
    long macSeed = ((long)TxBaseMac[2] << 24) + ((long)TxBaseMac[3] << 16) + ((long)TxBaseMac[4] << 8) + TxBaseMac[5];
    rngSeed(macSeed);
    
#ifdef Regulatory_Domain_AU_915

    for(int i = 0; i < 256; i++) {
        FHSSsequence[i] = rng5Bit();
    }

#elif defined Regulatory_Domain_AU_433

    for(int i = 0; i < 256; i++) {
        FHSSsequence[i] = rng0to2();
    }

#endif
}