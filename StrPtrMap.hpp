/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRPTRMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CStrPtrMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STRPTRMAP_HPP
#define STRPTRMAP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Map.hpp"

/******************************************************************************
** 
** This is the base class used for items stored in a str->ptr map collection.
**
*******************************************************************************
*/

class CStrPtrMapItem : public CMapItem
{
public:
	//
	// Constructors/Destructor.
	//
	CStrPtrMapItem(const CString& strKey, void* pObject);
	virtual ~CStrPtrMapItem();

	//
	// Methods.
	//
	virtual uint Key() const;
	virtual bool operator==(const CMapItem& rRHS) const;

	//
	// Members.
	//
	CString	m_strKey;
	void*	m_pObject;
};

/******************************************************************************
** 
** This is the map used to link strings to objects.
**
*******************************************************************************
*/

class CStrPtrMap : public CMap
{
public:
	//
	// Constructors/Destructor.
	//
	CStrPtrMap();
	~CStrPtrMap();

	//
	// Methods.
	//
	void  Add(const CString& strKey, void* pObject);
	void  Remove(const CString& strKey);
	void* Find(const CString& strKey) const;

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CStrPtrMap::CStrPtrMap()
	: CMap()
{
}

inline CStrPtrMap::~CStrPtrMap()
{
}

inline void CStrPtrMap::Add(const CString& strKey, void* pObject)
{
	CMap::Add(*(new CStrPtrMapItem(strKey, pObject)));
}

inline void CStrPtrMap::Remove(const CString& strKey)
{
	CMap::Remove(CStrPtrMapItem(strKey, NULL));
}

inline void* CStrPtrMap::Find(const CString& strKey) const
{
	CStrPtrMapItem* pItem = static_cast<CStrPtrMapItem*>(CMap::Find(CStrPtrMapItem(strKey, NULL)));

	return (pItem != NULL) ? pItem->m_pObject : NULL;
}

inline CStrPtrMapItem::CStrPtrMapItem(const CString& strKey, void* pObject)
	: m_strKey(strKey)
	, m_pObject(pObject)
{
}

inline CStrPtrMapItem::~CStrPtrMapItem()
{
}

inline uint CStrPtrMapItem::Key() const
{
	uint nKey = 0;

	for (const tchar* psz = m_strKey; *psz != TXT('\0'); ++psz)
		nKey = (nKey * 17) | *psz;

	return nKey;
}

inline bool CStrPtrMapItem::operator==(const CMapItem& rRHS) const
{
	const CStrPtrMapItem* pRHS = static_cast<const CStrPtrMapItem*>(&rRHS);

	return (m_strKey == pRHS->m_strKey);
}

#endif //STRPTRMAP_HPP
