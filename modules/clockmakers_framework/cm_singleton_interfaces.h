/* cm_singleton_interfaces.h */

#ifndef CM_SINGLETON_INTERFACES_H
#define CM_SINGLETON_INTERFACES_H

#pragma region godot_includes
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/binder_common.h"
#include "core/variant/typed_array.h"
#pragma endregion godot_includes

#pragma region cm_includes
#include "data_manager/game_data_manager.h"
#pragma endregion cm_includes

namespace cm_singleton_interfaces
{

class GameDataManager : public Object
{
	GDCLASS(GameDataManager, Object);

public:
	enum DataType
	{
		CM_DATA_TYPE_NONE,
		CM_DATA_TYPE_CORE,
		CM_DATA_TYPE_USER,
		CM_DATA_TYPE_TOOLS
	};

protected:
	static void _bind_methods();
	static GameDataManager *singleton;

public:
	static GameDataManager *get_singleton() { return singleton; };

	GameDataManager() { singleton = this; };
};

} // namespace cm_singleton_interfaces

VARIANT_ENUM_CAST(cm_singleton_interfaces::GameDataManager::DataType);

#endif // CM_SINGLETON_INTERFACES_H
