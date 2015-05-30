#include "Flor.h"

using namespace std;

// bool perteneceH(Habilidad h, vector<Habilidad> hs){
// 	bool b = false;
// 	int l = hs.size();
// 	int i = 0;
// 	while(i<l){
// 		if(h == hs[i]){
// 			b = true;
// 		}
// 		i++;
// 	}
// 	return b;

// }

// vector<Habilidad> sinRepetidosH(vector<Habilidad> hs){
// 	vector<Habilidad> nhw;
// 	int l = hs.size();
// 	int i = 0;
// 	if(l == 0){
// 		nhw=hs;
// 	}
// 	while(i<l){
// 		if(!perteneceH(hs[i],nhw)){
// 			nhw.push_back(hs[i]);
// 		}
// 		i++;
// 	}
// 	return nhw;
// }

// bool vidaValidaF(Vida v, vector<Habilidad> habilidades){
// 	bool b;
// 	int lH = habilidades.size();
// 	int valorRealVida = 100 / (lH + 1);
// 	b = (v == valorRealVida);
// 	return b;
// }

// bool cPegaValidoF(int cP, vector<Habilidad> habilidades){
// 	bool b;
// 	if(perteneceH(Atacar, habilidades)){
// 		b = (cP == (12 / habilidades.size()));
// 	}else{
// 		b = (cP == 0);
// 	}
// 	return b;
// }

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

Flor::Flor(){}

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
	os << "Flor {" << endl;
	os << "Vida : " << this->_vida << endl;
	os << "Pega : " << this->_cuantoPega << endl;
	os << "Habilidades : ";
	int i = 0;
	int l = this->_habilidades.size();
	while(i < l){
		os << tipoHabilidad(this->_habilidades[i]) << " ";
		i++;
	}
	os << endl;
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
