#include <iostream>
#include <algorithm>
#include <random>

#include "micro-grid.hpp"

std::random_device rd;
std::mt19937 g(rd());

void greedy_random_swap( micro_grid_t &m1, int epochs );

void random_shuffle( micro_grid_t &m1, int epochs ){

    int i, j, k; 

    // start from prev
    
    // start random
    for ( i = 0 ; i < m1.houses.size() ; i++)
        std::shuffle(m1.houses[i].load_var.begin(), m1.houses[i].load_var.end(), g);

    double best_cost = m1.simulate() ;

    for( i = 0 ; i < epochs ; i++ ){
        
        std::uniform_int_distribution<int> uni( 0 , m1.houses.size() - 1 ); 

        int index = uni( g );   // gets random house index
        //int index = 0 ;

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

            std::cout << buffer << " " << index << " : " ;
            m1.houses[index].print_load_var() ;
        }

        else{
            m1 = m1_copy ;
        }

    }
}

void shift_right( micro_grid_t& m1, int epochs );

int main(){
    int i;

    micro_grid_t m1 ;

    double best_cost = m1.simulate() ;

    std::cout << best_cost << "\n" ;

    for ( i = 0 ; i < m1.houses.size() ; i++)
        m1.houses[i].print_load_var() ;

    // random shuffle
    //random_shuffle( m1, 0 );

    // shift right   
    shift_right( m1, 48);
    
    // greedy-random swap
    //greedy_random_swap( m1, 1e5 ) ;


    m1.save_cost( "../micro-grid/data/m1_cost_best.csv" ) ; 
    
    std::cout << "final result : \n" ;
    std::cout << m1.simulate() << "\n" ;
    for ( i = 0 ; i < m1.houses.size() ; i++)
        m1.houses[i].print_load_var() ;
    
    
    


    return 0;
}


void greedy_random_swap( micro_grid_t &m1, int epochs ){
    
    int i, j, k;

    double best_cost = m1.simulate() ;

    for( i = 0 ; i < epochs ; i++ ){
        
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

}

void shift_right( micro_grid_t& m1, int epochs=NUM_OF_INTERVALS ){

    int i, j, k;

    double best_cost = m1.simulate() ;

    micro_grid_t m1_best = m1 ;

    for( k = 0 ; k < 1 ; k++ ){
    //for( k = 0 ; k < m1.houses.size() ; k++ ){

        for( i = 0 ; i < epochs ; i++ ){
        
            // time-shift
            std::rotate(m1.houses[k].load_var.rbegin(), m1.houses[k].load_var.rbegin() + 1, 
                m1.houses[k].load_var.rend());

            // std::shuffle(m1.houses[0].load_var.begin(), m1.houses[0].load_var.end(), g);

            for( j = 1 ; j < m1.houses.size() ; j++ ){
                m1.houses[j].load_var = m1.houses[0].load_var ;
            }

            double cost = m1.simulate() ;

            if( cost < best_cost ){
                m1_best = m1 ;
                best_cost = cost ;

                char buffer[100] ;
                sprintf(buffer, "%8.2f", best_cost) ;

                std::cout << buffer << " " << k << " : " ;
                m1.houses[k].print_load_var() ;
    
            }
            else{
                
            }
            
        }
    }

    m1 = m1_best ;

}


