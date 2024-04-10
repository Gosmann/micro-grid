#include "micro-grid.hpp"

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

house_t::house_t( int house_num, int num_of_pvs ){

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

                int i;
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

                int i;
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
}

void house_t::print_vector( std::vector<double> vector ){
    int i;
    
    for( i = 0 ; i < vector.size() ; i++ ){
        std::cout << "[" << vector[i] << "]" ; 
    }
    std::cout << "\n" ; 

}


