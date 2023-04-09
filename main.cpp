/*
Programa de Perceptron V1

Compilacion: g++ main.cpp -o Ejecutable -std=c++11
Ejecucion: ./Ejecutable
*/

#include <iostream>

using namespace std;

float Evaluate(float*, float*, int, int);
int Threshold(float);
float* W_update(float*, float*, int, int, int);
void Train(float*, int*, float*);
void PrintAll(int, int, float, int*, int*, float*);
bool Validation(int*, int*);

int Divergence = 0;
int main(){  
    float X[]   = {1, 1, 1, 1,  //Bias
                   0, 0, 1, 1,  //X1
                   0, 1, 0, 1}; //X2

    int Y_and[] = {0, 0, 0, 1};
    int Y_or[]  = {0, 1, 1, 1};
    int Y_xor[] = {0, 1, 1, 0};
    //Omega debe ser un vector columna, pero 
    //para simplificar la programacion se considerara
    //vector fila.
    float w_and[] = {0 , 0, 0};
    float w_or[]  = {0 , 0, 0};
    float w_xor[] = {0 , 0, 0};

    cout<<"Entrenando neurona para AND"<<endl;
    Train(X, Y_and, w_and);
    cout<<"Los pesos finales son:"<<endl;
    cout<<"w_and = ["<<w_and[0]<<" , "<<w_and[1]<<" , "<<w_and[2]<<"]"<<endl<<endl;

    cout<<"Entrenando neurona para OR"<<endl;
    Train(X, Y_or, w_or);
    cout<<"Los pesos finales son:"<<endl;
    cout<<"w_or = ["<<w_or[0]<<" , "<<w_or[1]<<" , "<<w_or[2]<<"]"<<endl<<endl;

    cout<<"Entrenando neurona para XOR"<<endl;
    Train(X, Y_xor, w_xor);
    cout<<"Los pesos finales son:"<<endl;
    cout<<"w_xor = ["<<w_xor[0]<<" , "<<w_xor[1]<<" , "<<w_xor[2]<<"]"<<endl<<endl;

    return 0;
}
//Paso 2.1 Evaluamos la clase predicha w^T * X_i 
//Evaluate(datos de entrada, vector de pesos, columnas totales, columna actual)
float Evaluate(float* x, float* omega, int ncols, int col){
    float Eval = 0;
    for(int i = 0; i < 3; i++){
        Eval += x[i*ncols + col] * omega[i];
    }
    return Eval;
}

int Threshold(float Val){
    if(Val > 0)
        return 1;
    return 0;
}

float* W_update(float* x, float* omega, int ncols ,int col, int sign){
    for(int i = 0; i < 3; i++){
        omega[i] += sign*x[i*ncols + col];
    }
    return omega;
}

void Train(float* X_in, int* Y_out, float* Weights){   
    int N_cols = 4;
    int Col_Act = 0;
    int Counter = 0;
    float Evaluation = 0;
    int Y_g[] = {0,0,0,0};
    bool Flag = true;

    while(Flag){
        Evaluation = Evaluate(X_in, Weights, N_cols, Col_Act);
        Y_g[Col_Act] = Threshold(Evaluation);
        
        if((Y_g[Col_Act] == 0) && (Y_out[Col_Act] == 1)){
            Weights = W_update(X_in, Weights, N_cols, Col_Act, 1);
        }

        if((Y_g[Col_Act] == 1) && (Y_out[Col_Act] == 0)){
            Weights = W_update(X_in, Weights, N_cols, Col_Act, -1);
        }

        //Descomentar esta linea para ver el entrenamiento
        //PrintAll(Col_Act, Counter, Evaluation, Y_g, Y_out, Weights);

        if(Col_Act < 3){
            Col_Act++;
        }
        else{
            Flag = Validation(Y_g, Y_out);
            Col_Act = 0;
            Counter++;
        }
    }
}

//Esta Funcion Se usa para ver la evolucion del entrenamiento del perceptron
void PrintAll(int _Col_Act, int _Counter, float _Evaluation, int* _Y_g, int* _Y_and, float* _w){
    if(_Col_Act % 4 == 0){
            cout<<"-----------------------------------------------"<<endl;
            cout<<"Iteracion "<<_Counter+1<<endl;
    } 
    cout<<"La columan Actual es: "<<_Col_Act+1<<endl;
    cout<<"Evaluacion: "<<_Evaluation<<endl;
    cout<<"Y_g es: "<<_Y_g[_Col_Act]<<" y Y es: "<<_Y_and[_Col_Act]<<endl;
    cout<<"Pesos nuevos:"<<endl;
    cout<<"w = ["<<_w[0]<<" , "<<_w[1]<<" , "<<_w[2]<<"]"<<endl<<endl;
}

bool Validation(int* _Y_g, int* _Y){
    bool _Flag = true;
    int cont = 0;
    for(int i = 0; i < 4; i++){
        if(_Y_g[i] == _Y[i]){
            cont++;
        }
        else{
            cont = 0;
        }
    }
    if(cont == 4){
        cout<<"Se pudo lograr el entrenamiento de la nuerona"<<endl;
        _Flag = false;
        Divergence = 0;
    }
    Divergence++;
    if(Divergence > 500){
        cout<<"No se pudo lograr el entrenamiento de la neurona"<<endl;
        _Flag = false;
    }
    return _Flag;
}