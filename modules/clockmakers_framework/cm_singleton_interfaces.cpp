/* cm_singleton_specifications. */

#include "cm_singleton_interfaces.h"

namespace cm_singleton_interfaces
{

void GameDataManager::_bind_methods()
{
	BIND_ENUM_CONSTANT(CM_DATA_TYPE_CORE);
	BIND_ENUM_CONSTANT(CM_DATA_TYPE_USER);
	BIND_ENUM_CONSTANT(CM_DATA_TYPE_TOOLS);
}

} // namespace cm_singleton_interfaces
