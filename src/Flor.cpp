#include "Flor.h"

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
	if(l == 0){
		nhw=hs;
	}
	while(i<l){
		if(!perteneceH(hs[i],nhw)){
			nhw.push_back(hs[i]);
		}
		i++;
	}
	return nhw;
}

bool vidaValidaF(Vida v, std::vector<Habilidad> habilidades){
	bool b;
	int lH = habilidades.size();
	int valorRealVida = 100 / (lH + 1);
	b = (v == valorRealVida);
	return b;
}

bool cPegaValidoF(int cP, std::vector<Habilidad> habilidades){
	bool b;
	if(perteneceH(Atacar, habilidades)){
		b = (cP == (12 / habilidades.size()));
	}else{
		b = (cP == 0);
	}
	return b;
}

std::string tipoHabilidad(Habilidad h){
	std::string poder;
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

Flor::Flor(Vida v, int cP, std::vector<Habilidad> hs){
	if(hs.size() == sinRepetidosH(hs).size() && vidaValidaF(v, hs) && cPegaValidoF(cP, hs)){
		this->_habilidades = hs;
		this->_vida = v;
		this->_cuantoPega = cP;
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
	os << "Flor {" << std::endl;
	os << "Vida : " << this->_vida << std::endl;
	os << "Pega : " << this->_cuantoPega << std::endl;
	os << "Habilidades : ";
	int i = 0;
	int l = this->_habilidades.size();
	while(i < l){
		os << tipoHabilidad(this->_habilidades[i]) << " ";
		i++;
	}
	os << std::endl;
	os << "}" << std::endl;
}

void Flor::Guardar(std::ostream& os){
	os << "{ F " << this->_vida << " " << this->_cuantoPega << " [ ";
	int i = 0;
	int l = this->_habilidades.size();
	while(i < l){
		os << tipoHabilidad(this->_habilidades[i]) << " ";
		i++;
	}
	os << "] }";
}

void Flor::Cargar(std::istream& is){
	std::string flor;
	getline(is, flor, 'F');
	getline(is, flor, ' ');
	std::string vidaC;
	getline(is, vidaC, ' ');
	this->_vida = std::atoi(vidaC.c_str());
	std::string cuantoPegaC;
	getline(is, cuantoPegaC, ' ');
	std::string basura;
	getline(is, basura, '[');
	this->_cuantoPega = std::atoi(cuantoPegaC.c_str());
	getline(is, flor, ' ');
	std::string habF; 
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
		// getline(is, habF, ' ');
	}
}
