/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAPITER.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CMapIter class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MAPITER_HPP
#define MAPITER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

// Forward declarations.
class CMap;
class CMapItem;

/******************************************************************************
** 
** Class used to iterate over a CMap.
**
*******************************************************************************
*/

class CMapIter
{
public:
	//
	// Constructors/Destructor.
	//
	CMapIter(const CMap& oMap);
	~CMapIter();

protected:
	//
	// Members.
	//
	const CMap&	m_oMap;
	size_t		m_nBucket;
	CMapItem*   m_pCurrent;

	//
	// External methods.
	//
	CMapItem* Next();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // MAPITER_HPP
