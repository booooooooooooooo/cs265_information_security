#include<stdio.h>
#include <stdint.h>

uint8_t keystreamByte[30] = {
  0xb8,0x08,0x29,0x4a,0xd6,0x57,0x37,0x6b,
  0x28,0xe5,0x95,0x34,0x26,0x52,0x6b,0xe5,
  0xc5,0xe7,0x81,0x4e,0x2b,0xce,0x11,0x4d,
  0x5e,0x11,0x22,0x57,0x38,0x33
};

uint8_t L[256];

uint8_t A[32];
uint8_t B[32];
uint8_t X[32];



//
// initL --- initialize the permutation L[]
//
void initL(unsigned char L[])
{
	int i,
		j,
		temp;

	int S[256],
		K[256];

	int key[10] = {0x21,0x41,0xa8,0x55,0x40,0x04,0xfa,0xbc,0x4c,0x5a};

	// Use RC4 to initialize L[]
	for(i = 0; i < 256; ++i)
	{
		S[i] = i;
		K[i] = key[i % 10];
	}

	j = 0;
	for(i = 0; i < 256; ++i)
	{
		j = (j + S[i] + K[i]) & 0xff;// x & 0xff is the same as x mod 256
		// swap S[i] and S[j]
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}

	// perm L[]
	for(i = 0; i < 256; ++i)
	{
		L[i] = S[i];

		printf("%02x ", L[i]);
		if((i & 0xf) == 0xf)
		{
			printf("\n");
		}

	}// next i

	printf("\n");

}// end initL

uint8_t fillAB1[4][2] = {
  {0x0, 0x1},
  {0x0, 0x0},
  {0x1, 0x0},
  {0x1, 0x1}
};

uint8_t fillAB2[8][2] = {

  {0x0, 0x0},
  {0x0, 0x1},
  {0x0, 0x2},
  {0x0, 0x3},
  {0x1, 0x0},
  {0x1, 0x1},
  {0x1, 0x2},
  {0x1, 0x3}
};

int isValidPost(uint8_t current, uint8_t prev){
  if( (prev >> 1) == (current & 0x7f) ) return 1;
  else return 0;
}

void printFillAfter1stIteration(){
  //convert A[], B[], X[] to fills after 1st iteration and print the fills out
  unsigned fillA;
  unsigned fillB;
  unsigned fillX;
  uint8_t lenfillA = 0;
  uint8_t lenfillB = 0;
  uint8_t lenfillX = 0;
  for(int i = 0; i < 25; i++){
    if(i == 0){
      fillA = A[0];
      fillB = B[0];
      fillX = X[0];
      lenfillA += 8;
      lenfillB += 8;
      lenfillX += 8;
    }else{
      fillA = fillA + ( (A[i] >> 7 ) & 0x1 << (lenfillA + 1) );
      fillX = fillX + ( (X[i] >> 7 ) & 0x1 << (lenfillX + 1) );
      uint8_t x = ((X[i - 1] & 0x20) >> 5) & 0x1;//x is the bit in X to decide whether B steps once or twice
      if(lenfillB < 32){
        if(x == 0){//B shift 1
          fillB = fillB + ( (B[i] >> 7 ) & 0x1 << (lenfillB + 1) );
          lenfillB += 1;
        }else{
          fillB = fillB + ( (B[i] >> 6 ) & 0x3 << (lenfillB + 2) );
          lenfillB += 2;
        }
      }
    }
  }
  printf("%d\n", fillA);
  printf("%d\n", fillB);
  printf("%d\n", fillX);
}

void solve(uint8_t level){
  if(level == 30){
    printFillAfter1stIteration();
  }else if(level == 0){
    for(int i = 0; i < 256; i++){
      for(int j = 0; j < 256; j++){
        A[0] = i;
        B[0] = j;
        X[0] =  keystreamByte[0]  ^ L[A[0]]  ^ L[B[0]];
        solve(1);
      }
    }
  }else{
    uint8_t x = ((X[level - 1] & 0x20) >> 5) & 0x1;//x is the bit in X to decide whether B steps once or twice
    if(x == 0){//B shift 1
      for(int i = 0; i < 4; i++){
        A[level] = A[level - 1] >> 1 + fillAB1[i][0] << 7;
        B[level] = B[level - 1] >> 1 + fillAB1[i][1] << 7;
        X[level] = keystreamByte[level] ^ L[A[level]] ^ L[B[level]];

        if(isValidPost(X[level], X[level - 1])){


          solve(level + 1);
        }
      }
    }else{// B shift 2


      for(int i = 0; i < 8; i++){
        A[level] = A[level - 1] >> 1 + fillAB2[i][0] << 7;
        B[level] = B[level - 1] >> 2 + fillAB2[i][1] << 6;
        X[level] = keystreamByte[level] ^ L[A[level]] ^ L[B[level]];
printf("hahaha\n" );
printf("level : %d\n", level);
printf("%d\n",X[level] );
printf("%d\n", X[level - 1]);
        if(isValidPost(X[level], X[level - 1])){

          solve(level + 1);
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  solve(0);
  return 0;
}
