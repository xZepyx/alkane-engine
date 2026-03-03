#pragma  once 

#include <vector>
#include <memory>
#include "renderer/renderable.hpp"

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    // Disable copy
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    // Allow move
    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = default;

    template<typename T, typename... Args>
    T& create(Args&&... args) {
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *obj;
        objects.push_back(std::move(obj));
        return ref;
    }

    void render(Renderer& renderer) const {
        for (const auto& obj : objects)
            obj->render(renderer);
    }

private:
    std::vector<std::unique_ptr<Renderable>> objects;
};