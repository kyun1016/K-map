﻿#include "KMap.h"

int main()
{
    // max 32bit
    KMap* map1 = new KMap(9, { 1,3,5,7,10,12,14,15,16,17,18,19,19,19,24,28,32,34,36,38,39,40,44,45,48,50,53,57,58,61,62,64,67,70,73,76,76,76,79,79,84,88,91,92,97,98,99,99,102,108,108,109,110,116,116,116,118,119,119,119,121,121,123,124,124,127,128,129,129,130,133,139,140,141,147,148,150,152,152,152,156,158,158,160,161,162,162,164,169,175,179,180,189,190,193,196,197,197,202,207,207,209,213,216,216,221,228,228,231,234,238,240,246,248,251,251,254,255,256,256,259,261,263,265,267,268,269,271,273,273,274,277,277,277,281,281,281,285,286,286,289,290,291,292,292,298,299,302,306,306,309,310,311,313,314,314,316,318,320,320,324,325,327,328,328,329,333,335,336,339,339,340,340,341,345,346,347,349,352,352,352,356,356,357,360,360,363,372,373,373,374,381,387,394,395,397,403,404,406,408,411,411,412,417,417,418,418,418,419,422,423,424,426,427,431,431,432,432,434,437,438,439,447,448,449,450,450,450,453,454,458,459,464,467,467,469,470,475,479,483,485,487,490,491,491,494,496,498,502,502,503,507,509,511 });
    // KMap* map1 = new KMap(5, { 1,3,5,7,8,10,14,20,21,22,23,24 });
    // KMap* map1 = new KMap(5, { 1,3,5,7});
    // KMap* map1 = new KMap(5, {20, 24 });
    // KMap* map1 = new KMap(5, { 8,24 });

    std::cout << "================================================" << std::endl;
    std::cout << "Step1. Check Make Gray List Logic" << std::endl;
    std::cout << "================================================" << std::endl;
    std::vector<int> grayList = map1->FindGrayList({ 2,2,2,1,2 });
    for (const auto& a : grayList)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Step2. Set Pre/In/Suffix Logic" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Default KarnaughMapNode: " << std::endl;
    map1->PrintKarnaughMapNode();
    std::cout << std::endl;

    //map1->SetPrefix("happy[");
    //map1->SetInfix({ "1", "2", "3", "4", "5" });
    //map1->SetSuffix("]");

    //std::cout << "Setting KarnaughMapNode: " << std::endl;
    //map1->PrintKarnaughMapNode();

    std::cout << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Step3. Check Default Value" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "X: ";
    map1->PrintX();
    std::cout << std::endl;
    std::cout << "Y: ";
    map1->PrintY();
    std::cout << std::endl;
    std::cout << "Dimension: ";
    map1->PrintDim();
    std::cout << std::endl;
    std::cout << "Map: " << std::endl;
    map1->PrintMap();
    std::cout << std::endl;
    std::cout << "KarnaughMapNode: " << std::endl;
    map1->PrintKarnaughMapNode();
    std::cout << std::endl;
    std::cout << "KarnaughMap: " << std::endl;
    map1->PrintKarnaughMap();
    std::cout << std::endl;

    return 0;
}