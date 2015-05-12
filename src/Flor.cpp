#include "Flor.h"

//Preguntar si puedo agregar funciones auxiliares sobre el cpp, o es como dice en el enunciado que los metodos se agregan en la parte privada
//faltaria probar las auxiliares (en realidad todo)

bool perteneceH(Habilidad h, std::vector<Habilidad> hs){
	bool b = false;
	int l = hs.size();
	int i = 0;
	while(i<l){
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
	if(l==0){
		i=l;
	}
	while(i<l){
		if(!perteneceH(hs[i],nhw)){
			nhw.push_back(hs[i]);
		}
		i++;
	}
	return nhw;
}

Flor::Flor(){}

//Acá habría que agregar algo que te diga que la vida y el cuantoPega es incorrecto si difiere del requiere, para no romper los invariantes de la espec
Flor::Flor(Vida v, int cP, std::vector<Habilidad> hs){
	int i=0;
	int l = sinRepetidosH(hs).size();
	if(l==0){
		i=l;
	}
	while(i<l){
		this->_habilidades.push_back(sinRepetidosH(hs)[i]);
		i++;
	}
	this->_vida = (100 / (this->_habilidades.size() + 1));
	if(perteneceH(Atacar, this->_habilidades)){
		this->_cuantoPega = (12 / this->_habilidades.size());
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
	os << "{ F " << this->_vida << " " << this->_cuantoPega << " [ ";
	int i = 0;
	int l = this->_habilidades.size();
	while(i < l){
		os << this->habilidades[i] << " ";
		i++;
	}
	os << "] }";
}

void Flor::Cargar(std::istream& is){
	cin >> is;

}
