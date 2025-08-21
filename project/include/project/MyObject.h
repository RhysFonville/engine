#include "engine/AssetManager/ObjectReflection/ReflectionMacro.h"
#include "engine/Object/Object.h"

class MyObject : public Object {
public:
	BEGIN_CLASS(MyObject);

	static std::expected<MyObject, Error> init() noexcept;
	
private:
	MyObject(Object&& obj) : Object{std::move(obj)} { }

	PROPERTY(int, x);
};

