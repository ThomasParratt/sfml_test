#include <SFML/Graphics.hpp>
#include <iostream>

void    drawBackground(sf::RenderWindow& window, sf::RectangleShape bg, float move)
{
    for (int i = 0; i < 1000; i += 1)
    {
        for (int j = 0; j < 500; j += 1)
        {
            if (i % 2 && j % 2)
            {
                bg.setPosition((i * 10) + move, j * 10);
                window.draw(bg);
            }
        }
    }
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(1000.0f, 500.0f), "CMake SFML Project");
    window.setFramerateLimit(60);

    sf::RectangleShape  square(sf::Vector2f(50.0f, 50.0f));
    sf::RectangleShape  square_2(sf::Vector2f(50.0f, 50.0f));
    sf::RectangleShape  bg(sf::Vector2f(10.0f, 10.0f));
    square.setFillColor(sf::Color::Red);
    square_2.setFillColor(sf::Color::Green);
    bg.setFillColor(sf::Color(100, 100, 100, 100));

    square.setPosition(100.0f, 450.0f);
    square_2.setPosition(350.0f, 450.0f);

    float x = 100.0f;
    float y = 450.0f; 
    static float move;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            sf::Vector2f position = square.getPosition();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (position.y >= 0.0f)
                {
                    square.move(0.0f, -0.1f);
                }
            }
            else
            {
                if (position.y <= 450.0f)
                {
                    square.move(0.0f, +0.1f);
                }
            }

            move -= 0.1f;
            square_2.setPosition(350.0f + move, 450.0f);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        drawBackground(window, bg, move);
        window.draw(square);
        window.draw(square_2);
    
        window.display();
    }
    return 0;
}

/*void    draw_squares(sf::RenderWindow& window, sf::RectangleShape square, sf::CircleShape player, sf::CircleShape pizza, sf::CircleShape tomato)
{
    for (int i = 0; i < 1000; i += 100)
    {
        for (int j = 0; j < 1000; j += 100)
        {
            if (i == 0 || i == 900 || j == 0 || j == 900)
            {
                square.setPosition(i, j);
                window.draw(square);
            }
        }
    }
    window.draw(pizza);
    window.draw(tomato);
    window.draw(player);
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(1000, 1000), "CMake SFML Project");

    sf::RectangleShape  square(sf::Vector2f(100, 100));
    sf::CircleShape     player(50);
    sf::CircleShape     pizza(400);
    sf::CircleShape     tomato(360);
    square.setFillColor(sf::Color::Red);
    player.setFillColor(sf::Color::Blue);
    pizza.setFillColor(sf::Color::Yellow);
    tomato.setFillColor(sf::Color::Red);

    int x = 100;
    int y = 100;
    player.setPosition(x, y);
    pizza.setPosition(x, y);
    tomato.setPosition(x + 40, y + 40);

    //sf::Font    font;
    //if (!font.loadFromFile("../../../usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"))
    //{
    //    std::cout << "Error loading font" << std::endl;
    //}

    //sf::Text    text;
    //text.setFont(font);
    //text.setString("Select your topping!");
    //text.setCharacterSize(50);
    //text.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                player.setPosition(x -= 1, y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                player.setPosition(x += 1, y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                player.setPosition(x, y -= 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                player.setPosition(x, y += 1);
            }


            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        draw_squares(window, square, player, pizza, tomato);
        //window.draw(text);

        window.display();
    }
    return 0;
}*/

/*int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}*/

/*int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}*/
