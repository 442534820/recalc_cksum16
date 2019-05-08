#include <stdint.h>

//pOld pNew shold be 2-bytes algined in all data stream
//replace_len should be an even number, odd will be implemented some time :)
uint16_t recalc_chksum16(uint16_t old_chksum, uint8_t* pOld, uint8_t* pNew, uint16_t replace_len)
{
    uint16_t ret;
    uint16_t v_new, v_old;

    if(replace_len % 2) return 0;

    ret = ~old_chksum;
    while(replace_len)
    {
        v_old = pOld[0] * 256 + pOld[1];
        v_new = pNew[0] * 256 + pNew[1];
        pOld += 2;
        pNew += 2;
        replace_len -= 2;
        if(ret < v_old)
            ret -= (1 + v_old);
        else
            ret -= v_old;
        if((uint32_t)ret + (uint32_t)v_new > 0xFFFF)
            ret += (v_new + 1);
        else
            ret += v_new;
    }
    return ~ret;
}
