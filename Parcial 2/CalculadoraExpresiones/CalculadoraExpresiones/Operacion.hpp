/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*
*
* @author MYCKEL CHAMORRO
* @author JUAN GALLARDO
* @author ADRIAN PAEZ
* TEMA: Proyecto Unidad 2
* FECHA DE CREACION : 14 DE ENERO DE 2022
* FECHA DE MODIFICACION: 20 DE ENERO DE 2022
*/

#pragma once
#include "CustomString.hpp"
#include "Stack.hpp"
#include <conio.h>
#include <string>

class Operation
{
public:

	/**
	 * @brief infix a prefix
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> infix_to_prefix1(Stack<string>);
	
	/**
	 * @brief comprobar operador
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_operator(char);
	
	/**
	 * @brief comprobar operador
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_operator1(string);
	
	/**
	 * @brief comprobar char trigonometrica
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_trig_fun(char);
	
	/**
	 * @brief comprobar trigonometrica
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_trig_fun1(string);
	
	/**
	 * @brief comprobar operando
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_operand(char);
	
	/**
	 * @brief char precedente
	 * 
	 * @return int 
	 */
	int precedence(char);
	
	/**
	 * @brief elemento precedente
	 * 
	 * @return int 
	 */
	int precedence1(string);
	
	/**
	 * @brief calcular
	 * 
	 * @return double 
	 */
	double calculate(Stack<string>);
	
	/**
	 * @brief ingresar datos
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> ingresar_datos();
	Stack<string> ingresar_datos_enteros();
	/**
	 * @brief invertir pila
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> invertir_pila(Stack<string>);

	/**
	 * @brief copiar pila
	 * 
	 * @return Stack<string> 
	 */
	Stack<string> copiar_pila(Stack<string>);
	bool evaluar_expresion(Stack<string>);
	char* ingreso(const char*);
};

Stack<string> Operation::infix_to_prefix1(Stack<string> infix)
{

    mystring str;

    Stack<string> cad = copiar_pila(infix);
    string result;
    string aux;
    string anterior = "";
    Nodo<string>* character = cad.get_primero();
    Stack<string> prefix;
    Stack<string> stack;
    while (character) {
        if (character->get_dato() == "(") {
            character->set_dato(")");
        }
        else if (character->get_dato() == ")") {
            character->set_dato("(");
        }
        character = character->get_siguiente();
    }
    character = cad.get_primero();
    string character1 = "";
    while (character) {
        character1 = character->get_dato();
        if (str.is_number(character1)) {
            prefix.insertar_por_la_cabeza(character1);
        }
        else if (character1 == "(") {
            stack.insertar_por_la_cabeza(character1);
        }
        else if (character1 == ")") {
            while ((stack.get_primero()->get_dato() != "(") && (!stack.empty_stack())) {
                prefix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
                stack.borrar_por_la_cabeza();
            }

            if (stack.get_primero()->get_dato() == "(") {
                stack.borrar_por_la_cabeza();
            }
        }
        else if (is_operator1(character1)) {

            if (stack.empty_stack()) {
                stack.insertar_por_la_cabeza(character1);
            }
            else {
                if (precedence1(character1) > precedence1(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character1);
                }
                else if ((precedence1(character1) == precedence1(stack.get_primero()->get_dato()))
                    && (character1 == "^")) {
                    while ((precedence1(character1) == precedence1(stack.get_primero()->get_dato()))
                        && (character1 == "^")) {
                        prefix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character1);
                }
                else if (precedence1(character1) == precedence1(stack.get_primero()->get_dato())) {
                    stack.insertar_por_la_cabeza(character1);
                }
                else {
                    while ((!stack.empty_stack()) && (precedence1(character1) < precedence1(stack.get_primero()->get_dato()))) {
                        prefix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
                        stack.borrar_por_la_cabeza();
                    }
                    stack.insertar_por_la_cabeza(character1);
                }
            }
        }

        else if (is_trig_fun1(character1) && anterior == ")") {

            prefix.insertar_por_la_cabeza(character1);
        }
        anterior = character1;
        character = character->get_siguiente();
    }
    while (!stack.empty_stack()) {
        prefix.insertar_por_la_cabeza(stack.get_primero()->get_dato());
        stack.borrar_por_la_cabeza();
    }


    return prefix;
}

int Operation::precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '%')
        return 2;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int Operation::precedence1(string c)
{
    if (c == "^")
        return 3;
    else if (c == "%")
        return 2;
    else if (c == "*" || c == "/")
        return 2;
    else if (c == "+" || c == "-")
        return 1;
    else
        return -1;
}

double Operation::calculate(Stack<string> prefix)
{
    if (prefix.empty_stack()) {
        return 0;
    }
    try
    {
        mystring str;
        Stack<string> cad = invertir_pila(prefix);
        //string result, prefix;
        string aux, aux2;
        string charac = "";
        char anterior = '.';
        Stack<string> stack;
        Nodo<string>* character = cad.get_primero();
        string character1 = "";
        while (character) {
            character1 = character->get_dato();
            if (str.is_number(character1)) {


                stack.insertar_por_la_cabeza(character1);


            }
            else if (character1 == "+") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(stod(aux) + stod(aux2)));

            }
            else if (character1 == "-") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(stod(aux) - stod(aux2)));

            }
            else if (character1 == "*") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(stod(aux) * stod(aux2)));

            }
            else if (character1 == "/") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(stod(aux) / stod(aux2)));

            }
            else if (character1 == "%") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(int(stod(aux)) % int(stod(aux2))));

            }
            else if (character1 == "^") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                aux2 = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();
                stack.insertar_por_la_cabeza(to_string(pow(stod(aux), stod(aux2))));

            }
            else if (character1 == "sen") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();

                stack.insertar_por_la_cabeza(to_string(sin(stod(aux))));

            }
            else if (character1 == "cos") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();

                stack.insertar_por_la_cabeza(to_string(cos(stod(aux))));

            }
            else if (character1 == "tan") {
                aux = stack.get_primero()->get_dato();
                stack.borrar_por_la_cabeza();

                stack.insertar_por_la_cabeza(to_string(tan(stod(aux))));

            }

            character = character->get_siguiente();

        }
        return stod(stack.get_primero()->get_dato());
    }
    catch (...)
    {
        cout << "excepcion" << endl;

    }

}

Stack<string> Operation::ingresar_datos()
{
    Stack<string> datos;
    Stack<string> datos1;
    Stack<string> datos2;
    mystring str;
    string dato = "";
    while (dato != "=") {
        system("cls");
        cout << "\tCALCULADORA EXPRESIONES " << endl;
        datos.mostrar_expresion_invertida();
        cout << "<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>" << endl;
        cout << "|   +   -   *   /   %   sen cos tan (   )  |" << endl;
        cout << "|   1          2           3         ^     |" << endl;
        cout << "|   4          5           6               |" << endl;
        cout << "|   7          8           9               |" << endl;
        cout << "|   0          .                           |" << endl;
        cout << "<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>" << endl;
        cout << "\nIngrese un numero u operador : ";
        cin >> dato;
        if (!datos.empty_stack()) {
            if (str.is_number(dato) && datos.get_primero()->get_dato() == ")") {
                datos.insertar_por_la_cabeza("*");
            }
            if (is_trig_fun1(dato) && str.is_number(datos.get_primero()->get_dato())) {
                datos.insertar_por_la_cabeza("*");
            }
            if (is_trig_fun1(dato) && datos.get_primero()->get_dato() == ")") {
                datos.insertar_por_la_cabeza("*");
            }
            if (dato == "(" && datos.get_primero()->get_dato() == ")") {
                datos.insertar_por_la_cabeza("*");
            }
            if (dato == "(" && str.is_number(datos.get_primero()->get_dato())) {
                datos.insertar_por_la_cabeza("*");
            }
        }
        if (str.is_number(dato)) {
            datos.insertar_por_la_cabeza(dato);
        }
        else {
            if (dato == "=" || dato == "sen" || dato == "cos" || dato == "tan" || dato == "+" || dato == "-" || dato == "/" || dato == "*" || dato == "(" || dato == ")" || dato == "%" || dato == "^") {
                datos.insertar_por_la_cabeza(dato);
            }
            else {
                cout << "Ingrese datos validos" << endl;
                system("pause");
            }
        }
    }
    cout << "_______________________________________" << endl;


    datos.borrar_por_la_cabeza();
    if (datos.empty_stack()) {
        return datos;
    }
    return invertir_pila(datos);
}

Stack<string> Operation::ingresar_datos_enteros()
{
    string dato = "99";
    Stack<string> datos;
    mystring str;
    int num = 0;
    char datos2[11];
    while (dato != "999") {



        strcpy_s(datos2, ingreso("Ingrese un numero a la pila "));
        //cout << datos2 << endl;
        dato = datos2;

        cout << endl;
        //cin >> dato;
        if (dato != "999" && stoi(dato) > 9) {
            datos.insertar_por_la_cabeza(dato);

        }


    }
    return datos;

}

Stack<string> Operation::invertir_pila(Stack<string> datos)
{
    Nodo<string>* dato = datos.get_primero();
    Stack<string> datos1;
    string aux;
    while (!datos.StackVacia()) {
        aux = datos.get_primero()->get_dato();
        datos.borrar_por_la_cabeza();
        datos1.insertar_por_la_cabeza(aux);
    }
    free(datos.get_primero());
    return datos1;
}

Stack<string> Operation::copiar_pila(Stack<string> datos)
{
    Nodo<string>* dato = datos.get_primero();
    Stack<string> datos1;
    string aux;
    while (dato) {
        aux = dato->get_dato();
        datos1.insertar_por_la_cabeza(aux);
        dato = dato->get_siguiente();

    }
    return datos1;
}

bool Operation::evaluar_expresion(Stack<string> datos1)
{

    Stack<string> datos = copiar_pila(datos1);
    Nodo<string>* dato = datos.get_primero();
    if (datos.empty_stack()) {
        return true;
    }

    string aux;
    string anterior;
    string cabeza;
    mystring str;
    bool result = false;
    int cont_paren_abi = 0;
    int cont_paren_cerr = 0;
    if (dato->get_dato() == "(") {
        cout << "aqui 13" << endl;
        return false;
    }
    if (dato->get_dato() == ")") {
        cont_paren_cerr++;
    }
    anterior = dato->get_dato();
    if (!is_trig_fun1(anterior)) {
        if (!str.is_number(anterior)) {
            if (!is_operator1(anterior)) {
                if (anterior != "(") {
                    if (anterior != ")") {
                        cout << "termino no valido" << endl;
                        return false;
                    }
                }
            }
        }

    }
    datos.borrar_por_la_cabeza();
    int cont_data = 0;
    while (!datos.empty_stack()) {
        aux = datos.get_primero()->get_dato();
        if (aux == "(") {
            if (is_operator1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            if (anterior == ")") {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            cont_paren_abi++;

        }
        if (aux == ")") {
            cont_paren_cerr++;
        }

        if (is_operator1(aux)) {
            if (is_operator1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }

            if (anterior == ")") {
                cout << "Expresion Invalida" << endl;
                return false;
            }



        }
        if (str.is_number(aux)) {
            if (str.is_number(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            if (is_trig_fun1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }


        }
        if (is_trig_fun1(aux)) {
            if (str.is_number(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
            if (is_trig_fun1(anterior)) {
                cout << "Expresion Invalida" << endl;
                return false;
            }
        }
        if (!is_trig_fun1(aux)) {
            if (!str.is_number(aux)) {
                if (!is_operator1(aux)) {
                    if (aux != "(") {
                        if (aux != ")") {
                            cout << "Expresion Invalida" << endl;
                            return false;
                        }
                    }
                }
            }

        }

        anterior = aux;
        datos.borrar_por_la_cabeza();
        cont_data++;


    }

    if (is_operator1(anterior)) {
        cout << "Expresion Invalida" << endl;
        return false;
    }
    if (is_trig_fun1(anterior) && cont_data == 0) {
        cout << "Expresion Invalida" << endl;
        return false;
    }
    if (anterior == ")") {
        cout << "Expresion Invalida" << endl;
        return false;
    }
    if (cont_paren_abi != cont_paren_cerr) {
        cout << "faltan parentesis" << endl;
        return false;
    }

    return true;
}

char* Operation::ingreso(const char* msj) {
    char dato[10];
    char c;
    int i = 0;
    printf("%s", msj);
    cout << endl;
    while ((c = _getch()) != 13) {
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            dato[i++] = c;
        }
    }
    dato[i] = '\0';
    return dato;
}

bool Operation::is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
        return true;
    }
    return false;
}

bool Operation::is_operator1(string c)
{
    if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%" || c == "^") {
        return true;
    }
    return false;
}

bool Operation::is_trig_fun(char c)
{
    if (c == 'S' || c == 'C' || c == 'T') {
        return true;
    }
    return false;
}

bool Operation::is_trig_fun1(string c)
{
    if (c == "sen" || c == "cos" || c == "tan") {
        return true;
    }
    return false;
}

bool Operation::is_operand(char c)
{
    if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9') {
        return true;
    }
    return false;
}
