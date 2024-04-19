#pragma once
#include <vector>
#include <iostream>
class KMap
{
public:
	KMap();
	KMap(const int& dim);
	KMap(const int& dim, const std::initializer_list<int>& list);
	KMap(const int& dim, const std::vector<int>& mMaps);
	KMap(const KMap& ref);
	KMap(const KMap* ref);
	~KMap() = default;
	KMap& operator=(KMap& ref);
	KMap& operator=(KMap* ref);

	bool CheckValue(const int& value) const;
	void PrintMap() const;
	void PrintDim() const;
	int GetDim() const;
	std::vector<int> GetMap() const;

	void SetDim(const int& dim);
	void SetMap(const std::vector<int>& map);
	void SetMap(const std::initializer_list<int>& list);

private:
	int mDim;
	std::vector<int> mMaps;
};

