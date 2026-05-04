#include <fstream>

#include "funciones.h"

#include <cstring>
#include <iostream>

#include "enum.h"

using namespace std;

void cargarDatos(void*& clinica,
                 const char* archivoPacientes,
                 const char* archivoDoctores,
                 const char* archivoCitas,
                 const char* archivoCancelaciones) {
        // crear los arreglos donde guardaremos pacientes y doctores
        void *pacientes;
        void *doctores;

        // usar la misma funcion para cargar pacientes y doctores
        // cargar pacientes
        cargarRegistros(archivoPacientes, pacientes, leerPaciente);
        // void **arregloPacientes = (void**)pacientes;
        // for (int i=0; arregloPacientes[i]; i++) {
        //     void **regPac = (void**)arregloPacientes[i];
        //     int dni = *(int*)regPac[0];
        //     char *nombre = (char*)regPac[1];
        //     cout<<nombre<<endl;
        // }

        //cargar doctores
        cargarRegistros(archivoDoctores, doctores, leerDoctores);
        // void **arregloDoctores = (void**)doctores;
        // for (int i=0; arregloDoctores[i]; i++) {
        //     void **regDoc = (void**)arregloDoctores[i];
        //     int dni = *(int*)regDoc[0];
        //     char *nombre = (char*)regDoc[1];
        //     cout<<dni<<endl;
        // }

        // Reservar espacio en la memoria para clinica y colocar los pacientes y doctores
        clinica = new void *[cliNumCampos]{};
        void**regClinica = (void**)clinica;
        regClinica[cliPacientes] = pacientes;
        regClinica[cliDoctores] = doctores;

        // Asignar los eventos a sus respectivos duenos
        cargarEventos(archivoCitas, clinica, pacCitas, leerCita, liberarCita);
        // void **arregloPacientes = (void**)pacientes;
        // for (int i=0; arregloPacientes[i]; i++) {
        //     void **regPac = (void**)arregloPacientes[i];
        //     void **citas = (void**)regPac[4];
        //     if (citas != nullptr) {
        //         for (int j=0; citas[j]; j++) {
        //             void **regCita = (void**)citas[j];
        //             int fecha = *(int*)regCita[citaFecha];
        //             int dniDoctor = *(int*)regCita[citaDniDoctor];
        //             cout<<dniDoctor<<endl;
        //         }
        //     }
        // }

        cargarEventos(archivoCancelaciones, clinica, pacCancelaciones, leerCancelacion, liberarCancelacion);

}

void cargarRegistros(const char*archivoPacientes, void*&datos, bool (*leerRegistro)(ifstream&, void*&)) {
    // esta funcion va a leer cada linea del archivo

    ifstream archivo(archivoPacientes, ios::in);
    void **registros = nullptr;// crear un arreglo de punteros generico inicializdo en nullptr
    int num=0, capacidad=0; // para la cantidad datos y la capacidad actual
    void *dato; // lo usaremos para leer cada linea
    while (leerRegistro(archivo, dato)) {
        if (num==capacidad) {
            incrementarCapacidad(registros, num, capacidad);
        }
        registros[num] = dato;
        num++;
    }
    if (registros == nullptr) {
        registros = new void *[1]{};
    }
    else registros[num] = nullptr;
    datos=registros;
}

void incrementarCapacidad(void**&registros, int num, int&capacidad) {
    capacidad+=5;
    if (registros == nullptr) {
        registros = new void *[capacidad+1]{};
    }
    else {
        void **aux =  new void *[capacidad+1]{};
        for (int i=0; i<num; i++) {
            aux[i] = registros[i];
        }
        delete [] registros;
        registros = aux;
    }
}

bool leerPaciente(ifstream&archivo, void*&paciente) {
    // 10000001,Juan Perez,30,M
    int dni, edad;
    char *nombre, genero, car;

    if (archivo.eof()) return false;
    archivo>>dni>>car;
    nombre = leerCadenaDelim(archivo, ',');
    archivo>>edad>>car>>genero;
    archivo.get();

    void **reg = new void *[pacNumCampos]{};
    reg[pacDni] = new int{dni};
    reg[pacNombre] = nombre;
    reg[pacEdad] = new int{edad};
    reg[pacGenero] = new char{genero};
    reg[pacCitas] = nullptr;
    reg[pacCancelaciones] = nullptr;

    paciente = reg;
    return true;
}

bool leerDoctores(ifstream&archivo, void*&doctores) {
    // 20000001,Miguel Garcia,0
    int dni, especialidad;
    char *nombre, car;
    if (archivo.eof()) return false;
    archivo>>dni>>car;
    nombre = leerCadenaDelim(archivo, ',');
    archivo>>especialidad;
    archivo.get();

    void **reg = new void *[docNumCampos]{};
    reg[docDni] = new int{dni};
    reg[docNombre] = nombre;
    reg[docEspecialidad] = new int{especialidad};

    doctores = reg;
    return true;
}


char *leerCadenaDelim(ifstream&archivo, char delim) {
    char *ptrCadena, aux[100];
    archivo.getline(aux, 100, delim);
    ptrCadena = new char[strlen(aux)+1];
    strcpy(ptrCadena, aux);
    return ptrCadena;
}


void cargarEventos(const char*nombreArchivo, void*&clinica, int pos, bool(*leerEvento)(ifstream&, void*&, int&),
    void (*liberarEventoNoAsociado)(void*&)) {
    ifstream archivo(nombreArchivo, ios::in);

    // Extrae el arreglo de pacientes de clinica (índice 0).
    void **arrClinica = (void**)clinica;
    void *pacientes = arrClinica[cliPacientes];

    // Bucle while que invoca a leerEvento.
    void *dato; // para guardar lo que se lee en cada linea del archivo
    int dniPaciente; // para guardar el dni de cada paciente leido en el archivo
    while (leerEvento(archivo, dato, dniPaciente)) { // esta funcion lee cada linea y lee dni
        // Busca al paciente por el DNI retornado.
        void **paciente = (void**)buscarPaciente(dniPaciente, pacientes);
        if (paciente !=nullptr) {
            void** eventosPaciente = (void**)paciente[pos]; // accedemos a los eventos del paciente, 4(citas) o 5(cancelaciones)
            agregarRegistroExacto(eventosPaciente, dato); // incrementamos el tamano del registro y guardamos el dato
            paciente[pos] = eventosPaciente; // cargamos a pacientes los eventos modificados
        }
        else {
            liberarEventoNoAsociado(dato); // el paciente no existe, liberamos la memoria creada al leer la linea
        }
    }
}

void * buscarPaciente(int dniPaciente, void*pacientes) {
    void **arrPacientes = (void**)pacientes;
    for (int i=0; arrPacientes[i]; i++) {
        void **paciente = (void**)arrPacientes[i];
        int dniGuarado = *(int*)(paciente[pacDni]);
        if (dniGuarado == dniPaciente) {
            return arrPacientes[i];
        }
    }
    return nullptr;
}

void agregarRegistroExacto(void**&eventosPaciente, void*dato) {
    // determinamos la cantidad de elementos
    int num=0;
    if (eventosPaciente != nullptr) {
        while (eventosPaciente[num]) {
            num++;
        }
    }

    void **aux = new void *[num+2]{};
    for (int i=0; i<num; i++) {
        aux[i] = eventosPaciente[i];
    }
    aux[num] = dato;
    aux[num+1] = nullptr;
    delete [] eventosPaciente;
    eventosPaciente = aux;
}

bool leerCita(ifstream&archivo, void*&cita, int&dniPaciente) {
    // 2026-02-01,08:00,10000001,20000001,0
    int anho;
    if (!(archivo >> anho)) return false;

    archivo.ignore();
    int mes, dia;
    archivo >> mes;
    archivo.ignore();
    archivo >> dia;
    int fecha = anho * 10000 + mes * 100 + dia;

    archivo.ignore();
    int hora, minuto;
    archivo >> hora;
    archivo.ignore();
    archivo >> minuto;
    int horaCompleta = hora * 100 + minuto;

    archivo.ignore();
    int dniDoctor;
    archivo >> dniPaciente;
    archivo.ignore();
    archivo >> dniDoctor;
    archivo.ignore();

    int estado;
    archivo >> estado;
    if (archivo.peek() == '\n') archivo.get();

    void **reg = new void *[citaNumCampos]{};
    reg[citaFecha] = new int(fecha);
    reg[citaHora] = new int(horaCompleta);
    reg[citaDniDoctor] = new int(dniDoctor);
    reg[citaEstado] = new int(estado);

    cita = reg;
    return true;
}

void liberarCita(void*&cita) {
    void **regCita = (void**)cita;
    delete (int*)regCita[citaFecha];
    delete (int*)regCita[citaHora];
    delete (int*)regCita[citaDniDoctor];
    delete (int*)regCita[citaEstado];
    delete[]regCita;
}

bool leerCancelacion(ifstream&archivo, void*&cancelacion, int&dniPaciente) {
    int anho;
    if (!(archivo >> anho)) return false;

    archivo.ignore();
    int mes, dia;
    archivo >> mes;
    archivo.ignore();
    archivo >> dia;
    int fecha = anho * 10000 + mes * 100 + dia;

    archivo.ignore();
    int hora, minuto;
    archivo >> hora;
    archivo.ignore();
    archivo >> minuto;
    int horaCompleta = hora * 100 + minuto;

    archivo.ignore();
    int dniDoctor;
    archivo >> dniPaciente;
    archivo.ignore();
    archivo >> dniDoctor;
    if (archivo.peek() == '\n') archivo.get();

    void** reg = new void*[canNumCampos];
    reg[canFecha] = new int(fecha);
    reg[canHora] = new int(horaCompleta);
    reg[canDniPaciente] = new int(dniPaciente);
    reg[canDniDoctor] = new int(dniDoctor);

    cancelacion = reg;
    return true;
}

void liberarCancelacion(void*&cancelacion) {
    void **regCancel= (void**)cancelacion;
    delete (int*)regCancel[citaFecha];
    delete (int*)regCancel[citaHora];
    delete (int*)regCancel[citaDniDoctor];
    delete (int*)regCancel[citaEstado];
    delete[]regCancel;
}

void cancelarCitas(void*&clinica) {
    void** regClinica = (void**)clinica;
    void** regPacientes = (void**)regClinica[cliPacientes];

    if (regPacientes == nullptr) return;
    for (int i = 0; regPacientes[i]; i++) {
        void** paciente = (void**)regPacientes[i];
        procesarCancelacionesPaciente(paciente);
    }
}

void procesarCancelacionesPaciente(void**paciente) {
    void** cancelaciones = (void**)paciente[pacCancelaciones];
    if (cancelaciones == nullptr) return;
    for (int i = 0; cancelaciones[i]; i++) {
        aplicarCancelacionPaciente(paciente, cancelaciones[i]);
    }
}

void aplicarCancelacionPaciente(void**paciente, void*cancelacion) {
    void **regCancelacion = (void**)cancelacion;

    int fecha = *(int*)regCancelacion[canFecha];
    int hora = *(int*)regCancelacion[canHora];
    int dniCanPaciente = *(int*)regCancelacion[canDniPaciente];
    int dniDoctor = *(int*)regCancelacion[canDniDoctor];

    int dniPaciente = *(int*)paciente[pacDni];
    if (dniCanPaciente != dniPaciente) return;

    void* cita = buscarCitaPaciente(paciente, fecha, hora, dniDoctor);
    if (cita != nullptr) {
        cancelarCita(cita);
    }
}

void* buscarCitaPaciente(void** paciente, int fecha, int hora, int dniDoctor) {
    void** citas = (void**)paciente[pacCitas];
    if (citas == nullptr) return nullptr;

    for (int i = 0; citas[i]; i++) {
        void* cita = citas[i];
        if (esMismaCita(cita, fecha, hora, dniDoctor)) {
            return cita;
        }
    }

    return nullptr;
}

bool esMismaCita(const void* cita, int fecha, int hora, int dniDoctor) {
    const void** regCita = (const void**)cita;
    int fechaCita = *(int*)regCita[citaFecha];
    int horaCita = *(int*)regCita[citaHora];
    int doctorCita = *(int*)regCita[citaDniDoctor];

    return fechaCita == fecha && horaCita == hora && doctorCita == dniDoctor;
}

void cancelarCita(void*& cita) {
    void** regCita = (void**)cita;
    int* estado = (int*)regCita[citaEstado];
    *estado = 0;
}

void imprimirReporte(ofstream& archivo, const void* clinica) {
    const void** regClinica = (const void**)clinica;
    const void** regPacientes = (const void**)regClinica[cliPacientes];
    const void* doctores = regClinica[cliDoctores];
    if (regPacientes == nullptr) return;

    for (int i = 0; regPacientes[i]; i++) {
        imprimirCitasPaciente(archivo, regPacientes[i], doctores);
    }
}

void imprimirCitasPaciente(ofstream& archivo, const void* paciente, const void* doctores) {
    const void** citas = (const void**)((const void**)paciente)[pacCitas];
    if (citas == nullptr) return;

    for (int i = 0; citas[i]; i++) {
        imprimirDetalleCita(archivo, paciente, citas[i]);

        int dniDoctor = *(int*)((const void**)citas[i])[citaDniDoctor];
        const void* doctor = buscarDoctor(dniDoctor, doctores);
        imprimirDoctor(archivo, doctor);

        archivo << "------------------------------" << endl;
        archivo << "==============================" << endl << endl;
    }
}

void* buscarDoctor(int dniDoctor, const void* doctores) {
    const void** regDoctores = (const void**)doctores;
    if (regDoctores == nullptr) return nullptr;

    for (int i = 0; regDoctores[i]; i++) {
        void** doctor = (void**)regDoctores[i];
        int dni = *(int*)doctor[docDni];
        if (dni == dniDoctor) return doctor;
    }

    return nullptr;
}
void imprimirDetalleCita(ofstream& archivo, const void* paciente, const void* cita) {
    const void** regCita = (const void**)cita;
    int fecha = *(int*)regCita[citaFecha];
    int hora = *(int*)regCita[citaHora];
    int estado = *(int*)regCita[citaEstado];

    imprimirCita(archivo, fecha, hora, estado);
    imprimirPaciente(archivo, paciente);
}

void imprimirCita(ofstream& archivo, int fecha, int hora, int estado) {
    archivo << "==============================" << endl;
    archivo << "DATOS DEL CITA" << endl;
    archivo << "------------------------------" << endl;
    imprimirFecha(archivo, fecha);
    imprimirHora(archivo, hora);
    imprimirEstado(archivo, estado);
    archivo << endl;
    archivo << "------------------------------" << endl;
    archivo << "DATOS DEL PACIENTE" << endl;
    archivo << "------------------------------" << endl;
}

void imprimirPaciente(ofstream& archivo, const void* paciente) {
    if (paciente != nullptr) {
        const void** regPaciente = (const void**)paciente;
        int dni = *(int*)regPaciente[pacDni];
        const char* nombre = (const char*)regPaciente[pacNombre];
        int edad = *(int*)regPaciente[pacEdad];
        char genero = *(char*)regPaciente[pacGenero];

        archivo << "DNI: " << dni << endl;
        archivo << "Nombre: " << nombre << endl;
        archivo << "Edad: " << edad << endl;
        archivo << "Genero: " << genero << endl;
    }

    archivo << "------------------------------" << endl;
    archivo << "DATOS DEL DOCTOR" << endl;
    archivo << "------------------------------" << endl;
}

void imprimirDoctor(ofstream& archivo, const void* doctor) {
    if (doctor != nullptr) {
        const void** regDoctor = (const void**)doctor;
        int dni = *(int*)regDoctor[docDni];
        const char* nombre = (const char*)regDoctor[docNombre];
        int especialidad = *(int*)regDoctor[docEspecialidad];

        archivo << "DNI: " << dni << endl;
        archivo << "Nombre: " << nombre << endl;
        imprimirEspecialidad(archivo, especialidad);
    }
}

void imprimirFecha(ostream& os, int fecha) {
    int anho = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;

    os << "Fecha: " << anho << "-";
    if (mes < 10) os << "0";
    os << mes << "-";
    if (dia < 10) os << "0";
    os << dia << endl;
}

void imprimirHora(ostream& os, int hora) {
    int horas = hora / 100;
    int minutos = hora % 100;

    os << "Hora: ";
    if (horas < 10) os << "0";
    os << horas << ":";
    if (minutos < 10) os << "0";
    os << minutos << endl;
}

void imprimirEstado(ostream& os, int estado) {
    if (estado == 1) {
        os << "Estado: RESERVADA" << endl;
    }
    else if (estado == 0) {
        os << "Estado: CANCELADA" << endl;
    }
    else {
        os << "Estado: NA" << endl;
    }
}

void imprimirEspecialidad(ostream& os, int especialidad) {
    switch (especialidad) {
        case 0: os << "Especialidad: CARDIOLOGIA" << endl; break;
        case 1: os << "Especialidad: DERMATOLOGIA" << endl; break;
        case 2: os << "Especialidad: NEUROLOGIA" << endl; break;
        case 3: os << "Especialidad: PEDIATRIA" << endl; break;
        case 4: os << "Especialidad: PSIQUIATRIA" << endl; break;
        case 5: os << "Especialidad: TRAUMATOLOGIA" << endl; break;
        case 6: os << "Especialidad: ENDOCRINOLOGIA" << endl; break;
        case 7: os << "Especialidad: GINECOLOGIA" << endl; break;
        case 8: os << "Especialidad: PSICOLOGIA" << endl; break;
        case 9: os << "Especialidad: ORTOPEDIA" << endl; break;
        default: os << "Especialidad: GENERAL" << endl; break;
    }
}