/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HANDLEMAP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CHandleMap class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef HANDLEMAP_HPP
#define HANDLEMAP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the map used to link generic handles to objects.
** NB: This used to be based on the WCL CMap class.
**
*******************************************************************************
*/

class CHandleMap
{
public:
	//
	// Constructors/Destructor.
	//
	CHandleMap();
	~CHandleMap();

	//
	// Methods.
	//
	void  Add(HANDLE hHandle, void* pObject);
	void  Remove(HANDLE hHandle);
	void* Find(HANDLE hHandle) const;

protected:
	// Type shorthands.
	typedef std::map<HANDLE, void*> HandleObjectMap;

	//
	// Members.
	//
	HandleObjectMap	m_oMap;		//!< The underlying container.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CHandleMap::CHandleMap()
{
}

inline CHandleMap::~CHandleMap()
{
}

inline void CHandleMap::Add(HANDLE hHandle, void* pObject)
{
	ASSERT(hHandle != NULL);

	m_oMap.insert(std::make_pair(hHandle, pObject));
}

inline void CHandleMap::Remove(HANDLE hHandle)
{
	ASSERT(hHandle != NULL);
	ASSERT(m_oMap.find(hHandle) != m_oMap.end());

	m_oMap.erase(m_oMap.find(hHandle));
}

inline void* CHandleMap::Find(HANDLE hHandle) const
{
	ASSERT(hHandle);

	HandleObjectMap::const_iterator it = m_oMap.find(hHandle);

	return (it != m_oMap.end()) ? it->second : NULL;
}

#endif //HANDLEMAP_HPP
