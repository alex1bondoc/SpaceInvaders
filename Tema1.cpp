#include "Tema1.h"
#include <random>
#include "object2D.h"
#include "transform2D.h"
#include <tuple>

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

int nr_chickens;
vector<pair<int, int>> chickens;
vector<pair<int, int>> initial_chickens = { {0,0}, {0,1}, {0,2}, {0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{1,4} };
int translateX_chicken = 0;
int translateY_chicken = 0;
int s = 2;
int nr_bullets;
vector<tuple<int, int, int>> bullets;
float respawn_time = -1;
int chicken_speed = 5;
vector<int> random_time_chickens;
vector<int> random_time_chickens2;
int hearts = 3;
int random_time = 100;
vector<tuple<int, int, int>> eggs;
int egg_speed = 2;
int rounds = 0;

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
    Mesh* enemy = object2D::create_enemy("enemy", corner, 60);
    Mesh* bullet = object2D::create_bullet("bullet", corner, 30);
    Mesh* egg = object2D::create_egg("egg", corner, 30);
    Mesh* heart = object2D::create_heart("heart", 1, glm::vec3(1, 0, 0));
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
    AddMeshToList(enemy);
    AddMeshToList(bullet);
    AddMeshToList(egg);
    AddMeshToList(heart);

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
            miny = 9, maxy = 0, minx = 17, maxx = 0;
            int aux[9][17] = { 0 };
            motors.clear(), cannons.clear();
            for (int i = 0; i < 9 && !ok; ++i) {
                for (int j = 0; j < 17 && !ok; ++j) {
                    if (grid[i][j] != 0) {
                        if (dfs(i, j, aux) == 10 - componente_ramase)
                            ok = 1;
                        else
                            ok = 2;
                    }
                }
            }

            for (int i = 0; i < nr_motors && ok == 1; ++i) {
                auto a = motors[i];
                int b = a.first;
                for (int l = 0; l < b; ++l) {
                    if (grid[l][a.second] != 0)
                        ok = 2;
                }
            }

            for (int i = 0; i < nr_cannon && ok == 1; ++i) {
                auto a = cannons[i];
                int b = a.first;
                for (int l = 8; l > b + 2; --l) {
                    if (grid[l][a.second] != 0)
                        ok = 2;
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
        if (hearts <= 0) {
            exit(1);
        }
        for (int i = 0; i < 3; i++) {
            if (i < hearts) {
                model_matrix_ = glm::mat3(1);
                model_matrix_ *= transform2D::Translate(1200 + static_cast<float>(i) * 30, 700);
                RenderMesh2D(meshes["heart"], shaders["VertexColor"], model_matrix_);
            }
        }
        if (chickens.size() == 0 && respawn_time <= 0) {
            int random = rand()%500;
            for (int i = 0; i < 10; ++i) {
                chickens.push_back({ 70 + initial_chickens[i].second * 160 + random, 450 + initial_chickens[i].first * 120});
                random_time_chickens.push_back(rand() % random_time + random_time / 2);
                random_time_chickens2.push_back(random_time_chickens[i]);
            }
            respawn_time = 5;
            s*=2;
            random_time /= 2;
            egg_speed *= 2;
            rounds++;
            if (rounds > 3) {
                exit(0);
            }
        }
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 17; ++j) {
                model_matrix_ = glm::mat3(1);
                model_matrix_ *= transform2D::Translate(j * 30 + translateX, i * 30 + translateY);
                model_matrix_ *= transform2D::Scale(0.5, 0.5);

                if (grid[i][j] == 1) {
                    
                    RenderMesh2D(meshes["square"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 2) {
                    
                    RenderMesh2D(meshes["motor"], shaders["VertexColor"], model_matrix_);
                }
                else if (grid[i][j] == 3) {
                    
                    RenderMesh2D(meshes["cannon"], shaders["VertexColor"], model_matrix_);
                }
            }
        }
        for (int i = 0; i < nr_bullets; ++i) {
            auto b = bullets[i];
            int j = std::get<0>(b);
            int k = std::get<1>(b);
            int l = std::get<2>(b);
            std::get<2>(bullets[i]) += 20;
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform2D::Translate(j, k + l);
            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], model_matrix_);
            if (720 < k+l) {
                bullets.erase(bullets.begin() + i);
                nr_bullets--;
            }
        }
        // iterate chickens backwards
        for (int i = (int)chickens.size() - 1; i >= 0; --i) {

            // draw chicken
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform2D::Translate(chickens[i].first, chickens[i].second);
            RenderMesh2D(meshes["enemy"], shaders["VertexColor"], model_matrix_);
            random_time_chickens[i] -= delta_time_seconds;
            if (random_time_chickens[i] <= 0) {
                random_time_chickens[i] = random_time_chickens2[i];
                eggs.push_back({ chickens[i].first, chickens[i].second, 35 });
            }
            // movement
            chickens[i].second -= 0.1f;
            chickens[i].first += s;

            if (chickens[i].first + 70 > 1300 || chickens[i].first - 70 < 0)
                s *= -1;

            // remove if off screen (use < not == !!)
            if (chickens[i].second < 1.0f) {
                chickens.erase(chickens.begin() + i);
                hearts--;
                continue; // chicken gone, skip to next
            }

            // bullet collision, iterate backwards
            for (int j = (int)nr_bullets - 1; j >= 0; --j) {

                int bx = std::get<0>(bullets[j]);
                int by = std::get<1>(bullets[j]) + std::get<2>(bullets[j]);

                float dx = bx - chickens[i].first;
                float dy = by - chickens[i].second;

                if (dx * dx + dy * dy <= 2525) {
                    bullets.erase(bullets.begin() + j);
                    nr_bullets--;

                    chickens.erase(chickens.begin() + i);
                    break; // go to next chicken
                }
            }
        }
        for (int i = 0; i < chickens.size(); i++) {

            float cx = chickens[i].first;
            float cy = chickens[i].second;
            float radius = 36.0f;

            bool hit = false;

            for (int gi = 0; gi < 9 && !hit; gi++) {
                for (int gj = 0; gj < 17 && !hit; gj++) {

                    if (grid[gi][gj] != 0) {
                        int mul = 1;
                        if (grid[gi][gj] == 3) mul = 3;
                        float left = gj * 30 + translateX;
                        float bottom = gi * 30 + translateY;
                        float right = left + 30;
                        float top = bottom + 30 * mul;

                        // punctul cel mai apropiat din pătrat
                        float closestX = cx;
                        if (cx < left) closestX = left;
                        else if (cx > right) closestX = right;

                        float closestY = cy;
                        if (cy < bottom) closestY = bottom;
                        else if (cy > top) closestY = top;

                        float dx = cx - closestX;
                        float dy = cy - closestY;

                        if (dx * dx + dy * dy <= radius * radius) {
                            hit = true;
                        }
                    }
                }
            }

            if (hit) {
                chickens.erase(chickens.begin() + i);
                random_time_chickens.erase(random_time_chickens.begin() + i);
                i--;                 // IMPORTANT ca să nu sari peste următorul
                hearts--;
                continue;            // exact cum ai la gloanțe
            }
        }
        // iterate eggs backwards
        for (int i = (int)eggs.size() - 1; i >= 0; --i) {

            float ex = get<0>(eggs[i]);
            float ey = get<1>(eggs[i]) + get<2>(eggs[i]);

            // desen
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform2D::Translate(ex, ey);
            RenderMesh2D(meshes["egg"], shaders["VertexColor"], model_matrix_);

            // mișcare
            get<2>(eggs[i]) -= egg_speed;
            ey = get<1>(eggs[i]) + get<2>(eggs[i]);

            // 1. dacă iese din ecran jos → șterge
            if (ey < 0) {
                eggs.erase(eggs.begin() + i);
                continue;
            }

            // 2. coliziune cu grid (nava)
            bool hitShip = false;

            for (int gi = 0; gi < 9 && !hitShip; gi++) {
                for (int gj = 0; gj < 17 && !hitShip; gj++) {

                    if (grid[gi][gj] != 0) {
                        int mul = 1;
                        if (grid[gi][gj] == 3) mul = 3;
                        float left = gj * 30 + translateX;
                        float bottom = gi * 30 + translateY;
                        float right = left + 30;
                        float top = bottom + 30 * mul;

                        float closestX = ex;
                        if (ex < left) closestX = left;
                        else if (ex > right) closestX = right;

                        float closestY = ey;
                        if (ey < bottom) closestY = bottom;
                        else if (ey > top) closestY = top;

                        float dx = (ex - closestX) / 10.0f;   // Raza X = 10
                        float dy = (ey - closestY) / 15.0f;   // Raza Y = 15

                        if (dx * dx + dy * dy <= 1.0f) {
                            hitShip = true;
                        }
                    }
                }
            }

            if (hitShip) {
                hearts--;
                eggs.erase(eggs.begin() + i);
                continue;
            }

            // 3. coliziune cu glonț
            for (int b = nr_bullets - 1; b >= 0; b--) {

                float bx = get<0>(bullets[b]);
                float by = get<1>(bullets[b]) + get<2>(bullets[b]);

                float dx = (bx - ex) / 10.0f;
                float dy = (by - ey) / 15.0f;

                if (dx * dx + dy * dy <= 1.0f) {

                    // șterge glonțul
                    bullets.erase(bullets.begin() + b);
                    nr_bullets--;

                    // șterge oul
                    eggs.erase(eggs.begin() + i);

                    break;
                }
            }
        }

        if (chickens.size() == 0) {
            respawn_time -= delta_time_seconds;
        }


    }
}

void Tema1::FrameEnd() {
    DrawCoordinateSystem();
}

void Tema1::OnInputUpdate(const float delta_time, const int mods) {
    if (window->KeyHold(GLFW_KEY_UP)) {
        translateY = fmin(720 - 30 * (maxy + 1), speeds[nr_motors] + translateY);
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        translateY -= speeds[nr_motors];
        translateY = std::fmax(translateY, - 30 * miny);
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        translateX = min(float(1280) - 30 * (maxx + 1), speeds[nr_motors] + translateX);
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        translateX -= speeds[nr_motors];
        translateX = std::fmax(translateX, -30 * ( minx));
    }
    
}

void Tema1::OnKeyPress(const int key, const int mods) {
    if (key == GLFW_KEY_SPACE) {
        for (auto c : cannons) {
            int x = c.second;
            int y = c.first;
            y+=3;
            x = x * 30 + translateX + 15;
            y = y * 30 + translateY;
            nr_bullets++;
            bullets.push_back({ x, y, 0 });

        }
    }
}
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
        printf("%d %d\n", mouse_x, pos_y);
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
                if (grid[j][i] == 3) { nr_cannon--; }
                else if (grid[j][i] == 2) { nr_motors--; }
                grid[j][i] = 0;
                ok = 1;
            }
            else {
                if (grid[j - 1][i] == 3) grid[j - 1][i] = 0, ok = 1, nr_cannon--;
                if (grid[j - 2][i] == 3) grid[j - 2][i] = 0, ok = 1, nr_cannon--;
                if (grid[j + 1][i] == 2) grid[j + 1][i] = 0, ok = 1, nr_motors--;
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
                    if (grid[j + 1][i] == 0 && grid[j + 2][i] == 0 && selected == 3) grid[j][i] = selected, ok = 1, nr_cannon++;
                    if (grid[j - 1][i] == 0 && selected == 2) grid[j][i] = selected, ok = 1, nr_motors++;
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
    if (grid[i][j] == 2) motors.push_back({ i, j });
    if (grid[i][j] == 3) cannons.push_back({ i,j });
    if (i >= maxy) { maxy = i; if (grid[i][j] == 3) maxy = i + 2; }
    if (i <= miny) { miny = i; if (grid[i][j] == 2) miny = i - 1;  }
    if (j > maxx) { maxx = j; }
    if (j < minx) { minx = j; }
    int di[4] = { 1,0,-1,0 };
    int dj[4] = { 0,-1,0,1 };
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (ni >= 0 && ni < 9 && nj >= 0 && nj < 17) {
            if (a[ni][nj] == 0 && grid[ni][nj] > 0) {
                size += dfs(ni, nj, a);
            }
        }
    }
    return size;
}
