#include<stdio.h>
#include <stdint.h>

uint8_t keystreamByte[30] = {
  0xb8,0x08,0x29,0x4a,0xd6,0x57,0x37,0x6b,
  0x28,0xe5,0x95,0x34,0x26,0x52,0x6b,0xe5,
  0xc5,0xe7,0x81,0x4e,0x2b,0xce,0x11,0x4d,
  0x5e,0x11,0x22,0x57,0x38,0x33
};

uint8_t L[256];

unsigned A;
unsigned B;
unsigned C;



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

uint8_t stepAB[12][2] = {
  {0x0, 0x1},
  {0x0, 0x0},
  {0x1, 0x0},
  {0x1, 0x1},
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
  //TODO
  printf("====Fills after 1st iteration\n");
}


void solve(uint8_t level){
  if(level == 30){
    printResult();
  }else if(level == 0){
    for(int i = 0; i < 256; i++){
      for(int j = 0; j < 256; j++){
        A = i;
        B = j;
        X =  keystreamByte[0]  - L[A[0]]  - L[B[0]];
        solve(1);
      }
    }
  }else{
    for(int i = 0; i < 12; i++){
      A = stepAB << l
      B =
      if(i < 4){
        X[level] = keystreamByte[level] - L[A[level]] - L[B[level]];
      }else{

      }


      A[level] = ((A[level - 1] >> 1) & 0x7f)+ (stepAB1[i][0] << 7);
      B[level] = ((B[level - 1] >> 1) & 0x7f)+ (stepAB1[i][1] << 7);
      X[level] = keystreamByte[level] - L[A[level]] - L[B[level]];
      // printf("============\n" );
      // printf("level : %d\n", level);
      // printf("A[level - 1] : %x\n", A[level - 1]);
      // printf("B[level - 1] : %x\n", B[level - 1]);
      // printf("X[level - 1] : %x\n", X[level - 1]);
      // printf("A[level] : %x\n", A[level]);
      // printf("B[level] : %x\n", B[level]);
      // printf("X[level] : %x\n", X[level]);

      if(isValidPost(X[level], X[level - 1])){
      //   printf("============\n" );
      //  printf("level : %d\n", level);
      //   printf("X[level - 1] : %x\n", X[level - 1]);
      //   printf("X[level] : %x\n", X[level]);
        solve(level + 1);
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
