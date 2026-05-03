#include "funciones.h"

void cargarDatos(void*&clinica,const char*nombArchPaci,const char*nombArchDoct,const char*nombArchCitas,
                 const char*nombArchCancela) {

    // cargamos pacientes y doctores
    void* pacientes;
    void* doctores;

    cargarPacientes(nombArchPaci, pacientes);
    // void** arregloPacientes = (void**)pacientes; // quitamos el camuflaje
    // for (int i=0; arregloPacientes[i]!=nullptr; i++) {
    //     void **pacienteActual = (void**)arregloPacientes[i]; // accedemos al archivador del paciente
    //     int dni = *(int*)(pacienteActual[0]);
    //     char *nombre = (char*)(pacienteActual[1]);
    //     int edad = *(int*)(pacienteActual[2]);
    //     char sexo = *(char*)(pacienteActual[3]);
    //     cout<<sexo<<endl;
    // }

    cargarDoctores(nombArchDoct, doctores);
    // void **arregloDoctores = (void**)doctores;
    // for (int i=0; arregloDoctores[i]!=nullptr; i++) {
    //     void **doctorActual = (void**)arregloDoctores[i];
    //     int dni = *(int*)(doctorActual[0]);
    //     cout<<dni<<endl;
    // }

    // cargamos pacientes y doctores a clinica
    clinica = new void*[2]{};
    void **regClinica = (void**)clinica;
    regClinica[0] = pacientes;
    regClinica[1] = doctores;

    // cargamos citas
    cargarCitas(nombArchCitas, clinica);
    void** arregloPacientes = (void**)pacientes; // quitamos el camuflaje
    for (int i=0; arregloPacientes[i]!=nullptr; i++) {
        void **pacienteActual = (void**)arregloPacientes[i]; // accedemos al archivador del paciente
        // int dni = *(int*)(pacienteActual[0]);
        // char *nombre = (char*)(pacienteActual[1]);
        // int edad = *(int*)(pacienteActual[2]);
        // char sexo = *(char*)(pacienteActual[3]);
        void **citasPaciente = (void**)pacienteActual[4];

        if (citasPaciente==nullptr) {
            cout<<"No tiene citas"<<endl;
        }
        else {
            for (int j=0; citasPaciente[j]!=nullptr; j++) {
                void **citaActual = (void**)citasPaciente[j];
                int fecha = *(int*)(citaActual[0]);
                int hora = *(int*)(citaActual[1]);
                int dniDoc = *(int*)(citaActual[2]);
                int estado = *(int*)(citaActual[3]);

                cout<< "Doc DNI: " << dniDoc<<endl;
            }
        }
    }



    //cargarCancelaciones(archivoCancelaciones, clinica);

}


void cargarDoctores(const char*nombArchDoct, void*&doctores) {
    ifstream archDocs(nombArchDoct, ios::in);
    void **registros=nullptr;
    int num=0, capacidad=0;
    void *doctor;

    while (leerDoctor(archDocs, doctor)) {
        if (num==capacidad) {
            incrementarCapacidad(registros, num, capacidad);
        }
        registros[num]=doctor;
        num++;
    }
    if (registros==nullptr) registros=new void*[1]{};
    else registros[num]=nullptr;
    doctores=registros;
}

void cargarPacientes(const char*nombArchPaci, void*&pacientes) {
    ifstream archPacientes(nombArchPaci);
    if (!archPacientes.is_open()) cout<<"no se abrio el archivo"<<endl;
    void **registros=nullptr;
    int num=0, capacidad=0;

    void *paciente;
    while (leerPaciente(archPacientes,paciente)) { // ahora podemos leer toda la info de pacientes de una
        if (num==capacidad) {
            incrementarCapacidad(registros, num, capacidad);
        }
        registros[num]=paciente;
        num++;
    }
    // si el archivo estuvo vacio, registros[0] apuntaria a una direccion nula, esto haria que explote
    if (registros==nullptr) {
        registros=new void*[1]{};
    }
    // si no esta vacio, cargamos pacientes
    else {
        registros[num]=nullptr;
    }
    pacientes=registros; // hacemos que el puntero simple apunte al doble
}

void incrementarCapacidad(void**&registros, int num, int&capacidad) {
    capacidad+=5;
    if (registros==nullptr) {
        registros=new void*[capacidad+1]{};
    }
    else {
        void** aux = new void*[capacidad+1]{};
        for (int i=0; i<num; i++) {
            aux[i]=registros[i];
        }
        delete[] registros;
        registros=aux;
    }
}

bool leerPaciente(ifstream&archPacientes,void*&paciente) {
// 10000001,Juan Perez,30,M
    int dni, edad;
    char *nombre, sexo;

    if (!(archPacientes>>dni)) return false;
    archPacientes.get();
    nombre=leerCadenaDelim(archPacientes,',');
    archPacientes>>edad;
    archPacientes.get();
    archPacientes>>sexo;
    archPacientes.get();

    void **reg = new void*[6]; // para poder acceder a las cajas

    reg[0] = new int{dni};
    reg[1] = nombre; // nombre ya es un puntero
    reg[2] = new int{edad};
    reg[3] = new char{sexo};
    reg[4] = nullptr; // para citas
    reg[5] = nullptr; // para cancelaciones

    paciente=reg;
    return true;
}

bool leerDoctor(ifstream&archDocs, void*&doctor) {
    // 20000001,Miguel Garcia,0
    int dni, codEspecialidad;
    char *nombre;
    if (!(archDocs>>dni)) return false;
    archDocs.get();
    nombre=leerCadenaDelim(archDocs, ',');
    archDocs>>codEspecialidad;
    archDocs.get();

    void **reg = new void*[3];
    reg[0] = new int{dni};
    reg[1] = nombre;
    reg[2] = new int{codEspecialidad};

    doctor=reg;
    return true;
}

char *leerCadenaDelim(ifstream& archPacientes,char delim) {
    char ptrAux[100];
    char *ptrCadena;
    archPacientes.getline(ptrAux, 100, delim);
    ptrCadena = new char[strlen(ptrAux)+1];
    strcpy(ptrCadena,ptrAux);
    return ptrCadena;
}

// empezamos a cruzar datos
void cargarCitas(const char*nombArchCitas,void*clinica) {//solo por valor porque el espacio de clinica ya se esta definido
    ifstream archCitas(nombArchCitas, ios::in);

    // desempaquetamos clinica y accedemos a pacientes
    void **regClinica=(void**)clinica;
    void *pacientes = regClinica[0];

    void *cita; // para guardar la cita leida
    int dniPaciente; // para guardar el dni del paciente leido en el archivo

    // mientras se pueda leer el archivo
    while (leerCita(archCitas, cita, dniPaciente)) {
        // buscar el paciente
        void **paciente = (void**)buscarPaciente(dniPaciente, pacientes);
        if (paciente != nullptr) { // si el paciente leido existe en el arreglo de pacientes
            void** citasPaciente = (void**)paciente[4]; // aqui cargaremos la cita
            agregarRegistroExacto(citasPaciente, cita); // metemos la cita en el historial del paciente
            paciente[4]=citasPaciente;
        }
        else { // si no existe, liberamos la memoria creada en leerCita
            void **regCita = (void**)cita;
            delete (int*)regCita[0];
            delete (int*)regCita[1];
            delete (int*)regCita[2];
            delete (int*)regCita[3];
            delete[]regCita;
        }
    }
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

    void** reg = new void*[4];
    reg[0] = new int(fecha);
    reg[1] = new int(horaCompleta);
    reg[2] = new int(dniDoctor);
    reg[3] = new int(estado);

    cita = reg;
    return true;
}

void *buscarPaciente(int dniPaciente, const void*pacientes) {
    const void** regPacientes = (const void**)pacientes;
    if (regPacientes == nullptr) return nullptr;

    for (int i=0; regPacientes[i]; i++) {
        void** paciente = (void**)regPacientes[i];
        int dni = *(int*)paciente[0];
        if (dni == dniPaciente) return paciente;
    }
    return nullptr;
}

void agregarRegistroExacto(void**&registros, void*registro) {
    int num=0;
    // determinamos la cantidad de registros
    if (registros != nullptr) {
        while (registros[num] != nullptr) num++;
    }
    // creamos un auxiliar
    void **aux =new void*[num+2]{}; // 2 porque anadiremos el registro y un nullptr al final
    for (int i=0; i<num; i++) {
        aux[i] = registros[i];
    }
    aux[num] = registro;
    aux[num+1] = nullptr;

    delete[]registros;
    registros = aux;
}