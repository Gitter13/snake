#include <iostream>
#include <vector>
#include <raylib.h>
#include <string>
using namespace std;

const float obnova_frame = 0.1;
const float min_cas_jidla = 1.0f;

const int sirka = 600;
const int vyska = 600;
bool death = false;
int snezeno = 0;

const int velikost_bloku = 60;


class Parts {
public:
    Vector2 position;
    char smer; // 'U' - up, 'D' - down, 'L' - left, 'R' - right
    Parts(Vector2 posi, char ismer){
        position = posi;
        smer = ismer;
    }

    void draw() {
        DrawRectangle(position.x, position.y, velikost_bloku, velikost_bloku, GREEN);
    }
};
vector<Parts> snake;

class Food {
public:
    Vector2 position;
    Food(Vector2 posi){
        position = posi;
    }

    void draw() {
        DrawCircle(position.x+(velikost_bloku/2), position.y+(velikost_bloku/2), velikost_bloku/2, RED);
    }

    bool control() {
        if (position.x == snake[0].position.x && position.y == snake[0].position.y) {
            // Add new part to snake
            Parts newPart = snake.back();
            snake.push_back(newPart);
            snezeno++;
            return true;
        }
        return false;
    }
};

vector<Food> foods;
float casovac_jidla = 2.0f;

int main() {
    InitWindow(sirka, vyska, "Snake Game");
    SetTargetFPS(60);

    // Initialize snake with one part
    snake.push_back(Parts({0, 0}, 'R'));

    float cas_od_posledni_obnovy = 0.0f;

    while (!WindowShouldClose()) {
        if (!death){
            float dt = GetFrameTime();
            casovac_jidla -= dt;
            cas_od_posledni_obnovy += dt;
            if (IsKeyPressed(KEY_LEFT)) {
                snake[0].smer = 'L';
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                snake[0].smer = 'R';
            }
            if (IsKeyPressed(KEY_UP)) {
                snake[0].smer = 'U';
            }
            if (IsKeyPressed(KEY_DOWN)) {
                snake[0].smer = 'D';
                cout << snake[0].smer << endl;
            }
            if (casovac_jidla <= 0.0f) {
                // Add new food
                int food_x = (rand() % (sirka / velikost_bloku)) * velikost_bloku;
                int food_y = (rand() % (vyska / velikost_bloku)) * velikost_bloku;
                foods.push_back(Food({(float)food_x, (float)food_y}));
                casovac_jidla = rand() % 5 + min_cas_jidla;
            }
            if (cas_od_posledni_obnovy >= obnova_frame) {
                //add parts from food here
                for (int i=0; i<foods.size(); i++) {
                    if(foods[i].control()){
                        foods.erase(foods.begin()+i);
                    }
                }
                
                // Move snake parts
                Parts &head = snake[0];
                float predpoved_y = head.position.y;
                float predpoved_x = head.position.x;
                switch (head.smer) {
                    case 'U': predpoved_y -= velikost_bloku; break;
                    case 'D': predpoved_y += velikost_bloku; break;
                    case 'L': predpoved_x -= velikost_bloku; break;
                    case 'R': predpoved_x += velikost_bloku; break;
                }

                //check collisions with itself
                for (size_t i = 1; i < snake.size(); ++i) {
                    if (predpoved_x == snake[i].position.x && predpoved_y == snake[i].position.y) {
                        if (i==1){
                            predpoved_y = head.position.y;
                            predpoved_x = head.position.x;
                            switch (snake[0].smer) {
                                case 'U': predpoved_y += velikost_bloku; break; //musí jít opačně
                                case 'D': predpoved_y -= velikost_bloku; break;
                                case 'L': predpoved_x += velikost_bloku; break;
                                case 'R': predpoved_x -= velikost_bloku; break;
                            }
                            break;
                        } else{
                            death = true;
                            break;
                        }
                    }
                }
                // Check collisions with walls     
                if (predpoved_x < 0) death = true;
                if (predpoved_x > sirka - velikost_bloku) death = true;
                if (predpoved_y < 0) death = true;
                if (predpoved_y > vyska - velikost_bloku) death = true;
                if (!death) {
                    for (size_t i = snake.size() - 1; i > 0; --i) {
                        snake[i].position = snake[i - 1].position;
                        snake[i].smer = snake[i - 1].smer;
                    }
                    head.position.x = predpoved_x;
                    head.position.y = predpoved_y;
                }
                cas_od_posledni_obnovy = 0.0f;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(("Snezene jidlo: " + to_string(snezeno)).c_str(), 10, 10, 20, WHITE);
        if (death) {
            DrawText("Game Over!", sirka / 2 - 80, vyska / 2 - 20, 40, RED);
        }

        // Draw food
        for (auto &jidlo : foods) {
            jidlo.draw();
        }
        // Draw snake
        for (auto &part : snake) {
            part.draw();
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}   