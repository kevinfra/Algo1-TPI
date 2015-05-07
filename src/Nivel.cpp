#include "Nivel.h"

Nivel::Nivel()
{
}

Nivel::Nivel(int ancho, int alto, int soles, std::vector<VampiroEnEspera>& spawninglist)
{
}

int Nivel::anchoN()
{
}

int Nivel::altoN()
{
}

int Nivel::turnoN()
{
}

int Nivel::solesN()
{
}

std::vector<FlorEnJuego>& Nivel::floresN()
{
}

std::vector<VampiroEnJuego>& Nivel::vampirosN()
{
}

std::vector<VampiroEnEspera>& Nivel::spawningN()
{
}

void Nivel::agregarFlor(Flor f, Posicion p)
{
}

void Nivel::pasarTurno()
{
}

bool Nivel::terminado()
{
}

bool Nivel::obsesivoCompulsivo()
{
}

void Nivel::Mostrar(std::ostream& os)
{
}

void Nivel::Guardar(std::ostream& os)
{
}

void Nivel::Cargar(std::istream& is)
{
}
