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
}

int KMap::GrayEncode(const int& num) const
{
	return num ^ (num >> 1);
}

bool KMap::CheckBox(const int& posY, const int posX, const int& lenY, const int& lenX) const
{
	if (mMaxY > (1 << lenY))
		return false;
	if (mMaxX > (1 << lenX))
		return false;

	for (int i = 0; i < (1 << lenY); ++i)
	{
		int y = posY + i;
		y %= mMaxY;
		for (int j = 0; j < (1 << lenX); ++j)
		{
			int x = posX + j;
			x %= mMaxX;

			if (!mMap[y][x])
				return false;
		}
	}
	return true;
}

void KMap::FindXY()
{
	mMaxX = 1 << ((1 + mDim) / 2);
	mMaxY = 1 << (mDim / 2);
	mMap = std::vector<std::vector<int>>(mMaxY, std::vector<int>(mMaxX, 0));
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
	std::vector<std::vector<int>> checked(mMap);
	for (int i = 0; i <= mDim; ++i)
	{
		for (int y = 0; y < mMaxY; ++y)
		{
			for (int x = 0; x < mMaxX; ++x)
			{

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
