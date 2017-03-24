#include<stdio.h>
#include <stdint.h>

int main(){
  uint8_t block[16] = {0x00, 0x56, 0x67, 0x44, 0x22, 0x89, 0xab, 0x4c, 0x5a, 0x11, 0xff, 0xf0,0x11, 0x11, 0x33, 0xaa};

  for(int i = 0; i <16; i++){
    printf("%d  ", block[i]);
  }
  printf("\n");



  mixColumn(block);

  for(int i = 0; i <16; i++){
    printf("%d  ", block[i]);
  }
  printf("\n");

  
  mixColumnInv(block);

  for(int i = 0; i <16; i++){
    printf("%d  ", block[i]);
  }
  printf("\n");
}
