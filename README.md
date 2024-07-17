# UpdateSystem

UpdateSystem is a lightweight and flexible update system for managing game loops or real-time simulations. 

It leverages the custom [ZeroTimer](https://github.com/stuxnet147/ZeroTimer) library for precise timekeeping, making it suitable for high-performance applications.

## Features

- Manage callbacks for frame updates
- Adjustable target frames per second (FPS)
- Uses a zero dependency custom timer

## Usage

To use the `UpdateSystem`, include the header files and link against the library in your project. 

Below is an example of how to integrate and use the `UpdateSystem`:

```cpp
#include <UpdateSystem.h>

void UpdateCallback(float deltaTime, float fps)
{
    std::cout << "DeltaTime: " << deltaTime << ", FPS: " << fps << std::endl;
}

int main()
{
    UpdateSystem updateSystem(60.0f); // Target 60 FPS

    updateSystem.RegisterCallback(UpdateCallback, "UpdateCallback");

    updateSystem.RegisterCallback([&](float deltaTime, float fps) {
        if (capture.Capture())
            sender.SendData(capture.GetImageData(), capture.GetWidth(), capture.GetHeight());
    }, "monitor_capture");

    updateSystem.run();

    updateSystem.UnregisterCallback(UpdateCallback);

    updateSystem.UnregisterCallback(monitor_capture);

    updateSystem.Stop();

    return 0;
}
```
## API Reference

`UpdateSystem(float targetFps)`

Constructor to initialize the update system with a target FPS.

`void RegisterCallback(std::function<void(float, float)> callback, std::string name)`

Registers a callback function to be called during the update loop.

`void UnregisterCallback(std::string name)`

Unregisters a previously registered callback.

`void Run()`

Starts the update loop. This function blocks and runs until stop() is called.

`void Stop()`

Stops the update loop.

`float GetFPS() const`

Returns the current FPS.

`void FixedUpdate(float deltaTime)`

Called internally to perform fixed updates.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements
Inspired by common game loop patterns.
