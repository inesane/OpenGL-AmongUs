#include "main.h"
#include "timer.h"
#include "maze.h"
#include "player.h"
#include "button.h"
#include "time.h"
#include "bomb.h"

#define GLT_IMPLEMENTATION
#include "gltext.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Maze maze1;
Player player1;
Player imposter1;
Button button1;
Button button2;
Button coin1;
Button coin2;
Bomb bomb1;
Bomb bomb2;

int n = 10;
int score = 0;
int ticks = 0;
int tasks_completed = 0, total_tasks = 2;
bool imposter_alive = true, button2_hit = false, coin1_hit = false, coin2_hit = false, bomb1_hit = false, bomb2_hit = false, game_over = false, won = false, buttons_collected = false;
time_t start_time = time(NULL);
int time_left = 30;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye(n / 2, n / 2, 4.5);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target(n / 2, n / 2, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    if (!game_over)
    {
        maze1.draw(VP);
        player1.draw(VP);
        if (imposter_alive)
        {
            imposter1.draw(VP);
            button1.draw(VP);
        }
        if (button2_hit)
        {
            if (!coin1_hit)
            {
                coin1.draw(VP);
            }
            if (!coin2_hit)
            {
                coin2.draw(VP);
            }
            if (!bomb1_hit)
            {
                bomb1.draw(VP);
            }
            if (!bomb2_hit)
            {
                bomb2.draw(VP);
            }
        }
        else
        {
            button2.draw(VP);
        }
    }
}

void tick_input(GLFWwindow *window)
{
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left)
    {
        // Do something
    }
}

int bellman_ford()
{
    int x1 = player1.position.x;
    int y1 = player1.position.y;
    int x2 = imposter1.position.x;
    int y2 = imposter1.position.y;
    int distance[n * n], parent[n * n];
    for (int i = 0; i < n * n; i++)
    {
        distance[i] = 100000;
        parent[i] = -1;
    }
    distance[x1 * n + y1] = 0;
    for (int i = 0; i < n * n; i++)
    {
        for (int j = 0; j < connected_blocks.size(); j++)
        {
            int block1_x = connected_blocks[j].first.first;
            int block1_y = connected_blocks[j].first.second;
            int block2_x = connected_blocks[j].second.first;
            int block2_y = connected_blocks[j].second.second;
            int block1_index = block1_x * n + block1_y;
            int block2_index = block2_x * n + block2_y;
            if (distance[block1_index] != 100000 && distance[block1_index] + 1 < distance[block2_index])
            {
                distance[block2_index] = distance[block1_index] + 1;
                parent[block2_index] = block1_index;
            }
        }
    }
    return parent[x2 * n + y2];
}

void tick_elements()
{
    ticks++;
    bool move = true;
    float check_x = player1.position.x + 0.5;
    float check_y = player1.position.y + 0.5;
    if (player1.position.x == button1.position.x && player1.position.y == button1.position.y && imposter_alive == true)
    {
        imposter_alive = false;
        tasks_completed++;
    }
    if (player1.position.x == button2.position.x && player1.position.y == button2.position.y && button2_hit == false)
    {
        button2_hit = true;
        tasks_completed++;
    }
    if (button2_hit)
    {
        if (player1.position.x == coin1.position.x && player1.position.y == coin1.position.y && !coin1_hit)
        {
            coin1_hit = true;
            score += 10;
        }
        if (player1.position.x == coin2.position.x && player1.position.y == coin2.position.y && !coin2_hit)
        {
            coin2_hit = true;
            score += 10;
        }
        if (player1.position.x == bomb1.position.x && player1.position.y == bomb1.position.y && !bomb1_hit)
        {
            bomb1_hit = true;
            score -= 10;
        }
        if (player1.position.x == bomb2.position.x && player1.position.y == bomb2.position.y && !bomb2_hit)
        {
            bomb2_hit = true;
            score -= 10;
        }
        if (imposter_alive == false && buttons_collected == false)
        {
            buttons_collected = true;
        }
        if (buttons_collected == true && player1.position.x == n - 1 && player1.position.y == n - 1)
        {
            game_over = true;
            won = true;
        }
    }
    if (player1.position.x == imposter1.position.x && player1.position.y == imposter1.position.y && imposter_alive == true)
    {
        game_over = true;
    }
    if (move_down == true)
    {
        for (int i = 0; i < walls.size(); i++)
        {
            if (walls[i].first.second == walls[i].second.second)
            {
                if ((walls[i].first.second < check_y) && (walls[i].first.second > (check_y - 1)) && (check_x < max(walls[i].first.first, walls[i].second.first)) && (check_x > min(walls[i].first.first, walls[i].second.first)))
                {
                    move = false;
                    break;
                }
            }
        }
        if (move)
            player1.position.y -= 1;
        move_down = false;
    }
    if (move_up == true)
    {
        for (int i = 0; i < walls.size(); i++)
        {
            if (walls[i].first.second == walls[i].second.second)
            {
                if ((walls[i].first.second > check_y) && (walls[i].first.second < (check_y + 1)) && (check_x < max(walls[i].first.first, walls[i].second.first)) && (check_x > min(walls[i].first.first, walls[i].second.first)))
                {
                    move = false;
                    break;
                }
            }
        }
        if (move)
            player1.position.y += 1;
        move_up = false;
    }
    if (move_right == true)
    {
        for (int i = 0; i < walls.size(); i++)
        {
            if (walls[i].first.first == walls[i].second.first)
            {
                if ((walls[i].first.first > check_x) && (walls[i].first.first < (check_x + 1)) && (check_y < max(walls[i].first.second, walls[i].second.second)) && (check_y > min(walls[i].first.second, walls[i].second.second)))
                {
                    move = false;
                    break;
                }
            }
        }
        if (move)
            player1.position.x += 1;
        move_right = false;
    }
    if (move_left == true)
    {
        for (int i = 0; i < walls.size(); i++)
        {
            if (walls[i].first.first == walls[i].second.first)
            {
                if ((walls[i].first.first < check_x) && (walls[i].first.first > (check_x - 1)) && (check_y < max(walls[i].first.second, walls[i].second.second)) && (check_y > min(walls[i].first.second, walls[i].second.second)))
                {
                    move = false;
                    break;
                }
            }
        }
        if (move)
            player1.position.x -= 1;
        move_left = false;
    }
    if (ticks % 50 == 0 && imposter_alive == true)
    {
        int val = bellman_ford();
        imposter1.position.y = val % n;
        imposter1.position.x = val / n;
    }
    if (time_left <= 0)
    {
        game_over = true;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    srand(time(NULL));
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    maze1 = Maze(0, 0, COLOR_ORANGE);
    player1 = Player(0, 0, COLOR_GREEN);
    imposter1 = Player(rand() % (n/2) + (n-1)/2, rand() % (n/2) + (n-1)/2, COLOR_RED);
    button1 = Button(rand() % (n - 1) + 1, rand() % (n - 1) + 1, COLOR_RED);
    button2 = Button(rand() % (n - 1) + 1, rand() % (n - 1) + 1, COLOR_GREEN);
    coin1 = Button(rand() % (n - 1) + 1, rand() % (n - 1) + 1, COLOR_YELLOW);
    coin2 = Button(rand() % (n - 1) + 1, rand() % (n - 1) + 1, COLOR_YELLOW);
    bomb1 = Bomb(rand() % (n - 1) + 1, rand() % (n - 1) + 1, COLOR_BLACK);
    bomb2 = Bomb(rand() % (n - 1) + 1, rand() % (n - 1) + 1, COLOR_BLACK);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv)
{
    srand(time(0));
    int width = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        if (time_left > 0 && game_over == false)
        {
            time_left = 30 - (int)(time(NULL) - start_time);
        }
        // Process timers

        if (t60.processTick())
        {
            // 60 fps
            // OpenGL Draw commands
            draw();

            if (game_over == true and won == true)
            {
                // cout<<"111111111"<<endl;
                gltInit();
                GLTtext *wontext = gltCreateText();
                gltSetText(wontext, "You Won Phoda Machaya Andha Paisa Treat++");
                gltBeginDraw();
                gltColor(1.0f, 1.0f, 1.0f, 1.0f);
                gltDrawText2D(wontext, 10.0f, 200.0f, 1.5f);
                gltEndDraw();
                gltDeleteText(wontext);
                // cout<<"22222222"<<endl;
            }

            if (game_over == true and won == false)
            {
                // cout<<"111111111"<<endl;
                gltInit();
                GLTtext *losttext = gltCreateText();
                gltSetText(losttext, "You Lost smh noob get rekt");
                gltBeginDraw();
                gltColor(1.0f, 1.0f, 1.0f, 1.0f);
                gltDrawText2D(losttext, 10.0f, 200.0f, 1.5f);
                gltEndDraw();
                gltDeleteText(losttext);
                // cout<<"22222222"<<endl;
            }

            gltInit();
            GLTtext *lighttext = gltCreateText();
            gltSetText(lighttext, "Light : ON");
            gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2D(lighttext, 50.0f, 30.0f, 1.0f);
            gltEndDraw();
            gltDeleteText(lighttext);

            gltInit();
            GLTtext *scoretext = gltCreateText();
            char scoretextarr[15];
            sprintf(scoretextarr, "Score : %d", score);
            gltSetText(scoretext, scoretextarr);
            gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2D(scoretext, 50.0f, 45.0f, 1.0f);
            gltEndDraw();
            gltDeleteText(scoretext);

            gltInit();
            GLTtext *taskstext = gltCreateText();
            char taskstextarr[15];
            sprintf(taskstextarr, "Tasks : %d / %d", tasks_completed, total_tasks);
            gltSetText(taskstext, taskstextarr);
            gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2D(taskstext, 50.0f, 60.0f, 1.0f);
            gltEndDraw();
            gltDeleteText(taskstext);
            gltTerminate();

            gltInit();
            GLTtext *timetext = gltCreateText();
            char timetextarr[15];
            sprintf(timetextarr, "Time Left : %d", time_left);
            gltSetText(timetext, timetextarr);
            gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2D(timetext, 50.0f, 75.0f, 1.0f);
            gltEndDraw();
            gltDeleteText(timetext);
            gltTerminate();
            glfwSwapBuffers(window);
            // cout<<"333333"<<endl;

            if(game_over == false)
            {
                tick_elements();
            }
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
