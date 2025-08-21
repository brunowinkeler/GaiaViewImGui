#include "UI/GuiRenderer.h"
#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include <vector>
#include <ctime>

namespace gaia::ui
{
    int FormatTimestamp(double value, char *buffer, int size, void *user_data)
    {
        std::time_t time = static_cast<std::time_t>(value);
        std::tm *tm = std::localtime(&time);
        std::strftime(buffer, size, "%H:%M:%S", tm);
        return 0;
    }

    GuiRenderer::GuiRenderer() : window_(nullptr), renderer_(nullptr) {}

    GuiRenderer::~GuiRenderer()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        if (renderer_)
            SDL_DestroyRenderer(renderer_);
        if (window_)
            SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void GuiRenderer::init(const char *title, int width, int height)
    {
        SDL_Init(SDL_INIT_VIDEO);
        window_ = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
        renderer_ = SDL_CreateRenderer(window_, nullptr);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();
        ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
        ImGui_ImplSDLRenderer3_Init(renderer_);
    }

    bool GuiRenderer::processEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                return false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE)
            {
                return false;
            }
        }
        return true;
    }

    void GuiRenderer::beginFrame()
    {
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
    }

    void GuiRenderer::plot(const gaia::sensor::SensorManager &manager)
    {
        ImGui::Begin("Sensor Data");
        for (const auto &sensor : manager.sensors())
        {
            if (!sensor)
            {
                continue;
            }

            auto &buffer = buffers_[sensor->id()];

            if (sensor->wasUpdated())
            {
                buffer.emplace_back(sensor->lastUpdateTime(), sensor->value());
                if (buffer.size() > bufferSize_)
                {
                    buffer.pop_front();
                }
                sensor->resetUpdated();
            }

            if (buffer.empty())
            {
                continue;
            }

            std::vector<double> x;
            std::vector<double> y;
            for (const auto &[timestamp, value] : buffer)
            {
                x.push_back(timestamp);
                y.push_back(static_cast<double>(value));
            }

            if (!x.empty() && !y.empty() && x.size() == y.size())
            {
                if (ImPlot::BeginPlot(sensor->name().c_str(), ImVec2(-1, 400)))
                {
                    ImPlot::SetupAxis(ImAxis_X1, nullptr, ImPlotAxisFlags_AutoFit); // auto-fit X axis
                    ImPlot::SetupAxisLimits(ImAxis_Y1, 18, 27);
                    ImPlot::SetupAxisFormat(ImAxis_X1, gaia::ui::FormatTimestamp, nullptr);
                    ImPlot::PlotLine(sensor->name().c_str(), x.data(), y.data(), static_cast<int>(y.size()));
                    ImPlot::EndPlot();
                }
            }
        }
        ImGui::End();
    }

    void GuiRenderer::endFrame()
    {
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer_, 25, 25, 25, 255);
        SDL_RenderClear(renderer_);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
        SDL_RenderPresent(renderer_);
    }

} // namespace gaia::ui