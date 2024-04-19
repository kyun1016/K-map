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

KMap::KMap(const KMap* ref)
	: mDim(ref->mDim)
	, mMaps(ref->mMaps)
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
	for (const auto& val : mMaps)
	{
		if (value == val)
			return true;
	}
	return false;
}

void KMap::CalckarnaughMap() const
{
	std::vector<int> ret;
	std::vector<int> visited(mMaps);

	for (int i = 1; i <= mDim; i++)
	{
		std::vector<bool> v(mDim - i, false);
		v.insert(v.end(), i, true);

		std::cout << i << std::endl;
		do {
			int mask = 0;
			for (int j = 0; j < mDim; j++) {
				if (v[j])
					mask += (1 << j);
			}
			for (int j = 0; j < (1 << mDim); ++j) {
				int temp = mask & j;
				if (temp == mask)
				{
					std::cout << j << std::endl;
				}
			}

			
			

		} while (std::next_permutation(v.begin(), v.end()));


	}




}

void KMap::PrintDim() const
{
	std::cout << mDim << std::endl;
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

void KMap::PrintKMap() const
{
}



int KMap::GetDim() const
{
	return mDim;
}

std::vector<int> KMap::GetMap() const
{
	return mMaps;
}

void KMap::SetDim(const int& dim)
{
	mDim = dim;
}

void KMap::SetMap(const std::vector<int>& map)
{
	mMaps = map;
}

void KMap::SetMap(const std::initializer_list<int>& list)
{
	mMaps = list;
}
