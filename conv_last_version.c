#include <stdint.h>
#include <stdio.h>
#include"pulpino.h"
#include"conv_input_data_flat.h"

#define RNW_CTRL (*(volatile unsigned int*)(CONV_BASE_ADDR + 0x00))
#define need_pic_signal (*(volatile unsigned int*)(CONV_BASE_ADDR + 0x04))
#define pixel_in (*(volatile unsigned int*)(CONV_BASE_ADDR + 0x08))
#define REG_SRAM (*(volatile unsigned int*)(CONV_BASE_ADDR + 0x0C))
#define REG_WEIGHT (*(volatile unsigned int*)(CONV_BASE_ADDR + 0x10))


int row_counter=0;
int channel_counter=0;
int i=0 ,g=0;
int main()
{
   uint sram_data;
 
    printf("Number:\n "); 

    RNW_CTRL=1;
    for(channel_counter = 0;channel_counter <3;channel_counter++){
        for(row_counter = 0;row_counter < 26; row_counter++){
            while(RNW_CTRL!=1){
            }
            need_pic_signal=0;
            if(row_counter == 0){
                for(i=0;i<3;i++){
                    int base_idx = channel_counter * 28 * 28 + i * 28 + 4*g;
                    for(g=0;g<7;g++){
                       pixel_in =   ((uint32_t)puic_data[base_idx + 3])        |  // 最右（最低字节）
                                    ((uint32_t)puic_data[base_idx + 2] << 8 ) |
                                    ((uint32_t)puic_data[base_idx + 1] << 16) |
                                    ((uint32_t)puic_data[base_idx + 0] << 24);   // 最左（最高字节）
	        
                    }
                }
	            for (i = 0; i < 6; i++) {
                    int base_idx = channel_counter * 25 + 4 * i;
                    REG_WEIGHT = ((uint32_t)Coeff_data[base_idx + 0] << 24) |
                                ((uint32_t)Coeff_data[base_idx + 1] << 16) |
                                ((uint32_t)Coeff_data[base_idx + 2] << 8 ) |
                                ((uint32_t)Coeff_data[base_idx + 3]);
}

// 最后一轮只发 1 个字节（最高位），其余位补 0
int last_idx = channel_counter * 25 + 24;
REG_WEIGHT = ((uint32_t)Coeff_data[last_idx] << 24);

            } else
	      for(i=0;i<7;i++){
            int base_idx_1 = channel_counter * 28 * 28 + i * 28 + row_counter+ 4*g;
                pixel_in =  ((uint32_t)puic_data[base_idx_1 + 3])        |  // 最右（最低字节）
                            ((uint32_t)puic_data[base_idx_1 + 2] << 8 ) |
                            ((uint32_t)puic_data[base_idx_1 + 1] << 16) |
                            ((uint32_t)puic_data[base_idx_1 + 0] << 24);   // 最左（最高字节）
	        
	        
            }
    
        }

    }

   

     while(RNW_CTRL!=2){}
     need_pic_signal=0;
     for(i=0;i<28*28;i++){
        sram_data = REG_SRAM;
         printf("Number:%u\n",sram_data);
              
                }
    return 0;
}
