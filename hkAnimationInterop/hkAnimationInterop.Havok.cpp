#include "stdafx.h"

#include "hkAnimationInterop.h"

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