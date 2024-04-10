#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#define NUM_OF_INTERVALS 48     // one day is composed of 24 hours
                                // so here, each interval lasts 30min

#define HOUSES_FILE "../micro-grid/houses.csv"
#define PV_FILE "../micro-grid/pv.csv"

#define DELIMITER ","

#define NUM_OF_HOUSES 15

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
        
        house_t( double ) ;              // constructor with init to double
        house_t( void ) ;                // constructor with no init ( init to zero ) 
        house_t( int , int) ;            // constructor with specified house profile and num of solar panels

} ;