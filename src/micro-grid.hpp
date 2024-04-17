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

class house_t {

    public:

        std::vector<double> load_var ;
        std::vector<double> load_fix ;
        std::vector<double> gen_pv ;

        int load_var_num ;          // number of cicles (30 min) load_var must be on
        double load_var_power ;     // power it has during this period

        void print_vector( std::vector<double> ) ;
        void print_load_var( void ) ;
        
        house_t( double ) ;              // constructor with init to double
        house_t( void ) ;                // constructor with no init ( init to zero ) 
        house_t( int , int, double = 0.25 ) ;            // constructor with specified house profile and num of solar panels

} ;

class micro_grid_t {
    
    public : 
        
        double alfa ;
        double beta ;
        std::vector< house_t > houses ;

        micro_grid_t(  ) ;

        double simulate(  ) ;
        int save_cost( std::string ) ;

} ;