#include "stdafx.h"

#include "hkAnimationInterop.h"

#include "Animation.h"
#include "AnimationContainer.h"
#include "Skeleton.h"

HKANIMATIONINTEROP_API AnimationContainer * loadAnimationContainer(Skeleton * skeleton, unsigned char * animationData, int animationSize)
{
    AnimationContainer* container = new AnimationContainer(skeleton, animationData, animationSize);
    return container;
}

HKANIMATIONINTEROP_API void unloadAnimationContainer(AnimationContainer * container)
{
    delete container;
}

HKANIMATIONINTEROP_API int getNumAnimations(AnimationContainer * container)
{
    return container->getNumAnimations();
}

HKANIMATIONINTEROP_API Animation * getAnimation(AnimationContainer * container, int index)
{
    return container->getAnimation(index);
}
