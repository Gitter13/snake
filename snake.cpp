#include <iostream>
#include <vector>
#include <raylib.h>
#include <string>
using namespace std;

const float obnova_frame = 0.5;
const float obnova_frame = 0.5;
const float min_cas_jidla = 1.0f;

const int sirka = 600;
const int vyska = 600;
bool death = false;
int snezeno = 0;
bool hrajeme_dva = false;
int kdo_vyhral = 0;
bool hrajeme_dva = false;
int kdo_vyhral = 0;

const int velikost_bloku = 60;


class Parts {
public:
    Vector2 position;
    Color barva;
    Color barva;
    char smer; // 'U' - up, 'D' - down, 'L' - left, 'R' - right
    Parts(Vector2 posi, char ismer, Color ibarva){
    Parts(Vector2 posi, char ismer, Color ibarva){
        position = posi;
        smer = ismer;
        barva = ibarva;
        barva = ibarva;
    }

    void draw() {
        DrawRectangle(position.x, position.y, velikost_bloku, velikost_bloku, barva);
        DrawRectangle(position.x, position.y, velikost_bloku, velikost_bloku, barva);
    }
};
vector<Parts> snake;
vector<Parts> snake_dva;
vector<Parts> snake_dva;

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
        if (hrajeme_dva &&(position.x == snake_dva[0].position.x && position.y == snake_dva[0].position.y)) {
            // Add new part to snake
            Parts newPart = snake_dva.back();
            snake_dva.push_back(newPart);
            snezeno++;
            return true;
        }
        if (hrajeme_dva &&(position.x == snake_dva[0].position.x && position.y == snake_dva[0].position.y)) {
            // Add new part to snake
            Parts newPart = snake_dva.back();
            snake_dva.push_back(newPart);
            snezeno++;
            return true;
        }
        return false;
    }
    
    
};

vector<Food> foods;
float casovac_jidla = 2.0f;

Vector2 check_collision(vector<Parts> &snake){
    //chekovani kolizi se steny sebou a presun casti hada
    // Move snake parts
    bool mrtev = false; //local death flag jestli umre tento had
    Parts &head = snake[0];
    float predpoved_y = head.position.y;
    float predpoved_x = head.position.x;
        switch (head.smer) {
            case 'U': predpoved_y -= velikost_bloku; break;
            case 'D': predpoved_y += velikost_bloku; break;
            case 'L': predpoved_x -= velikost_bloku; break;
            case 'R': predpoved_x += velikost_bloku; break;
        }
    if (snake.size() > 1){
        //co když jde nazpátek?
        if (predpoved_x == snake[1].position.x && predpoved_y == snake[1].position.y) {
            predpoved_y = head.position.y;
            predpoved_x = head.position.x;
            switch (snake[0].smer) {
                case 'U': predpoved_y += velikost_bloku; break; //musí jít opačně
                case 'D': predpoved_y -= velikost_bloku; break;
                case 'L': predpoved_x += velikost_bloku; break;
                case 'R': predpoved_x -= velikost_bloku; break;
            }
        }
    }
    //check collisions with itself
    for (int i = 2; i < snake.size()-1; ++i) {
        if (predpoved_x == snake[i].position.x && predpoved_y == snake[i].position.y) {
            death = true;
            mrtev = true;
            break;
        }
    }
    // Check collisions with walls     
    if (predpoved_x < 0) death = true, mrtev = true;
    if (predpoved_x > sirka - velikost_bloku) death = true, mrtev = true;
    if (predpoved_y < 0) death = true, mrtev = true;
    if (predpoved_y > vyska - velikost_bloku) death = true, mrtev = true;

    if (mrtev) {
        if (hrajeme_dva) {
            if (&snake == &snake_dva) {
                if (kdo_vyhral == 2) {
                    kdo_vyhral = 12;
                } else{
                    kdo_vyhral = 1;
                }
            } else {
                kdo_vyhral = 2;
            }
        }
    }
    return {predpoved_x, predpoved_y};
        
}

int main() {
    InitWindow(sirka, vyska, "Snake Game");
    SetTargetFPS(60);

    // Initialize snake with one part
    snake.push_back(Parts({0, 0}, 'R', GREEN));
    if (hrajeme_dva) {
        snake_dva.push_back(Parts({sirka - velikost_bloku, vyska - velikost_bloku}, 'L', YELLOW));
    }
    snake.push_back(Parts({0, 0}, 'R', GREEN));
    if (hrajeme_dva) {
        snake_dva.push_back(Parts({sirka - velikost_bloku, vyska - velikost_bloku}, 'L', YELLOW));
    }
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
            }
            if (hrajeme_dva) {
                if (IsKeyPressed(KEY_A)) {
                    snake_dva[0].smer = 'L';
                }
                if (IsKeyPressed(KEY_D)) {
                    snake_dva[0].smer = 'R';
                }
                if (IsKeyPressed(KEY_W)) {
                    snake_dva[0].smer = 'U';
                }
                if (IsKeyPressed(KEY_S)) {
                    snake_dva[0].smer = 'D';
                }
            }
            if (hrajeme_dva) {
                if (IsKeyPressed(KEY_A)) {
                    snake_dva[0].smer = 'L';
                }
                if (IsKeyPressed(KEY_D)) {
                    snake_dva[0].smer = 'R';
                }
                if (IsKeyPressed(KEY_W)) {
                    snake_dva[0].smer = 'U';
                }
                if (IsKeyPressed(KEY_S)) {
                    snake_dva[0].smer = 'D';
                }
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
                Vector2 zkouska_snake = check_collision(snake);
                Vector2 zkouska_snake_dva;
                //check collision for two snakes
                if (hrajeme_dva) {
                    zkouska_snake_dva = check_collision(snake_dva);
                    for (int j=0; j<snake.size()-1; j++) {
                        if(snake[j].position.x == zkouska_snake_dva.x && snake[j].position.y == zkouska_snake_dva.y){
                            death = true;
                            if (kdo_vyhral == 0) {
                                kdo_vyhral = 1;
                            } else if (kdo_vyhral == 2){
                                kdo_vyhral = 12;
                Vector2 zkouska_snake = check_collision(snake);
                Vector2 zkouska_snake_dva;
                //check collision for two snakes
                if (hrajeme_dva) {
                    zkouska_snake_dva = check_collision(snake_dva);
                    for (int j=0; j<snake.size()-1; j++) {
                        if(snake[j].position.x == zkouska_snake_dva.x && snake[j].position.y == zkouska_snake_dva.y){
                            death = true;
                            if (kdo_vyhral == 0) {
                                kdo_vyhral = 1;
                            } else if (kdo_vyhral == 2){
                                kdo_vyhral = 12;
                            }
                            break;
                        }
                    }
                    if (zkouska_snake.x == zkouska_snake_dva.x && zkouska_snake.y == zkouska_snake_dva.y){
                        death = true;
                        kdo_vyhral = 12;
                    }
                    for (int j=0; j<snake_dva.size()-1; j++) {
                        if(snake_dva[j].position.x == zkouska_snake.x && snake_dva[j].position.y == zkouska_snake.y){
                        }
                    }
                    if (zkouska_snake.x == zkouska_snake_dva.x && zkouska_snake.y == zkouska_snake_dva.y){
                        death = true;
                        kdo_vyhral = 12;
                    }
                    for (int j=0; j<snake_dva.size()-1; j++) {
                        if(snake_dva[j].position.x == zkouska_snake.x && snake_dva[j].position.y == zkouska_snake.y){
                            death = true;
                            if (kdo_vyhral == 0) {
                                kdo_vyhral = 2;
                            } else if (kdo_vyhral == 1){
                                kdo_vyhral = 12;
                            }
                            if (kdo_vyhral == 0) {
                                kdo_vyhral = 2;
                            } else if (kdo_vyhral == 1){
                                kdo_vyhral = 12;
                            }
                            break;
                        }
                    }
                }
                // Move snake parts
                // Move snake parts
                if (!death) {
                    for (size_t i = snake.size() - 1; i > 0; --i) {
                        snake[i].position = snake[i - 1].position;
                        snake[i].smer = snake[i - 1].smer;
                    }
                    snake[0].position.x = zkouska_snake.x;
                    snake[0].position.y = zkouska_snake.y;
                    if (hrajeme_dva) {
                        for (size_t i = snake_dva.size() - 1; i > 0; --i) {
                            snake_dva[i].position = snake_dva[i - 1].position;
                            snake_dva[i].smer = snake_dva[i - 1].smer;
                        }
                        snake_dva[0].position.x = zkouska_snake_dva.x;
                        snake_dva[0].position.y = zkouska_snake_dva.y;
                    }
                    snake[0].position.x = zkouska_snake.x;
                    snake[0].position.y = zkouska_snake.y;
                    if (hrajeme_dva) {
                        for (size_t i = snake_dva.size() - 1; i > 0; --i) {
                            snake_dva[i].position = snake_dva[i - 1].position;
                            snake_dva[i].smer = snake_dva[i - 1].smer;
                        }
                        snake_dva[0].position.x = zkouska_snake_dva.x;
                        snake_dva[0].position.y = zkouska_snake_dva.y;
                    }
                }
                cas_od_posledni_obnovy = 0.0f;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(("Snezene jidlo: " + to_string(snezeno)).c_str(), 10, 10, 20, WHITE);
        if (death) {
            DrawText("Game Over!", sirka / 2 - 80, vyska / 2 - 20, 40, RED);
            DrawText("Stiskni ENTER pro restart hry.", sirka / 2 - 150, vyska / 2 + 30, 20, LIGHTGRAY);
            if (kdo_vyhral != 0) {
                if (kdo_vyhral == 12) {
                    DrawText("Remiza!", sirka / 2 - 60, vyska / 2 + 30, 30, ORANGE);
                } else {
                    if (kdo_vyhral == 1) DrawText("Vyhral zeleny hrac!", sirka / 2 - 100, vyska / 2 + 30, 30, GREEN);
                    else if (kdo_vyhral == 2) DrawText("Vyhral zluty hrac!", sirka / 2 - 100, vyska / 2 + 30, 30, YELLOW);
                }
            }
            if (hrajeme_dva) {
                DrawText("HRA PRO DVA.", sirka / 2 - 220, vyska / 2 + 70, 20, LIGHTGRAY);
            } else {
                DrawText("Stiskni MEZERNIK pro hru pro dva.", sirka / 2 - 100, vyska / 2 + 70, 20, LIGHTGRAY);
            }
            if (IsKeyPressed(KEY_SPACE)){
                hrajeme_dva = !hrajeme_dva;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                // Reset game
                snake.clear();
                snake_dva.clear();
                snake.push_back(Parts({0, 0}, 'R', GREEN));
                if (hrajeme_dva) {
                    snake_dva.push_back(Parts({sirka - velikost_bloku, vyska - velikost_bloku}, 'L', YELLOW));
                }
                foods.clear();
                snezeno = 0;
                death = false;
                kdo_vyhral = 0;
            }
            DrawText("Stiskni ENTER pro restart hry.", sirka / 2 - 150, vyska / 2 + 30, 20, LIGHTGRAY);
            if (kdo_vyhral != 0) {
                if (kdo_vyhral == 12) {
                    DrawText("Remiza!", sirka / 2 - 60, vyska / 2 + 30, 30, ORANGE);
                } else {
                    if (kdo_vyhral == 1) DrawText("Vyhral zeleny hrac!", sirka / 2 - 100, vyska / 2 + 30, 30, GREEN);
                    else if (kdo_vyhral == 2) DrawText("Vyhral zluty hrac!", sirka / 2 - 100, vyska / 2 + 30, 30, YELLOW);
                }
            }
            if (hrajeme_dva) {
                DrawText("HRA PRO DVA.", sirka / 2 - 220, vyska / 2 + 70, 20, LIGHTGRAY);
            } else {
                DrawText("Stiskni MEZERNIK pro hru pro dva.", sirka / 2 - 100, vyska / 2 + 70, 20, LIGHTGRAY);
            }
            if (IsKeyPressed(KEY_SPACE)){
                hrajeme_dva = !hrajeme_dva;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                // Reset game
                snake.clear();
                snake_dva.clear();
                snake.push_back(Parts({0, 0}, 'R', GREEN));
                if (hrajeme_dva) {
                    snake_dva.push_back(Parts({sirka - velikost_bloku, vyska - velikost_bloku}, 'L', YELLOW));
                }
                foods.clear();
                snezeno = 0;
                death = false;
                kdo_vyhral = 0;
            }
        }

        // Draw food
        for (auto &jidlo : foods) {
            jidlo.draw();
        }
        // Draw snake
        for (auto &part : snake) {
            part.draw();
        }
        if (hrajeme_dva) {
            for (auto &part : snake_dva) {
                part.draw();
            }
        }
        if (hrajeme_dva) {
            for (auto &part : snake_dva) {
                part.draw();
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}   