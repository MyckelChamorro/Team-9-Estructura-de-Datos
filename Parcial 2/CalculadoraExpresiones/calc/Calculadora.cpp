/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*
*
* @author MYCKEL CHAMORRO
* @author JUAN GALLARDO
* @author ADRIAN PAEZ
* TEMA: Proyecto Unidad 2
* FECHA DE CREACION : 14 DE ENERO DE 2022
* FECHA DE MODIFICACION: 23 DE ENERO DE 2022
*/

#include <iostream>
#include "Operacion.hpp"
#include "Stack.hpp"
#include "CustomString.hpp"

using namespace std;

int main()
{
    try
    {
        Operation op;

        mystring str;
       
        Stack<string> datos;
        datos = op.ingresar_datos();
        
        cout << endl;
        if (op.evaluar_expresion(datos)) {
            Stack<string> prefija;
            prefija = op.infix_to_prefix1(datos);

            char comp;
            cout << "¿Quiere comparar la expresion ingresada con otra? (y/n): ";
            cin >> comp;

            if (comp == 'y')
            {           
                int signo;
                cout << "¿Signo?" << endl;
                cout << "1. >" << endl;
                cout << "2. <" << endl;
                cout << "3. =" << endl;
                cout << "\n-> Seleccione una opcion: " << endl;
                cin >> signo;
                while (signo < 1 || signo > 3)
                {
                    cout << "Seleccione una opcion valida: ";
                    cin >> signo;
                }
                Stack<string> datos2;
                datos2 = op.ingresar_datos();
                if (op.evaluar_expresion(datos2)) {

                    Stack<string> prefija2;
                    prefija2 = op.infix_to_prefix1(datos2);
                    cout << "Expresion 1: " << op.calculate(prefija) << endl;
                    cout << "Expresion 2: " << op.calculate(prefija2) << endl;
                    op.compare(op.calculate(prefija), op.calculate(prefija2), signo);
                }
                else
                {
                    cout << "Error Tipo2" << endl;
                }
                
            }
            else if (comp == 'n')
            {
                cout << "RESULTADO DE LA EXPRESION: " << op.calculate(prefija) << endl;
            }
            else
            {
                cout << "Opcion no valida... Saliendo del sistema" << endl;
                system("exit");
            }
        }
        else {
            cout << "EXPRESION INVALIDA" << endl;
        }
        
    }
    catch (const std::exception&)
    {
        cout << "Error Tipo1" << endl;

    }

        
}

