#pragma once

#include "Transform.h"

class hkaAnimation;
class hkaAnimationBinding;
class hkaAnimatedSkeleton;
class hkaDefaultAnimationControl;

class AnimationContainer;

class Animation
{
public:
    Animation(AnimationContainer* container, hkaAnimationBinding* binding);
    ~Animation();

    const float getDuration();
    const int getNumFrames();
    const float getFrameDuration() { return getDuration() / getNumFrames(); }

    hkaAnimation* getAnimation() { return this->m_Animation; }
    hkaAnimationBinding* getBinding() { return this->m_Binding; }
    AnimationContainer* getContainer() { return this->m_Container; }

    Transform* getTransforms(const float time);
    int* getBoneIndexMap(int &count);
private:
    hkaAnimation* m_Animation;
    hkaAnimationBinding* m_Binding;
    AnimationContainer* m_Container;
    hkaAnimatedSkeleton* m_AnimatedSkeleton;
    hkaDefaultAnimationControl* m_AnimationControl;
};

