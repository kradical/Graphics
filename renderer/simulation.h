#pragma once

#include <cstddef>
#include <glm/gtc/type_ptr.hpp>

struct SDL_Window;
union SDL_Event;
class Scene;

class Simulation
{
    Scene* mScene;

    int mDeltaMouseX;
    int mDeltaMouseY;

public:
    void Init(Scene* scene);
    void HandleEvent(const SDL_Event& ev);
    void Update(float deltaTime);

    void* operator new(size_t sz);

    uint32_t cubeTransformID;
    uint32_t orbitTransformID;
};
