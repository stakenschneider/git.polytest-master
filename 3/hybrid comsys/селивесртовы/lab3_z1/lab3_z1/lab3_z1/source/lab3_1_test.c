#include <stdio.h>

int main()
{
	int inA, inB, inC, inD;
	int res;
	// For adders
	int refOut[3] = {270, 490, 1310};
	int pass;
	int i;

	inA = 10;
	inB = 20;
	inC = 30;
	inD = 40;

	// Call the adder for 5 transactions
	for (i=0; i<3; i++)
	{
		res = lab1_1(inA, inB, inC, inD);

		fprintf(stdout, "  %d*%d+%d+%d=%d \n", inA, inB, inC, inD, res);

	  // Test the output against expected results
		if (res == refOut[i])
			pass = 1;
		else
			pass = 0;

		inA=inA+10;
		inB=inB+10;
		inC=inC+10;
		inD=inD+10;
	}

	if (pass)
	{
		fprintf(stdout, "----------Pass!------------\n");
		return 0;
	}
	else
	{
		fprintf(stderr, "----------Fail!------------\n");
		return 1;
	}
}
