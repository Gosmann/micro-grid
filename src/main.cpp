#include <iostream>
#include <algorithm>
#include <random>

#include "micro-grid.hpp"

std::random_device rd;
std::mt19937 g(rd());
 
int main(){

    micro_grid_t m1 ;

    double best_cost = m1.simulate() ;

    std::cout << best_cost << " : " ;
    m1.houses[0].print_load_var() ;

    int i, j, k;
    
    // random shuffle
    
    for( i = 0 ; i < 1e6 ; i++ ){
        
        std::uniform_int_distribution<int> uni( 0 , m1.houses.size() - 1 ); 

        int index = uni( g );   // gets random house index

        // random shuffle
        micro_grid_t m1_copy = m1 ; 

        std::shuffle(m1.houses[index].load_var.begin(), m1.houses[index].load_var.end(), g);

        for( j = 1 ; j < m1.houses.size() ; j++ ){
            //m1.houses[j].load_var = m1.houses[0].load_var ;
        }

        double cost = m1.simulate() ;

        if( cost < best_cost ){
            best_cost = cost ;

            char buffer[100] ;
            sprintf(buffer, "%8.2f", best_cost) ;

            std::cout << buffer << " " << k << " : " ;
            m1.houses[index].print_load_var() ;
        }

        else{
            m1 = m1_copy ;
        }

    }
    

    // shift right   
    /*
    for( k = 0 ; k < m1.houses.size() ; k++ ){

        for( i = 0 ; i < NUM_OF_INTERVALS ; i++ ){
        
            // time-shift
            std::rotate(m1.houses[k].load_var.rbegin(), m1.houses[k].load_var.rbegin() + 1, 
                m1.houses[k].load_var.rend());

            // std::shuffle(m1.houses[0].load_var.begin(), m1.houses[0].load_var.end(), g);

            for( j = 1 ; j < m1.houses.size() ; j++ ){
                // m1.houses[j].load_var = m1.houses[0].load_var ;
            }

            double cost = m1.simulate() ;

            if( cost < best_cost ){
                best_cost = cost ;

                char buffer[100] ;
                sprintf(buffer, "%8.2f", best_cost) ;

                std::cout << buffer << " " << k << " : " ;
                m1.houses[k].print_load_var() ;
    
            }
            else{
                //std::cout << cost << " : " ;
                //m1.houses[0].print_load_var() ;
            }
            
        }
    
    }
    */

    // greedy-random swap
    /*
    for( i = 0 ; i < 10e6 ; i++ ){
        
        // random shuffle
        // std::shuffle(m1.houses[0].load_var.begin(), m1.houses[0].load_var.end(), g);

        std::uniform_int_distribution<int> uni( 0 , m1.houses.size() - 1 ); 

        int index = uni( g );   // gets random house index

        std::uniform_int_distribution<int> uni2( 0 , NUM_OF_INTERVALS - 1 ); 
        // gets random time 

        int t1 = uni2( g );  
        int t2 = uni2( g );  

        // std::cout << index << " " << t1 << " " << t2 << " \n" ;

        std::iter_swap( m1.houses[index].load_var.begin() + t1, m1.houses[index].load_var.begin() + t2 );
        
        for( j = 1 ; j < m1.houses.size() ; j++ ){
            // m1.houses[j].load_var = m1.houses[0].load_var ;
        }

        double cost = m1.simulate() ;

        if( cost < best_cost ){
            best_cost = cost ;

            char buffer[100] ;
            sprintf(buffer, "%8.2f", best_cost) ;

            std::cout << buffer << " " << index << " : " ;
            m1.houses[index].print_load_var() ;
        }
        else{
            std::iter_swap( m1.houses[index].load_var.begin() + t1, m1.houses[index].load_var.begin() + t2 );
        }
        
    }
    */
    
    
    


    return 0;
}