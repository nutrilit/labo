#pragma once
#include <iostream>

// (a) Klasa GameObject
class GameObject {
public:
    virtual ~GameObject() {}

    // Metody czysto wirtualne
    virtual void update() = 0;
    virtual void draw() const = 0;

    // Metoda z cia³em (mo¿e byæ nadpisana)
    virtual void start() {
        std::cout << "GameObject started." << std::endl;
    }
};

// (b) Klasa UpdatableObject
class UpdatableObject {
public:
    virtual ~UpdatableObject() {}

    // Abstrakcyjna metoda update()
    virtual void update() = 0;
};

// (c) Klasa DrawableObject
class DrawableObject {
public:
    virtual ~DrawableObject() {}

    // Abstrakcyjna metoda draw()
    virtual void draw() const = 0;
};

// (d) Klasa TransformableObject
class TransformableObject {
public:
    virtual ~TransformableObject() {}

    // Abstrakcyjne metody translate(), rotate() i scale()
    virtual void translate(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(float factor) = 0;
};

// (e) Klasa ShapeObject
class ShapeObject : public DrawableObject, public TransformableObject {
public:
    virtual ~ShapeObject() {}

    // Dziedziczone metody z DrawableObject i TransformableObject
    // Metody te s¹ abstrakcyjne, wiêc musz¹ byæ nadpisane przez klasy pochodne
};
