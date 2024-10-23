/* cm_enums.h */

#ifndef CM_ENUMS_H
#define CM_ENUMS_H

#pragma region godot_includes
#include "core/string/ustring.h"
#include "core/typedefs.h"
#pragma endregion godot_includes

#undef DECL_ENUM_ELEMENT
#undef BEGIN_ENUM
#undef END_ENUM

#ifndef GENERATE_ENUM_STRINGS
    #define DECL_ENUM_ELEMENT( element ) element
    #define BEGIN_ENUM( ENUM_NAME ) typedef enum tag##ENUM_NAME
    #define END_ENUM( ENUM_NAME ) ENUM_NAME; \
            char* get_string_##ENUM_NAME(enum tag##ENUM_NAME index);
#else
    #define DECL_ENUM_ELEMENT( element ) #element
    #define BEGIN_ENUM( ENUM_NAME ) char* gs_##ENUM_NAME [] =
    #define END_ENUM( ENUM_NAME ) ; char* get_string_##ENUM_NAME(enum \
            tag##ENUM_NAME index){ return gs_##ENUM_NAME [index]; }
#endif

namespace cm_enums
{

BEGIN_ENUM(CM_DataChannel)
{
	DECL_ENUM_ELEMENT(CM_DATA_CHANNEL_NONE),
	DECL_ENUM_ELEMENT(CM_DATA_CHANNEL_CORE),
	DECL_ENUM_ELEMENT(CM_DATA_CHANNEL_USER),
	DECL_ENUM_ELEMENT(CM_DATA_CHANNEL_TOOLS)
}
END_ENUM(CM_DataChannel);

} // namespace cm_enums

#endif
