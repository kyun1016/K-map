#include "KMap.h"

KMap::KMap()
	: mDim(0)
	, mMaps(std::vector<int>())
{
}

KMap::KMap(const int& dim)
	: mDim(dim)
	, mMaps(std::vector<int>())
{
}

KMap::KMap(const int& dim, const std::initializer_list<int>& list)
	: mDim(dim)
	, mMaps(list)
{
}

KMap::KMap(const int& dim, const std::vector<int>& mMaps)
	: mDim(dim)
	, mMaps(mMaps)
{
}

KMap::KMap(const KMap& ref)
	: mDim(ref.mDim)
	, mMaps(ref.mMaps)
{
}

KMap& KMap::operator=(KMap& ref)
{
	if (this == &ref)
	{
		return *this;
	}

	mDim = ref.mDim;
	mMaps = ref.mMaps;
	
	return *this;
}

KMap& KMap::operator=(KMap* ref)
{
	if (this == ref)
	{
		return *this;
	}

	mDim = ref->mDim;
	mMaps = ref->mMaps;

	return *this;
}

bool KMap::CheckValue(const int& value) const
{
	for (auto& val : mMaps)
	{
		if (value == val)
			return true;
	}
	return false;
}

void KMap::PrintMap() const
{
	for (int y = 0; y < (1 << mDim / 2); ++y)
	{
		for (int x = 0; x < (1 << ((mDim + 1) / 2)); ++x)
		{
			int num = x + y * (1 << ((mDim + 1) / 2));
			if (CheckValue(num))
				std::cout << "1 ";
			else
				std::cout << "0 ";
		}
		std::cout << std::endl;
	}
}
