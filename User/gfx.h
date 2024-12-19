#pragma once

const uint32_t TICK_DELAY = 0x40;
const uint32_t COLOR_DEPTH = 8;
const uint32_t COLOR_COUNT = (1 << COLOR_DEPTH);
const uint32_t COLOR_MAX = COLOR_COUNT - 1;
uint32_t bitDuration[COLOR_DEPTH];

const int xres = 16;
const int yres = 15;
uint8_t frameBuffer[yres * xres];
uint32_t time = 0;

#include "gfxBalanced.h"

void initLUTs()
{
    for(uint32_t i = 0; i < COLOR_DEPTH; i++)
    {
        int dur = (1 << i);
        bitDuration[i] = TICK_DELAY * (dur + 1);
    }
    gfxLUTInit();
}

volatile int frame = 0;
void __attribute__((interrupt("WCH-Interrupt-fast"))) gfxTickHandler(void)
{
    static int segment = 0;
    static int bit = 0;

    setLeds(segment, bit+8-COLOR_DEPTH);

    segment++;
    if(segment == 16)
    {
        segment = 0;
        bit++;
        if(bit == COLOR_DEPTH)
        {
            bit = 0;
            frame++;
        }
        SysTick->CMP = bitDuration[bit];
    }
    SysTick->SR=0;
}

void initGfx()
{
    initLUTs();
    SysTick->SR=0;
    SysTick->CNT=0;
    SysTick->CMP=TICK_DELAY;
    SysTick->CTLR=1 | 2| 4 | 8;
    NVIC_EnableIRQ(SysTicK_IRQn);
    SetVTFIRQ((u32)gfxTickHandler, SysTicK_IRQn, 0, ENABLE);
}
