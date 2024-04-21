#include "KMap.h"

KMap::KMap()
	: mDim(0)
	, mMaxX(0)
	, mMaxY(0)
	, mSelectList(std::vector<int>())
	, mMap(std::vector<std::vector<int>>())
	, mKarMap(std::vector<std::vector<int>>())
{
}

KMap::KMap(const int& dim)
	: mDim(dim)
	, mSelectList(std::vector<int>())
	, mKarMap(std::vector<std::vector<int>>())
{
	Init();
}

KMap::KMap(const int& dim, const std::initializer_list<int>& list)
	: mDim(dim)
	, mSelectList(list)
	, mKarMap(std::vector<std::vector<int>>())
{
	Init();
}

KMap::KMap(const int& dim, const std::vector<int>& list)
	: mDim(dim)
	, mSelectList(list)
	, mKarMap(std::vector<std::vector<int>>())
{
	Init();
}

KMap::KMap(const KMap& ref)
	: mDim(ref.mDim)
	, mMaxX(ref.mMaxX)
	, mMaxY(ref.mMaxY)
	, mSelectList(ref.mSelectList)
	, mMap(ref.mMap)
	, mKarMap(ref.mKarMap)
{
}

KMap::KMap(const KMap* ref)
	: mDim(ref->mDim)
	, mMaxX(ref->mMaxX)
	, mMaxY(ref->mMaxY)
	, mSelectList(ref->mSelectList)
	, mMap(ref->mMap)
	, mKarMap(ref->mKarMap)
{
}

KMap& KMap::operator=(KMap& ref)
{
	if (this == &ref)
	{
		return *this;
	}

	mDim = ref.mDim;
	mMaxX = ref.mMaxX;
	mMaxY = ref.mMaxY;
	mSelectList = ref.mSelectList;
	Init();

	return *this;
}

KMap& KMap::operator=(KMap* ref)
{
	if (this == ref)
	{
		return *this;
	}

	mDim = ref->mDim;
	mMaxX = ref->mMaxX;
	mMaxY = ref->mMaxY;
	mSelectList = ref->mSelectList;
	Init();

	return *this;
}

void KMap::Init()
{
	FindXY();
	FindSelectList();
	FindMap();
	FindkarnaughMap();
	FindkarnaughMapGUI();
}

int KMap::GrayEncode(const int& num) const
{
	return num ^ (num >> 1);
}

std::pair<bool, int> KMap::CheckBox(const std::vector<std::vector<int>>& visited, const int& posY, const int posX, const int& lenY, const int& lenX, const int& dir) const
{
	if (mMaxY < (1 << lenY))
		return { false, 0 };
	if (mMaxX < (1 << lenX))
		return { false, 0 };

	int ret = 0;
	for (int i = 0; i < (1 << lenY); ++i)
	{
		int y = posY + i * dirY[dir] + mMaxY;
		y %= mMaxY;
		for (int j = 0; j < (1 << lenX); ++j)
		{
			int x = posX + j * dirX[dir] + mMaxX;
			x %= mMaxX;
			if (visited[y][x] != 0)
				ret++;

			if (!mMap[y][x])
				return { false, 0 };
		}
	}
	return { true, ret };
}

void KMap::UpdateVisited(std::vector<std::vector<int>>& visited, const int& posY, const int posX, const int& lenY, const int& lenX, const int& dir) const
{
	if (dir > 3)
		return;
	for (int i = 0; i < (1 << lenY); ++i)
	{
		int y = posY + i * dirY[dir] + mMaxY;
		y %= mMaxY;
		for (int j = 0; j < (1 << lenX); ++j)
		{
			int x = posX + j * dirX[dir] + mMaxX;
			x %= mMaxX;
			visited[y][x] = 0;
		}
	}
}

void KMap::FindXY()
{
	mMaxX = 1 << ((1 + mDim) / 2);
	mMaxY = 1 << (mDim / 2);
	mMap = std::vector<std::vector<int>>(mMaxY, std::vector<int>(mMaxX, 0));
	mKarMapGUI = std::vector<std::vector<int>>(mMaxY, std::vector<int>(mMaxX, 0));
}

void KMap::FindSelectList()
{
	std::sort(mSelectList.begin(), mSelectList.end());

	while (!mSelectList.empty() && mSelectList.back() >= mMaxX * mMaxY) {
		mSelectList.pop_back();
	}
}

void KMap::FindMap()
{
	for (int y = 0; y < mMaxY; ++y)
	{
		for (int x = 0; x < mMaxX; ++x)
		{
			int num = x + y * mMaxX;
			mMap[y][x] = 0;
			for (const auto& a : mSelectList)
			{
				if (a == GrayEncode(num))
				{
					mMap[y][x] = 1;
				}
			}
		}
	}
}

void KMap::FindkarnaughMap()
{
	std::vector<std::vector<int>> visited(mMap);
	std::queue<std::pair<int, int>> qu;

	for (int y = 0; y < mMaxY; ++y)
	{
		for (int x = 0; x < mMaxX; ++x)
		{
			if (mMap[y][x])
				qu.push({ y,x });
		}
	}


	while (!qu.empty()) {
		std::pair<int, int> pos = qu.front();
		qu.pop();

		if (visited[pos.first][pos.second] == 0)
			continue;

		for (int i = mDim; i >= 0; --i)
		{
			for (int j = 0; j <= i; ++j)
			{
				int lenX = j;
				int lenY = i - j;
				// std::cout << "[" << pos.first << "," << pos.second << "]: " << i << ", " << lenY << "," << lenX << std::endl;
				std::pair<bool, int> ret0 = CheckBox(visited, pos.first, pos.second, lenY, lenX, 0);
				std::pair<bool, int> ret1 = CheckBox(visited, pos.first, pos.second, lenY, lenX, 1);
				std::pair<bool, int> ret2 = CheckBox(visited, pos.first, pos.second, lenY, lenX, 2);
				std::pair<bool, int> ret3 = CheckBox(visited, pos.first, pos.second, lenY, lenX, 3);

				// std::cout << ret0.first << " " << ret1.first << " " << ret2.first << " " << ret3.first << " " << std::endl;
				// std::cout << ret0.second << " " << ret1.second << " " << ret2.second << " " << ret3.second << " " << std::endl;
				int flag = 5;
				int maxValue = 0;
				if (ret3.first && maxValue <= ret3.second)
				{
					flag = 3;
					maxValue = ret3.second;
				}
				if (ret2.first && maxValue <= ret2.second)
				{
					flag = 2;
					maxValue = ret2.second;
				}
				if (ret1.first && maxValue <= ret1.second)
				{
					flag = 1;
					maxValue = ret1.second;
				}
				if (ret0.first && maxValue <= ret0.second)
				{
					flag = 0;
					maxValue = ret0.second;
				}

				if (maxValue > 0) {
					// std::cout << ret0.second << " " << ret1.second << " " << ret2.second << " " << ret3.second << " " << std::endl;
					UpdateVisited(visited, pos.first, pos.second, lenY, lenX, flag);
				}

				if (flag != 5 && maxValue > 0)
				{
					mKarMap.push_back({ pos.first, pos.second, lenY, lenX, flag });
				}
			}
		}
	}
}

void KMap::FindkarnaughMapGUI()
{
	for (int pos = 0; pos < mKarMap.size(); ++pos) {
		int posY = mKarMap[pos][0];
		int posX = mKarMap[pos][1];
		int lenY = mKarMap[pos][2];
		int lenX = mKarMap[pos][3];
		int dir = mKarMap[pos][4];
		for (int i = 0; i < (1 << lenY); ++i)
		{
			int y = posY + i * dirY[dir] + mMaxY;
			y %= mMaxY;
			for (int j = 0; j < (1 << lenX); ++j)
			{
				int x = posX + j * dirX[dir] + mMaxX;
				x %= mMaxX;
				mKarMapGUI[y][x] += pos;
			}
		}
	}
}

void KMap::PrintX() const
{
	std::cout << mMaxX << std::endl;
}

void KMap::PrintY() const
{
	std::cout << mMaxY << std::endl;
}

void KMap::PrintDim() const
{
	std::cout << mDim << std::endl;
}

void KMap::PrintList() const
{
	for (const auto& a : mSelectList)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
}

void KMap::PrintMap() const
{
	for (int y = 0; y < mMaxY; ++y)
	{
		for (int x = 0; x < mMaxX; ++x)
		{
			std::cout << mMap[y][x] << " ";
		}
		std::cout << std::endl;
	}
}

void KMap::PrintKMap() const
{
	for (auto& a : mKarMap)
	{
		for (auto& b : a)
		{
			std::cout << b << " ";
		}
		std::cout << std::endl;
	}
}

void KMap::PrintKarnaughMap() const
{
	int a = mKarMap.size();
	int size = 0;
	while (a > 0) {
		a /= 10;
		++size;
	}
		
	for (int y = 0; y < mMaxY; ++y)
	{
		for (int x = 0; x < mMaxX; ++x)
		{
			std::cout.width(size);
			std::cout << mKarMapGUI[y][x] << " ";
		}
		std::cout << std::endl;
	}
}



int KMap::GetDim() const
{
	return mDim;
}

std::vector<int> KMap::GetList() const
{
	return mSelectList;
}

std::vector<std::vector<int>> KMap::GetMap() const
{
	return std::vector<std::vector<int>>();
}

std::vector<std::vector<int>> KMap::GetKarnaughMap() const
{
	return std::vector<std::vector<int>>();
}

void KMap::SetDim(const int& dim)
{
	mDim = dim;
	Init();
}

void KMap::SetList(const std::vector<int>& list)
{
	mSelectList = list;
	Init();
}

void KMap::SetList(const std::initializer_list<int>& list)
{
	mSelectList = list;
	Init();
}
