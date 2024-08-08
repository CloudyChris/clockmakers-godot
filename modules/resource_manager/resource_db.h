/* resource_db.h */

#include "core/io/resource.h"
#include "core/templates/hash_map.h"

#include "modules/gdscript/language_server/godot_lsp.h"
#include "modules/uuid/uuid.h"

class TrackedResource : public Resource {
	GDCLASS(TrackedResource, Resource);

protected:
	UUID uuid;

	static void _bind_methods();

public:
	const UUID &get_uuid() const { return uuid; };

	TrackedResource();
	~TrackedResource();
};

class FieldData {
public:
	uint64_t field_size;
};

class GameResourceInterface : public TrackedResource {
	GDCLASS(GameResourceInterface, TrackedResource);

protected:
	HashMap<String, FieldData> fields;
};

class GameResource : public TrackedResource {
	GDCLASS(GameResource, TrackedResource);

public:
	GameResource();
	~GameResource();
};

template <typename GR>
class ResourceDB : public GameResource {
	GDCLASS(ResourceDB, GameResource);

public:
	ResourceDB();
	~ResourceDB();

private:
	HashMap<UUID, Vector<TrackedResource>> resources;
};
