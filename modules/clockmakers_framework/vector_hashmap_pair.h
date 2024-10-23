/* vector_hashmap_pair.h */

#ifndef VECTOR_HASHMAP_PAIR_H
#define VECTOR_HASHMAP_PAIR_H

#include "core/templates/hash_map.h"
#include "core/variant/typed_array.h"

// Crashes if TValue is not default constructible and trivially destructible
template <typename TKey, typename TValue>
class VectorHashMapPair
{
private:
	Vector<TValue> values;
	HashMap<TKey, uint64_t> values_cache;

public:
	bool is_empty() const;

	bool has(TKey p_key) const;

	TValue *get_one_const(TKey p_key) const;
	TValue *get_one(TKey p_key);
	TValue *create_one(TKey p_key);
	bool delete_one(TKey p_key);

	HashMap<TKey, TValue *> get_const(Vector<TKey> p_keys = Vector<TKey>()) const;
	HashMap<TKey, TValue *> get(Vector<TKey> p_keys = Vector<TKey>());

	VectorHashMapPair();
	VectorHashMapPair(const VectorHashMapPair<TKey, TValue> &p_vhm_pair);
	~VectorHashMapPair();
};

#endif // VECTOR_HASHMAP_PAIR_H
