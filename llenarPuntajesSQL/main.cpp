#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <pqxx/pqxx>

typedef unsigned int Rut;
typedef std::array<std::string, 7> tupla;

size_t numeroAleatorio() { return 750 - (rand() % 276); }
void llenarBaseDatos(Rut, Rut, const std::string &);
void llenarFila(Rut, pqxx::stream_to &);
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

  Rut rutInicio = 14575191, rutTermino = 19843284;

  try {
    llenarBaseDatos(rutInicio, rutTermino, configConexion);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  participante();

  return EXIT_SUCCESS;
}

void llenarBaseDatos(Rut rutInicio, Rut rutTermino,
                     const std::string &configuracion) {
  pqxx::connection conexion(configuracion);
  pqxx::work transaccion(conexion);
  std::string tablaObjetivo("puntajes");

  tupla columnas{"rut",      "nem",      "ranking", "matematica",
                 "lenguaje", "ciencias", "historia"};

  pqxx::stream_to streamLlenado(transaccion, tablaObjetivo, columnas);
  srand(time(NULL));

  for (Rut rut = rutInicio; rut <= rutTermino; rut++) {
    llenarFila(rut, streamLlenado);
  }
  streamLlenado.complete();
  transaccion.commit();
}

void llenarFila(Rut rut, pqxx::stream_to &streamLlenado) {
  auto nem = std::to_string(numeroAleatorio());
  auto ranking = std::to_string(numeroAleatorio());
  auto matematica = std::to_string(numeroAleatorio());
  auto lenguaje = std::to_string(numeroAleatorio());
  auto ciencias = std::to_string(numeroAleatorio());
  auto historia = std::to_string(numeroAleatorio());
  streamLlenado << tupla{std::to_string(rut),
                         nem,
                         ranking,
                         matematica,
                         lenguaje,
                         ciencias,
                         historia};
}

void participante() {
  std::cout << std::endl << "=== Tarea ===" << std::endl;
  std::cout << std::endl << "Sebastián Pérez Berrios" << std::endl;
  std::cout << std::endl << "subida de puntajes a PostgreSQL" << std::endl;
}
