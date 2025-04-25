#ifndef ENEMY_H
#define ENEMY_H

#include "entities/MovingEntities.h"

class Enemy : public MovingEntity
{
public:
    Enemy(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
    void moveTo(const int x, const int y);
    void moveToCell(std::pair<int, int> pathToCell);
    bool isMovingToCell() const;
    // bool canAttack() const;
    int getAttackRadius() const;
    virtual void update(const int delta) override;
    void generateNewPath();

private:
    /**
     * @brief update movement of enemy
     *
     * @param delta - time in milliseconds
     */
    void updateMovement(const int delta);

    // movement
    int newX = 0;      // position X to move
    int newY = 0;      // position Y to move
    bool movingToCell = false; // is moving to cell
    std::pair<int, int> path;  // diff of cells to move
    // consts
    const float baseSpeed = 0.002f;   // speed of enemy
    // const float attackSpeed = 0.0025f; // speed of attack enemy
    // const int attackRadius = 4;        // attack radius (in cells)
    std::shared_ptr<Animation> movement; // movement animation
    std::shared_ptr<Animation> death;
};


#endif // ENEMY_H