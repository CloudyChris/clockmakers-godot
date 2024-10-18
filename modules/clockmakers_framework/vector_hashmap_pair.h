/* vector_hashmap_pair.h */

#ifndef VECTOR_HASHMAP_PAIR_H
#define VECTOR_HASHMAP_PAIR_H

#include "core/templates/hash_map.h"
#include "core/variant/typed_array.h"

// !IMPORTANT! Only supports TValue types with a default constructor
template <typename TKey, typename TValue>
class VectorHashMapPair
{
private:
	Vector<TValue> values;
	HashMap<TKey, uint64_t> values_cache;

public:
	bool has(TKey p_key) const;

	TValue *get_pointer_const(TKey p_key) const;
	TValue *get_pointer(TKey p_key);
	TValue *create_one(TKey p_key);

	TValue get_value(TKey p_key) const;
	TValue &get_value_m(TKey p_key);
	void set_value(TKey p_key, const TValue &p_value);

	HashMap<TKey, TValue *> get_pointers_const(Vector<TKey> p_keys) const;
	HashMap<TKey, TValue *> get_pointers(Vector<TKey> p_keys);

	HashMap<TKey, TValue> get_values(Vector<TKey> p_keys) const;
	void set_values(HashMap<TKey, TValue> p_pairs);

	VectorHashMapPair();
	VectorHashMapPair(const VectorHashMapPair<TKey, TValue> &p_vhm_pair);
	~VectorHashMapPair();
};

#endif // VECTOR_HASHMAP_PAIR_H
