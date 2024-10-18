/* vector_hashmap_pair.cpp */

#include "vector_hashmap_pair.h"

template <typename TKey, typename TValue>
VectorHashMapPair<TKey, TValue>::VectorHashMapPair()
{
}

template <typename TKey, typename TValue>
VectorHashMapPair<TKey, TValue>::VectorHashMapPair(const VectorHashMapPair<TKey, TValue> &p_vhm_pair)
	: values(p_vhm_pair.values)
	, values_cache(p_vhm_pair.values_cache)
{
}

template <typename TKey, typename TValue>
VectorHashMapPair<TKey, TValue>::~VectorHashMapPair()
{
	values.clear();
	values_cache.clear();
}

template <typename TKey, typename TValue>
bool VectorHashMapPair<TKey, TValue>::has(TKey p_key) const
{
	return values_cache.has(p_key);
}

template <typename TKey, typename TValue>
TValue *VectorHashMapPair<TKey, TValue>::get_pointer_const(TKey p_key) const
{
	if (!values.cache.has(p_key))
	{
		ERR_PRINT_ED("Key does not exist");
		return nullptr;
	}

	uint64_t values_index = values_cache.get(p_key);

	if (values_index > values.size())
	{
		ERR_PRINT_ED("Values cache index error");
		return nullptr;
	}

	return &values.ptr()[values_index];
}

template <typename TKey, typename TValue>
TValue *VectorHashMapPair<TKey, TValue>::get_pointer(TKey p_key)
{
	if (!values.cache.has(p_key))
	{
		ERR_PRINT_ED("Key does not exist");
		return nullptr;
	}

	uint64_t values_index = values_cache.get(p_key);

	if (values_index > values.size())
	{
		ERR_PRINT_ED("Values cache index error");
		return nullptr;
	}

	return &values.ptrw()[values_index];
}

template <typename TKey, typename TValue>
TValue *VectorHashMapPair<TKey, TValue>::create_one(TKey p_key)
{
	uint64_t new_index = values.size();
	values.push_back(TValue());
	values_cache.insert(p_key, new_index);

	return &values.ptrw()[new_index];
}

template <typename TKey, typename TValue>
TValue VectorHashMapPair<TKey, TValue>::get_value(TKey p_key) const
{
	CRASH_COND_MSG(!values.cache.has(p_key), "Key does not exist");

	uint64_t values_index = values_cache.get(p_key);

	return values.get(values_index);
}

template <typename TKey, typename TValue>
TValue &VectorHashMapPair<TKey, TValue>::get_value_m(TKey p_key)
{
	CRASH_COND_MSG(!values.cache.has(p_key), "Key does not exist");

	uint64_t values_index = values_cache.get(p_key);

	return values.get_m(values_index);
}

template <typename TKey, typename TValue>
void VectorHashMapPair<TKey, TValue>::set_value(TKey p_key, const TValue &p_value)
{
	if (!values_cache.has(p_key))
	{
		int64_t new_index = values.size();
		values.push_back(p_value);
		values_cache.insert(p_key, new_index);
		return;
	}

	values.set(values_cache.get(p_key), p_value);
}

template <typename TKey, typename TValue>
HashMap<TKey, TValue *> VectorHashMapPair<TKey, TValue>::get_pointers_const(Vector<TKey> p_keys) const
{
	HashMap<TKey, TValue> r_pairs;
	if (!p_keys.is_empty())
	{
		for (TKey key : p_keys)
		{
			r_pairs.insert(key, get_pointer_const(key));
		}
	}
	else
	{
		for (KeyValue<TKey, uint64_t> kv : values_cache)
		{
			r_pairs.insert(kv.key, get_pointer_const(kv.key));
		}
	}
}

template <typename TKey, typename TValue>
HashMap<TKey, TValue *> VectorHashMapPair<TKey, TValue>::get_pointers(Vector<TKey> p_keys)
{
	HashMap<TKey, TValue> r_pairs;
	if (!p_keys.is_empty())
	{
		for (TKey key : p_keys)
		{
			r_pairs.insert(key, get_pointer(key));
		}
	}
	else
	{
		for (KeyValue<TKey, uint64_t> kv : values_cache)
		{
			r_pairs.insert(kv.key, get_pointer(kv.key));
		}
	}
}

template <typename TKey, typename TValue>
HashMap<TKey, TValue> VectorHashMapPair<TKey, TValue>::get_values(Vector<TKey> p_keys) const
{
	HashMap<TKey, TValue> r_pairs;
	if (!p_keys.is_empty())
	{
		for (TKey key : p_keys)
		{
			r_pairs.insert(key, get_value(key));
		}
	}
	else
	{
		for (KeyValue<TKey, uint64_t> kv : values_cache)
		{
			r_pairs.insert(kv.key, get_value(kv.key));
		}
	}

	return r_pairs;
}

template <typename TKey, typename TValue>
void VectorHashMapPair<TKey, TValue>::set_values(HashMap<TKey, TValue> p_pairs)
{
	for (KeyValue<TKey, TValue> kv : p_pairs)
	{
		set_value(kv.key, kv.value);
	}
}
