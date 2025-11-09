#include "Tema1.h"
#include <random>
#include "object2D.h"
#include "transform2D.h"

using namespace std;
using namespace m1;

int grid[9][17] = { 0 };
bool click1 = false;
bool clik2 = false;
int selected = 0;
int mouse_x_pos_ = 0;
int mouse_y_pos_ = 0;
float mouse_x_pos2_ = 0.f;
float mouse_y_pos2_ = 0.f;
int componente_ramase = 10;
int can_start = 0;
int aux[9][17] = { 0 };
int nr_motors = 0;
int nr_cannon = 0;
int game = 0;
int maxx = -1, minx = 17, maxy = -1, miny = 9;
vector<pair<int, int>> cannons;
vector<pair<int, int>> motors;
float speeds[10] = { 4, 8, 10, 11, 12, 12.5, 13 };
float translateX = 0, translateY = 0;

void Tema1::Init() {
    const glm::ivec2 resolution = window->GetResolution();
    const auto camera = GetSceneCamera();
    camera->SetOrthographic(0, static_cast<float>(resolution.x), 0, static_cast<float>(resolution.y), 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    constexpr auto corner = glm::vec3(0, 0, 0);
    constexpr float square_side = 100;

    Mesh* editorBlock = object2D::create_square("editorBlock", corner, square_side, glm::vec3(0 / 255.f, 0 / 255.f, 255.f / 255.f), true);
    Mesh* componentsRectangle = object2D::create_rectangle("componentRectangle", corner, 200, 240, glm::vec3(1, 0, 0));
    Mesh* remainingBlocksRectangle = object2D::create_rectangle("remainingBlocksRectangle", corner, 920, 110, glm::vec3(0, 1, 0));
    Mesh* remainingBlock = object2D::create_square("remainingBlock", corner, 70, glm::vec3(0, 1, 0), true);
    Mesh* validStart = object2D::create_start_button("validStart", corner, 110, glm::vec3(0, 1, 0), true);
    Mesh* invalidStart = object2D::create_start_button("invalidStart", corner, 110, glm::vec3(1, 0, 0), true);
    Mesh* blocksRectangle = object2D::create_rectangle("blocksRectangle", corner, 1030, 550, glm::vec3(0, 0, 1));
    Mesh* block = object2D::create_square("block", corner, 50, glm::vec3(0, 0, 1), true);
    Mesh* square = object2D::create_block("square", corner, 60, glm::vec3(0.7, 0.7, 0.7), true);
    Mesh* motor = object2D::create_motor("motor", corner, 60, glm::vec3(1, 0, 0), glm::vec3(255.f / 255.f, 165.f / 255.f, 0), true);
    Mesh* cannon = object2D::create_cannon("cannon", corner, 60, glm::vec3(0.5, 0.5, 0.5), true);

    AddMeshToList(editorBlock);
    AddMeshToList(componentsRectangle);
    AddMeshToList(remainingBlocksRectangle);
    AddMeshToList(remainingBlock);
    AddMeshToList(validStart);
    AddMeshToList(invalidStart);
    AddMeshToList(blocksRectangle);
    AddMeshToList(block);
    AddMeshToList(square);
    AddMeshToList(motor);
    AddMeshToList(cannon);
}

void Tema1::FrameStart() {
    glClearColor(0.f, 0.f, 0.f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(const float delta_time_seconds) {
    if (game == 0) {
        if (nr_cannon > 0 && nr_motors > 0) {
            int ok = 0;
            miny = 9, maxy = 0, minx = 17, maxy = 0;
            int aux[9][17] = { 0 };

            for (int i = 0; i < 9 && !ok; ++i) {
                for (int j = 0; j < 17 && !ok; ++j) {
                    if (grid[i][j] != 0) {
                        if (dfs(i, j, aux) == 10 - componente_ramase)
                            ok = 1;
                        else
                            ok = 2, printf("aici\n");
                    }
                }
            }

            for (int i = 0; i < nr_motors && ok == 1; ++i) {
                auto a = motors[i];
                int b = a.first;
                for (int l = 0; l < b; ++l) {
                    if (grid[l][a.second] != 0)
                        ok = 2, printf("aici2\n");
                }
            }

            for (int i = 0; i < nr_cannon && ok == 1; ++i) {
                auto a = cannons[i];
                int b = a.first;
                for (int l = 8; l > b + 2; --l) {
                    if (grid[l][a.second] != 0)
                        ok = 2, printf("aici3\n");
                }
            }

            if (ok == 2) can_start = 0;
            else if (ok == 1) can_start = 1;
        }
        else can_start = 0;

        if (can_start) {
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform2D::Translate(1170, 590);
            RenderMesh2D(meshes["validStart"], shaders["VertexColor"], model_matrix_);
        }
        else {
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform2D::Translate(1170, 590);
            RenderMesh2D(meshes["invalidStart"], shaders["VertexColor"], model_matrix_);
        }

        if (click1 == 1) {
            if (selected == 1) {
                model_matrix_ = glm::mat3(1);
                model_matrix_ *= transform2D::Translate(mouse_x_pos_ - 30, mouse_y_pos_ - 30);
                RenderMesh2D(meshes["square"], shaders["VertexColor"], model_matrix_);
            }
            if (selected == 2) {
                model_matrix_ = glm::mat3(1);
                model_matrix_ *= transform2D::Translate(mouse_x_pos_ - 30, mouse_y_pos_ - 30);
                RenderMesh2D(meshes["motor"], shaders["VertexColor"], model_matrix_);
            }
            if (selected == 3) {
                model_matrix_ = glm::mat3(1);
                model_matrix_ *= transform2D::Translate(mouse_x_pos_ - 30, mouse_y_pos_ - 30);
                RenderMesh2D(meshes["cannon"], shaders["VertexColor"], model_matrix_);
            }
        }

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(0, 0);
        RenderMesh2D(meshes["componentRectangle"], shaders["VertexColor"], model_matrix_);

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(70, 90);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], model_matrix_);

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(0, 240);
        RenderMesh2D(meshes["componentRectangle"], shaders["VertexColor"], model_matrix_);

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(70, 330);
        RenderMesh2D(meshes["motor"], shaders["VertexColor"], model_matrix_);

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(0, 480);
        RenderMesh2D(meshes["componentRectangle"], shaders["VertexColor"], model_matrix_);

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(70, 510);
        RenderMesh2D(meshes["cannon"], shaders["VertexColor"], model_matrix_);

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(230, 590);
        RenderMesh2D(meshes["remainingBlocksRectangle"], shaders["VertexColor"], model_matrix_);

        for (int i = 0; i < componente_ramase; ++i) {
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform2D::Translate(250 + i * 90, 610);
            RenderMesh2D(meshes["remainingBlock"], shaders["VertexColor"], model_matrix_);
        }

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform2D::Translate(230, 20);
        RenderMesh2D(meshes["blocksRectangle"], shaders["VertexColor"], model_matrix_);

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 17; ++j) {
                if (grid[i][j] == 0) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Translate(240 + j * 60, 30 + i * 60);
                    RenderMesh2D(meshes["block"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 1) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Translate(235 + j * 60, 25 + i * 60);
                    RenderMesh2D(meshes["square"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 2) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Translate(235 + j * 60, 25 + i * 60);
                    RenderMesh2D(meshes["motor"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 3) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Translate(235 + j * 60, 25 + i * 60);
                    RenderMesh2D(meshes["cannon"], shaders["VertexColor"], model_matrix_);
                }
            }
        }
    }
    else {
        printf("%d %d %d %d\n", minx, maxx, miny, maxy);
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 17; ++j) {
                if (grid[i][j] == 1) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Scale(0.5, 0.5);
                    model_matrix_ *= transform2D::Translate(100 + j * 60 + translateX, 100 + i * 60 + translateY);
                    RenderMesh2D(meshes["square"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 2) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Scale(0.5, 0.5);
                    model_matrix_ *= transform2D::Translate(100 + j * 60 + translateX, 100 + i * 60 + translateY);
                    RenderMesh2D(meshes["motor"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 3) {
                    model_matrix_ = glm::mat3(1);
                    model_matrix_ *= transform2D::Scale(0.5, 0.5);
                    model_matrix_ *= transform2D::Translate(100 + j * 60 + translateX, 100 + i * 60 + translateY);
                    RenderMesh2D(meshes["cannon"], shaders["VertexColor"], model_matrix_);
                }
            }
        }
    }
}

void Tema1::FrameEnd() {
    DrawCoordinateSystem();
}

void Tema1::OnInputUpdate(const float delta_time, const int mods) {
    if (window->KeyHold(GLFW_KEY_UP)) {
        translateY = min(float(720), speeds[nr_motors] + translateY);
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        translateY -= speeds[nr_motors];
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        translateX += speeds[nr_motors];
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        translateX -= speeds[nr_motors];
    }
}

void Tema1::OnKeyPress(const int key, const int mods) {}
void Tema1::OnKeyRelease(const int key, const int mods) {}

void Tema1::OnMouseMove(const int mouse_x, const int mouse_y, const int delta_x, const int delta_y) {
    if (click1) {
        mouse_x_pos_ = mouse_x;
        mouse_y_pos_ = 720 - mouse_y;
    }
}

void Tema1::OnMouseBtnPress(const int mouse_x, const int mouse_y, const int button, const int mods) {
    int pos_y = 720 - mouse_y;
    if (button == 1) {
        if (click1 == false) {
            click1 = true;
            mouse_x_pos_ = mouse_x;
            mouse_y_pos_ = pos_y;
        }
        if (mouse_x >= 70 && pos_y >= 90 && mouse_x < 130 && pos_y < 220) selected = 1;
        else if (mouse_x >= 70 && pos_y >= 300 && mouse_x < 130 && pos_y < 390) selected = 2;
        else if (mouse_x >= 70 && pos_y >= 510 && mouse_x < 130 && pos_y < 690) selected = 3;
        else if (mouse_x >= 1170 && pos_y >= 590 && mouse_x <= 1280 && pos_y <= 700 && can_start) game = 1;
    }
    else if (button == 2) {
        int pos_y = 720 - mouse_y;
        if (mouse_x >= 230 && pos_y >= 20 && mouse_x <= 1260 && pos_y <= 570) {
            int ok = 0;
            int i = (mouse_x - 230) / 60;
            int j = (pos_y - 20) / 60;

            if (grid[j][i] != 0) {
                if (grid[j][i] == 3) { nr_cannon--; cannons.erase(remove(cannons.begin(), cannons.end(), make_pair(j, i)), cannons.end()); }
                else if (grid[j][i] == 2) { nr_motors--; motors.erase(remove(motors.begin(), motors.end(), make_pair(j + 1, i)), motors.end()); }
                grid[j][i] = 0;
                ok = 1;
            }
            else {
                if (grid[j - 1][i] == 3) grid[j - 1][i] = 0, ok = 1, nr_cannon--, cannons.erase(remove(cannons.begin(), cannons.end(), make_pair(j - 1, i)), cannons.end());
                if (grid[j - 2][i] == 3) grid[j - 2][i] = 0, ok = 1, nr_cannon--, cannons.erase(remove(cannons.begin(), cannons.end(), make_pair(j - 2, i)), cannons.end());
                if (grid[j + 1][i] == 2) grid[j + 1][i] = 0, ok = 1, nr_motors--, motors.erase(remove(motors.begin(), motors.end(), make_pair(j + 1, i)), motors.end());
            }
            if (ok) componente_ramase++;
        }
    }
}

void Tema1::OnMouseBtnRelease(const int mouse_x, const int mouse_y, const int button, const int mods) {
    if (button == 1) {
        int ok = 0;
        int pos_y = 720 - mouse_y;
        if (mouse_x >= 230 && pos_y >= 20 && mouse_x <= 1260 && pos_y <= 570 && componente_ramase > 0) {
            int i = (mouse_x - 230) / 60;
            int j = (pos_y - 20) / 60;
            if ((selected == 3 && j <= 6 || selected == 2 && j >= 1 || selected == 1) && grid[j][i] == 0) {
                if (grid[j - 1][i] != 3 && grid[j - 2][i] != 3 && grid[j + 1][i] != 2) {
                    if (grid[j + 1][i] == 0 && grid[j + 2][i] == 0 && selected == 3) grid[j][i] = selected, ok = 1, nr_cannon++, cannons.push_back({ j, i });
                    if (grid[j - 1][i] == 0 && selected == 2) grid[j][i] = selected, ok = 1, nr_motors++, motors.push_back({ j, i });
                    if (selected == 1) { grid[j][i] = selected, ok = 1; }
                }
            }
        }
        if (ok) componente_ramase--;
        click1 = false;
        selected = 0;
    }
}

void Tema1::OnMouseScroll(const int mouse_x, const int mouse_y, const int offset_x, const int offset_y) {}
void Tema1::OnWindowResize(const int width, const int height) {}

int Tema1::dfs(int i, int j, int a[9][17]) {
    a[i][j] = 1;
    int size = 1;
    int di[4] = { 1,0,-1,0 };
    int dj[4] = { 0,-1,0,1 };
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (ni >= 0 && ni < 9 && nj >= 0 && nj < 17) {
            if (a[ni][nj] == 0 && grid[ni][nj] > 0) {
                if (ni >= maxy) { maxy = ni; if (grid[ni][nj] == 3) maxy = ni + 2; }
                if (ni <= miny) { miny = ni; if (grid[ni][nj] == 2) miny = ni - 1; std::printf("%d\n", miny); }
                if (nj > maxx) { maxx = nj; }
                if (nj < minx) { minx = nj; }
                size += dfs(ni, nj, a);
            }
        }
    }
    return size;
}
