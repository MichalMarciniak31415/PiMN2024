
#include <iostream>
#include "box.h"


int main() {
    Box b1(1,1,1);
    Box b2(3, 1, 2);
   
    std::cout <<"Volume is " << b1.volume() << std::endl;
    std::cout << "Volume is " << b2.volume() << std::endl;

}


