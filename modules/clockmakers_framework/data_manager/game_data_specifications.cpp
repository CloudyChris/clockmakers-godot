/* game_data_specifications.cpp */

#include "game_data_specifications.h"
#include "core/object/object.h"

FieldSpecification::FieldSpecification()
{
}

FieldSpecification::~FieldSpecification()
{
}

TableSpecification::TableSpecification()
{
}

TableSpecification::~TableSpecification()
{
	fields.~VectorHashMapPair();
}
