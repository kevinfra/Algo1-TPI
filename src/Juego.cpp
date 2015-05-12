#include "Juego.h"

Juego::Juego()
{
}

Juego::Juego(std::vector<Flor>& flores, std::vector<Vampiro>& vamps)
{
}

int Juego::nivelActual()
{
}

void Juego::pasarNivel()
{
}

std::vector<Flor>& Juego::floresJ()
{
}

std::vector<Vampiro>& Juego::vampirosJ()
{
}

std::vector<Nivel>& Juego::nivelesJ()
{
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
		int m = 0;
		int lHabilidadesFloresNiveles = this->_niveles[n].habilidadesF().size();
		while (m < lHabilidadesFloresNiveles){
			oss << this->_niveles[n].habilidadesF()[m] << " ";
			m++;
		} 
		os << "] } ";
		//falta la lista de vampiros en juego!!!
		n++;
	}
	
}

void Juego::Cargar(std::iostream& is)
{
}
