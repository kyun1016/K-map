#include "KMap.h"

int main()
{
    KMap* map = new KMap(5, { 0,1,2,3,4 });

    KMap* map2 = new KMap(map);
    map2->SetMap({ 1,2,3,4,5,6 });

    map->PrintMap();
    map2->PrintMap();

    return 0;
}