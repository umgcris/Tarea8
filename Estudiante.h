#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
#include "Persona.h"
#include <mysql.h>

using namespace std;

class Estudiante : Persona {
private:
    string codigo;
    int id_estudiante = 0;

    
    string limpiarDato(string dato) {
        string resultado = "";
        for (char c : dato) {
            if (c == '\'' || c == ';' || c == '--' || c == '\\') continue;
            resultado += c;
        }
        return resultado;
    }

public:
    Estudiante() {}
    Estudiante(string nom, string ape, string dir, string fn, int tel, int id_ts, string cod, int id_e)
        : Persona(nom, ape, dir, tel, fn, id_ts) {
        codigo = cod;
        id_estudiante = id_e;
    }

    
    void setCodigo(string cod) { codigo = limpiarDato(cod); }
    void setIdEstudiante(int id_e) { id_estudiante = id_e; }
    void setNombres(string nom) { nombres = limpiarDato(nom); }
    void setApellidos(string ape) { apellidos = limpiarDato(ape); }
    void setDireccion(string dir) { direccion = limpiarDato(dir); }
    void setTelefono(int tel) { telefono = tel; }
    void setFechaNacimiento(string fn) { fecha_nacimiento = fn; }
    void setIdTipoSangre(int id_ts) { id_tipo_sangre = id_ts; }

    void crear() {
        int q_estado = 0;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string t = to_string(telefono);
            string id_ts = to_string(id_tipo_sangre);

            
            string check = "SELECT codigo FROM estudiantes WHERE codigo = '" + codigo + "'";
            mysql_query(cn.getConector(), check.c_str());
            MYSQL_RES* res = mysql_store_result(cn.getConector());
            if (mysql_num_rows(res) > 0) {
                cout << "Error: El codigo " << codigo << " ya existe en la base de datos." << endl;
                mysql_free_result(res);
            }
            else {
                mysql_free_result(res);
                string consulta = "INSERT INTO estudiantes(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES ('" + codigo + "', '" + nombres + "', '" + apellidos + "', '" + direccion + "', " + t + ", '" + fecha_nacimiento + "', " + id_ts + ");";
                q_estado = mysql_query(cn.getConector(), consulta.c_str());
                if (!q_estado) cout << "Ingreso de datos Exitoso..." << endl;
                else cout << "Error al insertar: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD conexion;
        conexion.abrir_conexion();
        MYSQL* conn = conexion.getConector();
        if (conn) {
            string query = "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, e.telefono, e.fecha_nacimiento, ts.sangre FROM estudiantes AS e INNER JOIN tipo_sangre AS ts ON e.id_tipo_sangre = ts.id_tipo_sangre;";
            mysql_query(conn, query.c_str());
            MYSQL_RES* res = mysql_store_result(conn);
            cout << "--- LISTADO DE ESTUDIANTES ---" << endl;
            while (MYSQL_ROW row = mysql_fetch_row(res)) {
                cout << row[0] << " | " << row[1] << " | " << row[2] << " " << row[3] << " | " << row[4] << " | " << row[7] << endl;
            }
            mysql_free_result(res);
        }
        conexion.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id_e = to_string(id_estudiante);
            string consulta = "UPDATE estudiantes SET codigo = '" + codigo + "', nombres = '" + nombres + "', apellidos = '" + apellidos + "', direccion = '" + direccion + "', telefono = " + to_string(telefono) + ", fecha_nacimiento = '" + fecha_nacimiento + "', id_tipo_sangre = " + to_string(id_tipo_sangre) + " WHERE id_estudiante = " + id_e;
            if (!mysql_query(cn.getConector(), consulta.c_str())) cout << "Modificacion Exitosa." << endl;
            else cout << "Error: " << mysql_error(cn.getConector()) << endl;
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "DELETE FROM estudiantes WHERE id_estudiante = " + to_string(id_estudiante);
            if (!mysql_query(cn.getConector(), consulta.c_str())) cout << "Registro eliminado." << endl;
            else cout << "Error al eliminar." << endl;
        }
        cn.cerrar_conexion();
    }
    bool existeTipoSangre(int id) {
        bool existe = false;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "SELECT id_tipo_sangre FROM tipo_sangre WHERE id_tipo_sangre = " + to_string(id);
            const char* c = consulta.c_str();
            mysql_query(cn.getConector(), c);

            MYSQL_RES* res = mysql_store_result(cn.getConector());
            if (mysql_num_rows(res) > 0) {
                existe = true;
            }
            mysql_free_result(res);
        }
        cn.cerrar_conexion();
        return existe;
    }
};  