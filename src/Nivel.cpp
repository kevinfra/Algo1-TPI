#include "Nivel.h"
#include <cmath>

bool spawningOrdenado(std::vector<VampiroEnEspera>& spawninglist){
  inv v = 1;
  int l = spawninglist.size();
  bool b = false;
  while(v < l){
    if(spawninglist[v-1].turno <= spawninglist[v].turno){
      if(spawninglist[v-1].fila <= spawninglist[v].fila){
        b = true;
      }
    }
    v++;
  }
}

bool spawningValido(std::vector<VampiroEnEspera>& spawninglist, int alto){
  int v = 0;
  int l = spawninglist.size();
  bool b = true;
  while(v < l){
    if(!spawninglist[v].fila>0 || !spawninglist[v].fila <= alto || !spawninglist.turno >= 0)){
      b = false;
    }
    v++;
  }
  return b;
}

bool noHayFlorEnPos(std::vector<FlorEnJuego> flores, Posicion pos){
  int l = flores.size();
  int v = 0;
  bool b = true;
  while(v < l){
    if(flores[v].pos == pos){
      b = false;
    }
    v++;
  }
  return b;
}


Nivel::Nivel(){}

Nivel::Nivel(int ancho, int alto, int soles, std::vector<VampiroEnEspera>& spawninglist){
  if(ancho>0){
    this->_ancho = ancho;
  }else{
    cerr << "ancho no valido" << endl;
  }
  if(alto > 0){
    this->_alto = alto;
  }else{
    cerr << "alto no válido" << endl;
  }
  if(soles >= 0){
    this->_soles = soles;
  }else{
    cerr << "cantidad de soles inválida" << endl;
  }
  this->_turno = 0;
  int t = spawninglist.size();
  int v = 0;
  if(spawningValido(spawninglist, alto) && spawningOrdenado(spawninglist)){
    while(v < t){
      this->_spawning.push_back(spawninglist[v]);
      v++;
    }
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
  if(!terminado){
    this->_turno++;
    std::vector<FlorEnJuego> preFlores;
    int l = this->_flores.size();
    int v = 0;
    while(v < l){
      preFlores[v].push_back(this->_flores[v]);
      v++;
    }
    this->_flores = floresVivas(this->_flores, this->_vampiros);
    this->_vampiros = vampirosVivos(preFlores, this->_vampiros);
    int vs=0;
    int ls = this->_spawning.size();
    if(ls > 0){
      while(vs < ls){
        if(this->_spawning[vs].turno < this->_turno){
          this->_vampiros.push_back(VampiroEnJuego(this->_spawning[vs].vampiro, Posicion(this->_ancho,this->_spawning[vs].fila), this->_spawning[vs].vampiro.vidaV() ));
        }
        vs++;
      }
    }
  }
}

bool Nivel::terminado()
{
}

bool Nivel::obsesivoCompulsivo()
{
}

void Nivel::Mostrar(std::ostream& os)
{
}

void Nivel::Guardar(std::ostream& os)
{
}

void Nivel::Cargar(std::istream& is)
{
}
