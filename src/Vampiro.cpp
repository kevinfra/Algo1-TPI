#include "Vampiro.h"

std::string TipoVampiro(ClaseVampiro clase)
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
  os << "Vampiro {" << std::endl;
  os << "Vida : " << this->_vida << std::endl;
  os << "Pega : " << this->_cuantoPega << std::endl;
  os << "Clase : " << TipoVampiro(this->_clase) << std::endl;
  os << "}" << std::endl;
}

void Vampiro::Guardar(std::ostream& os)
{
  os << "{ V " << TipoVampiro(this->_clase) << " " << this->_vida << " " << this->_cuantoPega << " }";
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
  this->_vida = std::atoi(vidaC.c_str());
  std::string cuantoPegaC;
	getline(is, cuantoPegaC, ' ');
  this->_cuantoPega = std::atoi(cuantoPegaC.c_str());
	
}
