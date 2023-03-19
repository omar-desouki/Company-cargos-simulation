#include <iostream>
#include "queue.h"
#include<fstream>
#include"Company.h"

using namespace std;

int main()
{
	Company* cptr=new Company();
	cptr->simulate();
	delete cptr;
	return 0;
}