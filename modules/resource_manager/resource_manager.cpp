/* resource_manager.cpp */

#include "resource_manager.h"
#include "core/io/resource.h"

////////////////////////////////////////////////////////
// ResourceManager

ResourceManager::CreateFunc ResourceManager::create_func = nullptr;

void ResourceManager::_bind_methods(){

};

ResourceManager *ResourceManager::singleton = nullptr;

ResourceManager *ResourceManager::get_singleton() {
	return singleton;
};

ResourceManager::ResourceManager() {
	singleton = this;
};

ResourceManager::~ResourceManager() {
	singleton = nullptr;
};
