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

  Flor f1(33,6,hab2);

  cout << f.vidaF() << ' ' << f.cuantoPegaF() << endl;

  Vampiro v(Caminante,50,50);

  Vampiro v1(Caminante,100,100);

  cout << v.vidaV() << ' ' << v.cuantoPegaV() << endl;

  vector<VampiroEnEspera> spawn;
  spawn.push_back(VampiroEnEspera(v,2,2));

  spawn.push_back(VampiroEnEspera(v1,3,3));

  Nivel n(5,5,100,spawn);

  cout << n.solesN() << endl;

  n.agregarFlor(f, Posicion(2,2));

  cout << "el largo de spawning es: " << n.spawningN().size() << endl;

  cout << n.solesN() << endl;

  n.pasarTurno();

  cout << n.solesN() << endl;

  cout << "el largo de spawning es: " << n.spawningN().size() << endl;

  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;

  vector<Flor> fs;
  fs.push_back(f);

  vector<Vampiro> vs;
  vs.push_back(v);

  Juego j(fs,vs);

  // Nivel n1(4,4,100,spawn);

  // j.agregarNivel(n);

  cout << j.muyDeExactas() << endl;

  cout << j.nivelesJ().size() << endl;

  // cout << "ingrese archivo para guardar flor" << endl;

  // string in;

  // cin >> in;

  // ofstream guardado(in);

  // f.Guardar(guardado);

  // cout << "flor guardada" << endl;

  // cout << "ingrese archivo para guardar Vampiro" << endl;

  // string inv;

  // cin >> inv;

  // ofstream guardadov(inv);

  // v.Guardar(guardadov);

  // cout << "vampiro guardado" << endl;

  // cout << "ingrese archivo para guardar el nivel" << endl;

  // string inNivel;

  // cin >> inNivel;

  // ofstream guardadon(inNivel);

  // n.Guardar(guardadon);

  // cout << "Nivel guardado" << endl;

  // cout << "ingrese nombre del archivo para guardar juego" << endl;

  // string inJ;

  // cin >> inJ;

  // ofstream guardarJ(inJ);

  // j.Guardar(guardarJ);

  // cout << "juego guardado" << endl;

  n.pasarTurno();

  cout << "el largo de spawning es: " << n.spawningN().size() << endl;

  cout << "el largo de flores es: " << n.floresN().size() << endl;

  cout << n.obsesivoCompulsivo() << endl;  

  n.agregarFlor(f1, Posicion(1,3));

  cout << "el largo de flores es: " << n.floresN().size() << endl;

  n.pasarTurno();

  cout << "el largo de spawning es: " << n.spawningN().size() << endl;

  cout << n.terminado() << endl;

  cout << "el largo de flores es: " << n.floresN().size() << endl;

  cout << n.obsesivoCompulsivo() << endl;  

  cout << "el largo de spawning es: " << n.spawningN().size() << endl;

  n.pasarTurno();

  cout << "el largo de spawning es: " << n.spawningN().size() << endl;

  n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
  
  n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;

  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;  

  n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
  
  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;  
  n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
  
  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;  
  n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
  
  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;  
n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;  

  n.pasarTurno();

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;


  f.Mostrar(cout);
  v.Mostrar(cout);
  n.Mostrar(cout);
  j.Mostrar(cout);
  // int pases=0;
  // while(n.terminado() == false){
  //   n.pasarTurno();
  //   pases++;
  //   cout << "Paso " << pases << " veces" << endl;
  // }  
  



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
