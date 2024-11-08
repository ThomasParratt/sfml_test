#ifndef SQUARE_HPP
# define SQUARE_HPP

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
        //Square() {}
        //Square(const Square& obj);
        Square(sf::Vector2f position, float squareSize)
        {
            this->top = position.y;
            this->bottom = position.y + squareSize;
            this->left = position.x;
            this->right = position.x + squareSize;
        }
        //~Square();
        //Square&  operator=(const Square& obj);
        // std::string     getName() const;
        // int             getGrade() const;
        float   getTop() const {return this->top;}
        float   getBottom() const {return this->bottom;}
        float   getLeft() const {return this->left;}
        float   getRight() const {return this->right;}
};

#endif