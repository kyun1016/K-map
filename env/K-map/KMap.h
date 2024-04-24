#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>

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
	int GrayDecode(const int& num) const;
	std::vector<int> FindGrayList(const std::vector<int>& node) const;
	std::vector<int> FindGrayList(const std::initializer_list<int>& node) const;
	
	void FindXY();
	void FindSelectList();
	void FindMap();
	void FindKarnaughMap();
	void PrintX() const;
	void PrintY() const;
	void PrintDim() const;
	void PrintList() const;
	void PrintMap() const;
	void PrintKMap() const;
	void PrintKarnaughMapNode() const;
	void PrintKarnaughMap() const;
	int GetDim() const;
	std::vector<int> GetList() const;
	std::vector<std::vector<int>> GetMap() const;
	std::vector<std::vector<int>> GetKarnaughMap() const;

	void SetDim(const int& dim);
	void SetList(const std::vector<int>& list);
	void SetList(const std::initializer_list<int>& list);

private:
	const int dirX[4] = { 1, 1, -1, -1 };
	const int dirY[4] = { 1, -1, 1, -1 };
	int mDim;
	int mMaxX;
	int mMaxY;
	std::vector<int> mSelectList;
	std::vector<std::vector<int>> mMap;
	std::vector<std::vector<int>> mKarMap;
	std::vector<std::vector<int>> mKarMapGUI;

	std::string mPrefix = "a[";
	std::string mSuffix = "]";
};

