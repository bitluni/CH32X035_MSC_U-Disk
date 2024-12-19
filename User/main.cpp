#include "massStorage.h"
#include "gfx.h"
#include "buttons.h"

extern "C" uint8_t *lastSector;

GPIO_TypeDef *pinsPort[16] = {GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA ,GPIOA,
                            GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB};
const int pins[16] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 3, 4, 6, 7, 8, 9, 10};


void setPin(int i, int v)
{
    if(v == -1)
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        GPIO_InitStructure.GPIO_Pin = 1 << pins[i];//GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(pinsPort[i], &GPIO_InitStructure);
    }
    else
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        GPIO_InitStructure.GPIO_Pin = 1 << pins[i];//GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(pinsPort[i], &GPIO_InitStructure);
        GPIO_WriteBit(pinsPort[i], 1 << pins[i], v ? Bit_SET : Bit_RESET);
    }
}

/*
void setPin2(int i, int v)
{
    if(i < 8)
    {
        if(v == -1)
        {
            GPIOA->CFGHR &= ~(0xf << (4 * (pins[0][i])));
            GPIOA->CFGHR |= (0b0100) << (4 * (pins[0][i]));
        }
        else
        {
            GPIOA->CFGHR &= ~(0xf<<(4 * (pins[0][i])));
            GPIOA->CFGHR |= (GPIO_Speed_50MHz | 0x0)<<(4 * (pins[0][i]));
            if(v)
                GPIOA->BSHR = 1 << (pins[0][i] + 00);
            else
                GPIOA->BSHR = 1 << (pins[0][i] + 16);   //clear
        }
    }
    else
    {
        if(v == -1)
        {
            GPIOB->CFGHR &= ~(0xf<<(4 * (pins[1][i - 8])));
            GPIOB->CFGHR |= (0b0100) << (4 * (pins[1][i - 8]));
        }
        else
        {
            GPIOB->CFGHR &= ~(0xf<<(4 * (pins[1][i - 8])));
            GPIOB->CFGHR |= (GPIO_Speed_50MHz | 0x0)<<(4 * (pins[1][i - 8]));
            if(v)
                GPIOB->BSHR = 1 << (pins[0][i - 8] + 00);
            else
                GPIOB->BSHR = 1 << (pins[0][i - 8] + 16);   //clear
        }
    }
}*/


void pix(int x, int y, uint8_t c)
{
    frameBuffer[x + y * xres] = c;
}

void showLine(int segment)
{
    for(int i = 0; i < 16; i++)
        setPin(i, -1);
    int y = 0;
    for(int i = 0; i < 16; i++)
        if(i == segment)
            setPin(i, 0);
        else
            setPin(i, frameBuffer[y++ * 16 + 15 - segment] ? 1 : -1);
}

void displayNumber(int n, int y = 0)
{
    for(int i = 0; i < 32; i++)
        pix(i & 15, (i >> 4) + y, (n >> i) & 1);
}

#include "font.h"
#include "Interpreter.h"
const uint8_t code[] = {0, 11, 0, 0, 0, 0, 133, 1, 0, 0, 16, 5, 0, 1, 4, 0, 4, 1, 7, 37, 4, 2, 40, 6, 5, 0, 4, 38, 9, 6, 5, 192, 3, 32, 9, 4, 4, 39, 4, 63, 32, 33, 4, 64, 38, 5, 255, 3, 32, 0, 60, 0, 0, 0, 0, 40, 1, 0, 0, 16, 4, 64, 39, 5, 255, 3, 32, 0, 78, 0, 0, 0, 0, 40, 1, 0, 0, 16, 4, 64, 39, 5, 255, 3, 32, 0, 96, 0, 0, 0, 0, 40, 1, 0, 0, 16, 6, 5, 192, 3, 32, 9, 4, 4, 38, 4, 63, 32, 33, 0, 120, 0, 0, 0, 0, 40, 1, 0, 0, 16, 6, 5, 192, 3, 32, 9, 4, 4, 38, 4, 63, 32, 33, 0, 144, 0, 0, 0, 0, 40, 1, 0, 0, 16, 4, 64, 38, 5, 255, 3, 32, 0, 162, 0, 0, 0, 0, 40, 1, 0, 0, 16, 4, 64, 38, 5, 255, 3, 32, 0, 180, 0, 0, 0, 0, 40, 1, 0, 0, 16, 6, 5, 192, 3, 32, 9, 4, 4, 39, 4, 63, 32, 33, 0, 204, 0, 0, 0, 0, 40, 1, 0, 0, 16, 4, 64, 39, 5, 255, 3, 32, 2, 4, 2, 7, 4, 3, 0, 253, 0, 0, 0, 21, 4, 2, 7, 4, 2, 0, 245, 0, 0, 0, 21, 1, 4, 0, 9, 3, 0, 2, 1, 0, 0, 16, 9, 3, 0, 2, 1, 0, 0, 16, 1, 4, 1, 9, 3, 1, 37, 6, 0, 14, 0, 0, 0, 18, 1, 0, 23, 1, 0, 0, 0, 58, 1, 0, 0, 16, 0, 34, 1, 0, 0, 0, 84, 1, 0, 0, 16, 0, 11, 0, 0, 0, 16, 4, 1, 7, 2, 0, 57, 1, 0, 0, 17, 4, 3, 7, 36, 4, 3, 8, 16, 5, 0, 1, 6, 37, 4, 2, 40, 6, 5, 0, 4, 38, 2, 9, 3, 37, 6, 0, 61, 1, 0, 0, 18, 1, 16, 5, 0, 160, 4, 240, 0, 255, 255, 255, 0, 4, 2, 7, 6, 4, 4, 38, 4, 3, 8, 6, 5, 255, 3, 32, 2, 0, 121, 1, 0, 0, 18, 4, 0, 4, 1, 8, 3, 37, 6, 0, 89, 1, 0, 0, 18, 1, 1, 16, 4, 1, 4, 44, 3, 4, 1, 4, 112, 3, 4, 1, 4, 168, 3, 4, 1, 4, 172, 3, 4, 1, 4, 176, 3, 4, 1, 5, 4, 1, 3, 4, 1, 5, 72, 1, 3, 4, 1, 5, 128, 1, 3, 4, 1, 5, 132, 1, 3, 4, 1, 5, 136, 1, 3, 4, 1, 5, 36, 2, 3, 4, 1, 5, 104, 2, 3, 4, 1, 5, 160, 2, 3, 4, 1, 5, 164, 2, 3, 4, 1, 5, 168, 2, 3, 16};

Interpreter interpreter;

#include "fat.h"

void drawHex(int x, int y, uint8_t v)
{
    const char *hex = "0123456789ABCDEF";
    drawChar(x,   y,   hex[v >> 4], 0xff, 0);
    drawChar(x+4, y, hex[v & 15], 0xff, 0);
}

uint8_t *getRoot()
{
    uint8_t *volume = (uint8_t *)IFLASH_UDISK_START_ADDR;
    uint32_t bytesPerSector = *(uint16_t*)&volume[0xb];
    uint32_t sectorsPerCluster = volume[0xd];
    uint32_t reservedSectors = *(uint16_t*)&volume[0xe];
    uint32_t fatCopies = volume[0x10];
    uint32_t sectorPerFat = *(uint16_t*)&volume[0x16];
    uint8_t *fat = volume + bytesPerSector * (sectorsPerCluster * (reservedSectors + fatCopies * sectorPerFat));
    return fat;
}

uint8_t *getBin(int *size)
{
    *size = 0;
    uint8_t *volume = (uint8_t *)IFLASH_UDISK_START_ADDR;
    uint32_t bytesPerSector = *(uint16_t*)&volume[0xb];
    uint32_t sectorsPerCluster = volume[0xd];
    int32_t bytesPerCluster = bytesPerSector * sectorsPerCluster;
    uint32_t maxRootEntries = *(uint16_t*)&volume[0x11];

    /*
    uint32_t reservedSectors = *(uint16_t*)&volume[0xe];
    uint32_t fatCopies = volume[0x10];
    uint32_t sectorPerFat = *(uint16_t*)&volume[0x16];
    uint8_t *fat = volume + bytesPerSector * (sectorsPerCluster * (reservedSectors + fatCopies * sectorPerFat));
*/
    uint8_t *root = (uint8_t *)getRoot();
    int offset = 0;
    while(root[offset] && offset < bytesPerCluster)    //todo continue next cluster
    {
        if(root[offset + 8] == 'B' && root[offset + 9] == 'I' && root[offset + 10] == 'N')
        {
            int cluster = *(uint16_t*)&root[offset + 0x1A];
            *size = *(uint32_t*)&root[offset + 0x1C];
            int rootSize = ((maxRootEntries * 32 + bytesPerSector - 1) / bytesPerSector) * bytesPerSector;
            return &root[(cluster - 2) * bytesPerCluster + rootSize];
        }
        offset += 32;
    }
    return 0;
}

Fat disk;

uint8_t *findBin(int *size)
{
    int i = 0;
    while(disk.GetRootDirEntry(i).Name[0])
    {
        if(disk.GetRootDirEntry(i).Name[8] == 'B' && disk.GetRootDirEntry(i).Name[9] == 'I' && disk.GetRootDirEntry(i).Name[10] == 'N')
        {
            *size = disk.GetRootDirEntry(i).FileSize;
            return disk.ClusterAddr(disk.GetRootDirEntry(i).FstClusLO);
        }
        i++;
    }
    return 0;
}

void enormousifyFAT(uint8_t *addr = (uint8_t *)0x5000, int rootFiles = 16)
{
    if(((uint16_t*)addr)[0] != 0xffff)
        return;
    uint8_t buf[256] = {0};
    IFlash_Prog_256((int)addr + 256, (uint32_t*)buf); //second part of headeris empty
    BPB *bpb = (BPB*)buf;
    bpb->jmpBoot[0] = 0xEB;
    bpb->jmpBoot[1] = 0x3C;
    bpb->jmpBoot[2] = 0x90;
    bpb->OEMName[0] = 'L';
    bpb->OEMName[1] = 'U';
    bpb->OEMName[2] = 'N';
    bpb->OEMName[3] = 'I';
    bpb->OEMName[4] = 'O';
    bpb->OEMName[5] = 'S';
    bpb->OEMName[6] = '6';
    bpb->OEMName[7] = '9';
    bpb->BytsPerSec = 512;
    bpb->SecPerClus = 1;
    bpb->ResvdSecCnt = 1;
    bpb->NumFATs = 2;
    bpb->RootEntCnt = rootFiles;
    bpb->TotSec16 = IFLASH_UDISK_SIZE / 512;
    bpb->Media = 0xf0;
    bpb->FATSz16 = 1;
            //only more than one sec with more than 172k
            //(bpb->TotSec16 + bpb->TotSec16 / 2 + 511) / 512;//only fat12
    bpb->SecPerTrk = 1;
    bpb->NumHeads = 1;
    bpb->HiddSec = 0;
    bpb->TotSec32 = 0;
    bpb->Ext.FAT16.DrvNum = 0x80;
    bpb->Ext.FAT16.Reserved1 = 0;
    bpb->Ext.FAT16.BootSig = 0x29;
    bpb->Ext.FAT16.VolID = 0x8411EF6C;
    bpb->Ext.FAT16.VolLab[0] = 'L';
    bpb->Ext.FAT16.VolLab[1] = 'U';
    bpb->Ext.FAT16.VolLab[2] = 'N';
    bpb->Ext.FAT16.VolLab[3] = 'I';
    bpb->Ext.FAT16.VolLab[4] = ' ';
    bpb->Ext.FAT16.VolLab[5] = ' ';
    bpb->Ext.FAT16.VolLab[6] = ' ';
    bpb->Ext.FAT16.VolLab[7] = ' ';
    bpb->Ext.FAT16.VolLab[8] = ' ';
    bpb->Ext.FAT16.VolLab[9] = ' ';
    bpb->Ext.FAT16.VolLab[10] = ' ';
    bpb->Ext.FAT16.FilSysType[0] = 'F';
    bpb->Ext.FAT16.FilSysType[1] = 'A';
    bpb->Ext.FAT16.FilSysType[2] = 'T';
    bpb->Ext.FAT16.FilSysType[3] = '1';
    bpb->Ext.FAT16.FilSysType[4] = '2';
    bpb->Ext.FAT16.FilSysType[5] = ' ';
    bpb->Ext.FAT16.FilSysType[6] = ' ';
    bpb->Ext.FAT16.FilSysType[7] = ' ';
    IFlash_Prog_256((int)addr, (uint32_t*)buf);
    //boot sector done
    //fat12s next
    for(int i = 0; i < 256; i++)
        buf[i] = 0;
    IFlash_Prog_256((int)addr + 512 + 256, (uint32_t*)buf);
    IFlash_Prog_256((int)addr + 512 + 256 + 512, (uint32_t*)buf);
    buf[0] = 0xf0;//0 cluster
    buf[1] = 0xff;//1 cluster
    buf[2] = 0xff;
    IFlash_Prog_256((int)addr + 512, (uint32_t*)buf);
    IFlash_Prog_256((int)addr + 512 + 512, (uint32_t*)buf);
    //last root dir
    for(int i = 0; i < 256; i++)
        buf[i] = 0;
    DirEntry *root = (DirEntry*)buf;
    root[0].Name[0] = 'L';
    root[0].Name[1] = 'U';
    root[0].Name[2] = 'N';
    root[0].Name[3] = 'I';
    root[0].Name[4] = ' ';
    root[0].Name[5] = ' ';
    root[0].Name[6] = ' ';
    root[0].Name[7] = ' ';
    root[0].Name[8] = ' ';
    root[0].Name[9] = ' ';
    root[0].Name[10] = ' ';
    root[0].Attr = 0x08;
    IFlash_Prog_256((int)addr + 512 + 512 + 512, (uint32_t*)buf);
}

void removeLongNames(int entries = 16)
{
    uint8_t buf[256] = {0};
    uint8_t *root = disk.GetRootDirAddr();
    int bufi = 0;
    int bufoff = 0;

    for(int i = 0; i < entries; i++)
    {
        if((root[i * 32 + 0xb] & 0xf) != 0xf)
        {
            for(int j = 0; j < 32; j++)
                buf[bufi++] = root[i * 32 + j];
            if(bufi == 256)
            {
                IFlash_Prog_256((int)root + bufoff, (uint32_t*)buf);
                bufoff += 256;
                bufi = 0;
            }
        }
    }
    if(bufi)
        IFlash_Prog_256((int)root + bufoff, (uint32_t*)buf);
}


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    Delay_Init();
    enormousifyFAT((uint8_t*)IFLASH_UDISK_START_ADDR, 16);
    disk.init(IFLASH_UDISK_START_ADDR, IFLASH_UDISK_SIZE);
    removeLongNames();
    initMassStorage();
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB;


 /*   for(int i = 0; i < 6; i++)
    {
        GPIOC->OUTDR &= ~(1 << buttonPins[i]); //pull down

        if(buttonPins[i] < 8)
        {
            GPIOC->CFGLR &= ~(0xf<<(4 * buttonPins[i]));
            GPIOC->CFGLR |= (0b1000) << (4 * buttonPins[i]);   //input pull mode
        }
        else if(buttonPins[i] < 16)
        {
            GPIOC->CFGHR &= ~(0xf<<(4 * (buttonPins[i] - 8)));
            GPIOC->CFGHR |= (0b1000) << (4 * (buttonPins[i] - 8));
        }
        else
        {
            GPIOC->CFGXR &= ~(0xf<<(4 * (buttonPins[i] - 16)));
            GPIOC->CFGXR |= (0b1000) << (4 * (buttonPins[i] - 16));
        }
    }*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    for(int i = 0; i < xres * yres; i++)
        frameBuffer[i] = 0;
    initButtons();
    //interpreter.init(code, sizeof(code));
    while(1)
    {
        static int counter = 0;

        if(0)
        {
            displayNumber(counter >> 4, 0);
            displayNumber(interpreter.IP, 2);
            displayNumber(interpreter.codeSize, 4);
        }
        if(interpreter.code)
            for(int i = 0; i < 256; i++)
                interpreter.execute();
        if((counter & 15) == 0)
        {
//            for(int i = 0; i < xres * 8; i++)
//                frameBuffer[i] = interpreter.mem.heap[(i << 2)];
//            for(int i = 0; i < xres * 7; i++)
//                frameBuffer[i + 16 * 8] = interpreter.mem.heap[(i << 2)+1024];
            if(interpreter.code)
            {
                for(int i = 0; i < xres * yres; i++)
                    frameBuffer[i] = interpreter.mem.gfx[(i << 2)];
            }
            else
            {
                processButtons(100);
                displayNumber(buttonBits(), 12);
                displayNumber((int)lastSector, 13);

                static int mode = 0;
                lastSector += buttonPressed(2) - buttonPressed(3);
                if(buttonPressed(4))
                {
                    //lastSector = (uint8_t*)&disk.GetRootDirEntry(i);// getBin(&size);
                    //lastSector = (uint8_t*)(disk.FATSz()*disk.)();
//                    lastSector = (uint8_t*)&disk.GetRootDirEntry(0);// getBin(&size);
                    int size = 0;
                    interpreter.init(getBin(&size), size);
                }
                if(buttonPressed(5))
                    mode ^= 1;

                if(mode == 0)
                {
                    drawHex(0, 0, ((int)lastSector >> 8) & 255);
                    drawHex(8, 0, (int)lastSector & 255);
                    drawHex(0, 6, lastSector[0]);
                    drawHex(8, 6, lastSector[1]);
                }
                else
                {
/*                    int a = disk.FATSz();
                    drawHex(0, 0, ((int)a >> 8) & 255);
                    drawHex(8, 0, (int)a & 255);
                    int b = ((BPB*)disk.volume)->ResvdSecCnt;//disk.FirstRootDirSecNum();
                    drawHex(0, 6, ((int)b >> 8) & 255);
                    drawHex(8, 6, (int)b & 255);
*/
                    for(int i = 0; i < 8; i++)
                        drawChar((i & 3) * 4, (i >> 2) * 6, lastSector[i], 255, 0);
                }
                //print(0, 0, "LUNI");
                //print(0, 5, "WAS");
                //print(0, 10, "HERE");
                //displayNumber(interpreter.IP, 13);
            }
        }
        showLine(counter & 15);
        counter++;
        //Delay_Us(100);
    }

}

