#include "Flor.h"

//Preguntar si puedo agregar funciones auxiliares sobre el cpp, o es como dice en el enunciado que los metodos se agregan en la parte privada
//faltaria probar las auxiliares (en realidad todo)

bool perteneceH(Habilidad h, std::vector<Habilidad> hs){
	bool b = false;
	int l = hs.size();
	int i = 0;
	while(i<=l){
		if(h == hs[i]){
			b = true;
		}
		i++;
	}
	return b;

}

std::vector<Habilidad> sinRepetidosH(std::vector<Habilidad> hs){
	std::vector<Habilidad> nhw;
	int l = hs.size();
	int i = 0;
	while(i<=l){
		if(!perteneceH(hw[i],nhw){
			nhw.push_back(hw[i]);
		}
		i++;
	}
	return nhw;
}

Flor::Flor(){}

//Acá habría que agregar algo que te diga que la vida y el cuantoPega es incorrecto si difiere del requiere, para no romper los invariantes de la espec
Flor::Flor(Vida v, int cP, std::vector<Habilidad> hs){
	this->_habilidades = sinRepetidosH(hs);
	this->_vida = 100 div (this->_habilidades.size() + 1);
	if(perteneceH(Atacar, this->_habilidades){
		this->_cuantoPega = 12 div this->_habilidades.size();
	}else{
		this->_cuantoPega = 0;
	}

}
Vida Flor::vidaF(){
	return this->_vida;
}
int Flor::cuantoPegaF(){
	return this->_cuantoPega;
}
std::vector<Habilidad>& Flor::habilidadesF(){
	return this->_habilidades;
}

void Flor::Mostrar(std::ostream& os){

}

void Flor::Guardar(std::ostream& os){

}

void Flor::Cargar(std::istream& is){

}
