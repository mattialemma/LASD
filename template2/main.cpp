
// Mattia Lemma N86005170

#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"
#include <iostream>

int main() {
    int ris = 0;
    int ris2 = 0;

do{
    while(true) {
        std::cout << "\n\n Si prega di digitare il numero corrispondente al test da eseguire: \n"
                  << "  1) lasdtest.\n"
                  << "  2) mytest - Template 1 e 2.\n"
                  << " -> ";
            std::cin >> ris;


        switch(ris) {

        case 1:
            std::cout << " Esecizione di lasdtest() in corso...\n";
            lasdtest();
            break;

        case 2:
            std::cout << " Esecuzione di mytest() in corso...\n";
           mytest::mytest();
            break;

        default:
            std::cout << " Scelta non valida, inserire 1 o 2. Grazie mille.\n";
            continue;
        }
        break;  
    }

    std::cout << "\n Vuole tornare al menù principale? (1 per si, 0 per no) -> ";
        std::cin >> ris2;
} while(ris2 != 0);

    std::cout << " Fine esecuzione. Grazie mille da Mattia Lemma.\n";



    return 0;
}