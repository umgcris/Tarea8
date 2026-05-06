#include <iostream>
#include <string>
#include <regex>
#include "Estudiante.h"

using namespace std;

// Prototipos de funciones de validación para mantener el main limpio
void menu();
bool validarCodigo(string c);
bool validarSoloLetras(string t);
bool validarTelefono(string t);
bool validarFecha(string f);

int main() {
    int opcion;
    char continuar;
    Estudiante e; // Objeto base

    do {
        system("cls"); // Limpia la pantalla en Windows
        cout << "************** MENU PRINCIPAL - DB_ESCUELA **************" << endl;
        cout << "1. Crear Registro (Insertar)" << endl;
        cout << "2. Leer Registros (Consultar)" << endl;
        cout << "3. Actualizar Registro (Modificar)" << endl;
        cout << "4. Eliminar Registro (Borrar)" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        string codigo, nombres, apellidos, direccion, fecha_nacimiento, input_sangre;
        int telefono, id_tipo_sangre, id_estudiante;

        switch (opcion) {
        case 1: { // CREAR
            cout << "\n--- Ingreso de Nuevo Estudiante ---" << endl;
            do {
                cout << "Codigo (E001): "; cin >> codigo;
            } while (!validarCodigo(codigo));
            cin.ignore();

            do {
                cout << "Nombres: "; getline(cin, nombres);
            } while (!validarSoloLetras(nombres));

            do {
                cout << "Apellidos: "; getline(cin, apellidos);
            } while (!validarSoloLetras(apellidos));

            cout << "Direccion: "; getline(cin, direccion);

            string tel_in;
            do {
                cout << "Telefono (8 digitos): "; cin >> tel_in;
            } while (!validarTelefono(tel_in));
            telefono = stoi(tel_in);

            do {
                cout << "Fecha Nacimiento (AAAA-MM-DD): "; cin >> fecha_nacimiento;
            } while (!validarFecha(fecha_nacimiento));

            bool sangre_ok = false;
            do {
                cout << "ID Tipo Sangre: "; cin >> input_sangre;
                if (regex_match(input_sangre, regex("[0-9]+"))) {
                    id_tipo_sangre = stoi(input_sangre);
                    if (e.existeTipoSangre(id_tipo_sangre)) sangre_ok = true;
                    else cout << "Error: ID de sangre inexistente." << endl;
                }
            } while (!sangre_ok);

            e = Estudiante(nombres, apellidos, direccion, fecha_nacimiento, telefono, id_tipo_sangre, codigo, 0);
            e.crear();
            break;
        }
        case 2: // LEER
            e.leer();
            break;
        case 3: // ACTUALIZAR
            e.leer();
            cout << "\nIngrese el ID del estudiante a modificar: ";
            cin >> id_estudiante;
            // Aquí repetirías el bloque de ingresos validado para actualizar
            e.setIdEstudiante(id_estudiante);
            // (Setters con datos nuevos...)
            e.actualizar();
            break;
        case 4: // ELIMINAR
            e.leer();
            cout << "\nIngrese el ID del estudiante a eliminar: ";
            cin >> id_estudiante;
            e.setIdEstudiante(id_estudiante);
            e.borrar();
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            return 0;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }

        cout << "\n¿Desea realizar otra operacion? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    return 0;
}

// --- Implementación de Validaciones ---
bool validarCodigo(string c) { return regex_match(c, regex("E[0-9]{3}")); }
bool validarSoloLetras(string t) { return regex_match(t, regex("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$")); }
bool validarTelefono(string t) { return regex_match(t, regex("[0-9]{8}")); }
bool validarFecha(string f) { return regex_match(f, regex("[0-9]{4}-[0-9]{2}-[0-9]{2}")); }