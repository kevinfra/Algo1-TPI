#include "Juego.h"

bool perteneceV(Vampiro v, std::vector<Vampiro> vamps){
	bool b = false;
	int l = vamps.size();
	int i = 0;
	while(i<l){
		if(v == vamps[i]){
			b = true;
		}
		i++;
	}
	return b;
}

int cuenta(Habilidad h,std::vector<Habilidad> hs){
	int cant = 0;
	int l = hs.size();
	int i = 0;
	while(i<l){
	  if(h == hs[i]){
	    cant++;
	  }
	}
	return cant;
}

bool cuentaMismosHabilidades(Flor f1, Flor f2){
	bool b = true;
    int l = f1.habilidadesF.size();
    int i = 0;
    while(i<l)
    {
      if(!(cuenta(f1.habilidadesF[i],f1.habilidadesF)==cuenta(f1.habilidadesF[i],f2.habilidadesF))){
    	  b = false;
      }
    }
	return b;
}

bool floresIguales(Flor f1, Flor f2){
	return (f1.habilidadesF.size() == f2.habilidadesF.size() && cuentaMismosHabilidades(f1,f2));
}

bool perteneceF(Flor f, std::vector<Flor> flores){
	bool b = false;
	int l = flores.size();
	int i = 0;
	while(i<l){
		if(floresIguales(f,flores[i])){
			b = true;
		}
		i++;
	}
	return b;
}



std::vector<Vampiro> sinRepetidosV(std::vector<Vampiro> vamps){
	std::vector<Vampiro> nhw;
	int l = vamps.size();
	int i = 0;
	while(i<l){
		if(!perteneceV(vamps[i],nhw)){
			nhw.push_back(vamps[i]);
		}
		i++;
	}
	return nhw;
}

std::vector<Vampiro> sinRepetidosF(std::vector<Flor> flores){
	std::vector<Flor> nhw;
	int l = flores.size();
	int i = 0;
	while(i<l){
		if(!perteneceF(flores[i],nhw)){
			nhw.push_back(flores[i]);
		}
		i++;
	}
	return nhw;
}


Juego::Juego()
{
}

Juego::Juego(std::vector<Flor>& flores, std::vector<Vampiro>& vamps)
{
	//Preguntar como hacer para que la lista de niveles se cree vacia
	//std::vector<Nivel> nivelesVacios;
	this->_niveles = std::vector<Nivel>();
	int i=0;
	int l = sinRepetidosV(vamps).size();
	while(i<l){
		this->_vampiros.push_back(sinRepetidosV(vamps)[i]);
		i++;
	}
	i=0;
	while(i<l){
		this->_flores.push_back(sinRepetidosF(flores)[i]);
		i++;
	}	
}



int Juego::nivelActual()
{
}

void Juego::pasarNivel()
{
}

std::vector<Flor>& Juego::floresJ()
{
	return this->_flores;
}

std::vector<Vampiro>& Juego::vampirosJ()
{
	return this->_vampiros;
}

std::vector<Nivel>& Juego::nivelesJ()
{
	return this->_niveles;
}

void Juego::agregarNivel(Nivel& n)
{
}

std::vector<Nivel> Juego::estosSaleFacil()
{
}

void Juego::altoCheat(int n)
{
}

bool Juego::muyDeExactas()
{ 
}

void Juego::Mostrar(std::ostream& os)
{
}

void Juego::Guardar(std::ostream& os)
{
	os << "{ J [ ";
	int i = 0;
	int lFores = this->_flores.size(); 
	while (i < lFores){
		os << "{ F " << this->_flores[i].vidaF() << " " << this->_flores[i].cuantoPegaF() << " [ ";
		int k = 0;
		int lHabilidadesFlores = this->_flores[i].habilidadesF().size();
		while(k < lHabilidadesFlores){
			os << this->_flores[i].habilidadesF()[k] << " ";
			k++;
		}
		os << "] } ";
		i++;
	}
	os << "] [ ";
	int j = 0;
	int lVampiros = this->_vampiros.size();
	while(j < lVampiros){
		os << "{ V " << this->_vampiros[j].claseV() << " " << this->_vampiros[j].vidaV() << " " << this->_vampiros[j].cuantoPegaV() << " ";
		j++;	
	}
	os << "] [ ";
	
	int n = 0;
	int lNiveles = this->_niveles.size();
	while(n < lNiveles){
		os << "{ N " << this->_niveles[n].anchoN() << " " << this->_niveles[n].altoN() << " " << this->_niveles[n].turnoN() << " " << this->_niveles[n].solesN() << " [ ";
	int f = 0;
	int lFlores = this->floresN().size();
	while (f < lFores){
		os << "( { F " << this->_flores[f].vidaF() << " " << this->_flores[f].cuantoPegaF() << " [ ";
		int h = 0;
		int lHabilidadesFlores = this->_flores[f].habilidadesF().size();
		while(h < lHabilidadesFlores){
			os << this->_flores[f].habilidadesF()[h] << " ";
			h++;
		}
		os << "] } ( " << this->_flores[f].pos.x << " " << this->_flores[f].pos.y " ) " << this->_flores[f].vida <<" ) ";
		f++;
	}
	
	os << "] [ ";
	int v = 0;
	int lVampiros = this->_vampiros.size();
	while(v < lVampiros){
		os << "( { V " << this->_vampiros[v].claseV() << " " << this->_vampiros[v].vidaV() << " " << this->_vampiros[v].cuantoPegaV() << " } ( " << this->_vampiros[v].pos.x; 
		os << " " << this->_vampiros[v].pos.y << " ) " << this->_vampiros[v].vida << " ) ";
		v++;	
	}
	os << "] [ ";
	int s = 0;
	int lSpawning = this->_spawning.size();
	while(s < lSpawning){
		os << "( { V " << this->_spawning[s].claseV() << " " << this->_spawning[s].vidaV() << " " << this->_spawning[s].cuantoPegaV() << " } " << this->_spawning[s].fila;
		os << " " << this->__spawning[s].turno << " ) ";
		s++;
	}
	os << "] }";
		n++;
	}
}

void Juego::Cargar(std::iostream& is)
{
}
