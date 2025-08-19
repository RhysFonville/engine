#include "engine/Object/Object.h"
#include "defines.h"

class PROJECT_API MyObject : public Object {
public:
	BEGIN_CLASS(MyObject);

	static std::expected<MyObject, Error> init() noexcept;
	
private:
	MyObject() : Object{} { }

	PROPERTY(int, x);
};

BEGIN_DEFS(MyObject);
