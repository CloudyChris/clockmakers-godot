/* game_data_specifications.cpp */

#include "game_data_specifications.h"
#include "core/object/object.h"
#include "modules/clockmakers_framework/cm_enums.h"

FieldSpecification::FieldSpecification()
{
}

FieldSpecification::~FieldSpecification()
{
}

Dictionary FieldSpecification::to_dict() const
{
	// TODO
}

void FieldSpecification::from_dict(Dictionary p_dict)
{
	// TODO
}

String FieldSpecification::to_json(uint8_t p_indent) const
{
	String ending = ",\n";
	String ending_string = "\",\n";
	String indent = "";
	String tab = "    ";

	for (int i = 0; i < p_indent * 4; i++)
	{
		indent += " ";
	}

	String json_string = indent + "{\n";

	// name
	json_string += indent + tab + "name: \"" + name + ending_string;

	// is_reference
	json_string += indent + tab + "is_reference: " + String(is_reference ? "true" : "false") + ending;

	// ref_table_name
	json_string += indent + tab + "ref_table_name: \"" + ref_table_name + ending_string;

	// ref_channel
	json_string += indent + tab + "ref_channel: \"" + String(cm_enums::get_string_CM_DataChannel(ref_channel)) + ending_string;

	// property_info
	json_string += indent + tab + "property_info: {\n";
	json_string += indent + tab + tab + "type: " + itos(info.type) + ending;
	json_string += indent + tab + tab + "name: \"" + info.name + ending_string;
	json_string += indent + tab + tab + "class_name: \"" + info.class_name + ending_string;
	json_string += indent + tab + tab + "hint: " + itos(info.hint) + ending;
	json_string += indent + tab + tab + "hint_string: \"" + info.hint_string + ending_string;
	json_string += indent + tab + tab + "usage: " + itos(info.usage) + "\n";
	json_string += indent + tab + "}\n";
	json_string += indent + "}";

	return json_string;
}

void FieldSpecification::from_json(JSON p_json)
{
	// TODO
}

TableSpecification::TableSpecification()
{
}

TableSpecification::~TableSpecification()
{
	fields.~VectorHashMapPair();
}

Dictionary TableSpecification::to_dict() const
{
	// TODO
}

void TableSpecification::from_dict(Dictionary p_dict)
{
	// TODO
}

String TableSpecification::to_json(uint8_t p_indent) const
{
	// TODO
	String ending = ",\n";
	String ending_string = "\",\n";
	String indent = "";
	String tab = "    ";

	for (int i = 0; i < p_indent * 4; i++)
	{
		indent += " ";
	}

	String json_string = "{\n";

	// name
	json_string += indent + tab + "name: \"" + name + ending_string;

	// path
	json_string += indent + tab + "path: \"" + path + ending_string;

	// channel
	json_string += indent + tab + "channel: \"" + String(cm_enums::get_string_CM_DataChannel(channel)) + ending_string;

	// fields
	json_string += indent + tab + "fields: [";

	if (fields.is_empty())
	{
		json_string += "]" + ending;
	}
	else
	{
		json_string += "\n";

		HashMap<String, FieldSpecification *> l_fields = fields.get_const();

		int count_processed = 0;

		for (KeyValue<String, FieldSpecification *> kv : l_fields)
		{
			json_string += kv.value->to_json(p_indent + 2);
			count_processed++;

			json_string += (count_processed < l_fields.size() ? ending : "\n");
		}
	}

	json_string += indent + tab + "]\n";

	json_string += indent + "}";

	return json_string;
}
