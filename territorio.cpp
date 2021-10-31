#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "imperio.h"
#include "territorio.h"
#include "utils.h"

using namespace std;



Territorio::Territorio() {


	
	estado = 0;
	pontosVit = 0;
	resistencia = 0;
	ouroTurno = 0;
	prodTurno = 0;
	turnoConquista = 0;
	anoConquista = 0;
	

}

Territorio::~Territorio() {

}


TerritorioInicial::TerritorioInicial() : Territorio() {
	tipoTerr = "Inicial";
	nome = "inicial";
	resistencia = 9;
	estado = 1;
	ouroTurno = 1;
	prodTurno = 1;
}


int Planicie::nPlanicie = 0;

Planicie::Planicie() : Territorio() {
	tipoTerr = "Continente";
	identifier = "planicie";
	nome = identifier + to_string(nPlanicie);
	resistencia = 5;
	estado = 0;
	nPlanicie++;
	pontosVit = 1;
	ouroTurno = 1;
	prodTurno = 1;
}

int Montanha::nMontanha = 0;

Montanha::Montanha() : Territorio() {
	tipoTerr = "Continente";
	identifier = "montanha";
	nome = identifier + to_string(nMontanha);
	resistencia = 6;
	estado = 0;
	nMontanha++;
	pontosVit = 1;
	ouroTurno = 0;
	prodTurno = 0;
}

int Fortaleza::nFortaleza = 0;

Fortaleza::Fortaleza() : Territorio() {
	tipoTerr = "Continente";
	identifier = "fortaleza";
	nome = identifier + to_string(nFortaleza);
	resistencia = 8;
	estado = 0;
	nFortaleza++;
	pontosVit = 1;
	ouroTurno = 0;
	prodTurno = 0;
}


int Mina::nMina = 0;

Mina::Mina() : Territorio() {
	tipoTerr = "Continente";
	identifier = "mina";
	nome = identifier + to_string(nMina);
	resistencia = 5;
	estado = 0;
	nMina++;
	pontosVit = 1;
	ouroTurno = 1;
	prodTurno = 0;
}

int Duna::nDuna = 0;

Duna::Duna() : Territorio() {
	tipoTerr = "Continente";
	identifier = "duna";
	nome = identifier + to_string(nDuna);
	resistencia = 4;
	estado = 0;
	nDuna++;
	pontosVit = 1;
	ouroTurno = 0;
	prodTurno = 1;
}

int Castelo::nCastelo = 0;

Castelo::Castelo() : Territorio() {
	tipoTerr = "Continente";
	identifier = "castelo";
	nome = identifier + to_string(nCastelo);
	resistencia = 7;
	estado = 0;
	nCastelo++;
	pontosVit = 1;
	ouroTurno = 1;
	prodTurno = 3;
}

int Refugio::nRefugio = 0;

Refugio::Refugio() : Territorio() {
	tipoTerr = "Ilha";
	identifier = "refugio";
	nome = identifier + to_string(nRefugio);
	resistencia = 9;
	estado = 0;
	nRefugio++;
	pontosVit = 2;
	ouroTurno = 1;
	prodTurno = 0;
}

int Pescaria::nPescaria = 0;

Pescaria::Pescaria() : Territorio() {
	tipoTerr = "Ilha";
	identifier = "pescaria";
	nome = identifier + to_string(nPescaria);
	resistencia = 9;
	estado = 0;
	nPescaria++;
	pontosVit = 2;
	ouroTurno = 0;
	prodTurno = 2;
}

string Territorio::gettipoT() {
	return this->tipoTerr;
}
string Territorio::getNome() {
	return this->nome;
}
int Territorio::getProdutos() {
	return this->prodTurno;
}
int Territorio::getOuro() {
	return this->ouroTurno;
}
int Territorio::getResistencia() {
	return this->resistencia;
}
int Territorio::getPontosVit() {
	return this->pontosVit;
}
int Territorio::getTurnoConquista() {
	return this->turnoConquista;
}
int Territorio::getAnoConquista() {
	return this->anoConquista;
}



//Carregar Territorios 
void Territorio::carregarTerritorios(string ficheiro) {

	string line, comando, tipoT, aux;
	int maxTipo = 0, i = 0, j = 0, valida = 0;
	ifstream file(ficheiro);

	if (file.is_open()) {

		while (getline(file, line)) {
			istringstream buff(line);
			i = 0;

			while (getline(buff, aux, ' ')) {
				i++;
				if (i == 1) {
					if (aux == "cria") {
						comando = aux;
					}
					else {
						valida = 1;
						break;
					}
				}
				else if (i == 2) {
						tipoT = aux;
				}
				else if (i == 3) {

					maxTipo = stoi(aux.c_str());
					if (maxTipo < 0) {
						valida = 1;
						break;
					}

				}
			}
			if (valida == 1) {
				break;

			}

			for (int j = 1; j <= maxTipo; j++) {
			if (tipoT == "planicie") {
				Territorio* t = new Planicie();
				territorios.push_back(t);
			}
			else if (tipoT == "montanha") {
				Territorio* t = new Montanha();
				territorios.push_back(t);
			}
			else if (tipoT == "fortaleza") {
				Territorio* t = new Fortaleza();
				territorios.push_back(t);
			}
			else if (tipoT == "mina") {
				Territorio* t = new Mina();
				territorios.push_back(t);
			}
			else if (tipoT == "duna") {
				Territorio* t = new Duna();
				territorios.push_back(t);
			}
			else if (tipoT == "castelo") {
				Territorio* t = new Castelo();
				territorios.push_back(t);
			}
			else if (tipoT == "refugio") {
				Territorio* t = new Refugio();
				territorios.push_back(t);
			}
			else if (tipoT == "pescaria") {
				Territorio* t = new Pescaria();
				territorios.push_back(t);
			}
		}

		}
		if (valida == 0) {
			cout << "Ficheiro lido com sucesso!" << endl;
		}
		else {	

			territorios.clear();
			cout << "<ERRO>: Ficheiro Invalido! " << endl;
		}
	}

	file.close();


}

//Criar Territorios 
int Territorio::criarTerritorio(vector <string> comandos) {

	//cria [Tipo de Territorio] [Quantidade]
	string tipoT;
	int n, validaNum = 0, validaNome = 0;

	tipoT = comandos[1];
	n = atoi(comandos[2].c_str());

	if (n < 1) {
		validaNum = 1;
	}
	if (tipoT != "planicie" && tipoT !="montanha" && tipoT != "fortaleza" && tipoT != "mina"&& tipoT != "duna"&& tipoT != "castelo"&& tipoT != "refugio"&& tipoT != "pescaria") {
		validaNome = 1;
	}
	if (validaNum == 1) {
		cout << "<ERRO>: Numero de Territorios Invalido" << endl;
	}
	if (validaNome == 1) {
		cout << "<ERRO>: Territorio '"<<tipoT<<"' Invalido!" << endl;
	}

	if (validaNome == 0 && validaNum == 0) {
		for (int j = 1; j <= n; j++) {
			if (tipoT == "planicie") {
				Territorio* t = new Planicie();
				territorios.push_back(t);
			}
			else if (tipoT == "montanha") {
				Territorio* t = new Montanha();
				territorios.push_back(t);
			}
			else if (tipoT == "fortaleza") {
				Territorio* t = new Fortaleza();
				territorios.push_back(t);
			}
			else if (tipoT == "mina") {
				Territorio* t = new Mina();
				territorios.push_back(t);
			}
			else if (tipoT == "duna") {
				Territorio* t = new Duna();
				territorios.push_back(t);
			}
			else if (tipoT == "castelo") {
				Territorio* t = new Castelo();
				territorios.push_back(t);
			}
			else if (tipoT == "refugio") {
				Territorio* t = new Refugio();
				territorios.push_back(t);
			}
			else if (tipoT == "pescaria") {
				Territorio* t = new Pescaria();
				territorios.push_back(t);
			}
		}
		cout << "Territorios criados com sucesso!" << endl;
		return n;
	}
	else {
		return 0;
	}
}

//Criar Territorio Inicial
void Territorio::criarTinicial() {
	Territorio* t = new TerritorioInicial();
	territorios.push_back(t);
}

//Listar Territorios 
void Territorio::listarTerritorios() {
	int i = 0;
	Interface iface;
	Imperio imp;

	cout << endl << "|--------------------------------------------------Dados do Jogo---------------------------------------------|" << endl << endl;

	cout << "				         Ano: " << iface.getAno() << " | Turno: " << iface.getTurno() << " | Fator Sorte: " << imp.getFatorSorte() << endl << endl
		 << "|------------------------------------------------------------------------------------------------------------|" << endl << endl << endl ;
	cout << "|------------------------------------------------Recusos do Imperio------------------------------------------|" << endl << endl << endl;
	cout << "		                      Ouro: " << imp.ouroCofre << " | Produtos: " << imp.produtosArmazem <<" | Forca Militar: "<<imp.getForcaMilitar()<< endl << endl << endl;
	
	///listar tecnologias
	
	cout << "|----------------------------------------------Tecnologias do Imperio----------------------------------------|" << endl << endl << endl;
	
	if (imp.getbolsa() == 1) {
		cout << "					       -Bolsa de valores;" << endl;
	}
	if (imp.getbanco() == 1) {
		cout << "					       -Banco Central;" << endl;
	}
	if (imp.getdrones() == 1) {
		cout << "					       -Drones Militares;" << endl;
	}
	if (imp.getmisseis() == 1) {
		cout << "					       -Misseis Teleguiados;" << endl;
	}
	if (imp.getdefesas() == 1) {
		cout << "					       -Defesas Territoriais;" << endl;
	}

	cout << endl << endl;
	


	//Listar Territorios Conquistados
	cout << "|---------------------------------------------Territorios Conquistados---------------------------------------|" << endl << endl << endl;
	for (Territorio* t : territorios) {
		if (t->estado == 1) {
			cout << "  Tipo: " << t->gettipoT()
				<< " | Nome: " << t->getNome()
				<< " | Resistencia: " << t->getResistencia()
				<< " | Prod. Ouro: " << t->getOuro()
				<< " | Prod. Produtos: " << t->getProdutos()
				<< " | Turno Conquistado: " << t->getTurnoConquista() << " / " << t->getAnoConquista() << endl;

		}
	}

	//Listar Territorios por Conquistar

	cout << endl << endl << "|--------------------------------------------Territorios por Conquistar--------------------------------------|" << endl << endl << endl;
	for (Territorio* t : territorios) {
		if (t->estado == 0) {
			cout << "  Tipo: " << t->gettipoT()
				<< " | Nome: " << t->getNome()
				<< " | Resistencia: " << t->getResistencia() << endl;
		}
	}

	//cout << endl << endl << "|-----------------------------------------------------Produtos-----------------------------------------------|" << endl << endl
		

}

//Listar 1 Territorio 
void Territorio::listarUmTerritorio(string nome) {
	
	int i = 0, verifica = 0;

	for (Territorio* t : territorios) {
		if (t->getNome() == nome) {
			cout << endl << endl << "|---------------------------------------------Dados do Territorio---------------------------------------------|" << endl << endl;
			cout << "  Tipo: " << t->gettipoT()
				<< " | Nome: " << t->getNome()
				<< " | Resistencia: " << t->getResistencia()
				<< " | Producao Ouro/Recursos: " << t->getOuro() << " / " << t->getProdutos() << endl;
			verifica = 1;
		}
	}

	if (verifica == 0) {
		cout << endl << "<AVISO>: Territorio inexistente!" << endl;
	}

}

//Conquistar 1 Territorio 
int Territorio::conquistarTerritorio(string nome) {

	int cont = 0;
	int ataque, verifica = 0;
	int IouC = 0; // ilha ou continente 
	Imperio imp;
	Interface inter;
	int numTerrConq = 0;

	imp.fatorSorte = imp.fatorSorteR();
	ataque = imp.getForcaMilitar() + imp.fatorSorte;


	for (Territorio* t : territorios) {
		if (t->estado == 1)
			numTerrConq++;
	}


	for (Territorio* t : territorios) {

		if (t->getNome() == nome && t->estado == 0) {
			if (t->tipoTerr == "Ilha") {
				if (imp.getmisseis() == 1 && numTerrConq > 4) { // tiver pelo menos 5 territorios
					IouC = 1;
				}
				else {
					IouC = 0;
					cout << "<AVISO>: Impossivel conquistar Ilhas sem a Tecnologia 'Misseis Teleguiados' e pelo menos 5 territorios no seu Imperio!" << endl;
					verifica = 4;
				}
			}
			else {
				IouC = 1;
			}
			if (IouC == 1) {
				if (t->getResistencia() <= ataque) {
					// se a resistencia do territorio for menor que a soma da forca militar + fator sorte, o territorio vai ser conquistado
					verifica = 1;
					t->estado = 1; // Territorio Conquistado
					t->turnoConquista = inter.getTurno();	
					cout << "==========================================================" << endl << endl;
					cout << " Forca Militar: " << imp.getForcaMilitar() <<"   |   Fator Sorte: " << imp.fatorSorteR() << endl;
					cout << " Resistencia do Territorio '" << t->getNome() <<"': " << t->getResistencia() << endl;
					cout << " Forca Militar + Fator Sorte >= Resistencia do Territorio" << endl << endl;
					cout << "==========================================================" << endl << endl;
				}
				else if (t->getResistencia() > ataque) {
					verifica = 2; // Tentativa de conquista falhada
					cout << "==========================================================" << endl << endl;
					cout << " Forca Militar: " << imp.getForcaMilitar() << "   |   Fator Sorte: " << imp.fatorSorteR() << endl;
					cout << " Resistencia do Territorio '" << t->getNome() << "': " << t->getResistencia() << endl;
					cout << " Forca Militar + Fator Sorte < Resistencia do Territorio" << endl << endl;
					cout << "==========================================================" << endl << endl;

					imp.forcaMilitar = imp.forcaMilitar--;

					if (imp.forcaMilitar < 0) {
						imp.forcaMilitar = 0;
					}
				}
			}
			break;
		}
		else if (t->getNome() == nome && t->estado == 1) {
			verifica = 3;
			break;
		}
		else {
			verifica = 0;
		}
	}


	
	if (verifica == 1) {
		cout << "<SUCESSO>: Territorio conquistado!" << endl;
		cont = 1;
	}
	else if (verifica == 2) {
		cout << "<AVISO>: Tentativa de conquista falhada..." << endl;

		if (imp.forcaMilitar > 0) 
			cout << "<AVISO>: Uma unidade de forca militar foi perdida!" << endl;

		cont = 1;
	}
	else if (verifica == 3) {
		cout << "<AVISO>: Territorio ja se encontra conquistado!" << endl;
	}
	else if (verifica == 4) {
		cont = 0;
	}
	else if (verifica == 0) {
		cout << "<ERRO>: Territorio Invalido!" << endl;

	}


return cont;

	
}



void Territorio::getUpdateImp(int incT) {


	Imperio imp;

	imp.updateimperio(incT, territorios);

}
int Territorio::getfInvasao(vector <string> comandos) {
	Imperio imp;
	int end;
	end = imp.feventos(comandos,territorios);
	return end;
}
int Territorio::geteventosInv() {
	Imperio imp;
	int end;
	end = imp.faseEventos(territorios);
	return end;
}

void Territorio::getToma(vector <string> comandos) {


	Imperio imp;

	imp.toma(comandos, territorios);

}

void Territorio::updateterr() {
	Interface inter;
	for (Territorio* t : territorios) {
		if (t->identifier == "montanha") {
			if (t->estado == 1) {

				if (t->turnoConquista < 4 && inter.getTurno()>t->turnoConquista + 2) {
				t->prodTurno = 1;

				}	else if (t->turnoConquista > 4 && inter.getTurno() >= t->turnoConquista - 3 && inter.getAno() == 2) {
				t->prodTurno = 1;
			}

			}
		} else if (t->identifier == "planicie") {
			if (inter.getAno() == 2) {
				t->prodTurno = 2;
			}
		}else if(t->identifier == "mina"){
			if (inter.getTurno() > 3) {
				t->ouroTurno = 2;
			}
			else {
				t->ouroTurno = 1;
			}
		}
		else if (t->identifier == "castelo") {
			if (inter.getTurno() < 3) {
				t->prodTurno = 3;
			}
			else {
				t->prodTurno = 0;
			}
		}
		else if (t->identifier == "pescaria") {
			if (inter.getAno() == 2) {
				t->prodTurno = 4;
			}
		}
	}
	
}
void Territorio::getCheckPV() {
	Imperio imp;
	imp.checkPV(territorios);
}