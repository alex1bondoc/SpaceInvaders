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
Mesh* create_enemy(const std::string& name, const glm::vec3 center, const float length) {
    
}
Mesh* create_bullet(const std::string& name, const glm::vec3 center, const float length) {

}
Mesh* create_egg(const std::string& name, const glm::vec3 center, const float length) {

}