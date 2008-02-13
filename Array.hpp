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
	size_t Size() const;

	//
	// Memory methods.
	//
	virtual void Reserve(size_t nSize);

protected:
	// Sort callback function.
	typedef int (*PFNQSCOMPARE)(const void* pItem1, const void* pItem2);

	//
	// Constructors/Destructor.
	//
	CArray(size_t nItemSize);
	CArray(const CArray& rArray);
	~CArray();

	//
	// Members.
	//
	byte*	m_pData;
	size_t	m_nSize;
	size_t	m_nAllocSize;
	size_t	m_nItemSize;

	//
	// Internal Methods.
	//
	void* At(size_t nIndex) const;
	void* operator[](size_t nIndex) const;

	void Set(size_t nIndex, const void* pItem);
	int  Add(const void* pItem);
	void Insert(size_t nIndex, const void* pItem);
	void Remove(size_t nIndex);
	void RemoveAll();

	void Sort(PFNQSCOMPARE pfnCompare);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline size_t CArray::Size() const
{
	return m_nSize;
}

inline void* CArray::At(size_t nIndex) const
{
	ASSERT(nIndex < m_nSize);

	return (m_pData + (nIndex * m_nItemSize));
}

inline void* CArray::operator[](size_t nIndex) const
{
	return At(nIndex);
}

#endif //ARRAY_HPP
