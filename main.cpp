#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctime>
//DANIEL FELIPE ALZATE MATEUS.
//JUAN DAVID ROBLEDO GARZON.
using namespace std;

//ESTRUCTURAS
struct Fecha
{
    char dia[10];
    char mes[10];
    char anio[10];
};

struct Titulares
{
    char nombre[30];
    Fecha fechaNacimiento;
    char telFijo[30];
    char celular[30];
    char direccion[30];
};

struct Tipo
{
    char ahoOCor[30];
    int tarSob=0;
    int sobreGiroUsado=0;
};

struct Cuenta
{
    char estado[30];
    Fecha fechaCreacion;
    int numeroCuenta=0;
    int saldo=0;
    Tipo tipo;
    Titulares *titulares;
};

//PROTOTIPO DE LAS FUNCIONES NECESARIAS PARA EL PROGRAMA.
int contadorCuentas();
int contadorTitulares(int nCuenta);
void inicializar(Cuenta *p);
void crearAux();
void crearCuentasYTitulares(Cuenta *p);
bool consignarEnCuenta(Cuenta *p, int numC, int monto);
bool retirarDeCuenta(Cuenta *p, int numC, int monto);
void transferirCuentaACuenta(Cuenta *p, int numC, int numC2, int monto);
void mostrarTitulares(Cuenta *p);
void mostrarCuentasFecha(Cuenta *p);
void mostrarInformacionDeTodasCuentas(Cuenta *p);
int calcularEdad( int anioAct, int mesAct, int fechAct, int anioNac, int mesNac, int fechNac);

//MAIN DEL PROGRAMA.
int main()
{

    int opcion=0, numC=0, numC2=0, monto=0, cuent=0;
    Cuenta *p;

    //SE LEE Y MUESTRA EL ARCHIVO INICIAL CON EL QUE SE EMPEZARA A TRABAJAR
    cout<<"                      Maximo, cuantas cuentas adicionales quiere que tenga este programa: ";
    cin>>cuent;

    cout<<endl;
    cout<<"                     .:Este es el archivo inicial de las cuentas junto con sus titulares:."<<endl<<endl;
    crearAux();
    ofstream archivoSalida("auxiliar.txt", ios::out | ios::app);

    //SE INICIALIZAN LOS ARREGLOS DINAMICOS NECESARIOS PARA EL PROYECTO
    p = new Cuenta[contadorCuentas()+cuent];
    for(int i=0; i<=contadorCuentas()+cuent; i++)
    {
        (p+i)->titulares = new Titulares[5];
    }
    inicializar(p);

    //INICIO DEL SWITCH CASE DENTRO DE UN DO WHILE PARA REALIZAR EL MENU SOLICITADO.
    do
    {
        //MENU CON LAS OPCIONES SOLICITADAS PARA EL TALLER.
        cout<<"                           .:BIENVENIDO A JAVIBANK, EL BANCO AMIGO DE LOS ESTUDIANTES:."<<endl<<endl;
        cout<<"                                                      .:MENU:."<<endl;
        cout<<"                             .:Presiona 1 para crear una cuentas con sus titulares:."<<endl;
        cout<<"                                   .:Presiona 2 para consignar en una cuenta:."<<endl;
        cout<<"                                    .:Presiona 3 para retirar de una cuenta:."<<endl;
        cout<<"                               .:Presiona 4 para transferir de una cuenta a otra:."<<endl;
        cout<<"                      .:Presiona 5 para mostrar todos los titulares y su edad de una cuenta:."<<endl;
        cout<<"            .:Presiona 6 para mostrar todas las cuentas que se abrieron antes de una fecha especifica:."<<endl;
        cout<<"                .:Presiona 7 para mostrar toda la informacion de cada una de las cuentas del banco:."<<endl;
        cout<<"                                     .:Presiona 8 para salir del programa:."<<endl<<endl;

        cout<<"Presiona el numero de la opcion deseada: ";
        cin>>opcion;
        cout<<endl;

        switch(opcion)
        {
        case 1:
            crearCuentasYTitulares(p);
            break;

        case 2:
            consignarEnCuenta(p, numC, monto);
            break;

        case 3:
            retirarDeCuenta(p, numC, monto);
            break;

        case 4:
            transferirCuentaACuenta(p, numC, numC2, monto);
            break;

        case 5:
            mostrarTitulares(p);
            break;

        case 6:
            mostrarCuentasFecha(p);
            break;

        case 7:
            mostrarInformacionDeTodasCuentas(p);
            break;

        case 8:
            cout<<"Muchas gracias por usar el programa, vuelve pronto :)"<<endl;
            opcion=9;
            break;

        default:
            cout<<"Opcion inexistente, vuelve a intentarlo :("<<endl<<endl;
            opcion=8;
        }
    }
    while(opcion<9);

    archivoSalida<<endl<<"#FIN";
    archivoSalida.close();
    //remove("auxiliar.txt");
    delete p;
}

//FUNCION QUE AYUDARA A LA ASIGNACION DE MEMORIA DINAMICA DEL ARREGLO DE CUENTAS
int contadorCuentas()
{
    int contCuen=0;
    char linea[80];

    ifstream entrada;
    entrada.open("auxiliar.txt",ios ::in);

    if(entrada.is_open())
    {
        while(!entrada.eof())
        {
            entrada.getline(linea,80,'\n');
            if(*linea=='#'&&linea[1]=='C')
            {
                contCuen++;
            }
        }
    }
    else
    {
        cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl;
    }
    entrada.close();
    return contCuen-1;
}

//FUNCION QUE NOS AYUDARA A CONTAR EL NUMERO DE TITULARES QUE TIENE CADA CUENTA
int contadorTitulares(int nCuenta)
{
    int contCuen=-1;
    int contTit=0;
    char linea[80];

    ifstream entrada;
    entrada.open("auxiliar.txt",ios ::in);

    if(entrada.is_open())
    {
        while(!entrada.eof())
        {
            entrada.getline(linea,80,'\n');
            if(*linea=='#'&&linea[1]=='C')
            {
                contCuen++;
            }
            if(*linea!='1' && *linea!='2' && *linea!='3' && *linea!='4' && *linea!='5' && *linea!='6' && *linea!='7' && *linea!='8' && *linea!='9' && *linea!='0' && *linea!='#')
            {
                if(contCuen==nCuenta)
                {
                    contTit++;
                }
            }
        }
    }
    else
    {
        cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl;
    }
    entrada.close();
    return contTit;
}

//FUNCION QUE LEE Y MUESTRA EL ARCHIVO CON EL QUE SE TRABAJARA INICIALMENTE
void inicializar(Cuenta *p)
{
    int contCuen=-1;
    int num=1;
    char linea[80];
    char aux[30];
    char *token;
    int contTit=0;
    int anio1=0, mes1=0, dia1=0, mesAux=0, diaAux=0;

    time_t tSac = time(NULL);
    tm tms = *localtime(&tSac);

    srand(time(NULL));


    ifstream entrada;
    entrada.open("cuentas.txt",ios ::in);

    if(entrada.is_open())
    {
        while(!entrada.eof())
        {
            entrada.getline(linea,80,'\n');
            if(*linea=='#'&&linea[1]=='C')
            {
                anio1=2020+rand()%2;
                if(anio1==tms.tm_year+1900)
                {
                    mes1=1+rand()%tms.tm_mon-1;
                    if(mes1==tms.tm_mon+1)
                    {
                        dia1=1+rand()%tms.tm_mday-1;
                    }
                    else
                    {
                        dia1=1+rand()%30;
                    }
                }
                else
                {
                    mes1=1+rand()%12;
                    dia1=1+rand()%30;
                }

                contCuen++;
                (p+contCuen)->numeroCuenta = contCuen;
                strcpy((p+contCuen)->estado,"ACTIVA");
                sprintf((p+contCuen)->fechaCreacion.anio, "%d", anio1);
                sprintf((p+contCuen)->fechaCreacion.mes, "%d", mes1);
                sprintf((p+contCuen)->fechaCreacion.dia, "%d", dia1);
                cout<<"#Cuenta "<<num<<endl;
                num++;
                contTit=0;
            }
            else if(*linea=='#' || *linea=='0')
            {
                cout<<linea<<endl;
            }
            else if(*linea=='1' || *linea=='2' || *linea=='3' || *linea=='4' || *linea=='5' || *linea=='6' || *linea=='7' || *linea=='8' || *linea=='9' || *linea=='0')
            {
                token=strtok(linea,"-");
                while(token!=NULL)
                {
                    (p+contCuen)->saldo=atoi(token);
                    while(token!=NULL)
                    {
                        token=strtok(NULL, "-");
                        strcpy((p+contCuen)->tipo.ahoOCor,token);
                        while(token!=NULL)
                        {
                            token=strtok(NULL, "-");
                            (p+contCuen)->tipo.tarSob=atoi(token);
                            break;
                        }
                        break;
                    }
                    break;
                }
                cout<<(p+contCuen)->saldo<<"-------"<<(p+contCuen)->tipo.ahoOCor<<"-------"<<(p+contCuen)->tipo.tarSob<<endl;
            }
            else
            {
                token=strtok(linea,"*");
                while(token!=NULL)
                {
                    strcpy(((p+contCuen)->titulares+contTit)->nombre, token);
                    while(token!=NULL)
                    {
                        token=strtok(NULL, "-");
                        strcpy(((p+contCuen)->titulares+contTit)->fechaNacimiento.anio, token);
                        while(token!=NULL)
                        {
                            token=strtok(NULL,"-");
                            strcpy(((p+contCuen)->titulares+contTit)->fechaNacimiento.mes, token);
                            while(token!=NULL)
                            {
                                token=strtok(NULL,"*");
                                strcpy(((p+contCuen)->titulares+contTit)->fechaNacimiento.dia, token);
                                while(token!=NULL)
                                {
                                    token=strtok(NULL, "*");
                                    strcpy(((p+contCuen)->titulares+contTit)->telFijo, token);
                                    while(token!=NULL)
                                    {
                                        token=strtok(NULL,"*");
                                        strcpy(((p+contCuen)->titulares+contTit)->celular, token);
                                        while(token!=NULL)
                                        {
                                            token=strtok(NULL,"*");
                                            strcpy(((p+contCuen)->titulares+contTit)->direccion, token);
                                            break;
                                        }
                                        break;
                                    }
                                    break;
                                }
                                break;
                            }
                            break;

                        }
                        break;
                    }
                    break;
                }
                cout<<((p+contCuen)->titulares+contTit)->nombre<<"      *"<<((p+contCuen)->titulares+contTit)->fechaNacimiento.anio<<"-"<<((p+contCuen)->titulares+contTit)->fechaNacimiento.mes<<"-"<<((p+contCuen)->titulares+contTit)->fechaNacimiento.dia<<"      *"<<((p+contCuen)->titulares+contTit)->telFijo<<"     *"<<((p+contCuen)->titulares+contTit)->celular<<"     *"<<((p+contCuen)->titulares+contTit)->direccion<<endl;
                contTit++;
            }
        }
        cout<<endl<<endl;
    }
    else
    {
        cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl<<endl;
    }
    entrada.close();
}

//FUNCION QUE CREA EL ARCHIVO QUE NOS AYUDARA A GUARDAR LAS NUEVAS CUENTAS CREADAS
void crearAux()
{
    char linea[80];

    ifstream entrada;
    ofstream salida;

    entrada.open("cuentas.txt", ios::in);
    salida.open("auxiliar.txt", ios::out);

    if(entrada.is_open())
    {
        if(salida.is_open())
        {
            while(!entrada.eof())
            {
                entrada.getline(linea,80,'\n');
                if(*linea=='#' && linea[1]=='F')
                {
                    //SE SALTA ESTA PARTE
                }
                else
                {
                    salida<<endl<<linea;
                }
            }
        }
        else
        {
            cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl<<endl;
        }
    }
    else
    {
        cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl<<endl;
    }
    entrada.close();
    salida.close();
}

//FUNCION QUE CREA LAS CUENTAS Y LOS TITULARES.
void crearCuentasYTitulares(Cuenta *p)
{
    int contCuen=0, contTit=0;

    contCuen = contadorCuentas()+1;

    time_t tSac = time(NULL);
    tm tms = *localtime(&tSac);

    ofstream archivoSalida("auxiliar.txt", ios::out | ios::app);

    if (archivoSalida.is_open())
    {
        cout<<"Ingrese el saldo incial de la cuenta: ";
        cin>>(p+contCuen)->saldo;
        cout<<"Ingrese el tipo de la cuenta: ";
        cin>>(p+contCuen)->tipo.ahoOCor;
        cout<<"Ingrese la tarjeta o sobregiro de la cuenta (segun sea el caso): ";
        cin>>(p+contCuen)->tipo.tarSob;
        cout<<"Cuantos titulares tendra la cuenta? ";
        cin>>contTit;

        for(int i=0; i<contTit; i++)
        {
            cout<<"Ingrese el nombre del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->nombre;
            cout<<"Ingrese el anio de nacimiento del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->fechaNacimiento.anio;
            cout<<"Ingrese el mes de nacimiento del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->fechaNacimiento.mes;
            cout<<"Ingrese el dia de nacimiento del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->fechaNacimiento.dia;
            cout<<"Ingrese el telefono fijo del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->telFijo;
            cout<<"Ingrese el celular del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->celular;
            cout<<"Ingrese la direccion del titular #"<<i+1<<": ";
            cin>>((p+contCuen)->titulares+i)->direccion;
            cout<<endl;
        }

        (p+contCuen)->numeroCuenta=contCuen;
        strcpy((p+contCuen)->estado,"ACTIVA");
        sprintf((p+contCuen)->fechaCreacion.anio, "%d", tms.tm_year+1900);
        sprintf((p+contCuen)->fechaCreacion.mes, "%d", tms.tm_mon+1);
        sprintf((p+contCuen)->fechaCreacion.dia, "%d", tms.tm_mday);

        archivoSalida<<endl<<"#Cuenta"<<endl;
        archivoSalida<<"#Saldo------Tipo-------Tarjeta/Sobregiro"<<endl;
        archivoSalida<<(p+contCuen)->saldo<<"-------"<<(p+contCuen)->tipo.ahoOCor<<"---------"<<(p+contCuen)->tipo.tarSob<<endl;
        archivoSalida<<"#Titulares"<<endl;

        for(int j=0; j<contTit; j++)
        {
            archivoSalida<<((p+contCuen)->titulares+j)->nombre<<"      *"<<((p+contCuen)->titulares+j)->fechaNacimiento.anio<<"-"<<((p+contCuen)->titulares+j)->fechaNacimiento.mes<<"-"<<((p+contCuen)->titulares+j)->fechaNacimiento.dia<<"      *"<<((p+contCuen)->titulares+j)->telFijo<<"     *"<<((p+contCuen)->titulares+j)->celular<<"     *"<<((p+contCuen)->titulares+j)->direccion<<endl;
        }
        archivoSalida<<"0";
        cout<<"La cuenta ha sido creada exitosamente :)"<<endl<<endl<<endl;
    }
    else
    {
        cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl<<endl;
    }

    archivoSalida.close();
}

//FUNCION QUE CONSIGNA EN UNA CUENTA DADO EL NUMERO DE LA CUENTA Y EL MONTO A CONSIGNAR.
bool consignarEnCuenta(Cuenta *p, int numC, int monto)
{
    if(numC==0)
    {
        cout<<"Ingresa el numero de la cuenta a la cual deseas consignar: ";
        cin>>numC;
        cout<<"Ingresa el monto que deseas consignarle a la cuenta: ";
        cin>>monto;
    }
    cout<<endl;
    numC--;

    for(int i=0; i<=contadorCuentas(); i++)
    {
        if(p[i].numeroCuenta==numC)
        {
            if(strcmp((p+i)->tipo.ahoOCor,"ahorros")==0)
            {
                cout<<"Cuenta: "<<p[i].numeroCuenta+1<<endl;
                cout<<"Tu antiguo saldo era de: "<<(p+i)->saldo<<endl;
                (p+i)->saldo+=monto;
                cout<<"Tu nuevo saldo es de: "<<(p+i)->saldo<<endl<<endl<<endl;
                return true;
            }
            else
            {
                if(p[i].tipo.sobreGiroUsado<monto)
                {
                    cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                    cout<<"Tu antiguo sobregiro usado era de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                    cout<<"Tu antiguo saldo era de: "<<p[i].saldo<<endl;
                    monto -= (p+i)->tipo.sobreGiroUsado;
                    (p+i)->tipo.sobreGiroUsado=0;
                    (p+i)->saldo+=monto;
                    cout<<"Tu nuevo sobregiro usado es de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                    cout<<"Tu nuevo saldo es de: "<<(p+i)->saldo<<endl<<endl<<endl;
                    return true;
                }
                else
                {
                    cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                    cout<<"Tu antiguo sobregiro usado era de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                    cout<<"Tu antiguo saldo era de: "<<(p+i)->saldo<<endl;
                    (p+i)->tipo.sobreGiroUsado-=monto;
                    cout<<"Tu nuevo sobregiro usado es de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                    cout<<"Tu nuevo saldo es de: "<<(p+i)->saldo<<endl<<endl<<endl;
                    return true;
                }
            }
        }
    }
    numC=0;
    monto=0;
}

//FUCNION QUE RETIRA DE UNA CUENTA DADO EL NUMERO DE LA CUENTA Y EL MONTO A CONSIGNAR.
bool retirarDeCuenta(Cuenta *p, int numC, int monto)
{
    if(numC==0)
    {
        cout<<"Ingresa el numero de la cuenta a la cual deseas retirar: ";
        cin>>numC;
        cout<<"Ingresa el monto que deseas retirarle a la cuenta: ";
        cin>>monto;
    }
    cout<<endl;
    numC--;

    for(int i=0; i<=contadorCuentas(); i++)
    {
        if((p+i)->numeroCuenta==numC)
        {
            if(strcmp((p+i)->tipo.ahoOCor,"ahorros")==0)
            {
                if(monto<=(p+i)->saldo)
                {
                    cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                    cout<<"Tu antiguo saldo era de: "<<(p+i)->saldo<<endl;
                    (p+i)->saldo-=monto;
                    cout<<"Tu nuevo saldo es de: "<<(p+i)->saldo<<endl<<endl<<endl;
                    return true;
                }
                else
                {
                    cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                    cout<<"El monto a retirar es mayor que tu saldo en la cuenta :("<<endl<<endl<<endl;
                    return false;
                }
            }
            else
            {
                if(monto<=((p+i)->saldo+(p+i)->tipo.tarSob-(p+i)->tipo.sobreGiroUsado))
                {
                    if(monto<(p+i)->saldo)
                    {
                        cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                        cout<<"Tu antiguo sobregiro usado era de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                        cout<<"Tu antiguo saldo era de: "<<(p+i)->saldo<<endl;
                        (p[i]).saldo-=monto;
                        cout<<"Tu nuevo sobregiro usado es de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                        cout<<"Tu nuevo saldo es de: "<<(p+i)->saldo<<endl<<endl<<endl;
                        return true;
                    }
                    else
                    {
                        cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                        cout<<"Tu antiguo sobregiro usado era de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                        cout<<"Tu antiguo saldo era de: "<<(p+i)->saldo<<endl;
                        monto -= (p+i)->saldo;
                        (p+i)->saldo=0;
                        (p+i)->tipo.sobreGiroUsado+=monto;
                        cout<<"Tu nuevo sobregiro usado es de: "<<(p+i)->tipo.sobreGiroUsado<<endl;
                        cout<<"Tu nuevo saldo es de: "<<(p+i)->saldo<<endl<<endl<<endl;
                        return true;
                    }
                }
                else
                {
                    cout<<"Cuenta: "<<(p+i)->numeroCuenta+1<<endl;
                    cout<<"El monto a retirar es mayor que tu saldo y sobregiro disponible en la cuenta :("<<endl<<endl<<endl;
                    return false;
                }
            }
        }
    }
    numC=0;
    monto=0;
}

//FUNCION QUE TRANSFIERE DE UNA CUENTA A OTRA DADO EL NUMERO DE LA CUENTA ORIGEN.
void transferirCuentaACuenta(Cuenta *p, int numC, int numC2, int monto)
{
    cout<<"Ingresa el numero de la cuenta de la cual se le descontara el dinero: ";
    cin>>numC;
    cout<<"Ingresa el numero de la cuenta a la que le llegara el dinero: ";
    cin>>numC2;
    cout<<"Ingresa el monto que deseas transferir: ";
    cin>>monto;

    if(retirarDeCuenta(p, numC, monto)==true)
    {
        consignarEnCuenta(p, numC2, monto);
        cout<<"La transferencia se realizo exitosamente :)"<<endl<<endl<<endl;
    }
    else
    {
        cout<<"No se pudo realizar la transferencia exitosamente debido a que la primera cuenta no tiene fondos suficientes :("<<endl<<endl;
    }
}

//FUNCION QUE DADO UN NUMERO DE CUENTA, MUESTRA TODOS SUS TITULARES CON SU EDAD.
void mostrarTitulares(Cuenta *p)
{
    int nCuenta=0;
    int tdia=0, tmes=0, tanio=0, edad=0;
    time_t tSac = time(NULL);

    tm tms = *localtime(&tSac);

    cout<<"ingresa el numero de cuenta que deseas revisar: ";
    cin>>nCuenta;
    cout<<endl<<"Cuenta: "<<nCuenta<<endl;
    nCuenta--;

    for(int i=0; i<contadorTitulares(nCuenta); i++)
    {
        tdia=atoi(((p+nCuenta)->titulares+i)->fechaNacimiento.dia);
        tmes=atoi(((p+nCuenta)->titulares+i)->fechaNacimiento.mes);
        tanio=atoi(((p+nCuenta)->titulares+i)->fechaNacimiento.anio);
        edad=calcularEdad(tms.tm_year+1900,tms.tm_mon+1,tms.tm_mday,tanio,tmes,tdia);

        cout<<((p+nCuenta)->titulares+i)->nombre<<" tiene una edad de "<<edad<<" anios"<<endl;
    }
    cout<<endl<<endl;
}

//FUNCION QUE DADA UNA FECHA, MUESTRA TODAS LAS CUENTAS QUE SE ABRIERON ANTES DE ESA FECHA
void mostrarCuentasFecha(Cuenta *p)
{
    int cdia, cmes, canio;
    int ndia, nmes, nanio;

    cout<<"ingrese el dia: ";
    cin>>cdia;
    cout<<"ingrese el mes: ";
    cin>>cmes;
    cout<<"ingrese el anio: ";
    cin>>canio;

    cout<<endl;

    for(int i=0; i<=contadorCuentas(); i++)
    {
        ndia=atoi((p+i)->fechaCreacion.dia);
        nmes=atoi((p+i)->fechaCreacion.mes);
        nanio=atoi((p+i)->fechaCreacion.anio);
        if(nanio<canio)
        {
            cout<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
            cout<<"#Saldo------Tipo-------Tarjeta/Sobregiro-------FechaCreacion"<<endl;
            cout<<(p+i)->saldo<<"-------"<<(p+i)->tipo.ahoOCor<<"-------"<<(p+i)->tipo.tarSob<<"-------"<<(p+i)->fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
            cout<<"#Titulares"<<endl;

            for(int j=0; j<contadorTitulares(i); j++)
            {
                cout<<((p+i)->titulares+j)->nombre<<"      *"<<((p+i)->titulares+j)->fechaNacimiento.anio<<"-"<<((p+i)->titulares+j)->fechaNacimiento.mes<<"-"<<((p+i)->titulares+j)->fechaNacimiento.dia<<"      *"<<((p+i)->titulares+j)->telFijo<<"     *"<<((p+i)->titulares+j)->celular<<"     *"<<((p+i)->titulares+j)->direccion<<endl;
            }
            cout<<"0"<<endl;
        }
        else if(nanio==canio && nmes<cmes)
        {
            cout<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
            cout<<"#Saldo------Tipo-------Tarjeta/Sobregiro-------FechaCreacion"<<endl;
            cout<<(p+i)->saldo<<"-------"<<(p+i)->tipo.ahoOCor<<"-------"<<(p+i)->tipo.tarSob<<"-------"<<(p+i)->fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
            cout<<"#Titulares"<<endl;

            for(int j=0; j<contadorTitulares(i); j++)
            {
                cout<<((p+i)->titulares+j)->nombre<<"      *"<<((p+i)->titulares+j)->fechaNacimiento.anio<<"-"<<((p+i)->titulares+j)->fechaNacimiento.mes<<"-"<<((p+i)->titulares+j)->fechaNacimiento.dia<<"      *"<<((p+i)->titulares+j)->telFijo<<"     *"<<((p+i)->titulares+j)->celular<<"     *"<<((p+i)->titulares+j)->direccion<<endl;
            }
            cout<<"0"<<endl;
        }
        else if(nanio==canio && nmes==cmes && ndia<cdia)
        {
            cout<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
            cout<<"#Saldo------Tipo-------Tarjeta/Sobregiro-------FechaCreacion"<<endl;
            cout<<(p+i)->saldo<<"-------"<<(p+i)->tipo.ahoOCor<<"-------"<<p[i].tipo.tarSob<<"-------"<<(p+i)->fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
            cout<<"#Titulares"<<endl;

            for(int j=0; j<contadorTitulares(i); j++)
            {
                cout<<((p+i)->titulares+j)->nombre<<"      *"<<((p+i)->titulares+j)->fechaNacimiento.anio<<"-"<<((p+i)->titulares+j)->fechaNacimiento.mes<<"-"<<((p+i)->titulares+j)->fechaNacimiento.dia<<"      *"<<((p+i)->titulares+j)->telFijo<<"     *"<<((p+i)->titulares+j)->celular<<"     *"<<((p+i)->titulares+j)->direccion<<endl;
            }
            cout<<"0"<<endl;
        }
    }
    cout<<"#FIN"<<endl<<endl<<endl;
}

//FUNCION QUE GENERA TANTO POR CONSOLA COMO EN UN ARCHIVO DE TEXTO TODA LA INFORMACION DE CADA UNA DE LAS CUENTAS DEL BANCO
void mostrarInformacionDeTodasCuentas(Cuenta *p)
{
    ofstream archivoSalida("informeGeneral.txt",ios::out);

    if (archivoSalida.is_open())
    {
        for(int i=0; i<=contadorCuentas(); i++)
        {
            if(strcmp((p+i)->tipo.ahoOCor,"ahorros")==0)
            {
                cout<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
                cout<<"#Saldo-------Tipo-------Tarjeta/Sobregiro-------Estado-------FechaCreacion"<<endl;
                cout<<(p+i)->saldo<<"-------"<<(p+i)->tipo.ahoOCor<<"---------"<<(p+i)->tipo.tarSob<<"--------------"<<(p+i)->estado<<"-------"<<(p+i)->fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
                cout<<"#Titulares"<<endl;
                cout<<"#nombre----------fecha Nacimiento----TelFijo-----Celular---Direccion"<<endl;

                archivoSalida<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
                archivoSalida<<"#Saldo------Tipo-------Tarjeta/Sobregiro-------Estado-------FechaCreacion"<<endl;
                archivoSalida<<(p+i)->saldo<<"-------"<<(p+i)->tipo.ahoOCor<<"---------"<<(p+i)->tipo.tarSob<<"--------------"<<(p+i)->estado<<"-------"<<(p+i)->fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
                archivoSalida<<"#Titulares"<<endl;
                archivoSalida<<"#nombre----------fecha Nacimiento----TelFijo-----Celular---Direccion"<<endl;
            }
            else
            {
                cout<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
                cout<<"#Saldo-------Tipo-------Tarjeta/Sobregiro-------SobregiroUsado-------Estado-------FechaCreacion"<<endl;
                cout<<(p+i)->saldo<<"------"<<(p+i)->tipo.ahoOCor<<"-------"<<(p+i)->tipo.tarSob<<"--------------"<<(p+i)->tipo.sobreGiroUsado<<"----------------"<<(p+i)->estado<<"-------"<<p[i].fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
                cout<<"#Titulares"<<endl;
                cout<<"#nombre----------fecha Nacimiento----TelFijo-----Celular---Direccion"<<endl;

                archivoSalida<<"#Cuenta "<<(p+i)->numeroCuenta+1<<endl;
                archivoSalida<<"#Saldo------Tipo-------Tarjeta/Sobregiro-------SobregiroUsado-------Estado-------FechaCreacion"<<endl;
                archivoSalida<<(p+i)->saldo<<"-------"<<(p+i)->tipo.ahoOCor<<"-------"<<(p+i)->tipo.tarSob<<"--------------"<<(p+i)->tipo.sobreGiroUsado<<"----------------"<<(p+i)->estado<<"-------"<<(p+i)->fechaCreacion.anio<<"-"<<(p+i)->fechaCreacion.mes<<"-"<<(p+i)->fechaCreacion.dia<<endl;
                archivoSalida<<"#Titulares"<<endl;
                archivoSalida<<"#nombre----------fecha Nacimiento----TelFijo-----Celular---Direccion"<<endl;
            }

            for(int j=0; j<contadorTitulares(i); j++)
            {
                cout<<((p+i)->titulares+j)->nombre<<"      *"<<((p+i)->titulares+j)->fechaNacimiento.anio<<"-"<<((p+i)->titulares+j)->fechaNacimiento.mes<<"-"<<((p+i)->titulares+j)->fechaNacimiento.dia<<"      *"<<((p+i)->titulares+j)->telFijo<<"     *"<<((p+i)->titulares+j)->celular<<"     *"<<((p+i)->titulares+j)->direccion<<endl;
                archivoSalida<<((p+i)->titulares+j)->nombre<<"      *"<<((p+i)->titulares+j)->fechaNacimiento.anio<<"-"<<((p+i)->titulares+j)->fechaNacimiento.mes<<"-"<<((p+i)->titulares+j)->fechaNacimiento.dia<<"      *"<<((p+i)->titulares+j)->telFijo<<"     *"<<((p+i)->titulares+j)->celular<<"     *"<<((p+i)->titulares+j)->direccion<<endl;
            }
            cout<<"0"<<endl;
            archivoSalida<<"0"<<endl;
        }
        cout<<"#FIN"<<endl<<endl<<endl;
        archivoSalida<<"#FIN";
    }
    else
    {
        cout<<"El archivo no se pudo abrir correctamente."<<endl<<endl<<endl;
    }
    archivoSalida.close();
}

//FUNCION QUE NOS AYUDA A CALCULAR LA EDAD EXACTA DE LOS TITULARES DE LAS CUENTAS
int calcularEdad( int anioAct, int mesAct, int fechAct, int anioNac, int mesNac, int fechNac)
{
    int respFech, respMes, edad;

    if(fechAct<fechNac)
    {
        fechAct=fechAct+30;
        mesAct=mesAct-1;
        respFech=fechAct-fechNac;
    }
    else
    {
        respFech =  fechAct - fechNac;
    }

    if(mesAct<mesNac)
    {
        mesAct = mesAct + 12;
        anioAct = anioAct - 1 ;
        respMes = mesAct - mesNac;
    }
    else
    {
        respMes = mesAct - mesNac;
    }

    edad=anioAct-anioNac;
    return edad;
}
