
#include "gridworld_route.h"
#include "position.h"
#include <fstream>
#include <iostream>
using namespace GPS;


/* A B C D E
 * F G H I J
 * K L M N O
 * P Q R S T
 * U V W X Y
 */
int main(){

    std :: ofstream thefile;
    thefile.open("posOutOfBounds.XML");
    //1110000
    thefile << GridWorldRoute("HRMHW",GridWorld(Position(91,0),1110607.76,0.0)).toGPX();
    thefile.close();
    return 0;
}

