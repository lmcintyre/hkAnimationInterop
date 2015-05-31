// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HKANIMATIONINTEROP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HKANIMATIONINTEROP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HKANIMATIONINTEROP_EXPORTS
#define HKANIMATIONINTEROP_API __declspec(dllexport)
#else
#define HKANIMATIONINTEROP_API __declspec(dllimport)
#endif

#include "Transform.h"

class AnimationContainer;
class Animation;
class Skeleton;

extern "C" {
    HKANIMATIONINTEROP_API void initHkInterop(void);
    HKANIMATIONINTEROP_API void quitHkInterop(void);

    // Skeleton
    HKANIMATIONINTEROP_API Skeleton* loadSkeleton(unsigned char* rigData, int rigSize);
    HKANIMATIONINTEROP_API void unloadSkeleton(Skeleton* skeleton);

    HKANIMATIONINTEROP_API int getNumBones(Skeleton* skeleton);
    HKANIMATIONINTEROP_API int getBoneNames(Skeleton* skeleton, char** output);
    HKANIMATIONINTEROP_API int getReferencePose(Skeleton* skeleton, Transform* output);
    HKANIMATIONINTEROP_API int getParentIndices(Skeleton* skeleton, int output []);

    // AnimationContainer
    HKANIMATIONINTEROP_API AnimationContainer* loadAnimationContainer(Skeleton* skeleton, unsigned char* animationData, int animationSize);
    HKANIMATIONINTEROP_API void unloadAnimationContainer(AnimationContainer* container);

    HKANIMATIONINTEROP_API int getNumAnimations(AnimationContainer* container);
    HKANIMATIONINTEROP_API Animation* getAnimation(AnimationContainer* container, int index);

    // Animation
    HKANIMATIONINTEROP_API float getDuration(Animation* animation);
    HKANIMATIONINTEROP_API float getFrameDuration(Animation* animation);
    HKANIMATIONINTEROP_API int getNumFrames(Animation* animation);
    HKANIMATIONINTEROP_API int getPose(Animation* animation, float timestamp, Transform* output);
}