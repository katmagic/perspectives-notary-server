
#include <stdio.h>
#include <unistd.h>

#include "bdb_storage.h"


int main (
		int const argument_count,
		char const * const * const arguments)
{
	if (argument_count != 2) {
		fprintf (stderr, "ERROR: usage: <db-path>\n");
		exit (1);
	}
	
	bdb_prime_env (arguments[1]);
	
	exit (0);
}

unsigned int notary_debug = DEBUG_ERROR;
