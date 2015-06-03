#include "Nivel.h"
#include <cmath>

using namespace std;

bool noHayFlorEnPos(vector<FlorEnJuego> flores, Posicion pos){
  int l = flores.size();
  int v = 0;
  while(v < l && !(flores[v].pos.x == pos.x && flores[v].pos.y == pos.y)){
    v++;
  }
  return v == l;
}

int danoFlor(FlorEnJuego flor, vector<VampiroEnJuego> vampiros){
  int cp = 0;
  int v = 0;
  int l = vampiros.size();
  while(v < l){
    if(vampiros[v].pos.x == flor.pos.x && vampiros[v].pos.y == flor.pos.y){
      cp = cp + vampiros[v].vampiro.cuantoPegaV();
    }
    v++;
  }
  return cp;
}

bool hayVampiroEnPos(FlorEnJuego flor, vector<VampiroEnJuego> vampiros){
  int lv = vampiros.size();
  int v = 0;
  while(v < lv && !(vampiros[v].pos.x == flor.pos.x && vampiros[v].pos.y == flor.pos.y)){
    v++;
  }
  return v < lv;
}

bool tieneHabilidad(Habilidad h, FlorEnJuego flor){
  int v = 0;
  int lh = flor.flor.habilidadesF().size();
  while(v < lh && h != flor.flor.habilidadesF()[v]){
    v++;
  }
  return v < lh;
}

bool florExplota(FlorEnJuego flor, vector<VampiroEnJuego> vampiros){
  return tieneHabilidad(Explotar, flor) && hayVampiroEnPos(flor, vampiros);
}

vector<FlorEnJuego> floresVivas(vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros){
  vector<FlorEnJuego> nuevaListaFlores;
  int l = flores.size();
  int v = 0;
  while(v < l){
    if(!florExplota(flores[v], vampiros) && flores[v].vida - danoFlor(flores[v], vampiros) > 0){
      nuevaListaFlores.push_back(FlorEnJuego(flores[v].flor, flores[v].pos, flores[v].vida - danoFlor(flores[v], vampiros)));
    }
    v++;
  }
  return nuevaListaFlores;
}

void floresIguales(vector<FlorEnJuego>& preFlores, vector<FlorEnJuego> flores){
  int v = 0;
  int lFlores = flores.size();
  int lPreFlores = preFlores.size();
  //Primero vacio la lista de pre(flores)
  while(v < lPreFlores){
    preFlores.pop_back();
    v++;
  }
  v = 0 ;
  //Ahora empiezo a llenarla con los elementos de la lista flores que quiero
  while(v < lFlores){
    preFlores.push_back(flores[v]);
    v++;
  }
}

bool enMira(FlorEnJuego flor, VampiroEnJuego vamp){
  return ((vamp.pos.y == flor.pos.y) && (vamp.pos.x >= flor.pos.x));
}

bool noIntercepta(VampiroEnJuego vamp, FlorEnJuego flor, vector<VampiroEnJuego> vampiros){
  int v = 0;
  int largoVampiros = vampiros.size();
  while(v < largoVampiros && !(enMira(flor, vampiros[v]) && (vampiros[v].pos.x <= vamp.pos.x))){
    v++;
  }
  return v == largoVampiros;
}

int danoV(VampiroEnJuego vamp, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros){
  int n = 0;
  int largoFlores = flores.size();
  int golpeFlores = 0;
  while(n < largoFlores){
    if(enMira(flores[n], vamp) && noIntercepta(vamp, flores[n], vampiros)){
      golpeFlores = golpeFlores + flores[n].flor.cuantoPegaF();
    }
    n++;
  }
  return golpeFlores;
}

bool hayFlorSobreviviente(Posicion p, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros){
  int x = 0;
  int largoFlores = flores.size();
  while(x < largoFlores && !(flores[x].pos.x == p.x && flores[x].pos.y == p.y && flores[x].vida - danoFlor(flores[x], vampiros) > 0)){
    x++;
  }
  return x < largoFlores;
}

bool hayFlorSobrevivienteExplota(Posicion p, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros){
  int n = 0;
  int largoFlores = flores.size();
  while(n < largoFlores && !(flores[n].pos.x == p.x && flores[n].pos.y == p.y && tieneHabilidad(Explotar, flores[n]))){
    n++;
  }
  return n < largoFlores;
}

void avanzaV(Posicion &p, VampiroEnJuego vamp){
  if(vamp.vampiro.claseV() == Desviado){
    if(p.y > 1){
      p.y = p.y-1;
    }
  }
  p.x = p.x - 1;
}

Posicion seMueve(VampiroEnJuego vamp, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros){
  Posicion p(vamp.pos.x, vamp.pos.y);
  if(hayFlorSobrevivienteExplota(p, flores, vampiros)){
    p.x++;
  }else if(!hayFlorSobreviviente(p,flores,vampiros)){
    avanzaV(p, vamp);
  }
  return p;
}

vector<VampiroEnJuego> vampirosVivos(vector<FlorEnJuego> preFlores, vector<VampiroEnJuego> preVampiros){
  int i = 0;
  int largoVampiros = preVampiros.size();
  std::vector<VampiroEnJuego> vampiros;
  while(i < largoVampiros){
    Vida vidaRestanteV = preVampiros[i].vida - danoV(preVampiros[i], preFlores, preVampiros);
    if(vidaRestanteV > 0){
      vampiros.push_back(VampiroEnJuego(preVampiros[i].vampiro, seMueve(preVampiros[i], preFlores, preVampiros), vidaRestanteV));
    }
    i++;
  }
  return vampiros;
}

int solesGenerados(vector<FlorEnJuego> preFlores, int preSoles){
  int s = preSoles+1;
  int v = 0;
  int lF = preFlores.size();
  while(v < lF){
    if(tieneHabilidad(Generar, preFlores[v])){
      s++;
    }
    v++;
  }
  return s;
}

void actualizarSpawning(vector<VampiroEnEspera>& spaw, int turno){
  vector<VampiroEnEspera> preSpaw = spaw;
  int v = 0;
  int largoSpaw = spaw.size();
  while(v < largoSpaw){
    spaw.pop_back();
    v++;
  }
  v = 0;
  while(v < largoSpaw){
    if(preSpaw[v].turno > turno){
      spaw.push_back(preSpaw[v]);
    }
    v++;
  }
}

bool vampiroEnColumnaCero(vector<VampiroEnJuego> vampiros){
  int v = 0;
  int largoVamps = vampiros.size();
  while(v < largoVamps && !(vampiros[v].pos.x == 0)){
    v++;
  }
  return v < largoVamps;
}

bool floresDesordenadas(vector<FlorEnJuego> floresOrdenadas){
  bool b;
  int largoF = floresOrdenadas.size();
  int v = 1;
  while(v < largoF){
    if(floresOrdenadas[v-1].pos.y <= floresOrdenadas[v].pos.y){
      if((floresOrdenadas[v-1].pos.y == floresOrdenadas[v].pos.y) && floresOrdenadas[v-1].pos.x <= floresOrdenadas[v].pos.x){
        b = false;
      }else if(floresOrdenadas[v-1].pos.y < floresOrdenadas[v].pos.y){
        b = false;
      }else{
        b = true;
        v = largoF;
      }
    }
    v++;
  }
  return b;
}

void swapF(int a, int b, vector<FlorEnJuego>& floresOrdenadas){
  FlorEnJuego florC = floresOrdenadas[a];
  floresOrdenadas[a] = floresOrdenadas[b];
  floresOrdenadas[b] = florC;
}

void ordenarFlores(vector<FlorEnJuego>& floresOrdenadas){
  int b;
  int largoFlores = floresOrdenadas.size();
  while(floresDesordenadas(floresOrdenadas)){
    b = 1;
    while(b < largoFlores){
      if((floresOrdenadas[b-1].pos.y > floresOrdenadas[b].pos.y) || ((floresOrdenadas[b-1].pos.y == floresOrdenadas[b].pos.y) && (floresOrdenadas[b-1].pos.x > floresOrdenadas[b].pos.x))){
        swapF(b-1, b, floresOrdenadas);
      }
      b++;
    }
  }
}

bool hayPatron(vector<FlorEnJuego> floresOrdenadas){
  int v = 1;
  int largoF = floresOrdenadas.size();
  while(v < largoF && tieneHabilidad(Atacar,floresOrdenadas[v-1]) == !(tieneHabilidad(Atacar,floresOrdenadas[v]))){
    v++;
  }
  return largoF <= 1 || v == largoF;
}

Nivel::Nivel(){}

Nivel::Nivel(int ancho, int alto, int soles, vector<VampiroEnEspera>& spawninglist){
  this->_ancho = ancho;
  this->_alto = alto;
  this->_soles = soles;
  this->_turno = 0;
  this->_spawning = spawninglist;
}

int Nivel::anchoN(){
  return this->_ancho;
}

int Nivel::altoN(){
  return this->_alto;
}

int Nivel::turnoN(){
  return this->_turno;
}

int Nivel::solesN(){
  return this->_soles;
}

vector<FlorEnJuego>& Nivel::floresN(){
  return this->_flores;
}

vector<VampiroEnJuego>& Nivel::vampirosN(){
  return this->_vampiros;
}

vector<VampiroEnEspera>& Nivel::spawningN(){
  return this->_spawning;
}

void Nivel::agregarFlor(Flor f, Posicion p){
  this->_soles = this->_soles - pow(2,f.habilidadesF().size());
  this->_flores.push_back(FlorEnJuego(f,p,f.vidaF()));
}

void Nivel::pasarTurno(){
    this->_turno++;
    vector<FlorEnJuego> preFlores;
    floresIguales(preFlores, this->_flores);
    floresIguales(this->_flores, floresVivas(this->_flores, this->_vampiros));
    this->_vampiros = vampirosVivos(preFlores, this->_vampiros);
    this->_soles = solesGenerados(preFlores, this->_soles);
    int vs=0;
    int largoSpaw = this->_spawning.size();
    while(vs < largoSpaw){
      if(this->_spawning[vs].turno <= this->_turno){
        this->_vampiros.push_back(VampiroEnJuego(this->_spawning[vs].vampiro, Posicion(this->_ancho,this->_spawning[vs].fila), this->_spawning[vs].vampiro.vidaV() ));
      }
      vs++;
    }
    actualizarSpawning(this->_spawning, this->_turno);
}

bool Nivel::terminado(){
   return vampiroEnColumnaCero(this->_vampiros) || (this->_vampiros.empty() && this->_spawning.empty());
}

bool Nivel::obsesivoCompulsivo(){
  vector<FlorEnJuego> floresOrdenadas = this->_flores;
  ordenarFlores(floresOrdenadas);
  return hayPatron(floresOrdenadas);
}

void Nivel::comprarSoles(int n){
  this->_soles = this->_soles + n;
}

void Nivel::Mostrar(ostream& os)
{
  os << "Nivel {";
  os << "Ancho : " << this->_ancho;
  os << " ,Alto : " << this->_alto;
  os << " ,Turno : " << this->_turno;
  os << " ,Soles : " << this->_soles << "\n";
  os << "\t Flores en juego : { " << "\n";
  int i = 0;
  int lFlores = this->_flores.size();
  while (i < lFlores){
    os << "\t \t {";
    this->_flores[i].flor.Mostrar(os);
    os << "\t \t Posicion: (" << this->_flores[i].pos.x << "," << this->_flores[i].pos.y << ") ";
    os << "Vida: " << this->_flores[i].vida << "}" << "\n";
    i++;
  }
  os << "\t }" << "\n";
  os << "\t Vampiros en juego : { " << "\n";
  int j = 0;
  int lVampiros = this->_vampiros.size();
  while(j < lVampiros){
    os << " \t \t {";
    this->_vampiros[j].vampiro.Mostrar(os);
    os << "\t \t Posicion: (" << this->_vampiros[j].pos.x << "," << this->_vampiros[j].pos.y << ") ";
    os << "Vida: " << this->_vampiros[j].vida << "}" << "\n";
    j++;
  }
  os << "\t }" << "\n";
  os << "\t Spawning : {" << "\n";
  int s = 0;
  int lSpawning = this->_spawning.size();
  while(s < lSpawning){
    os << " \t \t {";
    this->_spawning[s].vampiro.Mostrar(os);
    os << "\t \t Fila: " << this->_spawning[s].fila;
    os << " ,Turno: " << this->_spawning[s].turno << "}" << "\n";
    s++;
  }
  os << "\t }" << "\n";
  os << "}" << endl;
}

void Nivel::Guardar(ostream& os)
{
  os << "{ N " << this->_ancho << " " << this->_alto << " " << this->_turno << " " << this->_soles << " [";
  int i = 0;
  int lFlores = this->_flores.size();
  while (i < lFlores){
	  os << " ( ";
    this->_flores[i].flor.Guardar(os);
    os << " ( "<< this->_flores[i].pos.x << " " << this->_flores[i].pos.y << " ) " << this->_flores[i].vida << " )";
    i++;
  }
  os << " ] [";
  int j = 0;
  int lVampiros = this->_vampiros.size();
  while(j < lVampiros){
	os << " ( ";
	this->_vampiros[j].vampiro.Guardar(os);
    os << " ( " << this->_vampiros[j].pos.x << " " << this->_vampiros[j].pos.y << " ) " << this->_vampiros[j].vida << " )";
    j++;
  }
  os << " ] [";
  int s = 0;
  int lSpawning = this->_spawning.size();
  while(s < lSpawning){
	os << " ( " << std::endl;
	this->_spawning[s].vampiro.Guardar(os);
	os << " " << this->_spawning[s].fila << " " << this->_spawning[s].turno << " )";
    s++;
  }
	os << " ] }" << endl;
}

void Nivel::Cargar(istream& is){
  string nivel;
  getline(is, nivel, 'N');
  getline(is, nivel, ' ');
  string anchoNivel;
  getline(is, anchoNivel, ' ');
  this->_ancho = atoi(anchoNivel.c_str());
  string altoNivel;
  getline(is, altoNivel, ' ');
  this->_alto = atoi(altoNivel.c_str());
  string turnoNivel;
  getline(is, turnoNivel, ' ');
  this->_turno = atoi(turnoNivel.c_str());
  string solesNivel;
  getline(is, solesNivel, ' ');
  this->_soles = atoi(solesNivel.c_str());
  string basura;
  getline(is, basura, ' ');
  string cambioTipo;
  getline(is, cambioTipo, ' ');
  char ultimoCambio=cambioTipo.back();
  while(ultimoCambio != ']') {
    Flor cargaflor;
    Posicion t;
    Vida v;
    cargaflor.Cargar(is);
    getline(is, basura, '(');
    getline(is, basura, ' ');
    string posicionFx;
    getline(is, posicionFx, ' ');
    t.x = atoi(posicionFx.c_str());
    string posicionFy;
    getline(is, posicionFy, ' ');
    t.y = atoi(posicionFy.c_str());
    getline(is, basura, ' ');
    string vidaFi;
    getline(is, vidaFi, ' ');
    v = atoi(vidaFi.c_str());
    getline(is, basura, ' ');
    FlorEnJuego fCargar(cargaflor,t,v);
    this->_flores.push_back(fCargar);
    getline(is, cambioTipo, ' ');
    ultimoCambio = cambioTipo.back();
  }
  getline(is, basura, ' ');
  getline(is, cambioTipo, ' ');
  ultimoCambio = cambioTipo.back();
  while(ultimoCambio != ']') {
    Vampiro cargaVampiro;
    Posicion p;
    Vida v;
    cargaVampiro.Cargar(is);
    getline(is, basura, '(');
    getline(is, basura, ' ');
    string posicionVx;
    getline(is, posicionVx, ' ');
    p.x = std::atoi(posicionVx.c_str());
    string posicionVy;
    getline(is, posicionVy, ' ');
    p.y = std::atoi(posicionVy.c_str());
    getline(is, basura, ' ');
    string vidaVj;
    getline(is, vidaVj, ' ');
    v = atoi(vidaVj.c_str());
    VampiroEnJuego vCargar(cargaVampiro, p, v);
    this->_vampiros.push_back(vCargar);
    getline(is, basura, ' ');
    getline(is, cambioTipo, ' ');
    ultimoCambio = cambioTipo.back();
  }
  getline(is, basura, ' ');
  getline(is, cambioTipo, ' ');
  ultimoCambio = cambioTipo.back();
  while(ultimoCambio != ']'){
    Vampiro cargarVS;
    int cargarFila;
    int cargarTurnoS;
    cargarVS.Cargar(is);
    getline(is, basura, ' ');
    string fila;
    getline(is, fila, ' ');
    cargarFila = atoi(fila.c_str());
    getline(is, basura, ' ');
    string turnoVs;
    getline(is, turnoVs, ' ');
    cargarTurnoS = std::atoi(turnoVs.c_str());
    VampiroEnEspera vSpawC(cargarVS,cargarFila,cargarTurnoS);
    this->_spawning.push_back(vSpawC);
    getline(is, cambioTipo, ' ');
    ultimoCambio = cambioTipo.back();
  }
}
