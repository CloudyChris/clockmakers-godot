/* vector_hashmap_pair.cpp */

#include "vector_hashmap_pair.h"

template <typename TKey, typename TValue>
VectorHashMapPair<TKey, TValue>::VectorHashMapPair()
{
	CRASH_COND_MSG(!std::is_default_constructible_v<TValue>, "TValue type is not default constructible");
	CRASH_COND_MSG(!std::is_trivially_destructible_v<TValue>, "TValue type is not trivially destructible");
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
TValue *VectorHashMapPair<TKey, TValue>::get_one_const(TKey p_key) const
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
TValue *VectorHashMapPair<TKey, TValue>::get_one(TKey p_key)
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
bool VectorHashMapPair<TKey, TValue>::delete_one(TKey p_key)
{
	if (!values.cache.has(p_key))
	{
		ERR_PRINT_ED("Key does not exist");
		return false;
	}

	uint64_t values_index = values_cache.get(p_key);

	if (values_index > values.size())
	{
		ERR_PRINT_ED("Values cache index error");
		return false;
	}

	values_cache.erase(p_key);
	TValue *to_be_deleted = get_one(p_key);
	to_be_deleted->~TValue();
	values.remove_at(values_index);

	return true;
}

template <typename TKey, typename TValue>
HashMap<TKey, TValue *> VectorHashMapPair<TKey, TValue>::get_const(Vector<TKey> p_keys) const
{
	HashMap<TKey, TValue> r_pairs;
	if (!p_keys.is_empty())
	{
		for (TKey key : p_keys)
		{
			r_pairs.insert(key, get_one_const(key));
		}
	}
	else
	{
		for (KeyValue<TKey, uint64_t> kv : values_cache)
		{
			r_pairs.insert(kv.key, get_one_const(kv.key));
		}
	}
}

template <typename TKey, typename TValue>
HashMap<TKey, TValue *> VectorHashMapPair<TKey, TValue>::get(Vector<TKey> p_keys)
{
	HashMap<TKey, TValue> r_pairs;
	if (!p_keys.is_empty())
	{
		for (TKey key : p_keys)
		{
			r_pairs.insert(key, get_one(key));
		}
	}
	else
	{
		for (KeyValue<TKey, uint64_t> kv : values_cache)
		{
			r_pairs.insert(kv.key, get_one(kv.key));
		}
	}
}
