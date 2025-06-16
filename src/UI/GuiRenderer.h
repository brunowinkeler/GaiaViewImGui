#pragma once
#include <SDL3/SDL.h>
#include "Sensor/SensorManager.h"
#include <unordered_map>
#include <deque>

namespace gaia::ui
{
    class GuiRenderer
    {
    public:
        GuiRenderer();
        ~GuiRenderer();

        void init(const char *title, int width, int height);
        bool processEvents();
        void beginFrame();
        void plot(const gaia::sensor::SensorManager &manager);
        void endFrame();

    private:
        SDL_Window *window_;
        SDL_Renderer *renderer_;
        std::unordered_map<std::string, std::deque<std::pair<double, float>>> buffers_;
        size_t bufferSize_ = 50;
    };
} // namespace gaia::ui