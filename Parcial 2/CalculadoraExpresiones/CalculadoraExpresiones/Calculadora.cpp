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
                op.compare(prefija, datos);

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
        else
        {
            cout << "EXPRESION INVALIDA" << endl;
        }

    }
    catch (const std::exception&)
    {
        cout << "Error Tipo1" << endl;

    }


}

