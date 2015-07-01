#include "Flor.h"

using namespace std;

string tipoHabilidad(Habilidad h){
	string poder;
	if(h==Generar){
		poder="Generar";
	}else if(h == Atacar){
		poder="Atacar";
	}else{
		poder="Explotar";
	}
	return poder;
}

Flor::Flor(){
	this->_vida = 100;
	this->_cuantoPega = 0;
}

Flor::Flor(Vida v, int cP, vector<Habilidad> hs){
	this->_habilidades = hs;
	this->_vida = v;
	this->_cuantoPega = cP;
}

Vida Flor::vidaF(){
	return this->_vida;
}

int Flor::cuantoPegaF(){
	return this->_cuantoPega;
}

vector<Habilidad>& Flor::habilidadesF(){
	return this->_habilidades;
}

void Flor::Mostrar(ostream& os){
	os << "Flor {";
	os << "Vida: " << this->_vida;
	os << " ,Pega: " << this->_cuantoPega;
	os << " ,Habilidades: ";
	int i = 0;
	int l = this->_habilidades.size();
	while(i < l){
		os << tipoHabilidad(this->_habilidades[i]) << " ";
		i++;
	}
	os << "}" << endl;
}

void Flor::Guardar(ostream& os){
	os << "{ F " << this->_vida << " " << this->_cuantoPega << " [ ";
	int i = 0;
	int l = this->_habilidades.size();
	while(i < l){
		os << tipoHabilidad(this->_habilidades[i]) << " ";
		i++;
	}
	os << "] }";
}

void Flor::Cargar(istream& is){
	string flor;
	getline(is, flor, 'F');
	getline(is, flor, ' ');
	string vidaC;
	getline(is, vidaC, ' ');
	this->_vida = atoi(vidaC.c_str());
	string cuantoPegaC;
	getline(is, cuantoPegaC, ' ');
	string basura;
	getline(is, basura, '[');
	this->_cuantoPega = atoi(cuantoPegaC.c_str());
	getline(is, flor, ' ');
	string habF; 
	while(habF.back() != ']'){
		getline(is, habF, ' ');
		if(habF != "]"){
			if(habF == "Atacar"){
				this->_habilidades.push_back(Atacar);
			}
			if(habF == "Explotar"){
				this->_habilidades.push_back(Explotar);
			}
			if(habF == "Generar"){
				this->_habilidades.push_back(Generar);
			} 
		}
	}
}
