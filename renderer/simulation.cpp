#include "simulation.h"

#include "scene.h"

#include "imgui.h"

#define FLYTHROUGH_CAMERA_IMPLEMENTATION
#include "flythrough_camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


#include <SDL2/SDL.h>

#include <math.h>

void Simulation::Init(Scene* scene)
{
    mScene = scene;

    std::vector<uint32_t> loadedMeshIDs;

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/cube/cube.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        uint32_t newInstanceID;
        AddMeshInstance(mScene, loadedMeshID, &newInstanceID);

        // scale up the cube
        cubeTransformID = scene->Instances[newInstanceID].TransformID;
        scene->Transforms[cubeTransformID].Scale = glm::vec3(2.0f);
        scene->Transforms[cubeTransformID].Translation = glm::vec3(0.0f, 2.0f, 0.0f);
    }

    // parent for teapot orbit
    Transform newTransform;
    newTransform.Scale = glm::vec3(0.5f);
    newTransform.Translation = glm::vec3(2.0f, 0.0f, 0.0f);
    newTransform.RotationOrigin = -newTransform.Translation;
    newTransform.ParentID = cubeTransformID;
    orbitTransformID = scene->Transforms.insert(newTransform);

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/teapot/teapot.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);

            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            Transform* transform = &scene->Transforms[newTransformID];

            transform->ParentID = orbitTransformID;
        }

        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            Transform* transform = &scene->Transforms[newTransformID];

            transform->ParentID = cubeTransformID;
            transform->Scale = glm::vec3(0.4f);
            transform->Translation = glm::vec3(-2.0f, 0.0f, 0.0f);
        }

        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);

            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            Transform* transform = &scene->Transforms[newTransformID];

            transform->ParentID = cubeTransformID;
            transform->Scale = glm::vec3(0.3f);
            transform->Translation = glm::vec3(0.0f, 2.0f, 0.0f);
        }
    }

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/floor/floor.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        AddMeshInstance(mScene, loadedMeshID, nullptr);
    }

    Camera mainCamera;
    mainCamera.Eye = glm::vec3(5.0f);
    glm::vec3 target = glm::vec3(0.0f);
    mainCamera.Look = normalize(target - mainCamera.Eye);
    mainCamera.Up = glm::vec3(0.0f, 1.0f, 0.0f);
    mainCamera.FovY = glm::radians(70.0f);
    mScene->MainCamera = mainCamera;
}

void Simulation::HandleEvent(const SDL_Event& ev)
{
    if (ev.type == SDL_MOUSEMOTION)
    {
        mDeltaMouseX += ev.motion.xrel;
        mDeltaMouseY += ev.motion.yrel;
    }
}

void Simulation::Update(float deltaTime)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    
    int mx, my;
    Uint32 mouse = SDL_GetMouseState(&mx, &my);

    //glm::mat4 rotation = glm::rotate(deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    //mScene->Transforms[orbitTransformID].Rotation *= glm::quat(rotation);

    if ((mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0)
    {
        flythrough_camera_update(
            value_ptr(mScene->MainCamera.Eye),
            value_ptr(mScene->MainCamera.Look),
            value_ptr(mScene->MainCamera.Up),
            NULL,
            deltaTime,
            5.0f, // eye_speed
            0.1f, // degrees_per_cursor_move
            80.0f, // max_pitch_rotation_degrees
            mDeltaMouseX, mDeltaMouseY,
            keyboard[SDL_SCANCODE_W], keyboard[SDL_SCANCODE_A], keyboard[SDL_SCANCODE_S], keyboard[SDL_SCANCODE_D],
            keyboard[SDL_SCANCODE_SPACE], keyboard[SDL_SCANCODE_LCTRL],
            0);
    }

    mDeltaMouseX = 0;
    mDeltaMouseY = 0;

    if (ImGui::Begin("Example GUI Window"))
    {
        ImGui::Text("Mouse Pos: (%d, %d)", mx, my);
    }
    ImGui::End();
}

void* Simulation::operator new(size_t sz)
{
    // zero out the memory initially, for convenience.
    void* mem = ::operator new(sz);
    memset(mem, 0, sz);
    return mem;
}
    