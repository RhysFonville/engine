#include "engine/AssetManager/ObjectReflection/ReflectionMacro.h"
#include "engine/Object/Object.h"

class MyObject : public Object {
public:
	BEGIN_CLASS(MyObject);

	static std::expected<MyObject, Error> init() noexcept;
	
private:
	MyObject() : Object{} { }

	PROPERTY(int, x);
};

