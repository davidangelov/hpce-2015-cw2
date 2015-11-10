#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

int main(int argc, char *argv[])
{	
	int sample_counter = 0;
	while(1){

		int16_t samples[2];            // Buffer containing one stereo sample sample (left and right, both 16 bit).
		unsigned cbBuffer=sizeof(samples);	// size in bytes of  one stereo sample (4 bytes)
		
		// Read one sample from input
		// Currently there is a lot of overhead here, as we have all the overhead of a system function call,
		// but only get four bytes in return.
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
		
		
		fprintf(stderr, "%d, %f, %d, %d \n", sample_counter, (float)sample_counter/44100, samples[0], samples[1]);
		sample_counter++;

		
	}

	return 0;
}
