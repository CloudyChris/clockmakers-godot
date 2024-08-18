/* tracked_resource.h */

#ifndef TRACKED_RESOURCE_H
#define TRACKED_RESOURCE_H

#include "core/io/resource.h"
#include "core/variant/variant.h"

class TrackedResource : public Resource
{
	GDCLASS(TrackedResource, Resource);

	struct UUID
	{
		String human_readable;
		PackedByteArray uuid;

		void _generate_uuid();
		void _update_uuid_string();

		UUID();
		~UUID();
	};

	UUID uuid;

protected:
	static void _bind_methods();

public:
	String get_human_readable_uuid();
	void set_human_readable_uuid(String p_uuid_string);

	PackedByteArray get_uuid();
	void set_uuid(PackedByteArray p_uuid);

	TrackedResource();
};

#endif
