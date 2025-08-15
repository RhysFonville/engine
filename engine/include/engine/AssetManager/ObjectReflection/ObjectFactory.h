#pragma once

#include <functional>
#include <memory>
#include "engine/Object/Object.h"

class ObjectFactory {
public:
    using CreateFn = std::function<std::unique_ptr<Object>()>;

    static ObjectFactory& instance() {
        static ObjectFactory inst;
        return inst;
    }

    void register_type(const std::string& name, CreateFn fn) {
        registry[name] = std::move(fn);
    }

    std::unique_ptr<Object> create(const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, CreateFn> registry;
};

template<typename T>
struct ObjectRegistrar {
    ObjectRegistrar(const char* name) {
        ObjectFactory::instance().register_type(name, []() { return std::make_unique<T>(); });
    }
};
