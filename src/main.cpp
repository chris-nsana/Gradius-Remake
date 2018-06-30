#include "Game.h"
#include <iostream>

int main()
{
    Game Gradius;
    Gradius.init();
    Gradius.Run();

	/*sf::RenderWindow window(sf::VideoMode(1120, 840), "Viper Motion", sf::Style::Close | sf::Style::Resize);
		std::shared_ptr<sf::Texture> playerTexture  = std::make_shared<sf::Texture>();
		sf::Sprite player;
		playerTexture->loadFromFile("./../src/images/PlayerSprite.png");
		player.scale(sf::Vector2f(0.5f, 0.5f));
		player.setTexture(*(playerTexture.get()));
		player.setPosition(560.0f, 420.0f);
	    Animation vicAnimation(playerTexture, sf::Vector2u(5, 2), 0.1f);
	    player.setTextureRect(vicAnimation.uvRect);
		sf::FloatRect bound_rect = player.getLocalBounds();
		player.setOrigin(bound_rect.left + bound_rect.width/2.0f, bound_rect.top  + bound_rect.height/2.0f);

	    float deltaTime = 0.0f;
	    sf::Clock clock;


	    while (window.isOpen())
	    {
	        deltaTime = clock.restart().asSeconds();

	        sf::Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }

	       vicAnimation.update(deltaTime);
	       player.setTextureRect(vicAnimation.uvRect);
	       //std::cout << "Yooo " << deltaTime << std::endl;

	        window.clear();
	        window.draw(player);
	        window.display();
	    }

	    return 0;*/

    return 0;
}
