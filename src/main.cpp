#include "Juego.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main(){

  cout << " Trabajo practico Flores vs Vampiros" << endl;

  vector<Habilidad> hab;
  hab.push_back(Atacar);

  vector<Habilidad> hab2;
  hab2.push_back(Atacar);
  hab2.push_back(Generar);

  vector<Habilidad> hab3;
  hab3.push_back(Explotar);
  hab3.push_back(Generar);

  Flor f(33,0,hab3);

  cout << f.vidaF() << ' ' << f.cuantoPegaF() << endl;

  Vampiro v(Caminante,50,50);

  cout << v.vidaV() << ' ' << v.cuantoPegaV() << endl;

  vector<VampiroEnEspera> spawn;
  spawn.push_back(VampiroEnEspera(v,2,2));

  Nivel n(5,5,100,spawn);

  cout << n.solesN() << endl;

  n.agregarFlor(f, Posicion(2,2));

  cout << n.solesN() << endl;

  n.pasarTurno();

  cout << n.solesN() << endl;

  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;

/*
  vector<Flor> fs;
  fs.push_back(f);

  vector<Vampiro> vs;
  vs.push_back(v);

  Juego j(fs,vs);

  j.agregarNivel(n);

  cout << j.muyDeExactas() << endl;
*/






  // -------------------------TESTS------------------------------
  //descomentar de acá para abajo para correrlos
  /*
  Flor f1(100 / 3,6,hab2);
  assert (f1.vidaF() == 100/3);
  assert (f1.cuantoPegaF() == 6);
  assert (f1.habilidadesF().size() == 2);
  assert (f1.habilidadesF()[0] == 1);
  assert (f1.habilidadesF()[1] == 0);

  cout << "Flor esta bien" << endl;

  Vampiro v1(Caminante,50,30);
  assert (v1.claseV == 0);
  assert (v1.vidaV() == 50);
  assert (v1.cuantoPegaV() == 30);

  cout << "Vampiro esta bien" << endl;

  Nivel n1(10,20,0,)
*/
  return 0;
}
