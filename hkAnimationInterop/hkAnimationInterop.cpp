// hkAnimationInterop.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>>
#include "hkAnimationInterop.h"

#include "AnimationContainer.h"
#include "Animation.h"

#include <strsafe.h>
#include <objbase.h>
#include <stdio.h>

#include <Animation/Animation/Rig/hkaSkeleton.h>


void PlatformInit();
void PlatformFileSystemInit();

static void HK_CALL errorReport(const char* msg, void* userContext)
{
    using namespace std;
    printf("%s", msg);
}

extern HKANIMATIONINTEROP_API void initHkInterop(void)
{
    PlatformInit();
    // Need to have memory allocated for the solver. Allocate 1mb for it.
    hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024));
    hkBaseSystem::init(memoryRouter, errorReport);
    PlatformFileSystemInit();
}

extern HKANIMATIONINTEROP_API void quitHkInterop(void)
{
    hkBaseSystem::quit();
    hkMemoryInitUtil::quit();
}

// AnimationContainer
extern HKANIMATIONINTEROP_API AnimationContainer* loadAnimationContainer(unsigned char * rigData, int rigSize, unsigned char * animationData, int animationSize)
{
    AnimationContainer* container = new AnimationContainer(rigData, rigSize, animationData, animationSize);
    return container;
}

extern HKANIMATIONINTEROP_API void unloadAnimationContainer(AnimationContainer* container)
{
    delete container;
}

extern HKANIMATIONINTEROP_API int getNumBones(AnimationContainer* container)
{
    return container->getNumBones();
}

extern HKANIMATIONINTEROP_API int getNumAnimations(AnimationContainer* container)
{
    return container->getNumAnimations();
}

// Animation
extern HKANIMATIONINTEROP_API Animation* getAnimation(AnimationContainer* container, int index)
{
    return container->getAnimation(index);
}

HKANIMATIONINTEROP_API int getBoneNames(AnimationContainer * container, char** output)
{
    int count = container->getNumBones();

    std::vector<const char*> boneNames = container->getBoneNames();
    for (int i = 0; i < count; ++i) {        
        //output[i] = _strdup(boneNames[i]);
        STRSAFE_LPCSTR name = boneNames[i];
        size_t len;

        StringCchLengthA(name, STRSAFE_MAX_CCH, &len);

        len += 1;

        output[i] = (STRSAFE_LPSTR) CoTaskMemAlloc(len);
        StringCchCopyA(output[i], len, name);
    }
    

    return count;
}

HKANIMATIONINTEROP_API int getReferencePose(AnimationContainer * container, Transform * output)
{
    int count = container->getNumBones();

    Transform* transforms = container->getReferencePose();
    for (int i = 0; i < count; ++i)
        output[i] = transforms[i];

    return count;
}

HKANIMATIONINTEROP_API int getParentIndices(AnimationContainer * container, int output [])
{
    hkaSkeleton *skele = container->getSkeleton();
    const int count = skele->m_parentIndices.getSize();
    hkInt16* src = skele->m_parentIndices.begin();
    for (int i = 0; i < count; ++i)
        output[i] = src[i];

    return count;
}

extern HKANIMATIONINTEROP_API float getDuration(Animation* animation)
{
    return animation->getDuration();
}

extern HKANIMATIONINTEROP_API float getFrameDuration(Animation* animation)
{
    return animation->getFrameDuration();
}

extern HKANIMATIONINTEROP_API int getNumFrames(Animation* animation)
{
    return animation->getNumFrames();
}

extern HKANIMATIONINTEROP_API int getTransforms(Animation* animation, float timestamp, Transform* output)
{
    int count = animation->getContainer()->getNumBones();

    Transform* transforms = animation->getTransforms(timestamp);
    for (int i = 0; i < count; ++i)
        output[i] = transforms[i];

    return count;
}

HKANIMATIONINTEROP_API int getBoneIndexMap(Animation * ptr, int output[], int max)
{
    int count;
    int *src = ptr->getBoneIndexMap(count);
    if (count > max)
        count = max;

    for (int i = 0; i < count; ++i)
        output[i] = src[i];

    return count;
}


// [id=keycode]
#include <Common/Base/keycode.cxx>

#undef HK_FEATURE_PRODUCT_AI
//#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR
#undef HK_FEATURE_PRODUCT_PHYSICS_2012
#undef HK_FEATURE_PRODUCT_SIMULATION
#undef HK_FEATURE_PRODUCT_PHYSICS

#include <Common/Base/Config/hkProductFeatures.cxx>

// Platform specific initialization

#include <Common/Base/System/Init/PlatformInit.cxx>