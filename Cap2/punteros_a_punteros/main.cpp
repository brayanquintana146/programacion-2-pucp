#include <iostream>
#include "funciones.h"

int main() {
    int** pacientes;
    char** nombresPacientes;
    int** doctores;
    char** nombresDoctores;
    int ***citas;
    int ***cancelaciones;


    cargarPacientes("DatosEntrada/pacientes.csv", pacientes, nombresPacientes);
    cargarDoctores("DatosEntrada/doctores.csv", doctores, nombresDoctores);
    cargarCitas("DatosEntrada/citas.csv", citas);
    cargarCancelaciones("DatosEntrada/cancelaciones.csv", cancelaciones);
    cancelarCitas(cancelaciones, citas);

    for (int i = 0; citas[i]!=nullptr; i++) {
        int **cita = citas[i];
        int *fechaHora = cita[0];
        int *dniPacienteDoctor = cita[1];
        int *estado = cita[2];

        int fecha = fechaHora[0];
        int hora = fechaHora[1];
        int dniPaciente = dniPacienteDoctor[0];
        int dniDoctor = dniPacienteDoctor[1];
        int estadoPacienteDoc = estado[0];

        cout<<estadoPacienteDoc<<endl;
    }

    // for (int i = 0; cancelaciones[i]!=nullptr; i++) {
    //     int **cancelacion = cancelaciones[i];
    //     int *datosCancelacion = cancelacion[0];
    //     int fecha = datosCancelacion[0];
    //     int hora = datosCancelacion[1];
    //     int dniPaciente = datosCancelacion[2];
    //     int dniDoctor = datosCancelacion[3];
    //     cout<<fecha<<endl;
    // }
    return 0;
}
