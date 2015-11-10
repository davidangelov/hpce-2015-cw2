#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

#define M_PI 3.14159265358979323846

int main(int argc, char *argv[])
{	
	int f, digit, i, j, t;
	int sample_counter = 0;

		//fprintf(stderr, " argv[0] = %s", argv[0]);
		//fprintf(stderr, " argv[1] = %s", argv[1]);
		
		if (argc == 2)
		{
			int s = strlen(argv[1]);
			//fprintf(stderr, " s = %d", s);
			i = 0;
			f = 0;
			while ( i < s )
			{	
				digit = argv[1][i]-'0';
				f = digit*pow(10,s - i - 1) + f;
				i++;
				//fprintf(stderr, " n = %d", n);
			}
		}
		else
		{
			f = 200;
		}
		//fprintf(stderr, " n = %d", n);
		//n = 1;
		sample_counter = 0;
	while(1){
// Buffer containing one stereo sample sample (left and right, both 16 bit).
		int16_t samples[2*512];
// size in bytes of  one stereo sample (4 bytes)
		unsigned cbBuffer=sizeof(samples);	
		// Read one sample from input
		// Currently there is a lot of overhead here, as we have all the overhead of a system function call,
		// but only get four bytes in return.

		for(j = 0 ; j < 2*512; j = j + 2){
			t = j + sample_counter;
			samples[j] = samples[j + 1] = 30000 * sin( ((float)t/44100) * 2 * M_PI * f);

		}
		sample_counter = (sample_counter + 1024) % 44100;
		
		
		// Copy one sample to output
		// And again, a lot of overhead just to get four bytes.
		int done=write(STDOUT_FILENO, samples, cbBuffer);
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(done!=cbBuffer){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
		}

		sample_counter++;


	}

	return 0;
}
