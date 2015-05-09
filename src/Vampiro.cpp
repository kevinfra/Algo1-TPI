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
}

void Vampiro::Cargar(std::istream& is)
{
}
