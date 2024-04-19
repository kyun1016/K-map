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