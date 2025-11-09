#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* create_square(const std::string& name, glm::vec3 left_bottom_corner, float length, glm::vec3 color, bool fill = false);
    Mesh* create_rectangle(const std::string& name, glm::vec3 left_bottom_corner, float length, float height, glm::vec3 color, bool fill = false);
    Mesh* create_motor(const std::string& name, glm::vec3 left_bottom_corner, float length, glm::vec3 color1, glm::vec3 color2 , bool fill = false);
    Mesh* create_cannon(const std::string& name, glm::vec3 left_bottom_corner, float length, glm::vec3 color, bool fill = false);
    Mesh* create_block(const std::string& name, glm::vec3 left_bottom_corner, float length, glm::vec3 color, bool fill = false);

    Mesh* create_start_button(const std::string& name, glm::vec3 left_bottom_corner, float lenght, glm::vec3 color, bool fill = false);

    Mesh* create_enemy(const std::string& name, glm::vec3 left_bottom_corner, float lenght);
    Mesh* create_bullet(const std::string& name, glm::vec3 left_bottom_corner, float lenght);
    Mesh* create_egg(const std::string& name, glm::vec3 left_bottom_corner, float lenght);
    Mesh* create_heart(const std::string& name,  float length, glm::vec3 color);

    // Create square with given bottom left corner, length and color
}
