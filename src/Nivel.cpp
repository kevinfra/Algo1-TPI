#include "Nivel.h"
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
  bool b = true;
  while(v < l){
    if(!(spawninglist[v].fila>0) || !(spawninglist[v].fila <= alto) || !(spawninglist[v].turno >= 0)){
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
    if(flores[v].pos.x == pos.x && flores[v].pos.y == pos.y){
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
    if(vampiros[v].pos.x == flor.pos.x && vampiros[v].pos.y == flor.pos.y){
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
    if(vampiros[v].pos.x == flor.pos.x && vampiros[v].pos.y == flor.pos.y){
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
  if (tieneHabilidad(Explotar, flor) && hayVampiroEnPos(flor, vampiros)){
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
  bool b = true;
  int v = 0;
  int largoVampiros = vampiros.size();
  while(v < largoVampiros){
    if(enMira(flor, vampiros[v]) && (vampiros[v].pos.x <= vamp.pos.x)){
      b = false;
    }
    v++;
  }
  return b;
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
  bool b = false;
  int x = 0;
  int largoFlores = flores.size();
  while(x < largoFlores){
    if(flores[x].pos.x == p.x && flores[x].pos.y == p.y && flores[x].vida - danoFlor(flores[x], vampiros) > 0){
      b = true;
    }
    x++;
  }
  return b;
}

bool hayFlorSobrevivienteExplota(Posicion p, std::vector<FlorEnJuego> flores, std::vector<VampiroEnJuego> vampiros){
  bool b = false;
  int n = 0;
  int largoFlores = flores.size();
  while(n < largoFlores){
    if(hayFlorSobreviviente(p,flores,vampiros) && !florNoExplota(flores[n], vampiros)){
      b = true;
    }
    n++;
  }
  return b;
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
  if(!hayFlorSobreviviente(p, flores, vampiros)){
    avanzaV(p, vamp);
  }else if(hayFlorSobrevivienteExplota(p,flores,vampiros)){
    p.x++;
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
      if(this->_spawning[vs].turno < this->_turno){
        this->_vampiros.push_back(VampiroEnJuego(this->_spawning[vs].vampiro, Posicion(this->_ancho,this->_spawning[vs].fila), this->_spawning[vs].vampiro.vidaV() ));
      }
      vs++;
    }
    actualizarSpawning(this->_spawning, this->_turno);
  }
}

bool Nivel::terminado(){
  bool b;
  b = ( vampiroEnColumnaCero(this->_vampiros) || (this->_vampiros.empty() && this->_spawning.empty()) );
  return b;
}

bool Nivel::obsesivoCompulsivo(){
  bool b;
  if(this->_flores.size() < 2){
    b = true;
  }else{
    std::vector<FlorEnJuego> floresOrdenadas = this->_flores;
    ordenarFlores(floresOrdenadas);
    b = hayPatron(floresOrdenadas);
  }
  return b;
}

void Nivel::Mostrar(std::ostream& os)
{
}

void Nivel::Guardar(std::ostream& os)
{
	os << "{ N " << this->anchoN() << " " << this->altoN() << " " << this->turnoN() << " " << this->solesN() << " [ ";
	int i = 0;
	int lFlores = this->floresN().size();
	while (i < lFlores){
		os << "( { F " << this->_flores[i].flor.vidaF() << " " << this->_flores[i].flor.cuantoPegaF() << " [ ";
		int k = 0;
		int lHabilidadesFlores = this->_flores[i].flor.habilidadesF().size();
		while(k < lHabilidadesFlores){
			os << this->_flores[i].flor.habilidadesF()[k] << " ";
			k++;
		}
		os << "] } ( " << this->_flores[i].pos.x << " " << this->_flores[i].pos.y << " ) " << this->_flores[i].vida << " ) ";
		i++;
	}

	os << "] [ ";
	int j = 0;
	int lVampiros = this->_vampiros.size();
	while(j < lVampiros){
		os << "( { V " << this->_vampiros[j].vampiro.claseV() << " " << this->_vampiros[j].vampiro.vidaV() << " " << this->_vampiros[j].vampiro.cuantoPegaV() << " } ( " << this->_vampiros[j].pos.x; 

		os << " " << this->_vampiros[j].pos.y << " ) " << this->_vampiros[j].vida << " ) ";
		j++;
	}
	os << "] [ ";
	int s = 0;
	int lSpawning = this->_spawning.size();
	while(s < lSpawning){
		os << "( { V " << this->_spawning[s].vampiro.claseV() << " " << this->_spawning[s].vampiro.vidaV() << " " << this->_spawning[s].vampiro.cuantoPegaV() << " } " << this->_spawning[s].fila;
		os << " " << this->_spawning[s].turno << " ) ";
	}
	os << "] }";
}

// void Nivel::Cargar(std::istream& is)
// {
//   std::string nivel;
//   getline(is, nivel, 'N');
//   getline(is, nivel, ' ');
//   std::string anchoN;
//   getline(is, anchoN, ' ');
//   this->_ancho = std::stoi(anchoN);
//   std::string altoN;
//   getline(is, altoN, ' ');
//   this->_alto = std::stoi(altoN);
//   std::string turnoN;
//   getline(is, turnoN, ' ');
//   this->_turno = std::stoi(turnoN);
//   std::string solesN;
//   getline(is, solesN, ' ');
//   this->_soles = std::stoi(solesN);
//   std::string basura;
//   getline(is, basura, '{');
//   getline(is, basura, ' ');
//   int i = 0;
//   int listaFloresN = this->_flores.size();
//   while(i < listaFloresN) {
//     std::string flor;
//     getline(is, flor, 'F');
//     getline(is, flor, ' ');
//     std::string vidaC;
//     getline(is, vidaC, ' ');    
//     this->_flores[i]. //FALTA TERMINAR
//     std::string cuantoPegaC;
//     getline(is, cuantoPegaC, '[');
//     this->_flores[i].Flor.cP = std::stoi(cuantoPegaC);
//     getline(is, flor, ' ');
//     std::string habF; 
//     while(habF != "]"){
      
      
//       getline(is, habF, ' ');
      
//       if(habF != "]"){
//         if(habF == "Atacar"){
          
//           this->_flores[i].flor.habilidadesF().push_back(Atacar);
//         }
//         if(habF == "Explotar"){
//           this->_flores[i].flor.habilidadesF().push_back(Explotar);
//         }
//         if(habF == "Generar"){
//           this->_flores[i].flor.habilidadesF().push_back(Generar);
//         } 
//       }
//     }
//     i++;
//   }
// }