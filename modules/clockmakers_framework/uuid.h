/* uuid.h */

#ifndef UUID_H
#define UUID_H

#include "core/object/class_db.h"
#include "core/variant/typed_array.h"

class UUID : public Object
{
	GDCLASS(UUID, Object);

protected:
	static const size_t uuid_size = 16;
	static const size_t uuid_string_size = 36;
	uint8_t *uuid;
	char *uuid_string;

	void _generate_uuid();
	void _update_uuid();
	void _update_uuid_string();

	static void _bind_methods();

public:
	char *get_uuid_string();
	char *get_uuid_string_const() const;
	void set_uuid_string(char *p_uuid_string);

	String get_uuid_string_bind();
	void set_uuid_string_bind(String p_uuid_string);

	uint8_t *get_uuid();
	uint8_t *get_uuid_const() const;
	void set_uuid(uint8_t *p_uuid);

	PackedByteArray get_uuid_bind();
	void set_uuid_bind(PackedByteArray p_uuid);

	UUID();
	UUID(const UUID &p_uuid);
	UUID(uint8_t *p_uuid);
	UUID(char *p_uuid_string);
	~UUID();
};

class Tracked
{
private:
	UUID uuid;

public:
	UUID get_uuid() const;
	UUID &get_uuid_m();
	void set_uuid(const UUID &p_uuid);

	Tracked();
	Tracked(const Tracked &p_tracked);
	~Tracked();
};

class TrackedObject : public Object
{
	GDCLASS(TrackedObject, Object);

private:
	UUID uuid;

protected:
	static void _bind_methods();

public:
	UUID get_uuid() const;
	UUID &get_uuid_m();
	void set_uuid(const UUID &p_uuid);

	TrackedObject();
	TrackedObject(const TrackedObject &p_tracked_object);
	~TrackedObject();
};

#endif
