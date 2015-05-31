#include "stdafx.h"

#include "hkAnimationInterop.h"

#include "Animation.h"
#include "AnimationContainer.h"
#include "Skeleton.h"


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

extern HKANIMATIONINTEROP_API int getPose(Animation* animation, float timestamp, Transform* output)
{
    int count;

    Transform* transforms = animation->getPose(timestamp, count);
    for (int i = 0; i < count; ++i)
        output[i] = transforms[i];

    return count;
}