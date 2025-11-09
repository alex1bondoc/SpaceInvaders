#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::create_start_button(
    const std::string& name,
    const glm::vec3 left_bottom_corner,
    const float length,
    const glm::vec3 color,
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;

    const std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, 0, -1), color), // 1
        VertexFormat(corner + glm::vec3(length / 2, length / 2, -1), color), // 2
        VertexFormat(corner + glm::vec3(length, length, -1), color), // 3
        VertexFormat(corner + glm::vec3(0, length, -1), color) // 4
    };

    const auto square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 , 4};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::create_rectangle(
    const std::string& name,
    const glm::vec3 left_bottom_corner,
    const float length,
    const float height,
    const glm::vec3 color,
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;

    const std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, 0, -1), color), // 1
        VertexFormat(corner + glm::vec3(length, height, -1), color), // 2 
        VertexFormat(corner + glm::vec3(0, height, -1), color) // 3
    };

    const auto square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::create_motor(
    const std::string& name,
    const glm::vec3 left_bottom_corner,
    const float length,       // lățimea pătratului
    const glm::vec3 color1,  // culoare pătrat
    const glm::vec3 color2,  // culoare flăcări
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // =========================
    // 1️⃣ PĂTRAT DE BAZĂ
    // =========================
    vertices.push_back(VertexFormat(corner, color1));                          // 0 - stânga jos
    vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color1));  // 1 - dreapta jos
    vertices.push_back(VertexFormat(corner + glm::vec3(length, length, 0), color1)); // 2 - dreapta sus
    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), color1));  // 3 - stânga sus

    indices.insert(indices.end(), { 0, 1, 2, 0, 2, 3 });  // două triunghiuri pentru pătrat

    // =========================
    // 2️⃣ FLĂCĂRI JOS
    // =========================
    //float flameHeight = length / 2.0f;
    //float flameWidth = length / 6.0f;

    //// Flacara 1 - stânga
    //vertices.push_back(VertexFormat(corner + glm::vec3(0, 0, 0), color2));  // 4 - sus
    //vertices.push_back(VertexFormat(corner + glm::vec3(flameWidth/ 2, -flameHeight, 0), color2)); // 5 - vârf jos
    //vertices.push_back(VertexFormat(corner + glm::vec3(2 *flameWidth, 0, 0), color2)); // 6 - jos dreapta
    //indices.insert(indices.end(), { 4, 5, 6 });

    //// Flacara 2 - mijloc
    //vertices.push_back(VertexFormat(corner + glm::vec3(length / 2 - flameWidth, 0, 0), color2)); // 7 - stânga sus
    //vertices.push_back(VertexFormat(corner + glm::vec3(length / 2, -flameHeight, 0), color2));    // 8 - vârf jos
    //vertices.push_back(VertexFormat(corner + glm::vec3(length / 2 + flameWidth, 0, 0), color2));  // 9 - dreapta sus
    //indices.insert(indices.end(), { 7, 8, 9 });

    //// Flacara 3 - dreapta
    //vertices.push_back(VertexFormat(corner + glm::vec3(length - 2 * flameWidth, 0, 0), color2));   // 10 - stânga sus
    //vertices.push_back(VertexFormat(corner + glm::vec3(length - flameWidth, -flameHeight, 0), color2)); // 11 - vârf jos
    //vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color2));                  // 12 - dreapta sus
    //indices.insert(indices.end(), { 10, 11, 12 });
    int base = 4;

    // top left
    vertices.push_back(VertexFormat(corner + glm::vec3(0.0f, 0.0f, 0), color2)); // 4 top
    vertices.push_back(VertexFormat(corner + glm::vec3(0.0f, -length * 0.6f, 0), color2)); // 5 bottom

    // spike 1
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.25f, -length * 0.3f, 0), color2)); // 6 top
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.25f, -length * 0.6, 0), color2)); // 7 bottom

    // spike 2
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.50f, -length * 0.3f, 0), color2)); // 8 top
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.50f, -length * 0.6f, 0), color2)); // 9 bottom

    // spike 3
    vertices.push_back(VertexFormat(corner + glm::vec3(length * 0.75f, -length * 0.3f, 0), color2)); // 10 top
    vertices.push_back(VertexFormat(corner + glm::vec3(length , -length * 0.6, 0), color2)); // 11 bottom

    // top right
    vertices.push_back(VertexFormat(corner + glm::vec3(length, 0.0f, 0), color2)); // 12 top



    std::vector<unsigned int> ind = {
        4,5,6,
        4,6,7,
        4,7,8,
        4,8,9,
        4,9,10,
        4,10,11,
        12,11,4,

    };

    indices.insert(indices.end(), ind.begin(), ind.end());

    // =========================
    // 3️⃣ CREARE MESH
    // =========================
    Mesh* motor = new Mesh(name);
    if (!fill) {
        motor->SetDrawMode(GL_LINE_LOOP); // pentru contur
    }
    motor->InitFromData(vertices, indices);

    return motor;
}


/**
 * Implementat - A treia formă (Tun)
 * Desenează un poligon cu o bază zimțată (ca o flacără).
 * 'length' este folosit ca lățimea formei.
 */
Mesh* object2D::create_cannon(
    const std::string& name,
    const glm::vec3 left_bottom_corner,
    const float length,       // lățimea pătratului
    const glm::vec3 color,    // culoarea pătratului și semicercului
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // =========================
    // 1️⃣ PĂTRAT DE BAZĂ
    // =========================
    vertices.push_back(VertexFormat(corner, color));                                  // 0 - stânga jos
    vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));       // 1 - dreapta jos
    vertices.push_back(VertexFormat(corner + glm::vec3(length, length, 0), color));  // 2 - dreapta sus
    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), color));       // 3 - stânga sus

    // Indici pentru pătrat (2 triunghiuri)
    indices.insert(indices.end(), { 0, 1, 2, 0, 2, 3 });

    // =========================
    // 2️⃣ SEMICERC DEASUPRA PĂTRATULUI
    // =========================
    int numSegments = 20;  // numărul de segmente pentru semicerc
    float radius = length / 2.0f;
    glm::vec3 center = corner + glm::vec3(length / 2.0f, length, 0); // centrul semicercului

    // Vertex centru semicerc
    vertices.push_back(VertexFormat(center, color)); // 4

    // Vertexi semicerc
    for (int i = 0; i <= numSegments; i++) {
        float theta = glm::pi<float>() * i / numSegments; // 0 → π
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), color)); // 5..25
    }

    // Indici pentru semicerc
    for (int i = 5; i < 5 + numSegments; i++) {
        indices.push_back(4);    // centrul semicercului
        indices.push_back(i);    // punct curent
        indices.push_back(i + 1);// punct următor
    }

    // =========================
    // 3️⃣ CREARE MESH
    // =========================
    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(0.1, 0.1, 0.1)));                                  // 0 - stânga jos
    vertices.push_back(VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(0.1, 0.1, 0.1)));       // 1 - dreapta jos
    vertices.push_back(VertexFormat(corner + glm::vec3(length, 3 * length, 0), glm::vec3(0.1, 0.1, 0.1)));  // 2 - dreapta sus
    vertices.push_back(VertexFormat(corner + glm::vec3(0, 3 * length, 0), glm::vec3(0.1, 0.1, 0.1)));       // 3 - stânga sus
    indices.insert(indices.end(), { 26, 27, 28, 26, 28, 29 });
    Mesh* cannon = new Mesh(name);
    if (!fill) {
        cannon->SetDrawMode(GL_LINE_LOOP); // contur
    }
    cannon->InitFromData(vertices, indices);

    return cannon;
}

Mesh* object2D::create_square(
    const std::string& name,
    const glm::vec3 left_bottom_corner,
    const float length,
    const glm::vec3 color,
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;

    const std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, 0, -1), color), // 1
        VertexFormat(corner + glm::vec3(length, length, -1), color), // 3
        VertexFormat(corner + glm::vec3(0, length, -1), color) // 4
    };

    const auto square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
Mesh* object2D::create_block(
    const std::string& name,
    const glm::vec3 left_bottom_corner,
    const float length,
    const glm::vec3 color,
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;

    const std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, 0, 0), color), // 1
        VertexFormat(corner + glm::vec3(length, length, 0), color), // 3
        VertexFormat(corner + glm::vec3(0, length, 0), color) // 4
    };

    const auto square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
const glm::vec3 COLOR_BLUE = glm::vec3(0.1f, 0.4f, 1.0f);
const glm::vec3 COLOR_GRAY = glm::vec3(0.6f, 0.6f, 0.6f);
const glm::vec3 COLOR_ORANGE = glm::vec3(1.0f, 0.5f, 0.0f);
const glm::vec3 COLOR_RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 COLOR_BLACK = glm::vec3(0.0f, 0.0f, 0.0f);
Mesh* object2D::create_enemy(const std::string& name, const glm::vec3 center, const float size) {
    Mesh* enemy = new Mesh(name);
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    unsigned int index = 0;

    float cx = center.x;
    float cy = center.y;
    float H = size;

    // --- Aripi ---
    float wing_h = H * 0.4f;
    float wing_w = H * 0.4f;

    // Aripa stanga
    vertices.push_back(VertexFormat(glm::vec3(cx - H / 4 , cy, 10), COLOR_GRAY)); // exterior
    vertices.push_back(VertexFormat(glm::vec3(cx - 5 * H / 4, cy + H / 2 , 10), COLOR_GRAY)); // jos 
    vertices.push_back(VertexFormat(glm::vec3(cx - H, cy + H, 10), COLOR_GRAY)); // sus
    indices.insert(indices.end(), { index, index + 1, index + 2 });
    index += 3;

    // Aripa dreapta
    vertices.push_back(VertexFormat(glm::vec3(cx + H / 4 , cy, 10), COLOR_GRAY));
    vertices.push_back(VertexFormat(glm::vec3(cx + 5 * H / 4, cy + H/2, 10), COLOR_GRAY));
    vertices.push_back(VertexFormat(glm::vec3(cx + H, cy + H, 10), COLOR_GRAY));
    indices.insert(indices.end(), { index, index + 1, index + 2 });
    index += 3;

    // --- Corp ---
    vertices.push_back(VertexFormat(glm::vec3(cx - H / 2, cy - H / 2, 0), COLOR_BLUE));
    vertices.push_back(VertexFormat(glm::vec3(cx + H / 2, cy - H / 2, 0), COLOR_BLUE));
    vertices.push_back(VertexFormat(glm::vec3(cx + H / 2, cy + H / 2, 0), COLOR_BLUE));
    vertices.push_back(VertexFormat(glm::vec3(cx - H / 2, cy + H / 2, 0), COLOR_BLUE));
    indices.insert(indices.end(), { index, index + 1, index + 2, index, index + 2, index + 3 });
    index += 4;

    // --- Cap ---
    float head_radius = H * 0.25f;
    int segments = 32;
    unsigned int center_idx = index;
    vertices.push_back(VertexFormat(glm::vec3(cx, cy + H / 2 + head_radius, 0), COLOR_GRAY));
    index++;
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * (float)M_PI * i / segments;
        float x = cx + head_radius * cos(angle);
        float y = cy + H / 2 + head_radius + head_radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), COLOR_GRAY));
    }
    for (int i = 0; i < segments; ++i) {
        indices.push_back(center_idx);
        indices.push_back(center_idx + i + 1);
        indices.push_back(center_idx + i + 2);
    }
    index = vertices.size();

    // --- Picioare ---
    float foot_h = H * 0.3f;
    float foot_w = H * 0.2f;

    // Picior stanga
    vertices.push_back(VertexFormat(glm::vec3(cx - foot_w, cy - H / 2, 0), COLOR_ORANGE));
    vertices.push_back(VertexFormat(glm::vec3(cx - foot_w * 1.2 , cy - H / 2 - foot_h, 0), COLOR_ORANGE));
    vertices.push_back(VertexFormat(glm::vec3(cx - 3 * foot_w, cy - H / 2 - foot_h / 2 , 0), COLOR_ORANGE));
    indices.insert(indices.end(), { index, index + 1, index + 2 });
    index += 3;

    // Picior dreapta
    vertices.push_back(VertexFormat(glm::vec3(cx + foot_w, cy - H / 2, 0), COLOR_ORANGE));
    vertices.push_back(VertexFormat(glm::vec3(cx + foot_w * 1.2, cy - H / 2 - foot_h, 0), COLOR_ORANGE));
    vertices.push_back(VertexFormat(glm::vec3(cx + 3 * foot_w, cy - H / 2 - foot_h, 0), COLOR_ORANGE));
    indices.insert(indices.end(), { index, index + 1, index + 2 });
    index += 3;

    enemy->InitFromData(vertices, indices);
    enemy->SetDrawMode(GL_TRIANGLES);
    return enemy;
}
Mesh* object2D::create_bullet(const std::string& name, const glm::vec3 left_bottom_corner, const float length) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    int numSegments = 40;  // numărul de segmente pentru semicerc
    float radius = length / 2.0f;
    glm::vec3 center = left_bottom_corner; // centrul semicercului

    // Vertex centru semicerc
    vertices.push_back(VertexFormat(center, glm::vec3(0.6,1,0.6))); // 4

    // Vertexi semicerc
    for (int i = 0; i <= numSegments; i++) {
        float theta = glm::two_pi<float>() * i / numSegments; // 0 → π
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), glm::vec3(0.6, 1, 0.6))); // 5..25
    }

    // Indici pentru semicerc
    for (int i = 5; i < 5 + numSegments; i++) {
        indices.push_back(4);    // centrul semicercului
        indices.push_back(i);    // punct curent
        indices.push_back(i + 1);// punct următor
    }
    Mesh* bullet = new Mesh(name);
    bullet->InitFromData(vertices, indices);
    return bullet;
}

Mesh* object2D::create_egg(const std::string& name, const glm::vec3 left_bottom_corner, const float length) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    int numSegments = 40;
    float radius = length / 2.0f;
    glm::vec3 center = left_bottom_corner; // centrul semicercului

    // Vertex centru semicerc
    vertices.push_back(VertexFormat(center, glm::vec3(1, 1, 0.8))); // 4

    // Vertexi semicerc
    for (int i = 0; i <= numSegments; i++) {
        float theta = glm::two_pi<float>() * i / numSegments; // 0 → π
        float x = radius / 1.5 * cos(theta);
        float y = radius * sin(theta);
        vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), glm::vec3(1, 1, 0.8))); // 5..25
    }

    // Indici pentru semicerc
    for (int i = 5; i < 5 + numSegments; i++) {
        indices.push_back(4);
        indices.push_back(i);
        indices.push_back(i + 1);// punct următor
    }
    Mesh* egg = new Mesh(name);
    egg->InitFromData(vertices, indices);
    return egg;
}