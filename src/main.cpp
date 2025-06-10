#include <SDL3/SDL.h>
#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include <deque>
#include <vector>
#include <memory>
#include <string>
#include <thread>

#include "Sensor/TemperatureSensor.h"
#include "DataSource/SimulatedDataSource.h"

class PlotBuffer
{
public:
    PlotBuffer(std::size_t maxSize) : maxSize_(maxSize) {}
    void add(float value)
    {
        if (buffer_.size() >= maxSize_)
            buffer_.pop_front();
        buffer_.push_back(value);
    }
    const std::deque<float> &data() const { return buffer_; }

private:
    std::size_t maxSize_;
    std::deque<float> buffer_;
};

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("GaiaView", 1280, 720, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    auto tempSensor = std::make_unique<gaia::sensor::TemperatureSensor>(
        "temp1", "Main Temp", "C", 15.0f, 30.0f, 1.0,
        std::make_unique<gaia::datasource::SimulatedDataSource>());
    PlotBuffer plotBuffer(300);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        tempSensor->tryUpdate();
        plotBuffer.add(tempSensor->value());

        ImGui::Begin("Temperature Plot");
        if (ImPlot::BeginPlot("Temperature", ImVec2(-1, 300)))
        {
            ImPlot::SetupAxesLimits(0, 400, 18, 26);
            std::vector<float> y(plotBuffer.data().begin(), plotBuffer.data().end());
            std::vector<float> x(y.size());
            for (size_t i = 0; i < y.size(); ++i)
                x[i] = static_cast<float>(i);
            ImPlot::PlotLine("Temp (C)", x.data(), y.data(), (int)y.size());
            ImPlot::EndPlot();
        }
        ImGui::End();

        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
