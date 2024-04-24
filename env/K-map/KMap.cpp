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
	FindKarnaughMap();
}

int KMap::GrayEncode(const int& num) const
{
	return num ^ (num >> 1);
}

int KMap::GrayDecode(const int& num) const
{
	int ret = num;
	for (int bit = 1 << 30; bit > 1; bit >>= 1)
	{
		if (ret & bit) ret ^= bit >> 1;
	}

	return ret;
}

std::vector<int> KMap::FindGrayList(const std::vector<int>& node) const
{
	std::vector<std::vector<int>> grayList;
	grayList.push_back(node);


	for (int i = 0; i < grayList.size(); ++i)
	{
		for (int j = 0; j < grayList[i].size(); ++j)
		{
			if (grayList[i][j] == 2)
			{
				grayList.push_back(grayList[i]);
				grayList[i][j] = 0;
				grayList[grayList.size() - 1][j] = 1;
			}
		}
	}

	std::vector<int> ret;
	for (const auto& numArray : grayList)
	{
		int gray = 0;
		for (const auto& num : numArray)
		{
			gray = gray * 2 + num;
		}
		ret.push_back(gray);
	}

	return ret;
}

std::vector<int> KMap::FindGrayList(const std::initializer_list<int>& node) const
{
	return FindGrayList(std::vector<int>(node));
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

void KMap::FindKarnaughMap()
{
	std::vector<std::vector<int>> visited(mMap);
	std::vector<int> node(mDim);

	for (int i = 0; i <= mDim; i++)
	{
		std::vector<bool> v(mDim - i, false);
		v.insert(v.end(), i, true);
		for (int j = 0; j < (1 << i); ++j)
		{
			do {
				int order = 0;
				for (int k = 0; k < mDim; k++) {
					if (v[k])
						node[k] = (j >> order++) % 2;
					else
						node[k] = 2;
				}

				std::vector<int> grayList = FindGrayList(node);

				int cnt = 0;
				bool flag = true;
				for (int k = 0; k < grayList.size(); ++k)
				{
					int num = GrayDecode(grayList[k]);
					int x = num % mMaxX;
					int y = num / mMaxX;

					if (mMap[y][x] == 0)
					{
						flag = false;
						break;
					}
					if (visited[y][x] != 0)
					{
						++cnt;
					}
				}

				if (flag && cnt > 0)
				{
					mKarMap.push_back(node);
					for (int k = 0; k < grayList.size(); ++k)
					{
						int num = GrayDecode(grayList[k]);
						int x = num % mMaxX;
						int y = num / mMaxX;
						visited[y][x] = 0;
						mKarMapGUI[y][x] = mKarMap.size();
					}
				}
			} while (std::next_permutation(v.begin(), v.end()));
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

void KMap::PrintKarnaughMapNode() const
{
	for (int i = 0; i < mKarMap.size(); ++i)
	{
		for (int j = 0; j < mKarMap[i].size(); ++j)
		{
			if (mKarMap[i][j] == 2)
				continue;
			if (mKarMap[i][j] == 0)
				std::cout << "!";
			std::cout << mPrefix << j << mSuffix;
			/*if (j != mKarMap[i].size() - 1)
				std::cout << " & ";*/
		}
		if (i != mKarMap.size() - 1)
			std::cout << " + ";
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
