#include "Juego.h"

using namespace std;

bool vampirosIguales(Vampiro v1, Vampiro v2){
	return (v1.vidaV() == v2.vidaV() && v1.cuantoPegaV() == v2.cuantoPegaV() && v1.claseV() == v2.claseV());
}

bool perteneceV(Vampiro v,vector<Vampiro> vamps){
	int l = vamps.size();
	int i = 0;
	while(i<l && !(vampirosIguales(v,vamps[i]))){
		i++;
	}
	return i < l;
}

int cuenta(Habilidad h,vector<Habilidad> hs){
	int cant = 0;
	int l = hs.size();
	int i = 0;
	while(i<l){
	  if(h == hs[i]){
	    cant++;
	  }
	  i++;
	}
	return cant;
}


bool cuentaMismosHabilidades(Flor f1, Flor f2){
    int l = f1.habilidadesF().size();
    int i = 0;
    while(i<l && cuenta(f1.habilidadesF()[i],f1.habilidadesF())==cuenta(f1.habilidadesF()[i],f2.habilidadesF()))
    {
     i++;
    }
	return i==l;
}

bool floresIguales(Flor f1, Flor f2){
	return (f1.habilidadesF().size() == f2.habilidadesF().size() && cuentaMismosHabilidades(f1,f2));
}

bool perteneceF(Flor f, vector<Flor> flores){
	int l = flores.size();
	int i = 0;
	while(i<l && !(floresIguales(f,flores[i]))){
		i++;
	}
	return i < l;
}



vector<Vampiro> sinRepetidosV(vector<Vampiro>& vamps){
	vector<Vampiro> _vampsSinRepetir;
	int l = vamps.size();
	int i = 0;
	while(i<l){
		if(!perteneceV(vamps[i],_vampsSinRepetir)){
			_vampsSinRepetir.push_back(vamps[i]);
		}
		i++;
	}
	return _vampsSinRepetir;
}

vector<Flor> sinRepetidosF(vector<Flor>& flores){
	vector<Flor> _floresSinRepetir;
	int l = flores.size();
	int i = 0;
	while(i<l){
		if(!perteneceF(flores[i],_floresSinRepetir)){
			_floresSinRepetir.push_back(flores[i]);
		}
		i++;
	}
	return _floresSinRepetir;
}

vector<int> nivelesGanados(vector<Nivel> niveles){
	vector<int> ganados;
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

int maxSoles(vector<Nivel> niveles){
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

int maxFloresmaxSoles(vector<Nivel> niveles, int soles){
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

Juego::Juego(vector<Flor>& flores, vector<Vampiro>& vamps)
{
	this->_niveles = vector<Nivel>();
	this->_nivelActual = 0;
	this->_vampiros = sinRepetidosV(vamps);
	this->_flores = sinRepetidosF(flores);
}



int Juego::nivelActual()
{
	return this->_nivelActual;
}

void Juego::pasarNivel()
{
	this->_nivelActual++;
}

vector<Flor>& Juego::floresJ()
{
	return this->_flores;
}

vector<Vampiro>& Juego::vampirosJ()
{
	return this->_vampiros;
}

vector<Nivel>& Juego::nivelesJ()
{
	return this->_niveles;
}

void Juego::agregarNivel(Nivel& n, int i)
{
	vector<Nivel> _nivelesSiguientes;
	int l = this->_niveles.size();
	int j = i;
	while(j<l){
		_nivelesSiguientes.push_back(this->_niveles[j]);
		j++;
	}
	this->_niveles.resize(i+1);
	this->_niveles[i] = n;
	j = 0;
	l = _nivelesSiguientes.size();
    while(j<l){
      this->_niveles.push_back(_nivelesSiguientes[j]);
      j++;
    }
}

void Juego::jugarNivel(Nivel& n, int i)
{
    this->_niveles[i] = n;
}

vector<Nivel> Juego::estosSaleFacil()
{
	int _maxSoles = maxSoles(this->_niveles);
	int _maxFloresmaxSoles = maxFloresmaxSoles(this->_niveles,_maxSoles);
    vector<Nivel> nivelesFaciles;
    int i = 0;
    int cantNiveles = this->_niveles.size();
    while(i<cantNiveles){
       if(this->_niveles[i].solesN() == _maxSoles && this->_niveles[i].floresN().size() == _maxFloresmaxSoles){
           nivelesFaciles.push_back(this->_niveles[i]);
       }
       i++;
    }
    return nivelesFaciles;
}

vector<VampiroEnJuego> vampirosMitadVida(vector<VampiroEnJuego>& vampiros)
{
   vector<VampiroEnJuego> _vampsMitad;
   int i = 0;
   int l = vampiros.size();
   while(i<l){
      if(!((vampiros[i].vida / 2) == 0)){
	      vampiros[i].vida = vampiros[i].vida / 2;
         _vampsMitad.push_back(vampiros[i]);
      }
      i++;
   }
   return _vampsMitad;
}

void Juego::altoCheat(int n)
{
	this->_niveles[n].vampirosN() = vampirosMitadVida(this->_niveles[n].vampirosN());
}

bool esFibonacciCasoBaseUno(vector<int> niveles){
    return (niveles.size()== 1 && niveles[0] ==1);
}

bool esFibonacciCasoBaseDos(vector<int> niveles){
    return (niveles.size()== 2 && niveles[0] ==1 && niveles[1] == 2);
}

bool Juego::muyDeExactas()
{
    vector<int> ganados = nivelesGanados(this->_niveles);
    int i = 2;
    int l = ganados.size();
    while(i<l && (ganados[i] == ganados[i-1] + ganados[i-2])){
    	i++;
    }
    return (i == l || esFibonacciCasoBaseUno(ganados) || esFibonacciCasoBaseDos(ganados));
}

void Juego::Mostrar(ostream& os)
{
	os << "Juego {" << endl;
	os << "Flores : {" << endl;
	int i = 0;
	int lFlores = this->_flores.size();
	while (i < lFlores){
		this->_flores[i].Mostrar(os);
		i++;
	}
	os << "}" << endl;
	os << "Vampiros : {" << endl;
	int j = 0;
	int lVampiros = this->_vampiros.size();
	while(j < lVampiros){
		this->_vampiros[j].Mostrar(os);
		j++;
	}
	os << "}" << endl;
	os << "Niveles : {" << endl;
	 int n = 0;
	int lNiveles = this->_niveles.size();
	while(n < lNiveles){
		this->_niveles[n].Mostrar(os);
		n++;
	}
	os << "}" << endl;
	os << "}" << endl;
}

void Juego::Guardar(ostream& os){
	os << "{ J [ ";
	int i = 0;
	int lFlores = this->_flores.size();
	while (i < lFlores){
		this->_flores[i].Guardar(os);
		i++;
	}
	os << " ] [ ";
	int j = 0;
	int lVampiros = this->_vampiros.size();
	while(j < lVampiros){
		this->_vampiros[j].Guardar(os);
		j++;
	}
	os << " ] [ ";
	int n = 0;
	int lNiveles = this->_niveles.size();
	while(n < lNiveles){
		this->_niveles[n].Guardar(os);
		n++;
	}
	os << " ] }" << endl;
}

void Juego::Cargar(iostream& is)
{
	string juego;
	getline(is, juego, 'J');
	string basura;
	string cambioTipo;
	getline(is, cambioTipo, ' ');
	char ultimoCambio=cambioTipo.back();
	while (ultimoCambio != ']') {
		Flor cargaF;
		cargaF.Cargar(is);
		this->_flores.push_back(cargaF);
		getline(is, basura, ' ');
		getline(is, cambioTipo, ' ');
		ultimoCambio = cambioTipo.back();
	}
	getline(is, basura, ' ');
	getline(is, cambioTipo, ' ');
	ultimoCambio = cambioTipo.back();
	while (ultimoCambio != ']') {
		Vampiro cargaF;
		cargaF.Cargar(is);
		this->_vampiros.push_back(cargaF);
		getline(is, basura, ' ');
		getline(is, cambioTipo, ' ');
		ultimoCambio = cambioTipo.back();
	}
	getline(is, basura, ' ');
	getline(is, cambioTipo, ' ');
	ultimoCambio = cambioTipo.back();
	while (ultimoCambio != ']') {
		Nivel cargaN;
		cargaN.Cargar(is);
		this->_niveles.push_back(cargaN);
		getline(is, basura, ' ');
		getline(is, cambioTipo, ' ');
		ultimoCambio = cambioTipo.back();
	}
	this->_nivelActual = 0;
}
