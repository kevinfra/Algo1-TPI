﻿#include "Nivel.h"
#include <cmath>

bool spawningOrdenado(std::vector<VampiroEnEspera>& spawninglist){
  int v = 1;
  int l = spawninglist.size();
  bool b = false;
  if(l == 1){b = true;}
  while(v < l){
    if(spawninglist[v-1].turno <= spawninglist[v].turno){
      if(spawninglist[v-1].fila <= spawninglist[v].fila){
        b = true;
      }
    }
    v++;
  }
  return b;
}

bool spawningValido(std::vector<VampiroEnEspera>& spawninglist, int alto){
  int v = 0;
  int l = spawninglist.size();
  while(v < l && spawninglist[v].fila>0 && spawninglist[v].fila <= alto && spawninglist[v].turno >= 0){
    v++;
  }
  return v == l;
}

bool noHayFlorEnPos(std::vector<FlorEnJuego> flores, Posicion pos){
  int l = flores.size();
  int v = 0;
  while(v < l && !(flores[v].pos.x == pos.x && flores[v].pos.y == pos.y)){
    v++;
  }
  return v == l;
}

int danoFlor(FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
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

bool hayVampiroEnPos(FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
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

bool florExplota(FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
  return tieneHabilidad(Explotar, flor) && hayVampiroEnPos(flor, vampiros);
}

std::vector<FlorEnJuego> floresVivas(std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
  std::vector<FlorEnJuego> nuevaListaFlores;
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

void floresIguales(std::vector<FlorEnJuego>& preFlores, std::vector<FlorEnJuego> flores){
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

bool noIntercepta(VampiroEnJuego vamp, FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
  int v = 0;
  int largoVampiros = vampiros.size();
  while(v < largoVampiros && !(enMira(flor, vampiros[v]) && (vampiros[v].pos.x <= vamp.pos.x))){
    v++;
  }
  return v == largoVampiros;
}

int danoV(VampiroEnJuego vamp, std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
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

bool hayFlorSobreviviente(Posicion p, std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
  int x = 0;
  int largoFlores = flores.size();
  while(x < largoFlores && !(flores[x].pos.x == p.x && flores[x].pos.y == p.y && flores[x].vida - danoFlor(flores[x], vampiros) > 0)){
    x++;
  }
  return x < largoFlores;
}

bool hayFlorSobrevivienteExplota(Posicion p, std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
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

Posicion seMueve(VampiroEnJuego vamp, std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
  Posicion p(vamp.pos.x, vamp.pos.y);
  if(hayFlorSobrevivienteExplota(p, flores, vampiros)){
    p.x++;
  }else if(!hayFlorSobreviviente(p,flores,vampiros)){
    avanzaV(p, vamp);
  }
  return p;
}

std::vector<VampiroEnJuego> vampirosVivos(std::vector<FlorEnJuego> preFlores, std::vector<VampiroEnJuego> preVampiros){
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

int solesGenerados(std::vector<FlorEnJuego> preFlores, int preSoles){
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

void actualizarSpawning(std::vector<VampiroEnEspera>& spaw, int turno){
  std::vector<VampiroEnEspera> preSpaw = spaw;
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

bool vampiroEnColumnaCero(std::vector<VampiroEnJuego> vampiros){
  int v = 0;
  int largoVamps = vampiros.size();
  while(v < largoVamps && !(vampiros[v].pos.x == 0)){
    v++;
  }
  return v < largoVamps;
}

bool floresDesordenadas(std::vector<FlorEnJuego> floresOrdenadas){
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

void swapF(int a, int b, std::vector<FlorEnJuego>& floresOrdenadas){
  FlorEnJuego florC = floresOrdenadas[a];
  floresOrdenadas[a] = floresOrdenadas[b];
  floresOrdenadas[b] = florC;
}

void ordenarFlores(std::vector<FlorEnJuego>& floresOrdenadas){
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
/*
bool hayPatron(std::vector<FlorEnJuego> floresOrdenadas){
  bool b = false;
  int v = 1;
  int largoF = floresOrdenadas.size();
  if(largoF == 2 && (tieneHabilidad(Atacar, floresOrdenadas[0]) && !tieneHabilidad(Atacar, floresOrdenadas[1])) || (!tieneHabilidad(Atacar, floresOrdenadas[0]) && tieneHabilidad(Atacar, floresOrdenadas[1]))){
    b = true;
    v = largoF;
  }
  while(v < largoF-1){
    if(((tieneHabilidad(Atacar, floresOrdenadas[v-1])) && (!tieneHabilidad(Atacar, floresOrdenadas[v])) && (tieneHabilidad(Atacar, floresOrdenadas[v+1]))) || ((!tieneHabilidad(Atacar, floresOrdenadas[v-1])) && (tieneHabilidad(Atacar, floresOrdenadas[v])) && (!tieneHabilidad(Atacar, floresOrdenadas[v+1])))){
      b = true;
    }else{
      v = largoF;
    }
  }
  return b;
}
*/
bool hayPatron(std::vector<FlorEnJuego> floresOrdenadas){
  int v = 1;
  int largoF = floresOrdenadas.size();
  while(v < largoF && tieneHabilidad(Atacar,floresOrdenadas[v-1]) == !(tieneHabilidad(Atacar,floresOrdenadas[v]))){
    v++;
  }
  return largoF == 1 || v == largoF;
}

Nivel::Nivel(){}

Nivel::Nivel(int ancho, int alto, int soles, std::vector<VampiroEnEspera>& spawninglist){
  if(ancho>0){
    this->_ancho = ancho;
  }else{
    std::cerr << "ancho no valido" << std::endl;
  }
  if(alto > 0){
    this->_alto = alto;
  }else{
    std::cerr << "alto no válido" << std::endl;
  }
  if(soles >= 0){
    this->_soles = soles;
  }else{
    std::cerr << "cantidad de soles inválida" << std::endl;
  }
  this->_turno = 0;
  int t = spawninglist.size();
  int v = 0;
  if(spawningValido(spawninglist, alto) && spawningOrdenado(spawninglist)){
    this->_spawning = spawninglist;
  }
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

std::vector<FlorEnJuego>& Nivel::floresN(){
  return this->_flores;
}

std::vector<VampiroEnJuego>& Nivel::vampirosN(){
  return this->_vampiros;
}

std::vector<VampiroEnEspera>& Nivel::spawningN(){
  return this->_spawning;
}

void Nivel::agregarFlor(Flor f, Posicion p){
  if(noHayFlorEnPos(this->_flores, p) && this->_soles >= pow(2,f.habilidadesF().size())){
    this->_soles = this->_soles - pow(2,f.habilidadesF().size());
    this->_flores.push_back(FlorEnJuego(f,p,f.vidaF()));
  }
}

void Nivel::pasarTurno(){
  if(!this->terminado()){
    this->_turno++;
    std::vector<FlorEnJuego> preFlores;
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
}

bool Nivel::terminado(){
   return vampiroEnColumnaCero(this->_vampiros) || (this->_vampiros.empty() && this->_spawning.empty());
}

bool Nivel::obsesivoCompulsivo(){
  std::vector<FlorEnJuego> floresOrdenadas = this->_flores;
  ordenarFlores(floresOrdenadas);
  return this->_flores.size() < 2 || hayPatron(floresOrdenadas);
}

void Nivel::comprarSoles(int n){
  this->_soles = this->_soles + n;
}

void Nivel::Mostrar(std::ostream& os)
{
  os << "Nivel {" << std::endl;
  os << "Ancho : " << this->_ancho << std::endl;
  os << "Alto : " << this->_alto << std::endl;
  os << "Turno : " << this->_turno << std::endl;
  os << "Soles : " << this->_soles << std::endl;
  os << "Flores : { " << std::endl;
  int i = 0;
  int lFlores = this->_flores.size();
  while (i < lFlores){
    this->_flores[i].flor.Mostrar(std::cout);
    i++;
  }
  os << "}" << std::endl;
  os << "Vampiros : { " << std::endl;
  int j = 0;
  int lVampiros = this->_vampiros.size();
  while(j < lVampiros){
    this->_vampiros[j].vampiro.Mostrar(std::cout);
    j++;
  }
  os << "}" << std::endl;
  os << "Spawning : {" << std::endl;
  int s = 0;
  int lSpawning = this->_spawning.size();
  while(s < lSpawning){
    this->_spawning[s].vampiro.Mostrar(std::cout);
    s++;
  }
  os << std::endl;
  os << "}" << std::endl;
  os << "}" << std::endl;
}

void Nivel::Guardar(std::ostream& os)
{
  os << "{ N " << this->_ancho << " " << this->_alto << " " << this->_turno << " " << this->_soles << " [ ";
  int i = 0;
  int lFlores = this->_flores.size();
  while (i < lFlores){
	  os << "( ";
    this->_flores[i].flor.Guardar(os);
    os << " ( "<< this->_flores[i].pos.x << " " << this->_flores[i].pos.y << " ) " << this->_flores[i].vida << " ) )";
    i++;
  }
  os << " ] [ ";
  int j = 0;
  int lVampiros = this->_vampiros.size();
  while(j < lVampiros){
	os << "( ";
	this->_vampiros[j].vampiro.Guardar(os); 
    os << " ( " << this->_vampiros[j].pos.x << " " << this->_vampiros[j].pos.y << " ) " << this->_vampiros[j].vida << " ) ";
    j++;
  }
  os << " ] [ ";
  int s = 0;
  int lSpawning = this->_spawning.size();
  while(s < lSpawning){
	os << "( " << std::endl;
	this->_spawning[s].vampiro.Guardar(os);
	os << this->_spawning[s].fila << " " << this->_spawning[s].turno << " )";
    s++;
  }

	os << " ] }" << std::endl;

}

// void Nivel::Guardar(std::ostream& os)
// {
// 	os << "{ N " << this->_ancho << " " << this->_alto << " " << this->_turno << " " << this->_soles << " [ ";
// 	int i = 0;
// 	int lFlores = this->_flores.size();
// 	while (i < lFlores){
// 		os << "( { F " << this->_flores[i].flor.vidaF() << " " << this->_flores[i].flor.cuantoPegaF() << " [ ";
// 		int k = 0;
// 		int lHabilidadesFlores = this->_flores[i].flor.habilidadesF().size();
// 		while(k < lHabilidadesFlores){
// 			os << this->_flores[i].flor.habilidadesF()[k] << " ";
// 			k++;
// 		}
// 		os << "] } ( " << this->_flores[i].pos.x << " " << this->_flores[i].pos.y << " ) " << this->_flores[i].vida << " ) ";
// 		i++;
// 	}

// 	os << "] [ ";
// 	int j = 0;
// 	int lVampiros = this->_vampiros.size();
// 	while(j < lVampiros){
// 		os << "( { V " << this->_vampiros[j].vampiro.claseV() << " " << this->_vampiros[j].vampiro.vidaV() << " " << this->_vampiros[j].vampiro.cuantoPegaV() << " } ( " << this->_vampiros[j].pos.x; 

// 		os << " " << this->_vampiros[j].pos.y << " ) " << this->_vampiros[j].vida << " ) ";
// 		j++;
// 	}
// 	os << "] [ ";
// 	int s = 0;
// 	int lSpawning = this->_spawning.size();
// 	while(s < lSpawning){
// 		os << "( { V " << this->_spawning[s].vampiro.claseV() << " " << this->_spawning[s].vampiro.vidaV() << " " << this->_spawning[s].vampiro.cuantoPegaV() << " } " << this->_spawning[s].fila;
// 		os << " " << this->_spawning[s].turno << " ) ";
//     s++;
// 	}
// 	os << "] }";
// }

 void Nivel::Cargar(std::istream& is)
 {
   std::string nivel;
   getline(is, nivel, 'N');
   getline(is, nivel, ' ');
   std::string anchoNivel;
   getline(is, anchoNivel, ' ');
   this->_ancho = std::atoi(anchoNivel.c_str());
   std::string altoNivel;
   getline(is, altoNivel, ' ');
   this->_alto = std::atoi(altoNivel.c_str());
   std::string turnoNivel;
   getline(is, turnoNivel, ' ');
   this->_turno = std::atoi(turnoNivel.c_str());
   std::string solesNivel;
   getline(is, solesNivel, ' ');
   this->_soles = std::atoi(solesNivel.c_str());
   std::string basura;
   getline(is, basura, '{');
   std::string cambioTipo;
   getline(is, cambioTipo, ' ');
   char ultimoCambio=cambioTipo.back();
   while(ultimoCambio != ']') {
    std::cout << "a comerlaaaa" << std::endl;
    Flor cargaf;
    Posicion t;
    Vida v;
     // this->_flores.push_back(fCargar.Cargar(is), );
     cargaf.Cargar(is);
     std::cout << "cargo la flor" << std::endl;
     getline(is, basura, '(');
     getline(is, basura, ' ');
     std::string posicionFx;
     getline(is, posicionFx, ' ');
     std::cout << "pos x lo pasa" << std::endl;
     t.x = std::atoi(posicionFx.c_str());
     std::string posicionFy;
     getline(is, posicionFy, ' ');
     std::cout << "pos y lo pasa" << std::endl;
     t.y = std::atoi(posicionFy.c_str());
     getline(is, basura, ' ');
     std::string vidaFi;
     getline(is, vidaFi, ' ');
     std::cout << "vida lo pasa" << std::endl;
     v = std::atoi(vidaFi.c_str());
     getline(is, basura, ' ');
     std::cout << "pasa el ' ' " << std::endl;
     FlorEnJuego fCargar(cargaf,t,v);
     this->_flores.push_back(fCargar);
     getline(is, cambioTipo, ' ');
     ultimoCambio = cambioTipo.back();
     std::cout << "no se va" << std::endl;
   }
   int j = 0;
   int listaVampirosN = this->_vampiros.size();
   while(j < listaVampirosN) {
    this->_vampiros[j].vampiro.Cargar(is);
     getline(is, basura, '(');
     getline(is, basura, ' ');
     std::string posicionVx;
     getline(is, posicionVx, ' ');
     this->_vampiros[j].pos.x = std::atoi(posicionVx.c_str());
     std::string posicionVy;
     getline(is, posicionVy, ' ');
     this->_vampiros[j].pos.y = std::atoi(posicionVy.c_str());
     getline(is, basura, ' ');
     std::string vidaVj;
     getline(is, vidaVj, ' ');
     this->_vampiros[j].vida = std::atoi(vidaVj.c_str());
     getline(is, basura, ')');
    j++;
   }
   int s = 0;
   int listaVampirosSpawN = this->_spawning.size();
   while(s < listaVampirosSpawN) {
    this->_spawning[s].vampiro.Cargar(is);
     getline(is, basura, ' ');
     std::string fila;
     getline(is, fila, ' ');
     this->_spawning[s].fila = std::atoi(fila.c_str());
     getline(is, basura, ' ');
     std::string turnoVs;
     getline(is, turnoVs, ' ');
     this->_spawning[s].turno = std::atoi(turnoVs.c_str());
     getline(is, basura, ')');
    s++;
   }
}
