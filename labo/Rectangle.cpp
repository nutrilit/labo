
#include "GameObject.cpp"
class Rectangle : public ShapeObject {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle." << std::endl;
    }

    void translate(float x, float y) override {
        std::cout << "Translating the rectangle by (" << x << ", " << y << ")." << std::endl;
    }

    void rotate(float angle) override {
        std::cout << "Rotating the rectangle by " << angle << " degrees." << std::endl;
    }

    void scale(float factor) override {
        std::cout << "Scaling the rectangle by a factor of " << factor << "." << std::endl;
    }
};
