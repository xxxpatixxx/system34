
#include <iostream>
#include "header/Game.h"



int main()
{
    //init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    //init game engine
    
 
    
    

   
    
    
            
           Game game;
           //Game loo
           while(game.running() && !game.getEndGame())
           {
               //Updat
               game.update();
               //Render
               game.render();
           }
           
         



          


        
        
            
        
    
           
            
        
      
        
       

    
    //end
    
    return 0;
}