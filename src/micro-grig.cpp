#include "micro-grid.hpp"
#include <cmath>

// constructos for house_t

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

house_t::house_t( int house_num, int num_of_pvs, double coeff ){
    int i; 

    load_var = std::vector<double> ( 0, 0 ) ;
    load_fix = std::vector<double> ( 0, 0 ) ;
    gen_pv = std::vector<double> ( 0, 0 ) ;
    
    
    // check for plausible values in house_num, must be [0, 14]
    if( house_num >= NUM_OF_HOUSES || house_num < 0 ){
        std::cout << "house_num out of bounds \n";
        house_num = 0 ;
    }
    
    if( num_of_pvs < 0 ){
        std::cout << "num_of_pvs must not be negative \n";
        num_of_pvs = 0 ;
    }

    std::string read_line ;
    
    std::ifstream houses_file ( HOUSES_FILE ) ;
    int line_count = 0 ;  
    
    // reads house data
    if ( houses_file.is_open() ){
        while ( getline ( houses_file , read_line ) ) {
            
            int i_start = 0 ;       // i_start
            int i_end = 0 ;         // i_end
 
            if( line_count >= 1 ){    // does not consider first line

                for(i = 0 ; i < house_num ; i++ ){
                    i_start = read_line.find( DELIMITER, i_start ) ;
                    i_start++;
                }              
            
                if( house_num >= NUM_OF_HOUSES ){
                    i_end = read_line.find( "\n", 0 ) ;
                }
                else{
                    i_end = read_line.find( DELIMITER, i_start + 1 ) ;
                }

                std::string value = read_line.substr(i_start , i_end - i_start - 1 ); 

                load_fix.push_back( stod(value) ) ;

                // std::cout << value << '\n';

            }

            line_count++ ;

        }
        houses_file.close();
    }
    else{
        std::cout << "unable to open file \n";
    } 

    std::ifstream pv_file ( PV_FILE ) ;
    line_count = 0 ;  
    
    // reads pv data
    if ( pv_file.is_open() ){
        while ( getline ( pv_file , read_line ) ) {
            
            int i_start = 0 ;       // i_start
            int i_end = 0 ;         // i_end
 
            if( line_count >= 1 ){    // does not consider first line

                for(i = 0 ; i < 1 ; i++ ){
                    i_start = read_line.find( DELIMITER, i_start ) ;
                    i_start++;
                }              
            
                if( house_num >= NUM_OF_HOUSES ){
                    i_end = read_line.find( "\n", 0 ) ;
                }
                else{
                    i_end = read_line.find( DELIMITER, i_start + 1 ) ;
                }

                std::string value = read_line.substr(i_start , i_end - i_start - 1 ); 

                gen_pv.push_back( stod(value) * num_of_pvs ) ;               

            }

            line_count++ ;

        }
        houses_file.close();

    }
    else{
        std::cout << "unable to open file \n";
    } 

    // creates load.var data
    double average_power = 524.569 ;   // average power cons. of the average house 
    
    load_var_num = 16 ;                // must be on 8h per day
    
    //double coeff = 0.25 ;              // energy of load_var with respect to load_fix

    load_var_power = ( NUM_OF_INTERVALS / load_var_num ) * average_power * coeff ;

    for( i = 0 ; i < load_var_num ; i++ ){
        load_var.push_back( load_var_power ) ;
    }
    for( i = load_var_num ; i < NUM_OF_INTERVALS ; i++ ){
        load_var.push_back( 0.0 ) ;
    }
    
}

void house_t::print_vector( std::vector<double> vector ){
    int i;
    
    for( i = 0 ; i < vector.size() ; i++ ){
        std::cout << "[" << vector[i] << "]" ; 
    }
    std::cout << "\n" ; 

}

void house_t::print_load_var( void ){
    int i;

    std::cout << "load_var: [" ;
    for( i = 0 ; i < NUM_OF_INTERVALS ; i++ ){
        if( load_var[i] == 0 ){
            std::cout << "⌷" ;
        }
        else{
            std::cout << "∎" ;
        }
    }
    std::cout << "]\n" ;


}

// constructors for microgrid_t

micro_grid_t::micro_grid_t( void ){

    alfa = 1.0 ;
    beta = 3.0 ;

    houses.push_back( house_t( 0, 2, 0.25 ) ) ;
    houses.push_back( house_t( 1, 2, 0.25 ) ) ;
    houses.push_back( house_t( 2, 1, 0.25 ) ) ;
    houses.push_back( house_t( 3, 1, 0.25 ) ) ;
    houses.push_back( house_t( 4, 0, 0.25 ) ) ;
    houses.push_back( house_t( 5, 0, 0.25 ) ) ;

}

double micro_grid_t::simulate( void ){
    int i, j;
    double cost = 0 ;

    for( i = 0 ; i < NUM_OF_INTERVALS ; i++ ){      // iterates over NUM_OF_INTERVALS

        double national_power = 0 ;

        for( j = 0 ; j < houses.size() ; j++ ){     // iterates over size of houses
            national_power += houses[j].load_fix[i] + houses[j].load_var[i] - houses[j].gen_pv[i] ;
        }

        if( national_power > 0 ){   // energy national-grid -> micro-grid
            cost += beta * (national_power * national_power ) ;
        }
        else{                       // // energy micro-grid -> national-grid
            cost += alfa * (national_power * national_power ) ;
        }

    }

    return std::sqrt(cost) ;
}
