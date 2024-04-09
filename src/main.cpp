#include <iostream>

#include "micro-grid.hpp"

int main(){

    house_t h1 ( 0 );
    
    h1.load_fix[10] = 1 ;
    h1.load_var[10] = 2 ;
    h1.gen_pv[10] = 3 ;

    h1.print_vector( h1.load_fix ) ; 
    h1.print_vector( h1.load_var ) ; 
    h1.print_vector( h1.gen_pv ) ; 

    return 0;

}