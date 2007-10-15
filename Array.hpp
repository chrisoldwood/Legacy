/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CArray class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ARRAY_HPP
#define ARRAY_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the base class for all array collections.
**
*******************************************************************************
*/

class CArray
{
public:
	//
	// Attributes.
	//
	int Size() const;

	//
	// Memory methods.
	//
	virtual void Reserve(int nSize);

protected:
	// Sort callback function.
	typedef int (*PFNQSCOMPARE)(const void* pItem1, const void* pItem2);

	//
	// Constructors/Destructor.
	//
	CArray(int nItemSize);
	CArray(const CArray& rArray);
	~CArray();

	//
	// Members.
	//
	byte*	m_pData;
	int		m_nSize;
	int		m_nAllocSize;
	int		m_nItemSize;

	//
	// Internal Methods.
	//
	void* At(int nIndex) const;
	void* operator[](int nIndex) const;

	void Set(int nIndex, const void* pItem);
	int  Add(const void* pItem);
	void Insert(int nIndex, const void* pItem);
	void Remove(int nIndex);
	void RemoveAll();

	void Sort(PFNQSCOMPARE pfnCompare);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CArray::Size() const
{
	return m_nSize;
}

inline void* CArray::At(int nIndex) const
{
	ASSERT((nIndex >= 0) && (nIndex < m_nSize));

	return (m_pData + (nIndex * m_nItemSize));
}

inline void* CArray::operator[](int nIndex) const
{
	return At(nIndex);
}

#endif //ARRAY_HPP
