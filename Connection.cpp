#include "Connection.h"
#include <iostream>

Connection::Connection()
{
	double r = ((double)rand() / (RAND_MAX));
	weightOld = r;
	weightDelta = 0;
}

Connection::~Connection()
{
}