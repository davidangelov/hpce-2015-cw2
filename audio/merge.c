#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

int main(int argc, char *argv[])
{	

	//fprintf(stderr, "argv[1] is: %s :", argv[1]);
	//fprintf(stderr, "argv[2] is: %s :", argv[2]);

	FILE *fp1;
	FILE *fp2;
	size_t result_fp1, result_fp2;
	long fp1_Size, fp2_Size;
	fp1=fopen(argv[1], "r");
	if (fp1==NULL) {fputs ("File error",stderr); exit (1);}
	fseek (fp1 , 0 , SEEK_END);
  	fp1_Size = ftell (fp1);
  	rewind (fp1);
	//fprintf(stderr, "fp1_Size = %ld", fp1_Size);


	fp2=fopen(argv[2], "r");
	if (fp2==NULL) {fputs ("File error",stderr); exit (2);}
	fseek (fp2 , 0 , SEEK_END);
  	fp2_Size = ftell (fp2);
  	rewind (fp2);
	//fprintf(stderr, "fp2_Size = %ld", fp2_Size);

	while(1){
		int i = 0;
		
		int16_t samples_fp1[512*2];
		int16_t samples_fp2[512*2];
		int16_t output[512*2];
		unsigned cbBuffer=sizeof(samples_fp1);	// size in bytes of  one stereo sample (4 bytes)

		result_fp1 = fread(samples_fp1, 2, 1024, fp1);
		//fprintf(stderr, "result_fp1 = %ld", result_fp1);
		if (result_fp1 == fp1_Size) {fputs ("Reading error",stderr); exit (3);}
		result_fp2 = fread(samples_fp2, 2, 1024, fp2);
		//fprintf(stderr, "result_fp2 = %ld", result_fp2);
		if (result_fp2 == fp2_Size) {fputs ("Reading error",stderr); exit (4);}

		while(i < 1024)
		{
			output[i] = (samples_fp1[i] + samples_fp2[i])/2;
			i++;
		}
		
		//fprintf(stderr, "first_file: %d and second_file: %d\n", samples_fp1, samples);
		// Read one sample from input
		// Currently there is a lot of overhead here, as we have all the overhead of a system function call,
		// but only get four bytes in return.
		
		// Copy one sample to output
		// And again, a lot of overhead just to get four bytes.
		int done=write(STDOUT_FILENO, output, cbBuffer);
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(done!=cbBuffer){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
		}
	}

	return 0;
}
