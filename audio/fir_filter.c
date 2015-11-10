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
	//FILE *fp2;
	double * co_buffer;
	size_t result_fp1; //, result_fp2;
	long fp1_Size; //, fp2_Size;
	fp1=fopen(argv[1], "r");
	if (fp1==NULL) {fputs ("File error",stderr); exit (1);}
	fseek (fp1 , 0 , SEEK_END);
  	fp1_Size = ftell (fp1);
  	rewind (fp1);

	co_buffer = (double*) malloc (sizeof(double)*fp1_Size);
  	if (co_buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	result_fp1 = fread(co_buffer, 2, 1024, fp1);
	//if (result_fp1 == fp1_Size) {fputs ("Reading error",stderr); exit (3);}

	//fprintf(stderr, "fp1_Size = %ld", fp1_Size);

	/*
	fp2=fopen(argv[2], "r");
	if (fp2==NULL) {fputs ("File error",stderr); exit (2);}
	fseek (fp2 , 0 , SEEK_END);
  	fp2_Size = ftell (fp2);
  	rewind (fp2);
	*/
	//fprintf(stderr, "fp2_Size = %ld", fp2_Size);

	while(1){

		double output = 0;
		// Buffer containing one stereo sample sample (left and right, both 16 bit).
		int16_t samples[2];
		unsigned cbBuffer=sizeof(samples);	// size in bytes of  one stereo sample (4 bytes)
		
		int co_size = sizeof(co_buffer)/sizeof(co_buffer[0]);

		int got=read(STDIN_FILENO, samples, cbBuffer);
		if(got<0){
			fprintf(stderr, "%s : Read from stdin failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(got==0){
			break;	 // end of file
		}else if(got!=cbBuffer){
			fprintf(stderr, "%s : Did not receive expected number of bytes.\n", argv[0]);
			exit(1);
		}

		double buffer[co_size];
		int i;
	  	for (i = co_size - 1; i>0; i--)
		{
  		buffer[i] = buffer[i - 1];
  		}
		buffer[0] = samples[0];

		for(i = 0; i < co_size; i++)
		{
  			output += co_buffer[i]*buffer[i];	
  		}
		samples[0] = output;
		samples[1] = output;
		
		
		//int16_t samples_fp1[512*2];
		//int16_t samples_fp2[512*2];
		//int16_t output[512*2];
		//unsigned cbBuffer=sizeof(co_buffer);	// size in bytes of  one stereo sample (4 bytes)

		//result_fp1 = fread(co_buffer, 2, 1024, fp1);
		//fprintf(stderr, "result_fp1 = %ld", result_fp1);
		//if (result_fp1 == fp1_Size) {fputs ("Reading error",stderr); exit (3);}
		//result_fp2 = fread(samples_fp2, 2, 1024, fp2);
		//fprintf(stderr, "result_fp2 = %ld", result_fp2);
		//if (result_fp2 == fp2_Size) {fputs ("Reading error",stderr); exit (4);}

		//while(i < 1024)
		//{
		//	output[i] = (samples_fp1[i] + samples_fp2[i])/2;
		//	i++;
		//}
		
		//fprintf(stderr, "first_file: %d and second_file: %d\n", samples_fp1, samples);
		// Read one sample from input
		// Currently there is a lot of overhead here, as we have all the overhead of a system function call,
		// but only get four bytes in return.
		
		// Copy one sample to output
		// And again, a lot of overhead just to get four bytes.



		int done=write(STDOUT_FILENO, samples, cbBuffer);
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(done!=cbBuffer){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
		}
	}

	return 0;
}
