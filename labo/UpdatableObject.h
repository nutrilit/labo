#pragma once
#pragma once
#ifndef UPDATEABLEOBJECT_H
#define UPDATEABLEOBJECT_H

class UpdatableObject {
public:
    virtual void update() = 0;  // Czysto wirtualna metoda update()
    virtual ~UpdatableObject() {}  // Wirtualny destruktor
};

#endif
