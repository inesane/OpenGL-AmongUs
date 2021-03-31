#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color)
{
    int vertex_buffer_data_index1 = 0;
    int vertex_buffer_data_index2 = 0;
    float x_center = 0.4;
    float y_center = 0.6;
    float radius = 0.2;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[2000];
    static GLfloat vertex_buffer_data2[2000];
    vertex_buffer_data[0] = 0.2f;
    vertex_buffer_data[1] = 0.3f;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 0.6f;
    vertex_buffer_data[4] = 0.3f;
    vertex_buffer_data[5] = 0.0f;
    vertex_buffer_data[6] = 0.2f;
    vertex_buffer_data[7] = 0.6f;
    vertex_buffer_data[8] = 0.0f;
    vertex_buffer_data[9] = 0.2f;
    vertex_buffer_data[10] = 0.6f;
    vertex_buffer_data[11] = 0.0f;
    vertex_buffer_data[12] = 0.6f;
    vertex_buffer_data[13] = 0.6f;
    vertex_buffer_data[14] = 0.0f;
    vertex_buffer_data[15] = 0.6f;
    vertex_buffer_data[16] = 0.3f;
    vertex_buffer_data[17] = 0.0f;

    vertex_buffer_data[18] = 0.1f;
    vertex_buffer_data[19] = 0.35f;
    vertex_buffer_data[20] = 0.0f;
    vertex_buffer_data[21] = 0.2f;
    vertex_buffer_data[22] = 0.35f;
    vertex_buffer_data[23] = 0.0f;
    vertex_buffer_data[24] = 0.2f;
    vertex_buffer_data[25] = 0.6f;
    vertex_buffer_data[26] = 0.0f;
    vertex_buffer_data[27] = 0.1f;
    vertex_buffer_data[28] = 0.35f;
    vertex_buffer_data[29] = 0.0f;
    vertex_buffer_data[30] = 0.2f;
    vertex_buffer_data[31] = 0.6f;
    vertex_buffer_data[32] = 0.0f;
    vertex_buffer_data[33] = 0.1f;
    vertex_buffer_data[34] = 0.6f;
    vertex_buffer_data[35] = 0.0f;

    vertex_buffer_data[36] = 0.2f;
    vertex_buffer_data[37] = 0.3f;
    vertex_buffer_data[38] = 0.0f;
    vertex_buffer_data[39] = 0.2f;
    vertex_buffer_data[40] = 0.2f;
    vertex_buffer_data[41] = 0.0f;
    vertex_buffer_data[42] = 0.3f;
    vertex_buffer_data[43] = 0.2f;
    vertex_buffer_data[44] = 0.0f;
    vertex_buffer_data[45] = 0.2f;
    vertex_buffer_data[46] = 0.3f;
    vertex_buffer_data[47] = 0.0f;
    vertex_buffer_data[48] = 0.3f;
    vertex_buffer_data[49] = 0.2f;
    vertex_buffer_data[50] = 0.0f;
    vertex_buffer_data[51] = 0.3f;
    vertex_buffer_data[52] = 0.3f;
    vertex_buffer_data[53] = 0.0f;

    vertex_buffer_data[54] = 0.5f;
    vertex_buffer_data[55] = 0.3f;
    vertex_buffer_data[56] = 0.0f;
    vertex_buffer_data[57] = 0.5f;
    vertex_buffer_data[58] = 0.2f;
    vertex_buffer_data[59] = 0.0f;
    vertex_buffer_data[60] = 0.6f;
    vertex_buffer_data[61] = 0.2f;
    vertex_buffer_data[62] = 0.0f;
    vertex_buffer_data[63] = 0.5f;
    vertex_buffer_data[64] = 0.3f;
    vertex_buffer_data[65] = 0.0f;
    vertex_buffer_data[66] = 0.6f;
    vertex_buffer_data[67] = 0.2f;
    vertex_buffer_data[68] = 0.0f;
    vertex_buffer_data[69] = 0.6f;
    vertex_buffer_data[70] = 0.3f;
    vertex_buffer_data[71] = 0.0f;

    vertex_buffer_data_index1 = 72;
    for (float i = -1.57; i <= 1.57; i += 0.1)
    {
        float x1 = sin(i) * radius + x_center;
        float x2 = sin(i + 0.1) * radius + x_center;
        float y1 = cos(i) * radius + y_center;
        float y2 = cos(i + 0.1) * radius + y_center;
        float arr[] = {x1, y1, 0, x2, y2, 0, x_center, y_center, 0};
        for (int j = 0; j < 9; j++)
        {
            vertex_buffer_data[vertex_buffer_data_index1] = arr[j];
            vertex_buffer_data_index1++;
        }
    }

    vertex_buffer_data2[0] = 0.3f;
    vertex_buffer_data2[1] = 0.6f;
    vertex_buffer_data2[2] = 0.0f;
    vertex_buffer_data2[3] = 0.3f;
    vertex_buffer_data2[4] = 0.4f;
    vertex_buffer_data2[5] = 0.0f;
    vertex_buffer_data2[6] = 0.65f;
    vertex_buffer_data2[7] = 0.4f;
    vertex_buffer_data2[8] = 0.0f;
    vertex_buffer_data2[9] = 0.3f;
    vertex_buffer_data2[10] = 0.6f;
    vertex_buffer_data2[11] = 0.0f;
    vertex_buffer_data2[12] = 0.65f;
    vertex_buffer_data2[13] = 0.4f;
    vertex_buffer_data2[14] = 0.0f;
    vertex_buffer_data2[15] = 0.65f;
    vertex_buffer_data2[16] = 0.6f;
    vertex_buffer_data2[17] = 0.0f;

    vertex_buffer_data_index2 = 18;

    this->object = create3DObject(GL_TRIANGLES, vertex_buffer_data_index1, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, vertex_buffer_data_index2, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
}

void Player::draw(glm::mat4 VP)
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

void Player::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Player::tick()
{
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
