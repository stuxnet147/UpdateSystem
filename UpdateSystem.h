#pragma once
#include <functional>
#include <iostream>
#include <map>

#include <Windows.h>

class UpdateSystem
{
public:
    UpdateSystem(float targetFps);

    void RegisterCallback(std::function<void(float, float)> callback, std::string name);
    void UnregisterCallback(std::string name);

    void Run();
    void Stop();
    float GetFPS() const;

private:
    std::map<std::string, std::function<void(float, float)>> m_callbacks;
    float m_targetFps = 0.0f;
    float m_frameTime = 0.0f;
    float m_fixedTimeAccumulator = 0.0f;
    float m_fps = 0.0f;
    bool m_running = true;

    void FixedUpdate(float deltaTime);
};
