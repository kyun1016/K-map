#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>

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
	std::pair<bool, int> CheckBox(const std::vector<std::vector<int>>& visited, const int& posY, const int posX, const int& lenY, const int& lenX, const int& dir) const;
	void UpdateVisited(std::vector<std::vector<int>>& visited, const int& posY, const int posX, const int& lenY, const int& lenX, const int& dir) const;
	
	void FindXY();
	void FindSelectList();
	void FindMap();
	void FindkarnaughMap();
	void FindkarnaughMapGUI();
	void PrintX() const;
	void PrintY() const;
	void PrintDim() const;
	void PrintList() const;
	void PrintMap() const;
	void PrintKMap() const;
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
};

