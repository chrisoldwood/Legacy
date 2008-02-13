/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMAP.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The TMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_TMAP_HPP
#define WCL_TMAP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Legacy/Map.hpp>

/******************************************************************************
** 
** This is a template version of the CMap class.
**
*******************************************************************************
*/

template<class K, class V> class TMap : public CMap
{
public:
	//
	// Constructors/Destructor.
	//
	TMap();
	~TMap();
	
	//
	// Methods.
	//
	void  Add(K Key, V Value);
	void  Remove(K Key);
	bool  Find(K Key, V& Value) const;
	V     Find(K Key) const;
	bool  Exists(K Key) const;
};

/******************************************************************************
** 
** This is the class used for items stored in the map.
**
*******************************************************************************
*/

template<class K, class V> class TMapItem : public CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	TMapItem(K Key);
	TMapItem(K Key, V Value);
	virtual ~TMapItem();

	//
	// Methods.
	//
	virtual uint Key() const;
	virtual bool operator==(const CMapItem& rRHS) const;

	//
	// Members.
	//
	K	m_Key;
	V	m_Value;
};

/******************************************************************************
** 
** Map hashing functions.
**
*******************************************************************************
*/

template<class K> inline uint HashKey(K Key)
{
	return reinterpret_cast<uint>(Key);
}

template<> inline uint HashKey<CString>(CString Key)
{
	uint nValue  = 0;

	for (const tchar* pChar = Key; *pChar != TXT('\0'); ++pChar)
		nValue = (nValue * 17) | *pChar;

	return nValue;
}

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

template<class K, class V> inline TMap<K, V>::TMap()
{
}

template<class K, class V> inline TMap<K, V>::~TMap()
{
}

template<class K, class V> inline void TMap<K, V>::Add(K Key, V Value)
{
	CMap::Add(*(new TMapItem<K, V>(Key, Value)));
}

template<class K, class V> inline void TMap<K, V>::Remove(K Key)
{
	CMap::Remove(TMapItem<K, V>(Key));
}

template<class K, class V> inline bool TMap<K, V>::Find(K Key, V& Value) const
{
	TMapItem<K, V>* pItem = static_cast<TMapItem<K, V>*>(CMap::Find(TMapItem<K, V>(Key)));

	if (pItem != NULL)
		Value = pItem->m_Value;

	return (pItem != NULL);
}

template<class K, class V> inline V TMap<K, V>::Find(K Key) const
{
	TMapItem<K, V>* pItem = static_cast<TMapItem<K, V>*>(CMap::Find(TMapItem<K, V>(Key)));

	ASSERT(pItem != NULL);

	return pItem->m_Value;
}

template<class K, class V> inline bool TMap<K, V>::Exists(K Key) const
{
	return CMap::Exists(TMapItem<K, V>(Key));
}

template<class K, class V> inline TMapItem<K, V>::TMapItem(K Key)
	: m_Key(Key)
{
}

template<class K, class V> inline TMapItem<K, V>::TMapItem(K Key, V Value)
	: m_Key(Key)
	, m_Value(Value)
{
}

template<class K, class V> inline TMapItem<K, V>::~TMapItem()
{
}

template<class K, class V> inline uint TMapItem<K, V>::Key() const
{
	return HashKey(m_Key);
}

template<class K, class V> inline bool TMapItem<K, V>::operator==(const CMapItem& rRHS) const
{
	const TMapItem<K, V>* pRHS = static_cast<const TMapItem<K, V>*>(&rRHS);

	return (m_Key == pRHS->m_Key);
}

#endif // WCL_TMAP_HPP
