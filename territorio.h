#ifndef TERRITORIO_H
#define TERRITORIO_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "imperio.h"
#include "utils.h"


class Territorio {    
   friend class Imperio;

protected:
    std::string tipoTerr;
    std::string nome;
    int resistencia;
    int prodTurno;
    int ouroTurno;
    int pontosVit;
    bool estado; // 1 - conquistado ; 0 - nao conquistado
    std::string identifier;
    int turnoConquista;
    int anoConquista;
    
public:
    std::vector <Territorio* > territorios;

    Territorio();
    ~Territorio();
    std::string gettipoT();
    std::string getNome();
    int getOuro();
    int getProdutos();
    int getResistencia();
    int getPontosVit();
    int getTurnoConquista();
    int getAnoConquista();


/////////////////////////////////////////////////////////////////////////////////////////////

    void carregarTerritorios(std::string ficheiro);
    void listarTerritorios();
    void listarUmTerritorio(std::string nome);
    int criarTerritorio(std::vector<std::string> comandos);
    void criarTinicial();
    int conquistarTerritorio(std::string nome);


    void getUpdateImp(int incT);
    int getfInvasao(std::vector<std::string> comandos);
    int geteventosInv();
    void getToma(std::vector<std::string> comandos);
    
    void getCheckPV();
    void updateterr();
 
/////////////////////////////////////////////////////////////////////////////////////////////
};

class TerritorioInicial : public Territorio
{
private:
public:
    TerritorioInicial();
};


class Planicie : public Territorio {

protected:
    int static nPlanicie;
public:
    Planicie();

};

class Montanha : public Territorio {
private:
    int static nMontanha;
public:
    Montanha();

};

class Fortaleza : public Territorio {
private:
    int static nFortaleza;
public:
    Fortaleza();
};

class Mina : public Territorio {
private:
    int static nMina;
public:
    Mina();
};

class Duna : public Territorio {
private:
    int static nDuna;
public:
    Duna();
};

class Castelo : public Territorio {
private:
    int static nCastelo;
public:
    Castelo();
};

class Refugio : public Territorio {
private:
    int static nRefugio;
public:
    Refugio();
};

class Pescaria : public Territorio {
private:
    int static nPescaria;
public:
    Pescaria();
};

#endif