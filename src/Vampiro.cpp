#include "Vampiro.h"

Vampiro::Vampiro(){}

Vampiro::Vampiro(ClaseVampiro cv, Vida v, int cP){
  this->_clase = cv;
  if(v > 0 && v <= 100){
    this->_vida = v;
  }
  if(cP > 0){
    this->_cuantoPega = cP;
  }
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

void Vampiro::Mostrar(std::ostream& os)
{
}

void Vampiro::Guardar(std::ostream& os)
{
  os << "{ V " << this->_clase << " " << this->_vida << " " << this->_cuantoPega << " }";
}

void Vampiro::Cargar(std::istream& is)
{
	std::string vampiro;
	getline(is, vampiro, 'V');
  getline(is, vampiro, ' ');
	std::string tipoV;
	getline(is, tipoV, ' ');
	if(tipoV == "Caminante"){
		this->_clase = Caminante;
	}else if(tipoV == "Desviado"){
		this->_clase = Desviado;
	}
	
  std::string vidaC;
	getline(is, vidaC, ' ');
  this->_vida = std::stoi(vidaC);
  std::string cuantoPegaC;
	getline(is, cuantoPegaC, ' ');
  this->_cuantoPega = std::stoi(cuantoPegaC);
	
}
