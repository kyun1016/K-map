#pragma once
#include <vector>
#include <iostream>
class KMap
{
public:
	KMap();
	KMap(const int& dim);
	KMap(const int& dim, const std::vector<int>& mMaps);
	KMap(const KMap& ref);
	~KMap() = default;
	KMap& operator=(KMap& ref);
	KMap& operator=(KMap* ref);


private:
	std::vector<int> mMaps;
	int mDim;
};

