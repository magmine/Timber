#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <unistd.h>

int main() {
	// Create a video mode object
	float scale = 0.74;
	sf::VideoMode vm(1366, 768);

	// Create and open a window for the game
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);
	// Create a texture to hold a graphic on the GPU
	sf::Texture textureBackground;
	// Load a graphic into the texture
	textureBackground.loadFromFile("content/graphics/background.png");
	// Create a sprite
	sf::Sprite spriteBackground;
	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	// Set the spriteBackground to cover the screen
	spriteBackground.setScale(scale, scale);
	spriteBackground.setPosition(0, 0);

	sf::Texture treeTexture;
	treeTexture.loadFromFile("content/graphics/tree.png");
	sf::Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(vm.width / 2, 0);
	treeSprite.setScale(scale, scale);

	sf::Texture insectTexture;
	insectTexture.loadFromFile("content/graphics/insect.png");
	sf::Sprite insectSprite;
	insectSprite.setTexture(insectTexture);
	insectSprite.setPosition(0, vm.height / 2);
	insectSprite.setScale(scale, scale);

	sf::Texture cloudTexture;
	cloudTexture.loadFromFile("content/graphics/cloud.png");

	sf::Sprite cloudSpriteSmall;
	cloudSpriteSmall.setTexture(cloudTexture);
	cloudSpriteSmall.setPosition(vm.width / 2, vm.height / 8);
	cloudSpriteSmall.setScale(scale - 0.3, scale - 0.3);

	sf::Sprite cloudSpriteBig;
	cloudSpriteBig.setTexture(cloudTexture);
	cloudSpriteBig.setPosition(0, vm.height / 10);
	cloudSpriteBig.setScale(scale, scale);

	sf::Sprite cloudSpriteMedium;
	cloudSpriteMedium.setTexture(cloudTexture);
	cloudSpriteMedium.setPosition(vm.width / 2, vm.height / 6);
	cloudSpriteMedium.setScale(scale - 0.15, scale - 0.15);

	bool beeActive = false;
	bool beeSpeed = 0.0f;
	// bool cloudSmallActive = false;
	// bool cloudSmallSpeed = 0.0f;
	// bool cloudBigActive = false;
	// bool cloudBigSpeed = 0.0f;
	// bool cloudMediumActive = false;
	// bool cloudMediumSpeed = 0.0f;

	sf::Clock clock;
	while (window.isOpen()) {
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		sf::Time eTime = clock.restart();

		/*
		****************************************
		Update the scene
		****************************************
		*/
		//setup the bee
		if (!beeActive) {
			srand(static_cast<uint32_t>(time(0) * 10));
			beeSpeed = (rand() % 50) + 50;
			beeActive = true;

			uint32_t beeHight = (rand() % 500) + vm.height / 2;
			insectSprite.setPosition(insectSprite.getPosition().x, beeHight);

		} else {
			sf::Vector2f insectNewPos(insectSprite.getPosition());
			insectNewPos.x += beeSpeed * eTime.asMilliseconds();
			if (insectNewPos.x > vm.width) {
				insectNewPos.x = 0;
				beeActive = false;
			} else if (insectNewPos.x < 0) {
				insectNewPos.x = vm.width;
			}
			insectSprite.setPosition(insectNewPos);
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		//usleep(20000);
		window.clear();

		// Draw our game scene here
		// sf::Vector2f insectNewPos(insectSprite.getPosition());
		// uint32_t pos_change = rand() % 50;
		// insectNewPos.x += pos_change > 25 ? pos_change : -5;

		// if (insectNewPos.x > vm.width) {
		// 	insectNewPos.x = 0;
		// } else if (insectNewPos.x < 0) {
		// 	insectNewPos.x = vm.width;
		// }
		// insectSprite.setPosition(insectNewPos);

		// sf::Vector2f cloudSmallNewPos(cloudSpriteSmall.getPosition());
		// cloudSmallNewPos.x = rand() % 100 > 5 ? rand() % 100 : -(rand() % 5);
		// if (cloudSmallNewPos.x > vm.width) {
		// 	cloudSmallNewPos.x = 0;
		// } else if (cloudSmallNewPos.x < 0) {
		// 	cloudSmallNewPos.x = vm.width;
		// }
		// cloudSpriteSmall.setPosition(cloudSmallNewPos);

		// sf::Vector2f cloudBigNewPos(cloudSpriteBig.getPosition());
		// cloudBigNewPos.x = rand() % 100 > 5 ? rand() % 100 : -(rand() % 5);
		// if (cloudBigNewPos.x > vm.width) {
		// 	cloudBigNewPos.x = 0;
		// } else if (cloudBigNewPos.x < 0) {
		// 	cloudBigNewPos.x = vm.width;
		// }
		// cloudSpriteBig.setPosition(cloudBigNewPos);

		window.draw(spriteBackground);
		window.draw(cloudSpriteBig);
		window.draw(cloudSpriteSmall);
		window.draw(cloudSpriteMedium);
		window.draw(treeSprite);
		window.draw(insectSprite);

		// Show everything we just drew
		window.display();
		//usleep(10000);
	}

	return 0;
}