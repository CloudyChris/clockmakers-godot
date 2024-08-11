/* resource_db.cpp */

#include "resource_db.h"

#include "core/object/class_db.h"
#include "core/object/object.h"

TrackedResource::TrackedResource() {}

TrackedResource::TrackedResource(const TrackedResource &p_tracked)
		: uuid(p_tracked.get_uuid())
{
	uuid._set_uuid(p_tracked.get_uuid());
}

const UUID &TrackedResource::get_uuid() const
{
	return uuid;
};

void TrackedResource::set_uuid(const UUID &p_uuid)
{
	uuid.set_uuid(p_uuid._get_uuid());
}

void TrackedResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &TrackedResource::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid", "uuid"), &TrackedResource::set_uuid);

	ADD_GROUP("Tracked Resource", "tracked_resource_");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tracked_resource_uuid"), "set_uuid", "get_uuid");
}

GameResourceInterface::GameResourceInterface()
{
	fields.clear();
	indices.clear();
}

GameResourceInterface::GameResourceInterface(const GameResourceInterface &p_interface)
{
	fields.append_array(p_interface.fields);
	indices = p_interface.indices;
}

const GameResourceInterface::FieldData *GameResourceInterface::get_field(const String &p_name) const
{
	if (!indices.has(p_name))
	{
		return nullptr;
	}

	const uint32_t m_index = indices.get(p_name);
	const uint32_t m_size = fields.size();

	if (unlikely((m_index) < 0 || (m_index) >= (m_size)))
	{
		return nullptr;
	}

	return &fields.get(indices.get(p_name));
}

void GameResourceInterface::set_field(const String &p_name, const FieldData &p_data)
{
	if (indices.has(p_name))
	{
		const uint32_t m_index = indices.get(p_name);
		const uint32_t m_size = fields.size();

		if (likely((m_index) >= 0 && (m_index) < (m_size)))
		{
			fields.set(indices[p_name], p_data);
			return;
		}
	}

	fields.push_back(p_data);
	indices[p_name] = fields.size() - 1;
}
