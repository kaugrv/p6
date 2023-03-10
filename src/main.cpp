#include <cstdlib>
#include <vector>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include <imgui.h>
#include "Boid.hpp"
#include "BoidGroup.hpp"
#include "doctest/doctest.h"

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Boids"}};

    BoidGroupBehavior GUI = BoidGroupBehavior{0.5, 0.5, 0.5, 0.};

    BoidGroup group_of_boids(200);

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Cyan);

        // Show the official ImGui demo window
        // ImGui::ShowDemoWindow();

        ImGui::Begin("Parameters");
        ImGui::SliderFloat("Cohesion", &GUI.m_cohesion, 0.f, 1.f);
        ImGui::SliderFloat("Separation", &GUI.m_separation, 0.f, 1.f);
        ImGui::SliderFloat("Alignment", &GUI.m_alignment, 0.f, 1.f);
        ImGui::SliderFloat("Square size", &GUI.m_radius, 0.f, 1.f);
        ImGui::End();

        group_of_boids.update_behavior(GUI);
        group_of_boids.update_all_boids(ctx.delta_time());
        group_of_boids.draw_boids(ctx);
    };

    ctx.maximize_window();

    // Should be done last. It starts the infinite loop.
    ctx.start();
};