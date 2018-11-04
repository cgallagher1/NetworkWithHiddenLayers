#include "Connection.h"
#include <iostream>

Connection::Connection()
{
	double r = (rand() % 2) - 1;
	weightOld = r;
	weightDelta = 0;
}

Connection::~Connection()
{
}