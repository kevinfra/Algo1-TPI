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

int danoFlor(FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
  int cp = 0;
  int v = 0;
  int l = vampiros.size();
  while(v < l){
    if(vampiro[v].pos = flor.pos){
      cp = cp + vampiros[v].vampiro.cuantoPegaV();
    }
    v++;
  }
  return cp;
}

bool hayVampiroEnPos(FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
  bool b = false;
  int lv = vampiros.size();
  int v = 0;
  while(v < lv){
    if(vampiros[v].pos == flor.pos){
      b = true;
    }
    v++;
  }
  return b;
}

bool tieneHabilidad(Habilidad h, FlorEnJuego flor){
  bool b = false;
  int v = 0;
  int lh = flor.flor.habilidadesF().size();
  while(v < lh){
    if(h == flor.flor.habilidadesF()[v]){
      b = true;
    }
    v++;
  }
  return b;
}

bool florNoExplota(FlorEnJuego flor, std::vector<VampiroEnJuego> vampiros){
  bool b = true;
  if (tieneHabilidad(Explotar, flor.flor) && hayVampiroEnPos(flor, vampiros)){
    b = false;
  }
  return b;
}

std::vector<FlorEnJuego> floresVivas(std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
  std::vector<FlorEnJuego> nuevaListaFlores;
  int l = flores.size();
  int v = 0;
  while(v < l){
    if(florNoExplota(flores[v], vampiros) && flores[v].vida - danoFlor(flores[v], vampiros) > 0){
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
    v++
  }
  v = 0 ;
  //Ahora empiezo a llenarla con los elementos de la lista flores que quiero
  while(v < lFlores){
    preFlores.push_back(flores[v]);
    v++;
  }
}

std::vector<VampiroEnJuego> vampirosVivos(std::vector<FlorEnJuego> preFlores, std::vector<VampiroEnJuego> preVampiros){


}

int solesGenerados(std::vector<FlorEnJuego> preFlores){
  int s = 1;
  int v = 0
  int lF = preFlores.size();
  while(v < lF){
    if(perteneceH(Generar, preFlores[v].habilidadesF())){
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
    if(preSpaw[v].turno >= turno){
      spaw.push_back(preSpaw[v]);
    }
    v++;
  }
}

bool vampiroEnColumnaCero(std::vector<VampiroEnJuego> vampiros){
  int v = 0;
  int largoVamps = vampiros.size();
  bool b = false;
  while(v < largoVamps){
    if(vampiros[v].pos.y == 0){
      b = true;
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
  if(!terminado){
    this->_turno++;
    std::vector<FlorEnJuego> preFlores;
    int l = this->_flores.size();
    int v = 0;
    floresIguales(preFlores, this->_flores);
    floresIguales(this->_flores, floresVivas(this->_flores, this->_vampiros));
    vampirosIguales(this->_vampiros, vampirosVivos(preFlores, this->_vampiros));
    int vs=0;
    int largoSpaw = this->_spawning.size();
    while(vs < largoSpaw){
      if(this->_spawning[vs].turno < this->_turno){
        this->_vampiros.push_back(VampiroEnJuego(this->_spawning[vs].vampiro, Posicion(this->_ancho,this->_spawning[vs].fila), this->_spawning[vs].vampiro.vidaV() ));
      }
      vs++;
    }
    actualizarSpawning(this->_spawning, this->_turno);
    this->_soles = this->_soles + solesGenerados(preFlores);
  }
}

bool Nivel::terminado(){
  bool b;
  b = ( vampiroEnColumnaCero(this->_vampiros) || (this->_vampiros.empty() && this->_spawning.empty()) )
  return b;
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
