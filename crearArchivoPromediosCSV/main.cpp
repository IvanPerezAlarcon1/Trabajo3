#include <stdio.h>

#include <fstream>
#include <iostream>
#include <pqxx/pqxx>

typedef unsigned int Rut;

void leerBaseDatos(const std::string &, std::ostream &);
void escribirArchivo(pqxx::icursorstream &, std::ostream &);
void participante();

int main(int argc, char **argv) {
  std::string nombreBBDD;
  std::string usuario;
  std::string contrasena;
  std::string ip("127.0.0.1");
  std::string puerto("5432");
  std::ofstream archivoSalida("puntajesPromedio-SQL.csv");

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

  try {
    leerBaseDatos(configConexion, archivoSalida);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  participante();
  return EXIT_SUCCESS;
}

void leerBaseDatos(const std::string &configuracion, std::ostream &salida) {
  pqxx::connection conexion(configuracion);
  pqxx::work transaccion(conexion);
  std::string query =
      "SELECT rut, ROUND(((nem + ranking + matematica + lenguaje + ciencias + "
      "historia ) / 6.0),2) as promedio "
      "FROM puntajes";
  size_t particion = 100000;
  pqxx::icursorstream streamLectura(transaccion, query, "Promedios", particion);

  escribirArchivo(streamLectura, salida);

  transaccion.commit();
}

void escribirArchivo(pqxx::icursorstream &streamLectura, std::ostream &salida) {
  for (auto iterador = pqxx::icursor_iterator(streamLectura);
       iterador != pqxx::icursor_iterator(); iterador++) {
    for (const auto &registro : *iterador) {
      salida << registro[0].c_str() << ';' << registro[1].c_str() << '\n';
    }
  }
}

void participante() {
  std::cout << std::endl << "=== Tarea ===" << std::endl;
  std::cout << std::endl << "Sebastián Pérez Berrios" << std::endl;
  std::cout << std::endl
            << "escritura de promedios a archivo desde PostgreSQL" << std::endl;
}
