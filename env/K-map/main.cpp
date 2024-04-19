#include "KMap.h"

int main()
{
    KMap* map = new KMap(5, { 0,1,2,3,4 });
    map->PrintMap();

    std::cout << "Hello World!\n";
}