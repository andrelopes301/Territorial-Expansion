#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "imperio.h"
#include "territorio.h"

class Interface {
private:

	static int ano;
	static int turno;

public:
	Interface();
	~Interface();
	void iniciarTurno();
	void help(int fase);
	int getTurno();
	int getAno();

};

#endif