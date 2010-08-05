//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlPair.h
//    Author:      Streamlet
//    Create Time: 2010-08-05
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLPAIR_H_E7935E32_4626_4FB9_B582_4D3DA2D9CF69_INCLUDED__
#define __XLPAIR_H_E7935E32_4626_4FB9_B582_4D3DA2D9CF69_INCLUDED__

namespace xl
{
	template <typename K, typename V>
	class Pair
	{
	public:
		K Key;
		V Value;

	public:
		Pair();
		Pair(const K &key);
		Pair(const K &key, const V &value);

	public:
		bool operator == (const Pair &that) const;
		bool operator != (const Pair &that) const;
		bool operator < (const Pair &that) const;
		bool operator > (const Pair &that) const;
		bool operator <= (const Pair &that) const;
		bool operator >= (const Pair &that) const;
	};

	template <typename K, typename V>
	Pair<K, V>::Pair()
	{

	}

	template <typename K, typename V>
	Pair<K, V>::Pair(const K &key)
		: Key(key)
	{

	}

	template <typename K, typename V>
	Pair<K, V>::Pair(const K &key, const V &value)
		: Key(key), Value(value)
	{

	}

	template <typename K, typename V>
	bool Pair<K, V>::operator == (const Pair &that) const
	{
		return this->Key == that.Key;
	}

	template <typename K, typename V>
	bool Pair<K, V>::operator != (const Pair &that) const
	{
		return this->Key != that.Key;
	}

	template <typename K, typename V>
	bool Pair<K, V>::operator < (const Pair &that) const
	{
		return this->Key < that.Key;
	}

	template <typename K, typename V>
	bool Pair<K, V>::operator > (const Pair &that) const
	{
		return this->Key > that.Key;
	}

	template <typename K, typename V>
	bool Pair<K, V>::operator <= (const Pair &that) const
	{
		return this->Key <= that.Key;
	}

	template <typename K, typename V>
	bool Pair<K, V>::operator >= (const Pair &that) const
	{
		return this->Key >= that.Key;
	}

} // namespace xl

#endif // #ifndef __XLPAIR_H_E7935E32_4626_4FB9_B582_4D3DA2D9CF69_INCLUDED__
