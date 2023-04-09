/*
Programa para testear Perceptron_V1

Compilacion: g++ main.cpp -o Ejecutable -std=c++11
Ejecucion: ./Ejecutable
*/

#include <iostream>

using namespace std;

void Evaluate(float, float, float*);

int main(){  
    int Y_and[] = {0, 0, 0, 1};
    int Y_or[]  = {0, 1, 1, 1};
    int Y_xor[] = {0, 1, 1, 0};

    //Cambiar los pesos por aquellos que devuelva el programa "Perceptron_V1"
    float w_and[] = {-2 , 2, 1};
    float w_or[]  = {0 , 1, 1};
    float w_xor[] = {1 , -1, 0};

    int Option, Continuar = 1;
    float x1 = 0, x2 = 0;

    while(Continuar == 1){
        cout<<"Opciones Disponibles: "<<endl;
        cout<<"1. Compuerta AND"<<endl;
        cout<<"2. Compuerta OR"<<endl;
        cout<<"3. Compuerta XOR"<<endl;
        cout<<"Que neurona desea probar? ";
        cin>>Option;
        switch (Option){
        case 1:
            cout<<"Ingrese el valor de x1: ";cin>>x1;
            cout<<"Ingrese el valor de x2: ";cin>>x2;
            Evaluate(x1, x2, w_and);
            break;

        case 2:
            cout<<"Ingrese el valor de x1: ";cin>>x1;
            cout<<"Ingrese el valor de x2: ";cin>>x2;
            Evaluate(x1, x2, w_or);
            break;

        case 3:
            cout<<"Ingrese el valor de x1: ";cin>>x1;
            cout<<"Ingrese el valor de x2: ";cin>>x2;
            Evaluate(x1, x2, w_xor);
            break;

        default:
            cout<<"Ingrese una opcion valida"<<endl<<endl;
            break;
        }
        cout<<"Para continuar presione 1"<<endl;
        cout<<"Para terminar presione cualquier tecla"<<endl;
        cout<<"Continuar?: ";cin>>Continuar;
        system("clear");
    }
    return 0;
}

void Evaluate(float _x1, float _x2, float* omega){
    float Evaluate = 0;
    Evaluate = omega[0] + omega[1]*_x1 + omega[2]*_x2;
    if(Evaluate > 0){
        Evaluate = 1; 
    }
    else{
        Evaluate = 0;
    }
    cout<<"La salida es: "<<Evaluate<<endl<<endl;
}
