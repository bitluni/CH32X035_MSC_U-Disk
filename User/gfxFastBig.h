#pragma once
uint32_t frameBufferBits0[16 * 8];
uint32_t frameBufferBits1[16 * 8];

uint8_t frameBufferSegmentBits[] =
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint32_t triStateLUT[] = {0x44444444, 0x44444443, 0x44444434, 0x44444433, 0x44444344, 0x44444343, 0x44444334, 0x44444333, 0x44443444, 0x44443443, 0x44443434, 0x44443433, 0x44443344, 0x44443343, 0x44443334, 0x44443333, 0x44434444, 0x44434443, 0x44434434, 0x44434433, 0x44434344, 0x44434343, 0x44434334, 0x44434333, 0x44433444, 0x44433443, 0x44433434, 0x44433433, 0x44433344, 0x44433343, 0x44433334, 0x44433333, 0x44344444, 0x44344443, 0x44344434, 0x44344433, 0x44344344, 0x44344343, 0x44344334, 0x44344333, 0x44343444, 0x44343443, 0x44343434, 0x44343433, 0x44343344, 0x44343343, 0x44343334, 0x44343333, 0x44334444, 0x44334443, 0x44334434, 0x44334433, 0x44334344, 0x44334343, 0x44334334, 0x44334333, 0x44333444, 0x44333443, 0x44333434, 0x44333433, 0x44333344, 0x44333343, 0x44333334, 0x44333333, 0x43444444, 0x43444443, 0x43444434, 0x43444433, 0x43444344, 0x43444343, 0x43444334, 0x43444333, 0x43443444, 0x43443443, 0x43443434, 0x43443433, 0x43443344, 0x43443343, 0x43443334, 0x43443333, 0x43434444, 0x43434443, 0x43434434, 0x43434433, 0x43434344, 0x43434343, 0x43434334, 0x43434333, 0x43433444, 0x43433443, 0x43433434, 0x43433433, 0x43433344, 0x43433343, 0x43433334, 0x43433333, 0x43344444, 0x43344443, 0x43344434, 0x43344433, 0x43344344, 0x43344343, 0x43344334, 0x43344333, 0x43343444, 0x43343443, 0x43343434, 0x43343433, 0x43343344, 0x43343343, 0x43343334, 0x43343333, 0x43334444, 0x43334443, 0x43334434, 0x43334433, 0x43334344, 0x43334343, 0x43334334, 0x43334333, 0x43333444, 0x43333443, 0x43333434, 0x43333433, 0x43333344, 0x43333343, 0x43333334, 0x43333333, 0x34444444, 0x34444443, 0x34444434, 0x34444433, 0x34444344, 0x34444343, 0x34444334, 0x34444333, 0x34443444, 0x34443443, 0x34443434, 0x34443433, 0x34443344, 0x34443343, 0x34443334, 0x34443333, 0x34434444, 0x34434443, 0x34434434, 0x34434433, 0x34434344, 0x34434343, 0x34434334, 0x34434333, 0x34433444, 0x34433443, 0x34433434, 0x34433433, 0x34433344, 0x34433343, 0x34433334, 0x34433333, 0x34344444, 0x34344443, 0x34344434, 0x34344433, 0x34344344, 0x34344343, 0x34344334, 0x34344333, 0x34343444, 0x34343443, 0x34343434, 0x34343433, 0x34343344, 0x34343343, 0x34343334, 0x34343333, 0x34334444, 0x34334443, 0x34334434, 0x34334433, 0x34334344, 0x34334343, 0x34334334, 0x34334333, 0x34333444, 0x34333443, 0x34333434, 0x34333433, 0x34333344, 0x34333343, 0x34333334, 0x34333333, 0x33444444, 0x33444443, 0x33444434, 0x33444433, 0x33444344, 0x33444343, 0x33444334, 0x33444333, 0x33443444, 0x33443443, 0x33443434, 0x33443433, 0x33443344, 0x33443343, 0x33443334, 0x33443333, 0x33434444, 0x33434443, 0x33434434, 0x33434433, 0x33434344, 0x33434343, 0x33434334, 0x33434333, 0x33433444, 0x33433443, 0x33433434, 0x33433433, 0x33433344, 0x33433343, 0x33433334, 0x33433333, 0x33344444, 0x33344443, 0x33344434, 0x33344433, 0x33344344, 0x33344343, 0x33344334, 0x33344333, 0x33343444, 0x33343443, 0x33343434, 0x33343433, 0x33343344, 0x33343343, 0x33343334, 0x33343333, 0x33334444, 0x33334443, 0x33334434, 0x33334433, 0x33334344, 0x33334343, 0x33334334, 0x33334333, 0x33333444, 0x33333443, 0x33333434, 0x33333433, 0x33333344, 0x33333343, 0x33333334, 0x33333333};

void gfxLUTInit()
{
}

void convertFrame()
{
    for(int bit = 0; bit < 8; bit++)
    {
        int bitMask = 1 << bit;
        for(int segment = 0; segment < 16; segment++)
        {
            int bits = 0;
            int b = (segment << 4) - segment; //segment * 15
            for(int l = 0; l < 15; l++)
                {
                    int p = b + l;
                    int c = 15 - (p & 15);
                    if(frameBuffer[p] & bitMask)
                        bits |= 1 << c;
                }
            frameBufferBits0[(bit << 4) | segment] = triStateLUT[bits & 0xff];
            frameBufferBits1[(bit << 4) | segment] = triStateLUT[bits >> 8];
            if(segment < 8)
                frameBufferBits0[(bit << 4) | segment] ^= 0b0111 << (segment << 2);
            else
                frameBufferBits1[(bit << 4) | segment] ^= 0b0111 << ((segment - 8) << 2);
        }
    }
}

inline void setLeds(int segment, int bit)
{
    GPIOC->OUTDR = frameBufferSegmentBits[segment + 8];
    GPIOD->OUTDR = frameBufferSegmentBits[segment];
    GPIOC->CFGLR = frameBufferBits0[(bit << 4) | segment];
    GPIOD->CFGLR = frameBufferBits1[(bit << 4) | segment];
}

