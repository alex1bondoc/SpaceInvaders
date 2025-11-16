#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"


namespace m1
{
    class Tema1 final : public gfxc::SimpleScene
    {
    public:
        Tema1() = default;
        ~Tema1() override = default;

        Tema1(const Tema1& other) : SimpleScene(other), model_matrix_()
        {
        }

        Tema1& operator=(const Tema1& other) {
            if (this != &other) {
            }
            return *this;
        }

        Tema1(Tema1&&) noexcept : model_matrix_()
        {
        }

        Tema1& operator=(Tema1&& other) noexcept {
            if (this != &other) {
            }
            return *this;
        }

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float delta_time_seconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float delta_time, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouse_x, int mouse_y, int delta_x, int delta_y) override;
        void OnMouseBtnPress(int mouse_x, int mouse_y, int button, int mods) override;
        void OnMouseBtnRelease(int mouse_x, int mouse_y, int button, int mods) override;
        void OnMouseScroll(int mouse_x, int mouse_y, int offset_x, int offset_y) override;
        void OnWindowResize(int width, int height) override;
        int dfs(int i, int j, int a[9][17]);
    protected:
        glm::mat3 model_matrix_;


       


    };
}   