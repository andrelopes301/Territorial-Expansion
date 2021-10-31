#ifndef IMPERIO_H
#define IMPERIO_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "territorio.h"
#include "utils.h"


class Imperio
{
	friend class Territorio;

private:
	int static fatorSorte;
	int static ouroCofre;
	int static produtosArmazem;
	int static capMaxArmazem;
	int static capMaxCofre;
	int static forcaMilitar;
	int static forcaMilitarMax;
	bool static drones;
	bool static misseis;
	bool static defesas;
	bool static bolsa;
	bool static banco;
	int static Pvitoria;

public:

	


	Imperio();
	~Imperio(); 
	int getFatorSorte();
	int fatorSorteR();
	int getforcaMilitarMax();
	int getForcaMilitar();
	int getcapMaxArmazem();
	int getcapMaxCofre();
	int getdrones();
	int getmisseis();
	int getdefesas();
	int getbolsa();
	int getbanco();
	void saldo();
	int getPvitoria();
	void checkPV(std::vector <Territorio* >territorios);
	


//Fase 2 - Fase de recolhas de produtos e ouro

	void updateimperio(int incT, std::vector <Territorio* >territorios);
	int maisprod();
	int maisouro();

//Fase 3 - Fase de compra de unidades militares e tecnologia

	int maismilitar();
	int compraTec(std::vector <std::string> comandos);

//Fase 4 - Fase de eventos
	int faseEventos(std::vector <Territorio* >territorios);
	void recurso_abandonado();
	int invasao(std::vector <Territorio* >territorios);
	void alianca_diplomatica();

// DEBUG
	int feventos(std::vector<std::string>comandos, std::vector <Territorio* >territorios);
	void modifica(std::vector<std::string>comandos);
	void toma(std::vector<std::string>comandos, std::vector <Territorio* > territorios);

};


#endif


