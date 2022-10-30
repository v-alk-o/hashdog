#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/evp.h>

#include "arg_utils.h"


void parse_args(int argc, char** argv, char** mode, char** digest, char** input_filename, char** output_filename)
{
	int option = 0;

	while ((option = getopt(argc, argv, "m:d:f:o:h")) != -1)
	{
        switch (option)
		{
			case 'm':
				*mode = optarg;
				break;

			case 'd':
				*digest = optarg;
				break;

			case 'f':
				*input_filename = optarg;
                   		break;
			case 'o':
				*output_filename = optarg;
                   		break;

			case 'h':
			case '?':
			default:
                fprintf(stderr, "Usage: %s [-m generate|lookup] [-d digest] [-f filename] [-o output]\n", argv[0]);
                exit(EXIT_FAILURE);
        	}
	}

	if (optind == 1)
	{
        fprintf(stderr, "Usage: %s [-m generate|lookup] [-d digest] [-f filename] [-o output]\n", argv[0]);
        exit(EXIT_FAILURE);
	}


	if(*mode == NULL)
	{
		fprintf(stderr, "Required argument -m\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if(strcmp(*mode, "generate") != 0 && strcmp(*mode, "lookup"))
		{
			fprintf(stderr, "Mode should be either 'generate' or 'lookup'\n");
			exit(EXIT_FAILURE);
		}
	}

	if(strcmp(*mode, "generate") == 0)
	{
		if(*digest == NULL)
		{
			fprintf(stderr, "Required argument -d\n");
			exit(EXIT_FAILURE);
		}
	}
}