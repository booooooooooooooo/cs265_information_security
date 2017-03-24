/*
Note:
void initL(unsigned char L[]) is copied from the code provided by author of problem "ORYX Stream Cipher Part I"
*/

#include<stdio.h>
#include <stdint.h>

uint8_t keystreamByte[30] = {
  0x93,0x48,0xa8,0xf4,0x41,
  0x9f,0xcf,0xdc,0xed,0x75,
  0xba,0xdc,0x6e,0xff,0x31,
  0x18,0x0c,0x85,0x14,0x89,
  0x43,0xb6,0xdb,0x6d,0x36,
  0x9a,0x57,0xaa,0x46,0x3f
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

uint8_t stepAB1[4][2] = {
  {0x0, 0x1},
  {0x0, 0x0},
  {0x1, 0x0},
  {0x1, 0x1}
};

uint8_t stepAB2[8][2] = {
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
  if( ((prev >> 1) & 0x7f) == (current & 0x7f) ) return 1;
  else return 0;
}

void printResult(){
  unsigned fillA;
  unsigned fillB;
  unsigned fillX;
  uint8_t lenfillA = 0;
  uint8_t lenfillB = 0;
  uint8_t lenfillX = 0;
  for(int i = 0; i < 25; i++){
    if(i == 0){
      fillA = (unsigned)A[0];
      fillB = (unsigned)B[0];
      fillX = (unsigned)X[0];
      lenfillA += 8;
      lenfillB += 8;
      lenfillX += 8;
    }else{
      fillX = fillX + ( ( ( (unsigned)X[i] >> 7 ) & 0x1)  << lenfillX  );
      lenfillX++;
      fillA = fillA + ( ( ( (unsigned)A[i] >> 7 ) & 0x1)  << lenfillA  );
      lenfillA++;
      uint8_t x = ((X[i] & 0x20) >> 5) & 0x1;//x is the bit in X to decide whether B steps once or twice
      // uint8_t x = ((X[i - 1] & 0x40) >> 6) & 0x1;
      if(lenfillB < 32){
        if(x == 0){//B steps once
          fillB = fillB + ( (((unsigned)B[i] >> 7 ) & 0x1 ) << lenfillB );
          lenfillB += 1;
        }else{
          fillB = fillB + ( (((unsigned)B[i] >> 6 ) & 0x3)  << lenfillB );
          lenfillB += 2;
        }
      }
    }

  }
  printf("====Fills after 1st iteration\n");

  printf("%x\n", fillX);
  printf("%x\n", fillA);
  printf("%x\n", fillB);


  if(((X[0] & 0x20) >> 5) & 0x1){
    int rd[16][3] = {
      {0, 0, 0},
      {0, 0, 1},
      {0, 0, 2},
      {0, 0, 3},
      {0, 1, 0},
      {0, 1, 1},
      {0, 1, 2},
      {0, 1, 3},
      {1, 0, 0},
      {1, 0, 1},
      {1, 0, 2},
      {1, 0, 3},
      {1, 1, 0},
      {1, 1, 1},
      {1, 1, 2},
      {1, 1, 3}
    };
    for(int i = 0; i < 16; i++){
      printf("====Initial Fills %d\n", i);
      printf("%x", (fillX << 1) + rd[i][0]);
      printf("%x", (fillA << 1) + rd[i][1]);
      printf("%x\n", (fillB << 2) + rd[i][2]);
    }
  }else{
    int rd[8][3] = {
      {0, 0, 0},
      {0, 0, 1},
      {0, 1, 0},
      {0, 1, 1},
      {1, 0, 0},
      {1, 0, 1},
      {1, 1, 0},
      {1, 1, 1}
    };
    for(int i = 0; i < 8; i++){
      printf("====Initial Fills %d\n", i);
      printf("%x", (fillX << 1) + rd[i][0]);
      printf("%x", (fillA << 1) + rd[i][1]);
      printf("%x\n", (fillB << 1) + rd[i][2]);
    }

  }



}


void solve(uint8_t level){
  if(level == 30){
    printResult();
  }else if(level == 0){
    for(int i = 0; i < 256; i++){
      for(int j = 0; j < 256; j++){
        A[0] = i;
        B[0] = j;
        X[0] =  keystreamByte[0]  - L[A[0]]  - L[B[0]];
        solve(1);
      }
    }
  }else{
    //x steps before A and B. So use the 25 bit of X[level - 1]
    uint8_t x = ((X[level - 1] & 0x40) >> 6) & 0x1;
    if(x == 0){//B shift 1
      for(int i = 0; i < 4; i++){
        A[level] = ((A[level - 1] >> 1) & 0x7f)+ (stepAB1[i][0] << 7);
        B[level] = ((B[level - 1] >> 1) & 0x7f)+ (stepAB1[i][1] << 7);
        X[level] = keystreamByte[level] - L[A[level]] - L[B[level]];

        if(isValidPost(X[level], X[level - 1])){
          solve(level + 1);
        }
      }
    }else{// B shift 2
      for(int i = 0; i < 8; i++){
        A[level] = ((A[level - 1] >> 1) & 0x7f) + (stepAB2[i][0] << 7);
        B[level] = ((B[level - 1] >> 2) & 0x3f) + (stepAB2[i][1] << 6);
        X[level] = keystreamByte[level] - L[A[level]] - L[B[level]];
        if(isValidPost(X[level], X[level - 1])){
          solve(level + 1);
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  initL(L);
  solve(0);
  return 0;
}
