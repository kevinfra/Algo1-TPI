#include "Vampiro.h"

using namespace std;

string TipoVampiro(ClaseVampiro clase)
{
  if(clase == Caminante){
    return "Caminante";
  }else if(clase == Desviado){
    return "Desviado";
  }
}

Vampiro::Vampiro(){}

Vampiro::Vampiro(ClaseVampiro cv, Vida v, int cP){
  this->_clase = cv;
  this->_vida = v;
  this->_cuantoPega = cP;
}

Vida Vampiro::vidaV()
{
  return this->_vida;
}

ClaseVampiro Vampiro::claseV()
{
  return this->_clase;
}

int Vampiro::cuantoPegaV()
{
  return this->_cuantoPega;
}

void Vampiro::Mostrar(ostream& os)
{
  os << "Vampiro {" << endl;
  os << "Vida : " << this->_vida << endl;
  os << "Pega : " << this->_cuantoPega << endl;
  os << "Clase : " << TipoVampiro(this->_clase) << endl;
  os << "}" << endl;
}

void Vampiro::Guardar(ostream& os)
{
  os << "{ V " << TipoVampiro(this->_clase) << " " << this->_vida << " " << this->_cuantoPega << " }";
}

void Vampiro::Cargar(istream& is)
{
	string vampiro;
	getline(is, vampiro, 'V');
  getline(is, vampiro, ' ');
	string tipoV;
	getline(is, tipoV, ' ');
	if(tipoV == "Caminante"){
		this->_clase = Caminante;
	}else if(tipoV == "Desviado"){
		this->_clase = Desviado;
	}	
  string vidaC;
	getline(is, vidaC, ' ');
  this->_vida = atoi(vidaC.c_str());
  string cuantoPegaC;
	getline(is, cuantoPegaC, ' ');
  this->_cuantoPega = atoi(cuantoPegaC.c_str());
}
