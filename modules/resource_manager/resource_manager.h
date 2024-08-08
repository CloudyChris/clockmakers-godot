/* resource_manager.h */

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"
#include "core/os/thread_safe.h"
#include "core/templates/rid.h"
#include "core/variant/variant.h"

class ResourceManager : public Object {
	GDCLASS(ResourceManager, Object);

public:
	ResourceManager();
	~ResourceManager();
};

#endif // RESOURCE_MANAGER_H
