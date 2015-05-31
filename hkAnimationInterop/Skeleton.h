#pragma once

#include <strsafe.h>
#include <objbase.h>

#include "Transform.h"

class hkaSkeleton;

class Skeleton
{
public:
    Skeleton(const void* rigData, const int rigSize);
    ~Skeleton();

    hkaSkeleton* getHavokSkeleton() { return this->m_HavokSkeleton; }

    char** getBoneNames(int &count);
    const int getNumBones();

    Transform* getReferencePose();

private:
    hkaSkeleton* m_HavokSkeleton;
};

