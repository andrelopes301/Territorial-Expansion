#include "utils.h"

using namespace std;


int Interface::ano = 1;
int Interface::turno = 1;


Interface::Interface() {

};

Interface::~Interface() {
    
}

void Interface::iniciarTurno() {
    string comando, aux, tipoT, ficheiro;
    int incT = 0, fase0 = 0, fase1 = 0, cont, contCarrega = 0, contCria = 0, contM, contT, contP, contO, end = 0;
   
    Territorio* m = new Territorio();
    Imperio imp;

    m->criarTinicial();
    int fase = 0, n;
    vector<string>comandos;
    
    cout << "|------------------------------------------------------------------------------------------------------------|" << endl << endl;
    cout << "                                          Conquista Expansao Territorial                                      " << endl << endl;
    cout << "|------------------------------------------------------------------------------------------------------------|" << endl << endl;

    do {

        if (turno > 6) {
            ano++;
            turno = 1;
        }
        m->updateterr();
            switch (fase) {
            case(0): 
                //Fase de carregar/criar territorios
                cout << endl << "---| Fase de Configuracao do Mundo |---" << endl;

                do{              
                    comandos.clear();
                    cout << endl << "Comando: ";
                    getline(cin, comando);
                    stringstream ss(comando);
                    while (getline(ss, aux, ' '))
                    comandos.push_back(aux);

                // Comandos da fase 0

                if (comandos[0] == "carrega" && comandos.size() == 2) {
                    ficheiro = comandos[1];
                    m->carregarTerritorios(ficheiro);
                    contCarrega++;
                }
                else if (comandos[0] == "cria" && comandos.size() == 3) {
                    tipoT = comandos[1];
                    n = atoi(comandos[2].c_str());
                    contCria += m->criarTerritorio(comandos);      
                }
                else if (comandos[0] == "help") {
                    help(fase);
                }
                else if (comandos[0] == "lista") {
                    if (comandos.size() == 1) {
                        //funcao para listar toda a informacao do jogo
                        m->listarTerritorios();
                    }
                    else if (comandos.size() == 2) {
                        //lista <nome>     //funcao para listar apenas um territorio
                        m->listarUmTerritorio(comandos[1]);

                    }
                    else {
                        cout << "<AVISO>: Comando Invalido! Utilize o comando <help> para mais ajuda!" << endl;
                    }
                }
                else if (comandos[0] == "avanca") {
                    if (contCarrega < 1 && contCria < 5) {
                        cout << "<AVISO>: Nao pode avancar de fase sem carregar um mundo ou criar os seus territorios!" << endl;
                    }
                }
                else {
                    cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                }
                
                } while (comandos[0] != "avanca" || contCarrega < 1 && contCria < 5);
                    fase=1;
                    
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            case(1): 
                //Fase 1 - Carregar/criar territorios
                cont = 0;
                cout << "|------------------------------------------------------------------------------------------------------------|" << endl << endl;
                cout << "                                                 Ano: " << ano << " | Turno: " << turno << endl << endl;
                cout << "|------------------------------------------------------------------------------------------------------------|" << endl << endl;
                cout << "---| Fase 1: Conquistar/Passar |---" << endl;
               
                do {
                    comandos.clear();
                    cout << endl << "Comando: ";
                    getline(cin, comando);
                    stringstream ss(comando);

                    while (getline(ss, aux, ' '))
                        comandos.push_back(aux);

                    // Comandos da fase 1

                    if (comandos[0] == "conquista" && comandos.size() == 2) {
                        if (cont == 0) {
                            string nome;
                            nome = comandos[1];
                            cont = m->conquistarTerritorio(nome);
                        }
                        else if(cont == 1)
                            cout << "<AVISO>: Apenas pode conquistar um territorio por turno!" << endl;
                        else if (cont == 2)
                            cout << "<AVISO>: Nao pode conquistar um territorio quando ja usou o comando passar!" << endl;
                    }
                    else if (comandos[0] == "passar") {
                        if (cont == 0) {
                            cout << "<AVISO>: Nao desejou conquistar um territorio este turno!" << endl;
                            cout << "<AVISO>: Utilize o comando <<avanca>> para ir para a proxima fase!" << endl;
                            cont = 2;                      
                        }
                        else if(cont==1){
                            cout << "<AVISO>: Nao pode passar um turno onde usou o comando conquistar!" << endl;
                        }
                        else if (cont == 2) {
                            cout << "<AVISO>: Ja executou o comando 'passar' anteriormente!" << endl;
                        }
                    }
                    else if (comandos[0] == "lista") {
                        if (comandos.size() == 1) {
                            //Listar toda a informacao do jogo
                            m->listarTerritorios();
                        }
                        else if (comandos.size() == 2) {
                            //Listar apenas um territorio
                            m->listarUmTerritorio(comandos[1]);
                        }
                    }
                    else if (comandos[0] == "help") {
                        help(fase);
                    }
                    else if (comandos[0] == "saldo") {
                        imp.saldo();
                    }
                    else if (comandos[0] == "avanca") {
                        if (cont == 0) {
                            cout << "<AVISO>: Nao pode avancar esta fase sem conquistar um territorio ou passar!" << endl;
                        }
                    }

                    ///Debug
                    else if (comandos[0] == "fevento" && comandos.size() == 2) {
                        // imp.feventos(comandos);
                        end = m->getfInvasao(comandos);
                        if(end==1){
                            m->listarTerritorios();
                            m->getCheckPV();
                            cout << endl << endl << "|--------------------------------------------------Pontos Vitoria--------------------------------------------|" << endl << endl
                                << "                                                         " << imp.getPvitoria() << endl;
                            exit(0);
                        }
                    }
                    else if (comandos[0] == "modifica" && comandos.size() == 3) {
                        if (comandos[1] == "prod" || comandos[1] == "ouro") {                  
                           
                            if (atoi(comandos[2].c_str()) >= 0)
                                imp.modifica(comandos);
                            else
                                cout << "<AVISO>: Quantidade Invalida!" << endl;
                        }
                        else {
                            cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;        
                        }
                    }
                    else if (comandos[0] == "toma" && comandos.size() == 3) {
                        if (comandos[1] == "terr" || comandos[1] == "tec") {

                            //imp.toma(comandos);
                            m->getToma(comandos);
                        }
                    }
                    else {
                        cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                    }
                } while (comandos[0] != "avanca" || cont < 1);
                
                fase = 2;
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            case(2):
                //Fase 2 - Recolha de produtos e o ouro criados
                cout << endl << "---| Fase 2: Recolha de Produtos e o Ouro |---" << endl << endl;          
               // imp.updateimperio(incT, territorios); // recolha dos produtos/ouros produzidos por cada territorio no imperio
                m->getUpdateImp(incT);
                contP = 0;
                contO = 0;

                if(imp.getbolsa() == 0){
                  cout << " Nesta fase, e possivel fazer a troca entre recursos em armazem/cofre!" << endl;
                  cout << " No entanto, precisa primeiro de adquirir a tecnologia 'Bolsa de Valores'!" << endl;
                }
 
                else {
                    cout << " Bolsa de Valores" << endl <<endl;
                    cout << " Nesta fase e possivel fazer a troca entre recursos em armazem/cofre!" << endl;
                    cout << " Para isso, utilize os comandos 'maisprod' ou 'maisouro' para realizar as trocas!" << endl;
                    cout << " 'maisprod' - Trocar duas unidades de ouro por uma de produtos!" << endl;
                    cout << " 'maisouro' - Trocar duas unidades de produtos por uma de ouro!" << endl << endl;
                }

                do {
                    comandos.clear();
                    cout << endl << "Comando: ";
                    getline(cin, comando);
                    stringstream ss(comando);

                    while (getline(ss, aux, ' '))
                        comandos.push_back(aux);

                    // Comandos da fase 2

                    if (comandos[0] == "maisprod") {
                        if (contP == 0) 
                            contP = imp.maisprod();                   
                        else 
                            cout << "<AVISO>: So pode efetuar esta troca uma vez por turno!" << endl;            
                    }
                    else if (comandos[0] == "maisouro") {

                        if (contO == 0)
                            contO = imp.maisouro();
                        else
                            cout << "<AVISO>: So pode efetuar esta troca uma vez por turno!" << endl;
                    }
                    else if (comandos[0] == "saldo") {
                        imp.saldo();
                    }
                    else if (comandos[0] == "help") {
                        help(fase);
                    }
                    else if (comandos[0] == "avanca") {
                    }
                    ///Debug
                    else if (comandos[0] == "fevento" && comandos.size() == 2) {
                        end = m->getfInvasao(comandos);
                        if(end==1){
                            m->listarTerritorios();
                            m->getCheckPV();
                            cout << endl << endl << "|--------------------------------------------------Pontos Vitoria--------------------------------------------|" << endl << endl
                                << "                                                         " << imp.getPvitoria() << endl;
                            exit(0);
                        }
                    }
                    else if (comandos[0] == "modifica" && comandos.size() == 3) {
                        if (comandos[1] == "ouro" || comandos[1] == "prod") {

                            if (atoi(comandos[2].c_str()) >= 0)
                                imp.modifica(comandos);
                            else
                                cout << "<AVISO>: Quantidade Invalida!" << endl;
                        }
                        else {
                            cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                        }
                    }
                    else if (comandos[0] == "toma" && comandos.size() == 3) {
                        if (comandos[1] == "terr" || comandos[1] == "tec") {

                           // imp.toma(comandos, m);
                            m->getToma(comandos);
                        }
                    }
                    else if (comandos[0] == "lista") {
                        if (comandos.size() == 1) {
                            //Listar toda a informacao do jogo
                            m->listarTerritorios();
                        }
                        else if (comandos.size() == 2) {
                            //Listar apenas um territorio
                            m->listarUmTerritorio(comandos[1]);
                        }
                    }
                    else {
                        cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                    }
                } while (comandos[0] != "avanca");
                fase = 3;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            case(3):
                //Fase 3 - Compra de unidades militares e de tecnologia
                cout << endl << "---| Fase 3: Compra de Unidades Militares e Tecnologia |---" << endl << endl;
                contM = 0;
                contT = 0;
                          
                    cout << "Nesta fase, e possivel aumentar a forca militar utilizando o comando 'maismilitar'!" << endl;
                    cout << " 'maismilitar' - Compra uma unidade de forca militar, gastando uma unidades de ouro e uma de produtos!" << endl << endl;
                    cout << "Nesta fase, e tambem possivel adquirir Tecnologia utilizando o comando 'adquire <tipo>'!" << endl;
  

                    do {
                    
                    comandos.clear();
                    cout << endl << "Comando: ";
                    getline(cin, comando);
                    stringstream ss(comando);
                    while (getline(ss, aux, ' '))
                        comandos.push_back(aux);

                    // Comandos da fase 3

                    if (comandos[0] == "maismilitar") {
                        if (contM == 0) {
                            contM = imp.maismilitar();
                        }
                        else {
                            cout << "<AVISO>: So pode comprar uma unidade de Forca Militar por turno!" << endl;
                        }
                    }
                    else if (comandos[0] == "adquire" && comandos.size() == 2) {
                        if (contT == 0) {
                            contT = imp.compraTec(comandos);
                        }
                        else {
                            cout << "<AVISO>: So pode adquirir uma tecnologia por turno!" << endl;
                        }

                    }
                    else if (comandos[0] == "lista") {
                        if (comandos.size() == 1) {
                            //Listar toda a informacao do jogo
                            m->listarTerritorios();
                        }
                        else if (comandos.size() == 2) {
                            //Listar apenas um territorio
                            m->listarUmTerritorio(comandos[1]);
                        }
                    }
                    else if (comandos[0] == "help") {
                        help(fase);

                    }
                    else if (comandos[0] == "saldo") {
                        imp.saldo();
                    }
                    else if(comandos[0] == "tecnologias"){

                        cout << " Tecnologias disponiveis:" << endl << endl;
                        cout << " - Drones Militares (drones) : Forca militar maxima passa a ser 5!" << endl;
                        cout << " - Misseis Teleguiados (misseis) : Necessaria para conquistar Ilhas!" << endl;
                        cout << " - Defesas Territoriais (defesas) : Acrescenta 1 unidade de resistencia a um territorio do imperio invadido!" << endl;
                        cout << " - Bolsa de Valores (bolsa) : Sistema para realizar trocas entre produtos/ouro!" << endl;
                        cout << " - Banco Central (banco) : Capacidade maxima do armazem e cofre passa a ser 5!" << endl;
                    }
                    else if (comandos[0] == "avanca") {
                    }
                    ///Debug
                    else if (comandos[0] == "fevento" && comandos.size() == 2) {
                        end = m->getfInvasao(comandos);
                        if (end == 1) {
                            m->listarTerritorios();
                            m->getCheckPV();
                            cout << endl << endl << "|--------------------------------------------------Pontos Vitoria--------------------------------------------|" << endl << endl
                                << "                                                         " << imp.getPvitoria() << endl;
                            exit(0);
                        }
                    }
                    else if (comandos[0] == "modifica" && comandos.size() == 3) {
                        if (comandos[1] == "ouro" || comandos[1] == "prod") {
                            
                            if (atoi(comandos[2].c_str()) >= 0)
                                imp.modifica(comandos);
                            else
                                cout << "<AVISO>: Quantidade Invalida!" << endl;
                        }
                        else {
                            cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                        }
                    }
                    else if (comandos[0] == "toma" && comandos.size() == 3) {
                        if (comandos[1] == "terr" || comandos[1] == "tec") {

                            m->getToma(comandos);
                     
                        }
                    }
                    else {
                        cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                    }
                } while (comandos[0] != "avanca");
                fase = 4;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            case(4):
                //Fase 4 - Ocorrência de um evento
                cout << endl << "---| Fase 4: Eventos |---" << endl << endl;
                //imp.faseEventos();
                end = m->geteventosInv();
                if (end == 1) {
                    m->listarTerritorios();
                    m->getCheckPV();
                    cout << endl << endl << "|--------------------------------------------------Pontos Vitoria--------------------------------------------|" << endl << endl
                        << "                                                         " << imp.getPvitoria() << endl;
                    exit(0);
                }
                do {
                    comandos.clear();
                    cout << endl << "Comando: ";
                    getline(cin, comando);
                    stringstream ss(comando);
                    
                    while (getline(ss, aux, ' '))
                        comandos.push_back(aux);

                    if (comandos[0] == "help") {
                        help(fase);
                    }
                    else if (comandos[0] == "lista") {
                        if (comandos.size() == 1) {
                            //Listar toda a informacao do jogo
                            m->listarTerritorios();
                        }
                        else if (comandos.size() == 2) {
                            //Listar apenas um territorio
                            m->listarUmTerritorio(comandos[1]);
                        }
                    }
                    else if (comandos[0] == "saldo") {
                        imp.saldo();
                    }
                    else if (comandos[0] == "avanca") {

                    }
                    ///Debug
                    else if (comandos[0] == "fevento" && comandos.size() == 2) {
                        end = m->getfInvasao(comandos);
                        if (end == 1) {
                            m->listarTerritorios();
                            m->getCheckPV();
                            cout << endl << endl << "|--------------------------------------------------Pontos Vitoria--------------------------------------------|" << endl << endl
                                << "                                                         " << imp.getPvitoria() << endl;
                            exit(0);
                        }
                    }
                    else if (comandos[0] == "modifica" && comandos.size() == 3) {
                        if (comandos[1] == "prod" || comandos[1] == "ouro") {

                            if (atoi(comandos[2].c_str()) >= 0)
                                imp.modifica(comandos);
                            else
                                cout << "<AVISO>: Quantidade Invalida!" << endl;
                        }
                        else {
                            cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                        }
                    }
                    else if (comandos[0] == "toma" && comandos.size() == 3) {
                        if (comandos[1] == "terr" || comandos[1] == "tec") {

                            m->getToma(comandos);
                        }
                        else {
                            cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                        }
                    }
                    else {
                        cout << "<AVISO>: Comando Invalido! Utilize o comando <<help>> para mais ajuda!" << endl;
                    }
                } while (comandos[0] != "avanca");
                break;
         }

         fase = 1;
         incT++;
         turno++;
        
    } while (incT < 12);

    m->getCheckPV();
    cout << endl << endl << "|--------------------------------------------------Pontos Vitoria--------------------------------------------|" << endl << endl 
                         << "                                                         "<<imp.getPvitoria()<< endl;
delete m;
 
}



void Interface::help(int fase) {

    cout << endl << "Comandos disponiveis nesta fase:" << endl;
    if (fase == 0) { // Fase de Configuracao do Mundo 
        cout << "  carrega <nomeFicheiro>" << endl
            << "  cria <tipo> <n>" << endl
            << "  lista" << endl
            << "  lista <nome>" << endl
            << "  avanca" << endl;
    }
    else {
        if (fase == 1) { // Fase   // Conquistar / Passar
            cout << "  conquista <nome>" << endl
                << "  passar" << endl
                << "  lista" << endl
                << "  lista <nome>" << endl
                << "  avanca" << endl;
        }
        else  if (fase == 2) { // Fase Recolha de produtos e ouro
            cout << "  lista" << endl
                << "  lista <nome>" << endl
                << "  maisouro" << endl
                << "  maisprod" << endl
                << "  avanca" << endl;
        }
        else  if (fase == 3) { // Fase  Compra de unidades militares e de tecnologia
           cout << "  maismilitar" << endl
                << "  adquire <tipo>" << endl
                << "  tecnologias" << endl
                << "  lista" << endl
                << "  lista <nome>" << endl
                << "  avanca" << endl;
        }
        else  if (fase == 4) { // Fase de Eventos
            cout << "  lista" << endl
                << "  lista <nome>" << endl
                << "  avanca" << endl;
        }
        cout << "  saldo" << endl << endl;
        cout << "Debug: " << endl
            << "  fevento <nome>" << endl
            << "  modifica <ouro/prod>" << endl
            << "  toma <terr/tec> <nome>" << endl
            << "  grava <nome>" << endl
            << "  ativa <nome>" << endl
            << "  apaga <nome>" << endl;
    }
}


int Interface::getAno() {
    return this->ano;

}
int Interface::getTurno() {
    return this->turno;
}
