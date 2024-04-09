#include <vector>
#include <iostream>

#define NUM_OF_INTERVALS 48     // one day is composed of 24 hours
                                // so here, each interval lasts 30min


/*
class micro_grid {

} ;
*/

class house_t {

    public:

        std::vector<double> load_var ;
        std::vector<double> load_fix ;
        std::vector<double> gen_pv ;

        void print_vector( std::vector<double> ) ;
        
        house_t( double ) ;                           // constructor with init to double
        house_t( void ) ;                             // constructor with no init ( init to zero ) 
} ;