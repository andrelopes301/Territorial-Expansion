#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "imperio.h"
#include "territorio.h"
#include "utils.h"

using namespace std;

int Imperio::fatorSorte = 0;
int Imperio::forcaMilitar = 0;
int Imperio::ouroCofre = 0;
int Imperio::produtosArmazem = 0;
int Imperio::forcaMilitarMax = 3;
int Imperio::capMaxArmazem = 3;
int Imperio::capMaxCofre = 3;
bool Imperio::drones = 0;
bool Imperio::misseis = 0;
bool Imperio::defesas = 0;
bool Imperio::bolsa = 0;
bool Imperio::banco = 0;
int Imperio::Pvitoria = 0;


Imperio::Imperio() {

	
}

Imperio::~Imperio() {

}

int Imperio::getFatorSorte() {
	return this->fatorSorte;
}

int Imperio::fatorSorteR() {

	srand((unsigned int)time(NULL));
	int sorte = rand() % 6 + 1;

	return sorte;
}

int Imperio::getForcaMilitar() {
	return this->forcaMilitar;
}

int Imperio::getforcaMilitarMax() {
	return this->forcaMilitarMax;
}

int Imperio::getcapMaxCofre() {
	return this->capMaxCofre;
}

int Imperio::getcapMaxArmazem() {
	return this->capMaxArmazem;
}

int Imperio::getdrones() {
	return this->drones;
}

int Imperio::getmisseis() {
	return this->misseis;
}

int Imperio::getdefesas() {
	return this->defesas;
}

int Imperio::getbolsa() {
	return this->bolsa;
}

int Imperio::getbanco() {
	return this->banco;
}
int Imperio::getPvitoria() {
	return this->Pvitoria;
}



void Imperio::saldo() {
		cout << endl << "===================================================" << endl << endl;
		cout << "	  Saldo disponivel no Imperio: " << endl << endl
		<< "	   Ouro: " << ouroCofre << "/"<< capMaxCofre <<" | Produtos: " << produtosArmazem<<"/"<< capMaxArmazem << endl << endl;
		cout << "===================================================" << endl<<endl;
}


//Fase 2 - Fase de recolhas de produtos e ouro

void Imperio::updateimperio(int incT, vector <Territorio* > territorios) {
	int produtos = produtosArmazem, ouro = ouroCofre;
	Territorio Terr;
	Interface inter;

	Terr.getOuro();

	

	for (Territorio *t: territorios) {
		
		if (t->nome == "inicial") {
			ouroCofre++;
			produtosArmazem++;
		}
		if (t->estado == 1) {
	
			Pvitoria += t->pontosVit;
			
			if (t->identifier == "planicie") {
				
				produtosArmazem += t->prodTurno;
					
				
				ouroCofre += t->ouroTurno;
				
			}
			else if (t->identifier == "montanha") {

				if (t->turnoConquista < incT - 2) {
					produtosArmazem += t->prodTurno;
					
				}
			}
			else if (t->identifier == "mina") {
				
					ouroCofre += t->ouroTurno;
					
				
			}
			else if (t->identifier == "duna") {
				produtosArmazem++;
			}
			else if (t->identifier == "castelo") {
				produtosArmazem += t->prodTurno;
				ouroCofre += t->ouroTurno;
				
			}
			else if (t->identifier == "refugio") {
				ouroCofre += t->ouroTurno;
				
			}
			else if (t->identifier == "pescaria") {
				
					produtosArmazem += t->prodTurno;
					
				
			}
		}
	}

	//cout << "Capacidade Maxima do Cofre(ouro): " << getcapMaxCofre() << endl;
	//cout << "Capacidade Maxima do Armazem(produtos): " << getcapMaxArmazem() << endl;


	cout << " Recebeu " << ouroCofre - ouro << " unidades de ouro" << endl;
	cout << " Recebeu " << produtosArmazem - produtos << " unidades de produto" << endl<<endl;


	if (ouroCofre > getcapMaxCofre()) {
		ouroCofre = getcapMaxCofre();
	}
	if (produtosArmazem > getcapMaxArmazem()) {
		produtosArmazem = getcapMaxArmazem();
	}

	saldo();

}

int Imperio::maisprod() {
	
	if (getbolsa() == 1) {

		if (ouroCofre > 1) {
			ouroCofre -= 2;
			produtosArmazem++;
			cout << "ouroCofre - 2 ("<< ouroCofre<<")" << endl << "produtosArmazem++(" << produtosArmazem << ")"<< endl;
			return 1;
		}
		else {
			cout << "<AVISO> Ouro insuficiente!" << endl;
			return 0;
		}
	}
	else {
		cout << "<AVISO> A Tecnologia 'Bolsa de valores' ainda nao foi adquirida!" << endl;
		return 0;
	}
}

int Imperio::maisouro() {
	
	if (getbolsa() == 1) {

		if (produtosArmazem > 1) {
			produtosArmazem -= 2;
			ouroCofre++;
			cout << "produtosArmazem - 2 (" << produtosArmazem << ")" << endl << "ouroCofre++(" << ouroCofre << ")" << endl;
			return 1;
		}
		else{
			cout << "<AVISO> Produtos insuficientes!" << endl;
			return 0;
		}
	}
	else {
		cout << "<AVISO> A Tecnologia 'Bolsa de valores' ainda nao foi adquirida!" << endl;
		return 0;
	}
}

//Fase 3 - Fase de compra de unidades militares e tecnologia

int Imperio::maismilitar(){

	if (ouroCofre < 1 || produtosArmazem < 1) {
		cout <<endl << "<AVISO> Ouro ou produtos insuficientes!" << endl;
		return 0;
	}
	else if (forcaMilitar == getforcaMilitarMax()) {
		cout << endl << "<AVISO> A forca militar do seu imperio encontra-se no maximo!" << endl;
		return 0;
	}
	else {
		produtosArmazem--;
		ouroCofre--;
		forcaMilitar++;
		cout << endl << "Produtos em armazem-- (" << produtosArmazem << ")" << endl;
		cout << "Ouro do Cofre-- (" << ouroCofre << ")" << endl; 
		cout << "Forca Militar++ (" << forcaMilitar << ")" << endl;
		
		if (forcaMilitar == getforcaMilitarMax()) 
			cout << "Atingiu a forca militar maxima!" << endl;
		return 1;
	}
}

int Imperio::compraTec(vector <string> comandos) {

	string tipoTec;
	//tipoTec = comandos[1] + comandos[2];
	tipoTec = comandos[1];
	//cout << tipoTec << endl;

	if (tipoTec == "drones") {
		if (ouroCofre >= 3) {
			ouroCofre -= 3;
			drones = 1;
			forcaMilitarMax = 5;
			cout << "Adquiriu a tecnologia 'Drones Militares'" << endl
				<< "A sua forca militar maxima passa a ser " << forcaMilitarMax << " unidades militares" << endl;

		}
		else {
			cout << " Saldo insuficiente" << endl;
		}

		return 1;
	}
	else if (tipoTec == "misseis") {
		if (ouroCofre >= 4) {
			ouroCofre -= 4;
			misseis = 1;
			cout << " Adquiriu a tecnologia 'Misseis Teleguiados'" << endl;
		}
		else {
			cout << "Saldo insuficiente!" << endl;
		}
		return 1;
	}
	else if (tipoTec == "defesas") {
		if (ouroCofre >= 4) {
			ouroCofre -= 4;
			defesas = 1;
			cout << " Adquiriu a tecnologia 'Defesas Territoriais'" << endl;
		}
		else {
			cout << " Saldo insuficiente" << endl;
		}
		return 1;
	}
	else if (tipoTec == "bolsa") {
		if (ouroCofre >= 2) {
			ouroCofre -= 2;
			bolsa = 1;
			cout << " Adquiriu a tecnologia 'Bolsa de Valores'" << endl;
		}
		else {
			cout << " Saldo insuficiente" << endl;
		}
		return 1;
	}
	else if (tipoTec == "banco") {
		if (ouroCofre >= 3) {
			ouroCofre -= 3;
			banco = 1;
			capMaxArmazem = 5;
			capMaxCofre = 5;

			cout << " Adquiriu a tecnologia 'Banco Central'" << endl;
		}
		else {
			cout << " Saldo insuficiente" << endl;
		}
		return 1;
	}
	else {
		return 0;
	}
	
}

// Fase 4 - Fase de eventos

int Imperio::faseEventos(vector <Territorio* >territorios) {
	int end;
	srand((unsigned int)time(NULL));
	int evento = rand() % 4; //Gera valor entre 0 e 3 correspondente a uma fase de eventos

	switch (evento) {
	case(0):
		// Recurso Abandonado
		cout << " Evento ocorrido: Recurso Abandonado" << endl << endl;
		recurso_abandonado();
		return 0;
		break;
	case(1):
		// Invasao
		cout << " Evento ocorrido: Invasao" << endl << endl;
		end = invasao(territorios);
		return end;
		break;
	case(2):
		//Aliança Diplomática
		cout << " Evento ocorrido: Alianca Diplomatica" << endl << endl;
		alianca_diplomatica();
		return 0;
		break;
	case(3):
		//Sem evento
		cout << " Nao ocorreu nenhum evento neste turno!" << endl;
		return 0;
		break;
	}

	return 0;
}

void Imperio::recurso_abandonado() {

	Interface inter;

	if (inter.getAno() == 1) {

		cout << "<INFO>: O recurso abandonado encontrado foi um produto!" << endl;

		if (produtosArmazem < capMaxArmazem) {
			produtosArmazem++;
			cout << "<INFO>: O produto foi adicionado ao armazem de produtos com sucesso!" << endl;
		}
		else
			cout << "<INFO>: Capacidade do armazem de produtos ja esta no maximo! O produto encontrado nao foi adicionado!" << endl;
	}
	else if (inter.getAno() == 2) {

		cout << "<INFO>: O recurso abandonado encontrado foi um ouro!" << endl;

		if (ouroCofre < capMaxCofre) {
			ouroCofre++;
			cout << "<INFO>: Uma unidade de ouro foi adicionada ao cofre de ouro com sucesso!" << endl;
		}
		else
			cout << "<INFO>: Capacidade do cofre de ouro ja esta no maximo! O ouro encontrado nao foi adicionado!" << endl;
	}

}

int Imperio::invasao(vector <Territorio* >territorios) {
	int defe0 = 0, defe1 = 0;
	int ultimo = 0, ultimoA = 0;
	int forca_invasao = 0;
	int invasao = 0;
	int numTerrConq = 0;
	int valida = 0;
	Territorio terr;
	Interface interface;

	if (interface.getAno() == 1)
		forca_invasao = 2;
	else if (interface.getAno() == 2)
		forca_invasao = 3;

	int fatorsorte = rand() % 6 + 1; // Entre 1 e 6
	invasao = fatorsorte + forca_invasao;


	for (Territorio* t : territorios) {

		if (t->turnoConquista > ultimo) {
			ultimo = t->turnoConquista;
		}

		if (t->turnoConquista > ultimoA) {
			ultimoA = t->anoConquista;
		}
	}
	for (Territorio* t : territorios) {


		valida = 0;
		defe0 = t->getResistencia() + 1;
		if (defesas == 1) { // se o imperio possuir tecnologia defesas territoriais
			defe1 = defe0;
		}
		else {
			defe1 = t->getResistencia();
		}
		if (t->turnoConquista == ultimo && t->anoConquista == ultimoA) {

			

			if (invasao < defe1) {
				cout << "<INFO>: Tentativa de invasao do Inimigo falhada!" << endl;
				break;
			}
			else if(invasao > defe1){
				t->estado = 0;
				valida = 1;
				cout << "<INFO>: O seu territorio " << t->getNome() << " foi conquistado pelo inimigo!" << endl;
				Pvitoria -= t->pontosVit;
				break;
			}
		}



		

	}
	for (Territorio* t : territorios) {

		if (t->estado == 1)
			numTerrConq++;
	}
	
	if (numTerrConq == 0) {
		return 1;
	}
	return 0;
}

void Imperio::alianca_diplomatica() {

	if (forcaMilitar < forcaMilitarMax){
		forcaMilitar += 1;
		cout << "A forca militar foi aumentada em uma unidade!" << endl;
	}

}


// Comandos Debug 				       		

int Imperio::feventos(vector <string> comandos, vector <Territorio* >territorios) {
	int end;
	if (comandos[1] == "recurso") {
		// Recurso Abandonado
		cout << endl << " Evento ocorrido: 'Recurso Abandonado'" << endl << endl;
		recurso_abandonado();
		return 0;
	}
	else if (comandos[1] == "invasao") {
		// Invasao
		cout << endl << " Evento ocorrido: 'Invasao'" << endl << endl;
		end = invasao(territorios);
		return end;
	}
	else if (comandos[1] == "alianca") {
		//Aliança Diplomática
		cout << endl << " Evento ocorrido: 'Alianca Diplomatica'" << endl;
		alianca_diplomatica();
		return 0;
	}
	else if (comandos[1] == "sem") {
		//Sem evento
		cout << endl << " Nao ocorreu nenhum evento!" << endl;
		return 0;
	}
	else {
		cout << endl << "<AVISO>: Evento '" << comandos[1] <<"' nao existe!" << endl;
		return 0;
	}
}

void Imperio::modifica(vector <string> comandos) {

	//Alterar a quantidade de ouro no cofre ou a quantidade de produtos no armazem
	//modifica [produto/ouro] [Quantidade]

	int n;
	string tipo;

	tipo = comandos[1];
	n = atoi(comandos[2].c_str());

	if (tipo == "ouro") {
		ouroCofre = n;
		capMaxCofre = n;
		cout << "<AVISO> O seu Imperio tem agora " << capMaxCofre << " unidades de ouro no cofre!" << endl;
	}

	else if (tipo == "prod") {
		produtosArmazem = n;
		capMaxArmazem = n;
		cout << "<AVISO> O seu Imperio tem agora " << capMaxArmazem << " unidades de produtos no armazem!" << endl;
	}


}

void Imperio::toma(vector <string> comandos, vector <Territorio* > territorios) {

	
	//toma [terr/tec] [nome]
	Territorio Terr;
	//Imperio I;
	string tipoT, nomeT;
	Interface inter;
	int valida = 0;
	tipoT = comandos[1];
	nomeT = comandos[2];

	

	if (tipoT == "terr") {
		for (Territorio* t : territorios) {
			valida = 0;
			if (t->getNome() == nomeT && t->estado == 0) {
				t->estado = 1;
				t->anoConquista = inter.getAno();
				t->turnoConquista = inter.getTurno();
				cout << "<SUCESSO>: Territorio '" << t->getNome() << "' conquistado!" << endl;
				break;
			}
			else if (t->getNome() == nomeT && t->estado == 1) {
				cout << "<AVISO>: Territorio '" << t->getNome() << "' ja se encontra conquistado!" << endl;
				break;
			}
			else
				valida = 1;

		}
		if(valida==1)
			cout << "<AVISO>: Territorio Invalido!" << endl;
		
	
	}
	else if (tipoT == "tec") {
		if (nomeT == "drones") {
			if (getdrones() != 1) {
				drones = 1;
				cout << "<AVISO>: A tecnologia Drones Militares foi adquirida!" << endl;
			}
			else {
				cout << "<AVISO>: A tecnologia Drones Militares ja se encontra adquirida!" << endl;
			}
		}
		else if (nomeT == "misseis") {
			if (getmisseis() != 1) {
				misseis = 1;
				cout << "<AVISO>: A tecnologia Misseis Teleguiados foi adquirida!" << endl;
			}
			else {
				cout << "<AVISO>: A tecnologia Misseis Teleguiados ja se encontra adquirida!" << endl;
			}
		}
		else if (nomeT == "bolsa") {
			if (getbolsa() != 1) {
				bolsa = 1;
				cout << "<AVISO>: A tecnologia Bolsa de Valores foi adquirida!" << endl;
			}
			else {
				cout << "<AVISO>: A tecnologia Bolsa de Valores ja se encontra adquirida!" << endl;
			}
		}
		else if (nomeT == "banco") {
			if (getbanco() != 1) {
				banco = 1;
				cout << "<AVISO>: A tecnologia Banco Central foi adquirida!" << endl;
			}
			else {
				cout << "<AVISO>: A tecnologia Banco Central foi encontra adquirida!" << endl;
			}
		}
		else {
			cout << "<AVISO>: Territorio Invalido!" << endl;
		}
	}
	

}

void Imperio::checkPV(vector <Territorio* >territorios) {
	int cont1 = 0, cont2 = 0;
	if (drones == 1 && misseis == 1 && banco == 1 && defesas == 1 && bolsa == 1) {
		Pvitoria++;
	}
	for (Territorio* t : territorios) {
		if (t->estado == 1) {
			cont1++;
		}
		cont2++;
	}
	if (cont1 == cont2) {
		Pvitoria++;
	}
}

