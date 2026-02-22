# Collisions

* If things can move, they will eventually hit something.
* You might need collisions then

The physics module provides simple AABB collision detection and resolution.

First include the required headers.

```
#include <alkane/physics/collisions.hpp>
```

---

### Collision Types

Two collision modes are supported.

```
CollisionType::Dynamic
CollisionType::Static
```

Behavior:

* Static → moving body against world geometry (platforms, walls)
* Dynamic → two moving bodies collide and share correction

---

### Checking Collision

You can check if two bodies overlap.

```
physics::checkCollision(a, b);
```

This uses AABB (axis‑aligned bounding box) collision.

Example:

```
if (physics::checkCollision(player, wall)) {
    // they overlap
}
```

Note that if you have sprite or some other body except 'the physics body'
call the resolve and check collision function like:

```cpp
physics::checkCollision(sprite.body, sprite.body);
physics::checkCollision(sprite.body, otherBody);
// Same goes for resolve collisions
```

---

### Resolving Collision

Detection tells you that something is wrong.
Resolution fixes it.

```
physics::resolveCollision(a, b, CollisionType::Static);
```

What it does:

* Computes overlap
* Finds collision normal
* Applies positional correction
* Applies velocity response (for dynamic bodies)

Example (player vs world):

```
physics::resolveCollision(player, wall, CollisionType::Static);
```

Example (entity vs entity):

```
physics::resolveCollision(a, b, CollisionType::Dynamic);
```

---

### How Resolution Works

The resolver performs:

* Minimum axis separation
* Static correction (push out)
* Dynamic split correction
* Basic impulse response
* Velocity cancellation on static collisions

It assumes equal mass and is designed for simple gameplay physics.

Meaning: predictable > realistic.

---

### Important Notes

> [!NOTE]
> Collision uses AABB from Body::getAABB().

> [!NOTE]
> Static collisions zero velocity along the collision normal.

> [!NOTE]
> Dynamic collisions apply a small impulse with low restitution.

---

After this your objects should stop going through walls.

If they still do — congratulations, you discovered tunneling.