#ifndef AVREMU_DEFS_H
#define AVREMU_DEFS_H

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <thread>
#include <mutex>
#include <ctime>
#include <fstream>
#include <cstdint>

#ifdef _WIN32
    #ifdef DLL_EXPORT
        #define AVREMU_DLL __declspec(dllexport)
    #else
        #define AVREMU_DLL __declspec(dllimport)
    #endif
#else
    #define AVREMU_DLL
#endif


//#define TRACE_ON
#ifdef TRACE_ON
#define TRACE_STRING(STR) printf("TRACE[%s,%s,%d] => %s\n",__FILE__,__FUNCTION__,__LINE__,STR)
#define TRACE_PRT(STR1,...) printf("TRACE[%s,%s,%d] => ",__FILE__,__FUNCTION__,__LINE__); printf(STR1,__VA_ARGS__); printf("\n")
#else
#define TRACE_STRING(STR)
#define TRACE_PRT(STR1,...)
#endif


#define  BIT(reg,b) ((reg & (0x01 << b)) != 0)
#define NBIT(reg,b) ((reg & (0x01 << b)) == 0)
#define SBIT(reg,b) (reg | (0x01<<b))
#define CBIT(reg,b) (reg & ~(0x01<<b))
#define WBIT(reg,b,v) ((reg & ~(0x01<<b)) | ((v!=0)<<b))

#define SAFE_DELETE(X) {if(X != 0){delete X; X = 0;}} do{}while(0)
#define SAFE_DELETE_ARR(X) {if(X != 0){delete[] X; X = 0;}} do{}while(0)

namespace avremu
{
 typedef uint8_t       u8;
 typedef uint16_t      u16;
 typedef uint32_t      u32;
 typedef uint64_t      u64;

 typedef int8_t        s8;
 typedef int16_t       s16;
 typedef int32_t       s32;
 typedef int64_t       s64;

 const u8 Error      = 1;
 const u8 Success    = 0;

 const u8 MaxOpcodeLength = 2;
 const u8 MaxOpcodeParamiters = 2;

 const u8 C_bit = 0;
 const u8 Z_bit = 1;
 const u8 N_bit = 2;
 const u8 V_bit = 3;
 const u8 S_bit = 4;
 const u8 H_bit = 5;
 const u8 T_bit = 6;
 const u8 I_bit = 7;
}

#define BYTES(v) avremu::u32(v)
#define KILO_BYTES(v) (avremu::u32(v)<<10)
#define MEGA_BYTES(v) (avremu::u32(v)<<20)

#define DB2W(hb,lb) (avremu::u16(hb)<<8 | avremu::u16(lb))
#define LBYTE(w) avremu::u8(w)
#define HBYTE(w) (avremu::u8(w >> 8))


#endif
