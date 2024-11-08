#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Square // Maybe this should be called ShapeLimits ?
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

// obstacle cycle
// more obstacles (with map?)
// jump on one press
// refactor
// classes?
// resource manager //assets

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
    //window.draw(square_3);
}

float    horiz_move(Square player, Square obstacle, float moveSpeed, float move, float deltaTime)
{
    if ((obstacle.getLeft() > player.getRight()))
        move -= moveSpeed * deltaTime;
    else if ((player.getRight() >= obstacle.getLeft()) && (player.getLeft() <= obstacle.getRight()))
    {
        if (player.getBottom() <= obstacle.getTop() + 1)
            move -= moveSpeed * deltaTime;
        else if (player.getBottom() <= obstacle.getTop())
            move -= moveSpeed * deltaTime;
    }
    else
        move -= moveSpeed * deltaTime;
    return (move);
}

void    vert_move(Square player, Square obstacle, float moveSpeed, float move, float deltaTime, float windowHeight, sf::RectangleShape& square)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getTop() >= 0.0f)
    {
        square.move(0.0f, -moveSpeed * deltaTime);
        // square.setOrigin(20.0f, 20.0f); ROTATION TO LOOK AT LATER
        // square.rotate(10.0f);
    }
    else if ((player.getRight() <= obstacle.getLeft() + 1) || (player.getLeft() >= obstacle.getRight()))
    {
        if (player.getBottom() < windowHeight)
            square.move(0.0f, moveSpeed * deltaTime);
    }
    else if (player.getBottom() < obstacle.getTop())
        square.move(0.0f, moveSpeed * deltaTime);
}

// sf::Text set_text(sf::Font& font, sf::RenderWindow& window)
// {
//     sf::Text    text;
//     text.setFont(font);
//     text.setString("HELLO WORLD");
//     text.setCharacterSize(50);
//     text.setFillColor(sf::Color::Red);
//     //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
//     return (text);
// }

// sf::Font load_font(sf::RenderWindow& window)
// {
//     sf::Font    font;
//     if (!font.loadFromFile("/usr/share/fonts/truetype/crosextra/Caladea-Regular.ttf"))
//     {
//         std::cout << "Font loading error" << std::endl;
//     }
//     std::cout << "Font loaded" << std::endl;
//     set_text(font, window);
//     return (font);
// }

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
    sf::RectangleShape  square_2(sf::Vector2f(squareSize * 2, squareSize * 2));
    //sf::RectangleShape  square_3(sf::Vector2f(squareSize, squareSize));
    sf::RectangleShape  bg(sf::Vector2f(bgSqSize, bgSqSize));
    square.setFillColor(sf::Color::Red);
    //square_2.setFillColor(sf::Color::Green);
    //square_3.setFillColor(sf::Color::Blue);
    bg.setFillColor(sf::Color(100, 100, 100, 100));

    square.setPosition(windowWidth / 4, windowHeight - squareSize);
    square_2.setPosition(windowWidth / 2, windowHeight - squareSize * 2);
    //square_3.setPosition(1500.0f, windowHeight - squareSize);

    float moveSpeed = 200.0f;
    static float move;

    //sf::Font    font = load_font(window);

    sf::Clock   clock;

    sf::Texture texture;
    if (!texture.loadFromFile("../../assets/CRATE_1A.PNG"))
    {
        std::cout << "Texture loading error" << std::endl;
    }
    sf::Sprite  sprite;
    square_2.setTexture(&texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.key.scancode == sf::Keyboard::Scan::Escape)
                window.close();
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        sf::Vector2f    playerPos = square.getPosition();
        sf::Vector2f    obstaclePos = square_2.getPosition();

        Square  player(playerPos, squareSize);
        Square  obstacle(obstaclePos, squareSize * 2);

        // UP AND DOWN
        vert_move(player, obstacle, moveSpeed, move, deltaTime, windowHeight, square);  
        move = horiz_move(player, obstacle, moveSpeed, move, deltaTime);

        square_2.setPosition(windowWidth / 2 + move, windowHeight - squareSize * 2); // this works but then another obstaacle doesn't come
        //square_2.move(-moveSpeed * deltaTime, 0.0f); // this works but then collision doesn't work
        if (obstacle.getRight() < 0)
            square_2.setPosition(windowWidth, windowHeight - squareSize * 2);

        //square_3.setPosition(1500.0f + move, windowHeight - squareSize);

        window.clear();

        drawBackground(window, bg, square_2, square, move);
        window.draw(square);
        // sf::Text text = set_text(font, window);
        // text.move(windowWidth - 500.0f, 0.0f);
        // window.draw(text);
    
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
