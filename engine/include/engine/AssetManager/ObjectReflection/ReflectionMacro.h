#define BEGIN_CLASS(class_name) \
public: \
	using ClassType = class_name; \
	static std::vector<Property>& static_properties() { \
		static std::vector<Property> properties; \
		return properties; \
	} \
	const std::vector<Property>& get_properties() const override { \
		return static_properties(); \
	} \
	static ObjectRegistrar<class_name> registrar; \
private:

#define END_CLASS(class_name) \
ObjectRegistrar<class_name> class_name::registrar{#class_name};

#define PROPERTY(type, name, pointer) \
	type name{}; \
	struct AutoRegister_##name { \
		AutoRegister_##name(type) { \
			ClassType::static_properties().push_back({#name, #type, pointer}); \
		} \
	} auto_register_##name{&name};
