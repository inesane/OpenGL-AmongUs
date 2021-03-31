#include "maze.h"
#include "main.h"
#include "mazefunc.h"

Maze::Maze(float x, float y, color_t color)
{
    maze_create();
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[1000][6];

    for (int i = 0; i < walls.size(); i++)
    {
        vertex_buffer_data[i][0] = walls[i].first.first;
        vertex_buffer_data[i][1] = walls[i].first.second;
        vertex_buffer_data[i][2] = 0;
        vertex_buffer_data[i][3] = walls[i].second.first;
        vertex_buffer_data[i][4] = walls[i].second.second;
        vertex_buffer_data[i][5] = 0;
    }
    for (int i = 0; i < walls.size(); i++)
    {
        this->object[i] = create3DObject(GL_LINES, 6, vertex_buffer_data[i], color, GL_FILL);
    }
}

void Maze::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (buttons_collected)
    {
        for (int i = 0; i < walls.size() - 3; i++)
        {
            draw3DObject(this->object[i]);
        }
    }
    else
    {
        for (int i = 0; i < walls.size(); i++)
        {
            draw3DObject(this->object[i]);
        }
    }
}

void Maze::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Maze::tick()
{
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}