#pragma once
/** UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
*			INGENIERIA SOFTWARE
*
*
* @author MYCKEL CHAMORRO
* @author JUAN GALLARDO
* @author ADRIAN PAEZ
* TEMA: Proyecto Unidad 2
* FECHA DE CREACION : 14 DE ENERO DE 2022
* FECHA DE MODIFICACION: 21 DE ENERO DE 2022
*/

#pragma once
#include <string>
using namespace std;
class mystring
{
public:

    /**
     * @brief extraer en cadena
     *
     * @return string
     */
    string substract(string, int, int);

    /**
     * @brief comparar strings
     *
     * @return true
     * @return false
     */
    bool is_equal(string, string);

    /**
     * @brief comprobar si es numero
     *
     * @return true
     * @return false
     */
    bool is_number(string);

};

string mystring::substract(string cad, int position_initial, int number_character)
{
    string cad_sub;
    int cont = 0;
    int cont_ch = 1;
    for (char& c : cad) {
        if (cont >= position_initial && cont < (position_initial + number_character)) {
            if (c == ' ') {
                cad_sub += " ";
            }
            else {
                cad_sub += c;
            }

        }
        cont++;

    }
    return cad_sub;
}

bool mystring::is_equal(string cad1, string cad2)
{
    if (cad1.length() != cad2.length()) {
        return false;
    }
    bool flag = false;
    int cont = 0;
    for (int i = 0; i < cad1.length(); i++) {
        if (substract(cad1, i, 1) == substract(cad2, i, 1)) {
            cont++;
        }
    }
    if (cont == cad1.length()) {
        flag = true;
    }
    return flag;
}

bool mystring::is_number(string cad)
{
    int points = 0;
    int charac = 0;
    int negative = 0;
    for (char& c : cad) {
        if (c == '.') {
            points++;
        }
        else if (c == '-') {
            negative++;
        }
        else if (c > '9' || c < '0') {
            charac++;
        }


    }
    if (points > 1) {
        return false;
    }
    if (negative > 1) {
        return false;
    }
    else if (negative == 1 && substract(cad, 0, 1) != "-") {
        return false;
    }
    if (negative == 1 && cad.length() == 1) {
        return false;
    }
    if (charac > 0) {
        return false;
    }
    return true;
}
