#include "stdafx.h"

#include <iostream>

#include "hkAnimationInterop.h"

#include "Skeleton.h"

#include <strsafe.h>
#include <objbase.h>

#include <Animation/Animation/Rig/hkaSkeleton.h>

HKANIMATIONINTEROP_API Skeleton * loadSkeleton(unsigned char * rigData, int rigSize)
{
    Skeleton* skeleton = new Skeleton(rigData, rigSize);
    return skeleton;
}

HKANIMATIONINTEROP_API void unloadSkeleton(Skeleton * skeleton)
{
    delete skeleton;
}

HKANIMATIONINTEROP_API int getNumBones(Skeleton * skeleton)
{
    return skeleton->getNumBones();
}

HKANIMATIONINTEROP_API int getBoneNames(Skeleton * skeleton, char ** output)
{
    int count;
    char** names = skeleton->getBoneNames(count);

    for (int i = 0; i < count; ++i) {
        output[i] = names[i];
    }

    return count;
}

HKANIMATIONINTEROP_API int getReferencePose(Skeleton * skeleton, Transform * output)
{
    int count = skeleton->getNumBones();

    Transform* transforms = skeleton->getReferencePose();
    for (int i = 0; i < count; ++i)
        output[i] = transforms[i];

    return count;
}

HKANIMATIONINTEROP_API int getParentIndices(Skeleton * skeleton, int output [])
{
    hkaSkeleton *skele = skeleton->getHavokSkeleton();
    const int count = skele->m_parentIndices.getSize();
    hkInt16* src = skele->m_parentIndices.begin();
    for (int i = 0; i < count; ++i)
        output[i] = src[i];

    return count;
}

