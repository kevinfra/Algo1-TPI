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


  j.agregarNivel(n,0);

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

   cout << "ingrese archivo para guardar el nivel" << endl;

   cout << "cant flores: " << n.floresN().size() << endl;

   string inNivel;

   cin >> inNivel;

   ofstream guardadon(inNivel);

   n.Guardar(guardadon);

  // cout << "Nivel guardado" << endl;
   
  // cout << "ingrese nombre del archivo para guardar juego" << endl;

  // string inJ;

  // cin >> inJ;

  // ofstream guardarJ(inJ);

  // j.Guardar(guardarJ);

  // cout << "juego guardado" << endl;

  n.agregarFlor(f1, Posicion(3,3));

  cout << "el largo de flores es: " << n.floresN().size() << endl;
  cout << "el largo de spawning es: " << n.spawningN().size() << endl;
  cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;

  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;  


  // f.Mostrar(cout);
  // v.Mostrar(cout);
  // n.Mostrar(cout);
  // j.Mostrar(cout);
  // // int pases=0;
  // while(n.terminado() == false){
  //   n.pasarTurno();
  //   pases++;
  //   cout << "Paso " << pases << " veces" << endl;
  // }  
  
  int pases=0;
  while(n.terminado() == false){
    n.pasarTurno();
    pases++;
    cout << "Paso " << pases << " veces" << endl;
    cout << "el largo de flores es: " << n.floresN().size() << endl;
    cout << "el largo de spawning es: " << n.spawningN().size() << endl;
    cout << "el largo de vampiros es: " << n.vampirosN().size() << endl;
    if(n.floresN().size() > 1){
      cout << "La posicion de f es (" << n.floresN()[0].pos.x << "," << n.floresN()[0].pos.y << ")" << endl;
      cout << "La posicion de f1 es (" << n.floresN()[1].pos.x << "," << n.floresN()[1].pos.y << ")" << endl;
    }else if(n.floresN().size() == 1){
      cout << "La posicion de f es (" << n.floresN()[0].pos.x << "," << n.floresN()[0].pos.y << ")" << endl;
    }else{
      cout << "no hay flores" << endl;
    }
    if(n.vampirosN().size() > 1){
      cout << "La posicion de v es (" << n.vampirosN()[0].pos.x << "," << n.vampirosN()[0].pos.y << ")" << endl;
      cout << "La posicion de v1 es (" << n.vampirosN()[1].pos.x << "," << n.vampirosN()[1].pos.y << ")" << endl;
    }else if(n.vampirosN().size() == 1){
      cout << "La posicion de v es (" << n.vampirosN()[0].pos.x << "," << n.vampirosN()[0].pos.y << ")" << endl;
    }else{
      cout << "no hay vampiros" << endl;
    }
  }


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
  string solo;

  cout << "Ingrese el nombre del archivo a cargar nivel" << endl;

  cin >> solo;

  ifstream asds(solo);

  Nivel nivelCargado;
  nivelCargado.Cargar(asds);


  assert (nivelCargado.anchoN() == 5);
  assert (nivelCargado.altoN() == 5);
  assert (nivelCargado.turnoN() == 1);
  assert (nivelCargado.solesN() == 98);
  assert (nivelCargado.floresN().size() == 1);
  assert (nivelCargado.vampirosN().size() == 0);
  assert (nivelCargado.spawningN().size() == 2);

  return 0;
}
