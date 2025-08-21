#include "engine/Object/Object.h"
#include "defines.h"

class PROJECT_API MyObject : public Object {
public:
	BEGIN_CLASS(MyObject);

	static std::expected<MyObject, Error> init() noexcept;
	
private:
	MyObject(Object&& obj) : Object{std::move(obj)} { }

	PROPERTY(int, x);
};

BEGIN_DEFS(MyObject);
