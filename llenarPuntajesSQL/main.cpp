#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <pqxx/pqxx>

#define bigInt unsigned long long

size_t numeroAleatorio() { return 750 - (rand() % 276); }
void llenarArchivo(bigInt, bigInt);
void participante();

int main(int argc, char** argv) {
  bigInt rutInicio = 14575191, rutTermino = 19843284;
  llenarArchivo(rutInicio, rutTermino);
  participante();

  return EXIT_SUCCESS;
}

void llenarArchivo(bigInt rutInicio, bigInt rutTermino) {
  pqxx::connection conexion(
      "dbname=psudb user=psu password=seba1331\
                 hostaddr=127.0.0.1 port=54322");
  ;
  pqxx::work transaccion(conexion);
  srand(time(NULL));
  for (bigInt rut = rutInicio; rut < rutTermino; rut++) {
    int nem = numeroAleatorio();
    int ranking = numeroAleatorio();
    int matematica = numeroAleatorio();
    int lenguaje = numeroAleatorio();
    int ciencias = numeroAleatorio();
    int historia = numeroAleatorio();
    char query[256];
    sprintf(
        query,
        "INSERT INTO puntajes (rut, nem, ranking, matematica, "
        "lenguaje,ciencias, historia) VALUES (%llu, %d, %d, %d, %d, %d, %d)",
        rut, nem, ranking, matematica, lenguaje, ciencias, historia);

    transaccion.exec(query);
  }
  transaccion.commit();
}

void participante() {
  std::cout << std::endl << "=== Tarea ===" << std::endl;
  std::cout << std::endl << "Sebastián Pérez Berrios" << std::endl;
  std::cout << std::endl
            << "creacion de archivo CSV usando OpenMP C++" << std::endl;
}
