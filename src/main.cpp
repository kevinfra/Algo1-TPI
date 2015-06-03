#include "Juego.h"
#include <iostream>
#include <assert.h>

using namespace std;

bool NivelesIgualesParaTest(Nivel n1, Nivel n2){
  return (n1.anchoN() == n2.anchoN() && n1.altoN() == n2.altoN() && n1.turnoN() == n2.turnoN() && n1.solesN() == n2.solesN());
}

int main(){

  cout << " Trabajo practico Flores vs Vampiros" << endl;


  //-----------------Test Flor-----------------
  cout << "Test Flor" << endl;

  vector<Habilidad> hab1;
  hab1.push_back(Atacar);

  vector<Habilidad> hab2;
  hab2.push_back(Atacar);
  hab2.push_back(Generar);

  vector<Habilidad> hab3;
  hab3.push_back(Explotar);
  hab3.push_back(Generar);

  vector<Habilidad> hab4;
  hab4.push_back(Explotar);
  hab4.push_back(Explotar);
  hab4.push_back(Atacar);
  hab4.push_back(Generar);
  hab4.push_back(Generar);
  hab4.push_back(Generar);


  Flor f1(33,0,hab3);

  Flor f2(33,6,hab2);

  Flor f3(50,12,hab1);

  Flor f4(25,6,hab4);

  Flor f5(33,0,hab3);

  Flor f6(33,6,hab2);

  Flor f7(33,0,hab3);

  Flor f8(33,6,hab2);

  assert(f1.vidaF() == 33);
  assert(f1.cuantoPegaF() == 0);
  //assert(f4.habilidadesF().size() == 0);

  cout << "f1 size : " << f1.habilidadesF().size() << endl;
  cout << "f2 size : " << f2.habilidadesF().size() << endl;
  cout << "f3 size : " << f3.habilidadesF().size() << endl;
  cout << "f4 size : " << f4.habilidadesF().size() << endl;

  f1.Mostrar(cout);
  ofstream guardarFlor("guardarFlor.txt");
  f1.Guardar(guardarFlor);
  ifstream cargarFlor("guardarFlor.txt");
  //f1.Cargar(cargarFlor);

  f4.Mostrar(cout);
  ofstream guardarFlor2("guardarFlor2.txt");
  f4.Guardar(guardarFlor2);
  ifstream cargarFlor2("guardarFlor2.txt");
  //f4.Cargar(cargarFlor2);

  //-------------Fin test Flor------------------
  //-------------Test Vampiro-------------------
  cout << "Test vampiro" << endl;

  Vampiro v1(Desviado,50,50);

  Vampiro v2(Caminante,100,100);

  Vampiro v3(Desviado,50,50);

  Vampiro v4(Caminante,100,100);

  Vampiro v5(Caminante,50,500000);

  Vampiro v6(Desviado,100,100);

  Vampiro v7(Desviado,1,50);

  Vampiro v8(Desviado,1,100);

  Vampiro v9(Caminante,0,50);

  Vampiro v10(Caminante,98,100);

  Vampiro v11(Caminante,33,50);

  Vampiro v12(Caminante,100,100);

  assert(v1.vidaV() == 50);
  assert(v1.cuantoPegaV() == 50);
  assert(v1.claseV() == Desviado);
  assert(v9.vidaV() == 0);
  assert(v9.cuantoPegaV() == 50);
  assert(v9.claseV() == Caminante);
  assert(v5.cuantoPegaV() == 500000);

  v1.Mostrar(cout);
  ofstream guardarVampiro("guardarVampiro.txt");
  v1.Guardar(guardarVampiro);
  ifstream cargarVampiro("guardarVampiro.txt");
  //v1.Cargar(cargarVampiro);


  //--------------Fin test vampiro--------------
  //--------------Test Nivel--------------------



  vector<VampiroEnEspera> spawn;
  spawn.push_back(VampiroEnEspera(v6,2,2));
  spawn.push_back(VampiroEnEspera(v1,3,3));
  spawn.push_back(VampiroEnEspera(v2,4,4));
  spawn.push_back(VampiroEnEspera(v3,4,5));
  spawn.push_back(VampiroEnEspera(v4,5,5));
  spawn.push_back(VampiroEnEspera(v5,6,5));

  vector<VampiroEnEspera> spawn2;
  spawn2.push_back(VampiroEnEspera(v7,1,0));
  spawn2.push_back(VampiroEnEspera(v8,2,0));
  spawn2.push_back(VampiroEnEspera(v9,3,0));
  spawn2.push_back(VampiroEnEspera(v10,3,0));

  Nivel n(10,10,100,spawn);

  Nivel n2(5,5,30,spawn);

  Nivel n3(2,8,100,spawn);

  Nivel n4(5,5,100,spawn);

  Nivel n5(2,4,100,spawn);

  Nivel n6(5,5,110,spawn);

  Nivel n7(12,12,100,spawn2);

  n.agregarFlor(f1, Posicion(4,3));
  n.agregarFlor(f2, Posicion(5,5));
  n.agregarFlor(f5, Posicion(6,6));
  n.agregarFlor(f8, Posicion(7,1));

  assert(n.obsesivoCompulsivo() == true);

  n2.agregarFlor(f1, Posicion(4,15));
  n2.agregarFlor(f2, Posicion(3,15));
  n2.agregarFlor(f5, Posicion(5,15));
  n2.agregarFlor(f8, Posicion(2,15));
  assert(n2.obsesivoCompulsivo() == false);

  //n2.agregarFlor(f3, Posicion(1,15));
  //n2.agregarFlor(f1, Posicion(2,15));
  //n2.agregarFlor(f2, Posicion(3,15));
  //n2.agregarFlor(f4, Posicion(4,15));

  //assert(n2.obsesivoCompulsivo() == true);

  cout << "El largo de spawning es: " << n.spawningN().size() << endl;
  cout << endl;
  cout << "Pasar turno" << endl;
  cout << "Soles iniciales: " << n.solesN() << endl;

  int pases=0;
  while(n.terminado() == false){
    n.pasarTurno();
    pases++;
    cout << "Turno: " << pases <<  endl;
    cout << "Soles: " << n.solesN() << endl;
    cout << "El largo de flores es: " << n.floresN().size() << endl;
    cout << "El largo de spawning es: " << n.spawningN().size() << endl;
    cout << "El largo de vampiros es: " << n.vampirosN().size() << endl;
    int j = 0;
    while(j<n.floresN().size()){
      n.floresN()[j].flor.Mostrar(cout);
      cout << "La posicion de Flor es (" << n.floresN()[j].pos.x << "," << n.floresN()[j].pos.y << ")" << endl;
      j++;
    }
    if(n.floresN().size() == 0){
      cout << "No hay flores" << endl;
    }
    j = 0;
    while(j<n.vampirosN().size()){
      n.vampirosN()[j].vampiro.Mostrar(cout);
      cout << "La posicion de Vampiro es (" << n.vampirosN()[j].pos.x << "," << n.vampirosN()[j].pos.y << ")" << endl;
      j++;
    }
    if(n.vampirosN().size() == 0){
      cout << "No hay vampiros" << endl;
    }
    cout << endl;
    cout << endl;
  }

  cout << "Soles finales: " << n.solesN() << endl;

  cout << "El largo de spawning es: " << n.spawningN().size() << endl;

  //---------------Fin test Nivel---------------
  //---------------Test Juego-------------------
  cout << "Test Juego" << endl;

  vector<Flor> fs;
  fs.push_back(f1);
  fs.push_back(f1);
  fs.push_back(f1);
  fs.push_back(f1);
  fs.push_back(f2);
  fs.push_back(f3);

  vector<Vampiro> vs;
  vs.push_back(v1);
  vs.push_back(v1);
  vs.push_back(v1);
  vs.push_back(v2);
  vs.push_back(v5);
  vs.push_back(v9);

  Juego j(fs,vs);

  assert(j.floresJ().size() == 3);
  assert(j.vampirosJ().size() == 4);
  assert(j.nivelesJ().size() == 0);

  j.agregarNivel(n,0);

  assert(j.nivelesJ().size() == 1);

  j.agregarNivel(n5,1);

  assert(j.nivelesJ().size() == 2);

  j.agregarNivel(n2,0);

  assert(NivelesIgualesParaTest(j.nivelesJ()[0],n2) == true);
  assert(NivelesIgualesParaTest(j.nivelesJ()[1],n) == true);
  assert(NivelesIgualesParaTest(j.nivelesJ()[2],n5) == true);

  j.agregarNivel(n3,1);

  assert(NivelesIgualesParaTest(j.nivelesJ()[0],n2) == true);
  assert(NivelesIgualesParaTest(j.nivelesJ()[1],n3) == true);
  assert(NivelesIgualesParaTest(j.nivelesJ()[2],n) == true);
  assert(NivelesIgualesParaTest(j.nivelesJ()[3],n5) == true);

  j.jugarNivel(n6,2);

  assert(NivelesIgualesParaTest(j.nivelesJ()[2],n6) == true);

  assert(j.estosSaleFacil().size() == 1);
  assert(j.estosSaleFacil()[0].solesN() == 110);

  n7.pasarTurno();

  j.agregarNivel(n7,4);


cout << "largo vampiros " << j.nivelesJ()[4].vampirosN().size() << endl;
  assert(j.nivelesJ()[4].vampirosN().size() == 4);
  j.altoCheat(4);
  assert(j.nivelesJ()[4].vampirosN().size() == 1);
  assert(j.nivelesJ()[4].vampirosN()[0].vida == 49);

  vector<VampiroEnEspera> spawnVacio;


  Juego j2(fs,vs);

  Nivel nVacio(10,10,40,spawnVacio);
  Nivel n1Vacio(10,10,40,spawnVacio);
  Nivel n2Vacio(10,10,40,spawnVacio);
  Nivel n3Vacio(10,10,40,spawnVacio);
  Nivel n4Vacio(10,10,40,spawnVacio);

  Nivel nLleno(10,10,30,spawn2);
  Nivel nLleno1(10,12,40,spawn2);
  Nivel nLleno2(10,10,30,spawn2);
  Nivel nLleno3(10,10,30,spawn2);

  j2.agregarNivel(nVacio,0);
  j2.agregarNivel(n1Vacio,1);
  j2.agregarNivel(n2Vacio,2);

  assert(j2.muyDeExactas() == false);

  Juego j3(fs,vs);

  j3.agregarNivel(nLleno,0);
  j3.agregarNivel(nVacio,1);
  j3.agregarNivel(n1Vacio,2);
  j3.agregarNivel(n2Vacio,3);
  j3.agregarNivel(nLleno1,4);
  j3.agregarNivel(n3Vacio,5);
  j3.agregarNivel(nLleno2,6);
  j3.agregarNivel(nLleno3,7);
  j3.agregarNivel(n4Vacio,8);

  assert(j3.muyDeExactas() == true);

  Juego j4(fs,vs);

  j4.agregarNivel(nLleno,0);
  j4.agregarNivel(nVacio,1);

  assert(j4.muyDeExactas() == true);

  Juego j5(fs,vs);

  j5.agregarNivel(nLleno,0);
  j5.agregarNivel(nVacio,1);
  j5.agregarNivel(n2Vacio,2);

  assert(j5.muyDeExactas() == true);
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

  n.Mostrar(cout);

  j.Mostrar(cout);

  cout << "ingrese archivo para guardar el nivel" << endl;

  string inNivel;

  cin >> inNivel;

  ofstream guardadon(inNivel);

  n.Guardar(guardadon);

  cout << "Nivel guardado" << endl;

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


  // f.Mostrar(cout);
  // v.Mostrar(cout);
  // n.Mostrar(cout);
  // j.Mostrar(cout);
  // // int pases=0;

  // int pases=0;
  // while(n.terminado() == false){
  //   n.pasarTurno();
  //   pases++;
  //   cout << "Paso " << pases << " veces" << endl;
  // }

  ofstream juegoGuardado("juego.txt");
  j.Guardar(juegoGuardado);


  // -------------------------TESTS------------------------------
  //descomentar de acá para abajo para correrlos
  /*
  cout << "Test Flor" << endl;
  Flor f1(100 / 3,6,hab2);
  assert (f1.vidaF() == 100/3);
  assert (f1.cuantoPegaF() == 6);
  assert (f1.habilidadesF().size() == 2);
  assert (f1.habilidadesF()[0] == 1);
  assert (f1.habilidadesF()[1] == 0);
  f.Mostrar(cout);
  f.Guardar(os);
  cout << "Flor esta bien" << endl;

  cout << "Test Vampiro" << endl;
  Vampiro v1(Caminante,50,30);
  assert (v1.claseV == 0);
  assert (v1.vidaV() == 50);
  assert (v1.cuantoPegaV() == 30);
  v.Mostrar(cout);
  v.Guardar(os);
  cout << "Vampiro esta bien" << endl;

  cout << "Test nivel" << endl;
  Nivel n1(10,20,0,)
*/
  string solo;

  cout << "Ingrese el nombre del archivo a cargar nivel" << endl;

  cin >> solo;

  ifstream asds(solo);

  Nivel nivelCargado;
  nivelCargado.Cargar(asds);


  assert (nivelCargado.anchoN() == 10);
  assert (nivelCargado.altoN() == 10);
  assert (nivelCargado.turnoN() == 12);
  assert (nivelCargado.solesN() == 135);
  assert (nivelCargado.floresN().size() == 1);
  assert (nivelCargado.vampirosN().size() == 6);
  assert (nivelCargado.spawningN().size() == 0);

  return 0;
}
