#include "Juego.h"

bool perteneceV(Vampiro v, std::vector<Vampiro> vamps){
	bool b = false;
	int l = vamps.size();
	int i = 0;
	while(i<l){
		if(v.vidaV() == vamps[i].vidaV() && v.cuantoPegaV() == vamps[i].cuantoPegaV() && v.claseV() == vamps[i].claseV()){
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

std::vector<int> nivelesGanados(std::vector<Nivel> niveles){
	std::vector<int> ganados;
	int i = 0;
	int niv = niveles.size();
	while(i<niv){
        if(niveles[i].vampirosN().size() == 0 && niveles[i].spawningN().size() == 0){
        	ganados.push_back(i);
        }
		i++;
	}
	return ganados;
}

int maxSoles(std::vector<Nivel> niveles){
     int max = 0;
     int i = 0;
     int cantNiveles = niveles.size();
     while(i<cantNiveles){
        if(niveles[i].solesN() > max){
          max = niveles[i].solesN();
        }
        i++;
     }
     return max;
}

int maxFloresmaxSoles(std::vector<Nivel> niveles, int soles){
	 int max = 0;
     int i = 0;
     int cantNiveles = niveles.size();
     while(i<cantNiveles){
        if(niveles[i].solesN() == soles && niveles[i].floresN().size() > max){
          max = niveles[i].floresN().size();
        }
        i++;
     }
     return max;
}

Juego::Juego()
{
}

Juego::Juego(std::vector<Flor>& flores, std::vector<Vampiro>& vamps)
{
	//Preguntar como hacer para que la lista de niveles se cree vacia
	//std::vector<Nivel> nivelesVacios;
	this->_niveles = std::vector<Nivel>();
	this->nivelActual = 0;
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
	return this->_nivelActual;
}

void Juego::pasarNivel()
{
	this->_nivelActual++;
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
	//topreguntar si se agrega al final de la lista de niveles
	//o si hace falta pasarle la posicion
	if(n.turnoN() == 0 && n.floresN().size() == 0 && n.vampirosN().size() == 0){
		this->_niveles.push_back(n);	
	}
}

std::vector<Nivel> Juego::estosSaleFacil()
{
	int _maxSoles = maxSoles(this->_niveles);
	int _maxFloresmaxSoles = maxFloresmaxSoles(this->_niveles,_maxSoles);
    std::vector<Nivel> nivelesFaciles;
    int i = 0;
    int cantNiveles = this->_niveles.size();
    while(i<cantNiveles){
       if(this->_niveles[i].solesN() == _maxSoles && this->_niveles[i].floresN().size() == _maxFloresmaxSoles){
           nivelesFaciles.push_back(this->_niveles[i]);
       }
    }
    return nivelesFaciles;
}

void Juego::altoCheat(int n)
{
	int i = 0;
	int vampiros = this->_niveles[n].vampirosN().size();
    while(i<vampiros){
        if(this->_niveles[n].vampirosN()[i].vida > 1){
           this->_niveles[n].vampirosN()[i].vida = 
           this->_niveles[n].vampirosN()[i].vida / 2;
        }
    	i++;
    }
}

bool Juego::muyDeExactas()
{
    bool esFibonacci = false;
    std::vector<int> ganados = nivelesGanados(this->_niveles);
    if(ganados.size() == 1 && ganados[0] == 1){
       esFibonacci = true;
    }
    if(ganados.size() == 2 && ganados[0] == 1 && ganados[1] == 2){
    	esFibonacci = true;
    }
    if(ganados.size() > 2){
    	int i = 2;
    	esFibonacci = true;
    	int niveles = ganados.size();
    	while(i<niveles){
            if(!(ganados[i] == ganados[i-1] + ganados[i-2]))
              {
              	esFibonacci = false;
              }
    		i++;
    	}
    }
    return esFibonacci;
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
		os << "{ F " << this->_flores[i].flor.vidaF() << " " << this->_flores[i].flor.cuantoPegaF() << " [ ";
		int k = 0;
		int lHabilidadesFlores = this->_flores[i].flor.habilidadesF().size();
		while(k < lHabilidadesFlores){
			os << this->_flores[i].flor.habilidadesF()[k] << " ";
			k++;
		}
		os << "] } ";
		i++;
	}
	os << "] [ ";
	int j = 0;
	int lVampiros = this->_vampiros.size();
	while(j < lVampiros){
		os << "{ V " << this->_vampiros[j].vampiro.claseV() << " " << this->_vampiros[j].vampiro.vidaV() << " " << this->_vampiros[j].vampiro.cuantoPegaV() << " ";
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
		os << " " << this->_spawning[s].turno << " ) ";
		s++;
	}
	os << "] }";
		n++;
	}
}

void Juego::Cargar(std::iostream& is)
{
}
