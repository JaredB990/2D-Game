#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "UtilityFunctions.hpp"
#include <iostream>

int main(int argc, char** argv) {
    Engine& engine = Engine::instance();

    textureManager tm;
    tm.loadTexture("Sprites", engine.getRenderer());
    std::map<std::string, SDL_Texture*>& textures = tm.getTextures();
    for (const auto& pair : textures) {
        std::cout << "Loaded texture: " << pair.first << std::endl;
    }
    Scene GameScene;
    Scene TitleScene;
    Scene EndScene;
    PlayerShip playerShip(tm.getTexture("Sprites\\Falcon.png"),256, 920, 64, 64, true);
    for (int x = 128; x < 1024; x+=64) {
        for (int y = 128; y < 512; y+=64) {
            if (y == 448 && (x >300 ||x<200)){
               auto* enemy = new EnemyShip(tm.getTexture("Sprites\\LvL1Enemy.png"),x, y, 48, 48, true, 1); 
               enemy->setOwned(true);
               GameScene.addObject(enemy);
            }
            else{
                auto* enemy = new EnemyShip(tm.getTexture("Sprites\\LvL1Enemy.png"),x, y, 48, 48, false, 1);
                enemy->setOwned(true);
                GameScene.addObject(enemy);
            }
            //auto* enemy = new EnemyShip(tm.getTexture("Sprites\\LvL1Enemy.png"),x, y, 48, 48, true, 1);
            //enemy->setOwned(true);
            //GameScene.addObject(enemy);
            
            
        }

    }

    



    GameScene.addObject(&playerShip);





    engine.setScene(&GameScene);
    engine.run();
}