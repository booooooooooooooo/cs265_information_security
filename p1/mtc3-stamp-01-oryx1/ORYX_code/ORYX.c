//
// Program to implement ORYX cipher
//
// Here, we only give the keystream generator,
// not full-blown encryption and decryption routines.
//
// Note that initial fills (specified in #define's)
// define the key
// Also note that L table is initialized using RC4
// (recall that the L table is known to the attacker)
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// polynomials
#define POLYNOMIAL_PX  0x8ce56011L
#define POLYNOMIAL_PA0 0xdb710641L
#define POLYNOMIAL_PA1 0xc3e887e1L
#define POLYNOMIAL_PB  0xa4031803L

// initial fills
#define INITIAL_FILL_X 0x70e8ac16L
#define INITIAL_FILL_A 0x9af1208dL
#define INITIAL_FILL_B 0x2a840fc5L


// MAXNUM == max number of fills stored at one time
// MAXSTEPS == max number of steps to iterate
#define MAXNUM 100
#define MAXSTEPS 100

// print statements
//#define PR_DETAILS
//#define PR_FILLS
#define PR_KEYSTREAM
#define PR_L

void genKeystream(unsigned long int A,
				  unsigned long int B,
				  unsigned long int X,
				  unsigned char keystreamByte[],
				  unsigned char L[],
				  int N);

unsigned long int stepX(unsigned long int X);

unsigned long int stepA(unsigned long int A,
						unsigned long int X);

unsigned long int stepB(unsigned long int B,
						unsigned long int X);

void initL(unsigned char L[]);

unsigned char high(unsigned long int X);


//
// begin main
//
int main(int argc, const char *argv[])
{
    int bytes;

	unsigned long int X,
					  A,
					  B;

	unsigned char keystreamByte[MAXSTEPS],
				  L[256];// known permutation

    if(argc != 2)
    {
oops:   fprintf(stderr, "\nUsage: %s numKeystreamBytes\n\n", argv[0]);
        fprintf(stderr, "where numKeystreamBytes == no. of keystream bytes to generate\n\n");
        exit(0);
    }

	bytes = atoi(argv[1]);
	if(bytes > MAXSTEPS)
	{
		fprintf(stderr, "\n\nError --- numKeystreamBytes must be <= %d\n\n", MAXSTEPS);
		goto oops;
	}

	// initial fills of K, A and B
	X = INITIAL_FILL_X;
	A = INITIAL_FILL_A;
	B = INITIAL_FILL_B;

	printf("\ninitial X = %08lx\n", X);
	printf("initial A = %08lx\n", A);
	printf("initial B = %08lx\n", B);

	printf("\ninitial (X >> 1) = %08lx\n", (X >> 1));
	printf("initial (A >> 1) = %08lx\n", (A >> 1));
	printf("initial (B >> 1) = %08lx\n", (B >> 1));
	printf("initial (B >> 2) = %08lx\n\n", (B >> 2));

	// initialization L[] permutation
	initL(L);

	// generate bytes bytes of keystream
	genKeystream(A, B, X, keystreamByte, L, bytes);

	printf("\nkeystream bytes generated = %d\n\n", bytes);

} // end main


//
// genKeystream --- generate the keystream bytes
//
void genKeystream(unsigned long int A,
				  unsigned long int B,
				  unsigned long int X,
				  unsigned char keystreamByte[],
				  unsigned char L[],
				  int N)
{
	int i;

	// generate N keystream bytes
	for(i = 0; i < N; ++i)
	{
		// step register X
		X = stepX(X);

		// step register A
		A = stepA(A, X);

		// step register B
		B = stepB(B, X);

		// calculate keystream byte
		keystreamByte[i] = (L[high(A)] + L[high(B)] + high(X)) & 0xff;
#ifdef PR_FILLS
		printf("X = %08lx\n", X);
		printf("A = %08lx\n", A);
		printf("B = %08lx\n", B);
#endif

#ifdef PR_KEYSTREAM
		printf("keystreamByte[%d] = %02x\n", i, keystreamByte[i]);
#endif

	}// next i

}// end genKeystream


//
// stepX -- step register X
//
unsigned long int stepX(unsigned long int X)
{
	static unsigned long int PX = POLYNOMIAL_PX;

	unsigned long int t;

	// new bit == poppar(X & PX)
	t = X & PX;

	t = (t >> 16) ^ t;
	t = (t >> 8) ^ t;
	t = (t >> 4) ^ t;
	t = (t >> 2) ^ t;
	t = ((t >> 1) ^ t) & 0x1;

	// put new bit in position 0
	t = (X >> 1) | (t << 31);

	return(t);

}// end stepX


//
// stepA --- step register A
//
unsigned long int stepA(unsigned long int A, unsigned long int X)
{
	static unsigned long int PA0 = POLYNOMIAL_PA0;
	static unsigned long int PA1 = POLYNOMIAL_PA1;

	unsigned long int t;

	int x;

	// x = X29 determines the polynomial
	x = ((X & 0x4) >> 2) & 0x1;


	// if x == 0 step A using PA0
	// else step A using PA1
	if(x == 0)
	{
		t = A & PA0;
	}
	else
	{
		t = A & PA1;
	}

	// new bit == poppar(A & PA)
	t = (t >> 16) ^ t;
	t = (t >> 8) ^ t;
	t = (t >> 4) ^ t;
	t = (t >> 2) ^ t;
	t = ((t >> 1) ^ t) & 0x1;

	// shift new bit to position 0
	t = (A >> 1) | (t << 31);

	return(t);

}// end stepA


//
// stepB --- step register B
//
unsigned long int stepB(unsigned long int B, unsigned long int X)
{
	static unsigned long int PB = POLYNOMIAL_PB;

	unsigned long int t0,
					  t1;

	int x;

	// x = X26 determines whether B steps once or twice
	x = ((X & 0x20) >> 5) & 0x1;

	// step B once

	// new bit == poppar(B & PB)
	t0 = B & PB;

	t0 = (t0 >> 16) ^ t0;
	t0 = (t0 >> 8) ^ t0;
	t0 = (t0 >> 4) ^ t0;
	t0 = (t0 >> 2) ^ t0;
	t0 = ((t0 >> 1) ^ t0) & 0x1;

	// shift new bit to position 0
	t0 = (B >> 1) | (t0 << 31);

	// if x == 1, step B again
	if(x == 1)
	{
		// new bit == poppar(t0 & PB)
		t1 = t0 & PB;

		t1 = (t1 >> 16) ^ t1;
		t1 = (t1 >> 8) ^ t1;
		t1 = (t1 >> 4) ^ t1;
		t1 = (t1 >> 2) ^ t1;
		t1 = ((t1 >> 1) ^ t1) & 0x1;

		// shift new bit to position 0
		t1 = (t0 >> 1) | (t1 << 31);

		return(t1);
	}
	else
	{
		return(t0);
	}

}// end stepB


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

#ifdef PR_L
		printf("%02x ", L[i]);
		if((i & 0xf) == 0xf)
		{
			printf("\n");
		}
#endif

	}// next i

#ifdef PR_L
	printf("\n");
#endif

}// end initL


//
// high --- mask off the high 8 bits
//          ( which are actually the low-order bits)
//
unsigned char high(unsigned long int X)
{
	return(X & 0xff);

}// end high
