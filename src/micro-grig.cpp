#include "micro-grid.hpp"

house_t::house_t( double val ){

    int i;

    house_t() ;

    load_var = std::vector<double> ( NUM_OF_INTERVALS, 0 ) ;
    load_fix = std::vector<double> ( NUM_OF_INTERVALS, 0 ) ;
    gen_pv = std::vector<double> ( NUM_OF_INTERVALS, 0 ) ;

    for(i = 0 ; i < NUM_OF_INTERVALS ; i++ ){
        load_var[i] = val ;
        load_fix[i] = val ;
        gen_pv[i] = val ;
    }
   
}

house_t::house_t( void ){
    load_var = std::vector<double> ( NUM_OF_INTERVALS, 0 ) ;
    load_fix = std::vector<double> ( NUM_OF_INTERVALS, 0 ) ;
    gen_pv = std::vector<double> ( NUM_OF_INTERVALS, 0 ) ;
}

void house_t::print_vector( std::vector<double> vector ){
    int i;
    
    for( i = 0 ; i < vector.size() ; i++ ){
        std::cout << "[" << vector[i] << "]" ; 
    }
    std::cout << "\n" ; 

}
