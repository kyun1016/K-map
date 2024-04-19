#include "KMap.h"

int main()
{
    // max 32bit
    KMap* map = new KMap(4, { 0,1,2,3,4 });

    KMap* map2 = new KMap(map);
    map2->SetMap({ 1,2,3,4,5,6 });

    map->PrintMap();
    map2->PrintMap();

    map2->CalckarnaughMap();

    return 0;
}