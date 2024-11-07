#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Square
{
    private:
        float   top;
        float   bottom;
        float   left;
        float   right;
    public:
        //Square()
        //Square(const Square& obj);
        Square(sf::Vector2f position, float squareSize);
        //~Square();
        //Square&  operator=(const Square& obj);
        // std::string     getName() const;
        // int             getGrade() const;
        float   getTop() const {return this->top;}
        float   getBottom() const {return this->bottom;}
        float   getLeft() const {return this->left;}
        float   getRight() const {return this->right;}
};

Square::Square(sf::Vector2f position, float squareSize)
{
    this->top = position.y;
    this->bottom = position.y + squareSize;
    this->left = position.x;
    this->right = position.x + squareSize;
}

// collisions    // DETERMINE DIFFERENT POSITION VALUES // in new function
// more obstacles (with map?)
// jump on one press
// refactor
// classes?
// resource manager

void    drawBackground(sf::RenderWindow& window, sf::RectangleShape bg, sf::RectangleShape square_2, sf::RectangleShape square, float move)
{
    float offsetX = fmod(move, 40);
    //std::cout << "offsetX = " << offsetX << std::endl;

    for (int i = 0; i < window.getSize().x / 20 + 1; i++)
    {
        for (int j = 0; j < window.getSize().y / 20 + 1; j++)
        {
            if ((i + j) % 2 == 0)
            {
                bg.setPosition((i * 20) + offsetX + 20, j * 20);
                window.draw(bg);
            }
        }
    }
    window.draw(square_2);
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(2000.0f, 1000.0f), "CMake SFML Project");
    //window.setFramerateLimit(60);

    sf::Vector2u    windowSize = window.getSize();
    unsigned int    windowWidth = windowSize.x;
    unsigned int    windowHeight = windowSize.y;
    float           squareSize = windowWidth / 20;
    float           bgSqSize = windowWidth / 100;

    sf::RectangleShape  square(sf::Vector2f(squareSize, squareSize));
    sf::RectangleShape  square_2(sf::Vector2f(squareSize, squareSize));
    sf::RectangleShape  bg(sf::Vector2f(bgSqSize, bgSqSize));
    square.setFillColor(sf::Color::Blue);
    square_2.setFillColor(sf::Color::Green);
    bg.setFillColor(sf::Color(100, 100, 100, 100));

    square.setPosition(200.0f, windowHeight - squareSize);
    square_2.setPosition(700.0f, windowHeight - squareSize);

    float moveSpeed = 200.0f;
    static float move;

    sf::Clock   clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // time elapsed each frame
        float deltaTime = clock.restart().asSeconds();

        sf::Vector2f    playerPos = square.getPosition();
        sf::Vector2f    obstaclePos = square_2.getPosition();
        // std::cout << "obstaclePos.y - squareSize = " << obstaclePos.y - squareSize << std::endl;
        // std::cout << "obstaclePos.x = " << obstaclePos.x << std::endl;
        // std::cout << "windowHeight - squareSize = " << windowHeight - squareSize << std::endl;

        // std::cout << "playerPosPos.x = " << playerPos.x << std::endl;
        // std::cout << "playerPosPos.y = " << playerPos.y << std::endl << std::endl;
        // std::cout << "obstaclePos.x = " << obstaclePos.x << std::endl;
        //std::cout << "obstaclePos.y = " << obstaclePos.y << std::endl << std::endl;

        //float   floorLevel = 

        Square  player(playerPos, squareSize);
        Square  obstacle(obstaclePos, squareSize);

        //std::cout << "player top = " << player.getTop() << std::endl;
        //std::cout << "player bottom = " << player.getBottom() << std::endl;
        //std::cout << "player left = " << player.getLeft() << std::endl;
        //std::cout << "player right = " << player.getRight() << std::endl << std::endl;
        //std::cout << "windowHeight = " << windowHeight << std::endl;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerPos.y >= 0.0f)
            square.move(0.0f, -moveSpeed * deltaTime);
        else if ((player.getRight() < obstacle.getLeft()) || (player.getLeft() > obstacle.getRight()))
        {
            if (player.getBottom() < windowHeight) 
            {
                    square.move(0.0f, moveSpeed * deltaTime);
            }
        }
        else if (player.getBottom() < obstacle.getTop())
        {
            square.move(0.0f, moveSpeed * deltaTime);
        }

        
        if ((obstacle.getLeft() > player.getRight()))
        {
            move -= moveSpeed * deltaTime;
        }
        if ((player.getRight() >= obstacle.getLeft()) && (player.getLeft() <= obstacle.getRight()))
        {
            if (player.getBottom() <= obstacle.getTop())
                move -= moveSpeed * deltaTime;
        }
        else
            move -= moveSpeed * deltaTime;
        square_2.setPosition(700.0f + move, windowHeight - squareSize);

        window.clear();

        drawBackground(window, bg, square_2, square, move);
        window.draw(square);
    
        window.display();
    }
    return 0;
}


// Helper function for drawing background
// void drawBackground(sf::RenderWindow& window, sf::RectangleShape bg, float move, unsigned int bgSqSize) {
//     unsigned int windowWidth = window.getSize().x;
//     unsigned int windowHeight = window.getSize().y;

//     for (int i = 0; i < windowWidth / bgSqSize + 1; ++i) {
//         for (int j = 0; j < windowHeight / bgSqSize + 1; ++j) {
//             if ((i + j) % 2 == 0) {  // alternate tiles
//                 bg.setPosition((i * bgSqSize) + move, j * bgSqSize);
//                 window.draw(bg);
//             }
//         }
//     }
// }

// int main() {
//     sf::RenderWindow window(sf::VideoMode(2000, 1000), "CMake SFML Project");

//     sf::Vector2u windowSize = window.getSize();
//     unsigned int windowWidth = windowSize.x;
//     unsigned int windowHeight = windowSize.y;
//     float squareSize = windowWidth / 20.0f;
//     float bgSqSize = windowWidth / 100.0f;

//     sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
//     sf::RectangleShape square_2(sf::Vector2f(squareSize, squareSize));
//     sf::RectangleShape bg(sf::Vector2f(bgSqSize, bgSqSize));
//     square.setFillColor(sf::Color::Blue);
//     square_2.setFillColor(sf::Color::Green);
//     bg.setFillColor(sf::Color(100, 100, 100, 100));

//     square.setPosition(200.0f, windowHeight - squareSize);
//     square_2.setPosition(700.0f, windowHeight - squareSize);

//     float moveSpeed = 50.0f;
//     float obstacleMoveSpeed = 100.0f;
//     float move = 0.0f;

//     sf::Clock clock;

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // Calculate time elapsed per frame
//         float deltaTime = clock.restart().asSeconds();

//         // Update player position based on user input and simple gravity
//         sf::Vector2f playerPos = square.getPosition();
//         sf::Vector2f obstaclePos = square_2.getPosition();

//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerPos.y >= 0.0f) {
//             square.move(0.0f, -moveSpeed * deltaTime);
//         } else if (playerPos.y < windowHeight - squareSize && 
//                    ((obstaclePos.x >= playerPos.x + squareSize) || (obstaclePos.x <= playerPos.x))) {
//             // Apply gravity when not at floor level or on obstacle
//             square.move(0.0f, moveSpeed * deltaTime);
//         }

//         // Move the background and obstacle
//         move -= moveSpeed * deltaTime;
//         square_2.setPosition(700.0f + move, windowHeight - squareSize);

//         // Reset the obstacle position if it goes off-screen
//         if (square_2.getPosition().x < -squareSize) {
//             move = windowWidth;  // Reset the move to reappear on the right side
//         }

//         // Rendering
//         window.clear();
//         drawBackground(window, bg, move, bgSqSize);
//         window.draw(square_2);
//         window.draw(square);
//         window.display();
//     }
//     return 0;
// }




































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

// cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -S /home/tparratt/Desktop/sfml -B /home/tparratt/Desktop/sfml/build

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
