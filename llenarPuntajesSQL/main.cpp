#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <pqxx/pqxx>

#define bigInt unsigned long long

size_t numeroAleatorio() { return 750 - (rand() % 276); }
void llenarBaseDatos(bigInt, bigInt, const std::string &);
void participante();

int main(int argc, char **argv) {
  std::string nombreBBDD;
  std::string usuario;
  std::string contrasena;
  std::string ip("127.0.0.1");
  std::string puerto("5432");

  if (argc < 4) {
    std::cerr << "Faltan argumentos, formato <nombre BBDD> <usuario> "
                 "<contraseña> <IP servidor = 127.0.0.1> <puerto = 5432>"
              << std::endl;
    return EXIT_FAILURE;
  }

  nombreBBDD = argv[1];
  usuario = argv[2];
  contrasena = argv[3];
  if (argc > 4) ip = argv[4];
  if (argc > 5) puerto = argv[5];
  char configConexion[256];

  sprintf(configConexion, "dbname=%s user=%s password=%s hostaddr=%s port=%s",
          nombreBBDD.c_str(), usuario.c_str(), contrasena.c_str(), ip.c_str(),
          puerto.c_str());

  bigInt rutInicio = 14575191, rutTermino = 19843284;
  llenarBaseDatos(rutInicio, rutTermino, configConexion);
  participante();

  return EXIT_SUCCESS;
}

void llenarBaseDatos(bigInt rutInicio, bigInt rutTermino,
                     const std::string &configuracion) {
  pqxx::connection conexion(configuracion);
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
