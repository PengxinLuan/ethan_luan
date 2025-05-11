#ifndef CONV_H
#define CONV_H

#include <stdint.h>
#include"pulpino.h"

#define REG_CTRL (*(volatile uint32_t*)(CONV_BASE_ADDR + 0x00))
#define need_pic (*(volatile uint32_t*)(CONV_BASE_ADDR + 0x04))
#define pixel_in (*(volatile uint32_t*)(CONV_BASE_ADDR + 0x08))


#endif // STATUS_FLAG_H