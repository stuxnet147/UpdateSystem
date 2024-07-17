#include <UpdateSystem.h>
#include <ZeroTimer.h>

UpdateSystem::UpdateSystem(float targetFps)
    : m_targetFps(targetFps), m_frameTime(1.0f / targetFps)
{
}

void UpdateSystem::RegisterCallback(std::function<void(float, float)> callback, std::string name)
{
    if (m_callbacks.find(name) != m_callbacks.end())
    {
        return;
    }
    m_callbacks.insert({ name, callback });
}

void UpdateSystem::UnregisterCallback(std::string name)
{
    m_callbacks.erase(name);
}

void UpdateSystem::Run()
{
    unsigned int previousTime = GetTickCount_();
    float accumulatedTime = 0.0f;

    while (m_running)
    {
        unsigned int currentTime = GetTickCount_();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        accumulatedTime += deltaTime;
        accumulatedTime = (std::min)(accumulatedTime, 1.0f);

        int numSteps = static_cast<int>(std::floor(accumulatedTime / m_frameTime));
        if (numSteps == 0)
        {
            continue;
        }

        float timePerStep = accumulatedTime / numSteps;
        accumulatedTime -= numSteps * timePerStep;
        for (int i = 0; i < numSteps; i++)
        {
            FixedUpdate(timePerStep);
        }

        for (auto& callback : m_callbacks)
        {
            callback.second(timePerStep, m_fps);
        }

        if (m_targetFps > 0)
        {
            float targetFrameTime = 1.0f / m_targetFps;
            float timeToSleep = targetFrameTime - timePerStep;
            if (timeToSleep > 0.0f)
            {
                Sleep((int)timeToSleep);
            }
        }

        m_fps = 1.0f / (timePerStep + accumulatedTime);
    }
}

void UpdateSystem::Stop()
{
    m_running = false;
}

float UpdateSystem::GetFPS() const
{
    return m_fps;
}

void UpdateSystem::FixedUpdate(float deltaTime)
{

}
