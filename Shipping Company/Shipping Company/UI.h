#pragma once
#include<iostream>
#include"Company.h"
#include <chrono>
#include <thread>
#include <string>
class Company;
using namespace std;
class UI
{
	string outputfile;
	int mode;
public:
	string askmode();
	void modeffect(Company* cmpnyptr,int hour,int day);
	void print(Company* cmpnyptr);
	string getoutput() const;
	void printfail();
	//void makeoutputfile(Company* cmpnyptr);
};