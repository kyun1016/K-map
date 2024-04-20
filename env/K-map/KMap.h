#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>

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

	void Init();

	int GrayEncode(const int& num) const;
	bool CheckBox(const int& posY, const int posX, const int& lenY, const int& lenX) const;
	void FindXY();
	void FindSelectList();
	void FindMap();
	void FindkarnaughMap();
	void PrintX() const;
	void PrintY() const;
	void PrintDim() const;
	void PrintList() const;
	void PrintMap() const;
	void PrintKMap() const;
	int GetDim() const;
	std::vector<int> GetList() const;
	std::vector<std::vector<int>> GetMap() const;
	std::vector<std::vector<int>> GetKarnaughMap() const;

	void SetDim(const int& dim);
	void SetList(const std::vector<int>& list);
	void SetList(const std::initializer_list<int>& list);

private:
	int mDim;
	int mMaxX;
	int mMaxY;
	std::vector<int> mSelectList;
	std::vector<std::vector<int>> mMap;
	std::vector<std::vector<int>> mKarMap;
};

