#pragma once

void gfxLUTInit()
{
}

void setLed(int a, int b, bool on)
{
    uint32_t cfg0 = 0x44444444;
    uint32_t cfg1 = 0x44444444;
    if(on)
    {
        if(b < 8)
        {
            cfg0 ^= 0b0111 << (b << 2);
        }
        else
        {
            cfg1 ^= 0b0111 << ((b - 8) << 2);
        }
    }
    if(a < 8)
    {
        GPIOC->OUTDR = 1 << a;
        GPIOD->OUTDR = 0;
        cfg0 ^= 0b0111 << (a << 2);
    }
    else
    {
        GPIOC->OUTDR = 0;
        GPIOD->OUTDR = 1 << (a - 8);
        cfg1 ^= 0b0111 << ((a - 8) << 2);
    }
    GPIOC->CFGLR = cfg0;
    GPIOD->CFGLR = cfg1;
}
