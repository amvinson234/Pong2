#ifndef VISIBLEGAMEOBJECT_H_INCLUDED
#define VISIBLEGAMEOBJECT_H_INCLUDED

#include<string>
#include"SFML/Graphics.hpp"

class VisibleGameObject
{
public:
    VisibleGameObject();

    //note following virtual keywords. my understanding is that this allows the derived class functions to overide the base class functions here when we have a base class pointer to a derived class object
    virtual ~VisibleGameObject();

    virtual void Load(std::string filename);
    virtual void Draw(sf::RenderWindow & window);
    virtual void Update(float elapsedTime);

    virtual std::string GetFilename();

    virtual float GetWidth() const;
    virtual float GetHeight() const;
    virtual sf::FloatRect GetBoundingRect() const;

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual bool IsLoaded() const;

    virtual void setAsLoaded();

protected:
    sf::Sprite& GetSprite();

private:
    sf::Sprite _sprite;
    sf::Texture _image;
    std::string _filename;
    bool _isLoaded;
};


#endif // VISIBLEGAMEOBJECT_H_INCLUDED
