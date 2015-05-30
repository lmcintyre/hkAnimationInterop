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

extern "C" {
    HKANIMATIONINTEROP_API void initHkInterop(void);
    HKANIMATIONINTEROP_API void quitHkInterop(void);

    // AnimationContainer
    HKANIMATIONINTEROP_API AnimationContainer* loadAnimationContainer(unsigned char* rigData, int rigSize, unsigned char* animationData, int animationSize);
    HKANIMATIONINTEROP_API void unloadAnimationContainer(AnimationContainer* ptr);

    HKANIMATIONINTEROP_API int getNumBones(AnimationContainer* ptr);
    HKANIMATIONINTEROP_API int getNumAnimations(AnimationContainer* ptr);
    HKANIMATIONINTEROP_API Animation* getAnimation(AnimationContainer* ptr, int index);
    HKANIMATIONINTEROP_API int getBoneNames(AnimationContainer* ptr, char** output);
    HKANIMATIONINTEROP_API int getReferencePose(AnimationContainer* ptr, Transform* output);
    HKANIMATIONINTEROP_API int getParentIndices(AnimationContainer* ptr, int output []);

    // Animation
    HKANIMATIONINTEROP_API float getDuration(Animation* ptr);
    HKANIMATIONINTEROP_API float getFrameDuration(Animation* ptr);
    HKANIMATIONINTEROP_API int getNumFrames(Animation* ptr);
    HKANIMATIONINTEROP_API int getTransforms(Animation* ptr, float timestamp, Transform* output);
    HKANIMATIONINTEROP_API int getBoneIndexMap(Animation* ptr, int output[], int max);
}