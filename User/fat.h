#pragma once
#include <stdint.h>

//doc see https://academy.cba.mit.edu/classes/networking_communications/SD/FAT.pdf
#pragma pack(1)
struct BPB
{
    uint8_t jmpBoot[3];
    char OEMName[8];
    uint16_t BytsPerSec;    //512
    uint8_t SecPerClus;     //1
    uint16_t ResvdSecCnt;   //6
    uint8_t NumFATs;        //2
    uint16_t RootEntCnt;
    uint16_t TotSec16;
    uint8_t Media;          //0xf8
    uint16_t FATSz16;       //1
    uint16_t SecPerTrk;
    uint16_t NumHeads;
    uint32_t HiddSec;
    uint32_t TotSec32;
    union
    {
        struct
        {
            uint8_t DrvNum;
            uint8_t Reserved1;
            uint8_t BootSig;
            uint32_t VolID;
            char VolLab[11];
            char FilSysType[8];
            uint8_t _zero[448];
            uint16_t Signature_word;
        }FAT16;
        struct
        {
            uint32_t FATSz32;
            uint16_t ExtFlags;
            uint16_t FSVer;
            uint32_t RootClus;
            uint16_t FSInfo;
            uint16_t BkBootSec;
            uint8_t Reserved[12];
            uint8_t DrvNum;
            uint8_t Reserved1;
            uint8_t BootSig;
            uint32_t VolID;
            uint8_t VolLab[11];
            uint8_t FilSysType[8];
            uint8_t _zero[420];
            uint16_t Signature_word;
        }FAT32;
    }Ext;
};

struct DirEntry
{
    char Name[11];
    uint8_t Attr;
    uint8_t NTRes;
    uint8_t CrtTimeTenth;
    uint16_t CrtTime;
    uint16_t CrtDate;
    uint16_t LstAccDate;
    uint16_t FstClusHI;
    uint16_t WrtTime;
    uint16_t WrtDate;
    uint16_t FstClusLO;
    uint32_t FileSize;
};
#pragma pack(0)

class Fat
{
public:
    uint8_t *volume;
    uint32_t volumeSize;

    Fat()
    {
        volumeSize = 0;
        volume = 0;
    }

    void init(uint32_t volume, uint32_t size)
    {
        this->volume = (uint8_t*)volume;
        this->volumeSize = size;
    }

    uint32_t FATSz()
    {
        if(((BPB*)volume)->FATSz16 != 0)
            return ((BPB*)volume)->FATSz16;
        else
            return ((BPB*)volume)->Ext.FAT32.FATSz32;
    }

    uint32_t TotSec()
    {
        if(((BPB*)volume)->TotSec16 != 0)
            return ((BPB*)volume)->TotSec16;
        else
            return ((BPB*)volume)->TotSec32;
    }

    uint32_t DataSec()
    {
        return TotSec() - (((BPB*)volume)->ResvdSecCnt + (((BPB*)volume)->NumFATs * FATSz()) + RootDirSectors());
    }

    uint32_t CountofClusters()
    {
        return DataSec() / ((BPB*)volume)->SecPerClus;
    }

    bool isFAT12()
    {
        return CountofClusters() < 4085;
    }

    bool isFAT16()
    {
        return !isFAT12() && (CountofClusters() < 65525);
    }

    bool isFAT32()
    {
        return !isFAT12() && !isFAT16();
    }

    uint32_t RootDirSectors()
    {
        return ((((BPB*)volume)->RootEntCnt * 32) + (((BPB*)volume)->BytsPerSec - 1)) / ((BPB*)volume)->BytsPerSec;
    }

    uint32_t FirstRootDirSecNum()
    {
        return ((BPB*)volume)->ResvdSecCnt + ((BPB*)volume)->NumFATs * FATSz();
        //TODO
        //On volumes formatted FAT32, the root directory can be of variable size. The location of the first
        //cluster of the root directory on the FAT32 volume is stored in the BPB_RootClus field.
    }

    uint32_t FirstDataSector()
    {
        return FirstRootDirSecNum() + RootDirSectors();
    }

    uint32_t FirstSectorofCluster(uint32_t n)
    {
        return ((n - 2) * ((BPB*)volume)->SecPerClus) + FirstDataSector();
    }

    uint32_t FATOffset(uint32_t n)
    {
        if(isFAT12())
            return n + (n / 2);
        else if(isFAT16())
            return n * 2;
        else if(isFAT32())
            return n * 4;
        return 0;
    }

    //12
    uint32_t ThisFATSecNum(uint32_t n)
    {
        return ((BPB*)volume)->ResvdSecCnt + (FATOffset(n) / ((BPB*)volume)->BytsPerSec);
    }

    uint32_t ThisFATEntOffset(uint32_t n)
    {
        return FATOffset(n) % ((BPB*)volume)->BytsPerSec;
    }

    uint32_t FATClusEntryVal(uint32_t n)
    {
        //entries 0 and 1 are reseverd and filled with
        //0: BPB_Media and higher bits are 1
        //1: FAT12: EOC mark
        //   FAT16/32 high 2 bits are dirty volume bits
        //   FAT16: ClnShutBitMask = 0x8000, HrdErrBitMask = 0x4000
        //   FAT32: ClnShutBitMask = 0x80000000, HrdErrBitMask = 0x40000000
        //ClnShutBitMask: 1 all ok. 0 dirty volume better scan
        //HrdErrBitMask: 1 no errors. io errors better scan

        //values
        //0 free cluster
        //2-MAX allocated, next cluster of file
        //MAX+1 - 0xff6/0xfff6/0xfffffff6 reserved
        //0xff7/0xfff7/0xfffffff7 bad cluster
        //0xff8/0xfff8/0xfffffff8 - 0xffe/0xfffe/0xfffffffe reserved maybe eof
        //0xfff/0xffff/0xffffffff eof

        if(isFAT12())
            return (*((uint16_t *) &volume[ThisFATEntOffset(n)]) >> (4 * (n & 1))) & 0x0ffff;
        else if(isFAT16())
            return *((uint16_t *) &volume[ThisFATEntOffset(n)]);
        else if(isFAT32())
            return (*((uint32_t *) &volume[ThisFATEntOffset(n)])) & 0x0FFFFFFF;
        return 0;
    }

    uint32_t SecOff(uint32_t sector)
    {
        return sector * ((BPB*)volume)->BytsPerSec;
    }

    uint32_t ClusterOff(uint32_t cluster)
    {
        return SecOff(FirstSectorofCluster(cluster));
    }

    uint8_t *ClusterAddr(uint32_t cluster)
    {
        return &volume[SecOff(FirstSectorofCluster(cluster))];
    }

    uint8_t *GetRootDirAddr()
    {
        return &volume[SecOff(FirstRootDirSecNum())];
    }

    //uint32_t FatEntry()
    DirEntry &GetRootDirEntry(uint32_t n)
    {
        return ((DirEntry*)&volume[SecOff(FirstRootDirSecNum())])[n];
    }
};
