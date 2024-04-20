#include "KMap.h"

int main()
{
    // max 32bit
    KMap* map1 = new KMap(4, { 0,1,2,3,4 });

    std::cout << "Step1. Check Default Value" << std::endl;
    std::cout << "X: ";
    map1->PrintX();
    std::cout << "Y: ";
    map1->PrintY();
    std::cout << "Dimension: ";
    map1->PrintDim();
    std::cout << "Map: " << std::endl;
    map1->PrintMap();

    std::cout << "Step2. Check CheckBox Logic" << std::endl;
    std::cout << map1->CheckBox(0, 3, 0, 0) << std::endl;
    std::cout << map1->CheckBox(0, 0, 0, 1) << std::endl;
    std::cout << map1->CheckBox(0, 0, 0, 2) << std::endl;
    std::cout << map1->CheckBox(1, 0, 0, 2) << std::endl;
    std::cout << map1->CheckBox(1, 3, 0, 0) << std::endl;
    

    return 0;
}