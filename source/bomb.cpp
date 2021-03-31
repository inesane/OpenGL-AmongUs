#include "bomb.h"
#include "main.h"

// int vertex_buffer_data_index = 0;

Bomb::Bomb(float x, float y, color_t color)
{
    int vertex_buffer_data_index = 0;
    float x_center = 0.5;
    float y_center = 0.5;
    float radius = 0.2;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[2000];
    static GLfloat vertex_buffer_data2[2000];

    for (float i = 0; i <= 6.28; i += 0.1)
    {
        float x1 = sin(i) * radius + x_center;
        float x2 = sin(i + 0.1) * radius + x_center;
        float y1 = cos(i) * radius + y_center;
        float y2 = cos(i + 0.1) * radius + y_center;
        float arr[] = {x1, y1, 0, x2, y2, 0, x_center, y_center, 0};
        for (int j = 0; j < 9; j++)
        {
            vertex_buffer_data[vertex_buffer_data_index] = arr[j];
            vertex_buffer_data_index++;
        }
    }

    vertex_buffer_data2[0] = 0.45f;
    vertex_buffer_data2[1] = 0.9f;
    vertex_buffer_data2[2] = 0.0f;
    vertex_buffer_data2[3] = 0.45f;
    vertex_buffer_data2[4] = 0.7f;
    vertex_buffer_data2[5] = 0.0f;
    vertex_buffer_data2[6] = 0.55f;
    vertex_buffer_data2[7] = 0.7f;
    vertex_buffer_data2[8] = 0.0f;
    vertex_buffer_data2[9] = 0.45f;
    vertex_buffer_data2[10] = 0.9f;
    vertex_buffer_data2[11] = 0.0f;
    vertex_buffer_data2[12] = 0.55f;
    vertex_buffer_data2[13] = 0.7f;
    vertex_buffer_data2[14] = 0.0f;
    vertex_buffer_data2[15] = 0.55f;
    vertex_buffer_data2[16] = 0.9f;
    vertex_buffer_data2[17] = 0.0f;

    int vertex_buffer_data_index2 = 18;

    this->object = create3DObject(GL_TRIANGLES, vertex_buffer_data_index/3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, vertex_buffer_data_index2/3, vertex_buffer_data2, COLOR_RED, GL_FILL);
}

void Bomb::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Bomb::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Bomb::tick()
{
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
