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
                Stack<string> datos2;
                datos2 = op.ingresar_datos();
                if (op.evaluar_expresion(datos2)) {

                    Stack<string> prefija2;
                    prefija2 = op.infix_to_prefix1(datos2);
                    char signo = 3;
                    cout << "¿Signo? (<, >, =): ";
                    cin >> signo;
                    if (signo == '>')
                    {
                        if (op.calculate(prefija) > op.calculate(prefija2)) 
                        { 
                            cout << "Expresion verdadera -> ";
                            datos.mostrar_expresion();
                            cout << " si es mayor que ";
                            datos2.mostrar_expresion();
                            cout << endl;
                            cout << endl;
                            
                        }
                        else 
                        {
                            cout << "Expresion falsa -> ";
                            datos.mostrar_expresion();
                            cout << " no es mayor que ";
                            datos2.mostrar_expresion();
                            cout << endl;
                            cout << endl;
                            
                        }
                    }
                    else if (signo == '<')
                    {
                        if (op.calculate(prefija) < op.calculate(prefija2)) 
                        {
                            cout << "Expresion verdadera -> ";
                            datos.mostrar_expresion();
                            cout << " si es menor que ";
                            datos2.mostrar_expresion();
                            cout << endl;
                            cout << endl;
                            
                        }
                        else
                        {
                            cout << "Expresion falsa -> ";
                            datos.mostrar_expresion();
                            cout << " no es menor que ";
                            datos2.mostrar_expresion();
                            cout << endl;
                            cout << endl;
                            
                        }
                    }
                    else if (signo == '=')
                    {
                        if (op.calculate(prefija) == op.calculate(prefija2)) 
                        {
                            cout << "Expresion verdadera -> ";
                            datos.mostrar_expresion();
                            cout << " si es igual que ";
                            datos2.mostrar_expresion();
                            cout << endl;
                            cout << endl;
                            
                        }
                        else
                        {
                            cout << "Expresion falsa -> ";
                            datos.mostrar_expresion();
                            cout << " no es igual que ";
                            datos2.mostrar_expresion();
                            cout << endl;
                            cout << endl;
                            
                        }
                    }
                    else
                    {
                        cout << "ERROR, no ingreso un signo correcto" << endl;
                    }

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

