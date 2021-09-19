/// INCLUSION DE LIBRERIAS HELPERS
#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
 
using namespace std;

/// FUNCION QUE NOS PERMITIRA MOVILIZAR EL CURSOR
void gotoxy(int x,int y){  
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}  

int main () {
	setlocale(LC_CTYPE,"Spanish"); /// ASIGNAMOS IDIOMA
	
	system("color F0"); // CAMBIAMOS EL COLOR DE LA CONSOLA A FONDO BLANCO LETRAS NEGRAS
    
    /// INICIA CENTRADO DE TEXTO PARA LA PRIMER INTERFAZ
    int counter;
    int value;
    string main_title = "Cálculo de Sueldo final de Empleado";
    
    value = main_title.size();
    value = value + 20;
    
    for (counter = 0; counter <= value; counter++) {
        cout << "*";
    }
    cout << "\n";
    
    for (counter = 0; counter <= value; counter++) {
        cout << " ";
        if (counter == 5) {
              cout << main_title;
        }
        cout << " ";
    }
    
    cout << "\n";
    for (counter = 0; counter <= value; counter++) {
        cout << "*";
    }
    cout << "\n";
    /// FINALIZA CENTRADO DE TEXTO PARA LA PRIMER INTERFAZ    
        
    cout<<"\nIngrese la siguiente información laboral: \n"<<endl;
    
    /// INICIA FORMULARIO
    int location[5][2] = {{13,8}, {14,10},{11,12}, {63,8}, {67,10}},x,y,z;
	// location array = groups of column, and row, for gotoxy()
	string form[5]={"nombres","apellidos","cargo","pagos_por_hora","horas_trabajadas"}, answer[5];
	// string form[] = allowing different text to be printed for instructions
 
	gotoxy(2,8); // locates 2nd column, sixth row
	cout << "1.Nombres :________________________________   4.Costo hora :$___________________";
	gotoxy(2,10);  // locates 2nd column, eigthth row
	cout << "2.Apellidos:_______________________________   5.horas laboradas :__________horas";
	gotoxy(2,12);  // locates 2nd column, tenth row
	cout << "3.Cargo :__________________________________";
 
	
	for(x=0;x<5;x++){
		y=location[x][0];
		z=location[x][1];
		gotoxy(y,z);
		getline(cin, answer[x]);
	}
	/// FINALIZA FORMULARIO
    
    /// LIMPIAMOS CONSOLA PARA MOSTRAR LA NUEVA INTERFAZ
    system("cls");
        
    /// INICIA DECLARACION DE VARIABLES PARA REALIZAR CALCULOS
    
    /// ACA CONVERTIMOS A DECIMAL EL VALOR DEL COSTO HORA Y HORAS LABORADAS
    // YA QUE NOS VIENE EN FORMATO DE STRING EN LA VARIABLE ANSWER
    double salario_neto = atof(answer[3].c_str()) * atof(answer[4].c_str());
	
	double porcentaje_descuento_renta = 7.5;
	double porcentaje_descuento_isss = 5.4;
	double descuento_fijo_seguro_vida = 12;
	
	double descuento_renta = (porcentaje_descuento_renta * salario_neto) / 100;
	double descuento_isss = (porcentaje_descuento_isss * salario_neto) / 100;
	
	double total_deducciones = descuento_renta + descuento_isss; 
	double total_liquido = (salario_neto - total_deducciones) - descuento_fijo_seguro_vida;
    /// FINALIZA DECLARION DE VARIABLES PARA REALIZAR CALCULOS
    
    /// INICIA CENTRADO DE TEXTO PARA LA SEGUNDA INTERFAZ
    int i;
    int j;
    int val;
    int val2; 
    
    string title = "\tEmpleado: "+answer[0]+", "+answer[1]+"\n";
    string title2 = "\tCargo: "+ answer[2];
    
    val = title.size();
    val = val + 20;
    
    val2 = title2.size();
    val2 = val2 + 20;
    
    for (i = 0; i <= val; i++) {
        cout << "*";
    }
    cout << "\n";
    
    for (i = 0; i <= val; i++) {
        if (i == 5) {
              cout << title;
        }
    }
    
    for (j = 0; j <= val2; j++) {
        if (j == 5) {
              cout << title2;
        }
    }
    
    cout << "\n";
    for (i = 0; i <= val; i++) {
        cout << "*";
    }
    cout << "\n";
    /// FINALIZA CENTRADO DE TEXTO PARA LA SEGUNDA INTERFAZ
    
    /// MOSTRAMOS LOS DATOS RECIBIDOS CON TODOS LOS DESCUENTOS APLICADOS DE LEY
    gotoxy(13, 7);
    cout<<"Sueldo Inicial: \t $ "<<salario_neto<<endl;
    gotoxy(13, 8);
    cout<<"(Descuentos de ley)\t"<<endl;
	gotoxy(13, 9);
    cout<<"Renta: \t\t $ "<<descuento_renta<<endl;
    gotoxy(13, 10);
    cout<<"ISSS: \t\t $ "<<descuento_isss<<endl;
    gotoxy(13, 11);
    cout<<"Seguro Vida: \t $ "<<descuento_fijo_seguro_vida<<endl;
    gotoxy(32, 12);
    cout<<"____________";
    gotoxy(13, 13);
    cout<<"Sueldo a pagar: \t $ "<<total_liquido;
    
    getch(); /// IMPIDE MOSTRAR MENSAJE POR DEFECTO DE LA CONSOLA
    
    return 0;
    
}

