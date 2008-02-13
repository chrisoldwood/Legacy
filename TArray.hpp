/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TARRAY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The TArray template class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_TARRAY_HPP
#define WCL_TARRAY_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Array.hpp"

/******************************************************************************
** 
** This is a template class used for arrays of primitive types.
**
*******************************************************************************
*/

template<class T> class TArray : protected CArray
{
public:
	// Sort callback function.
	typedef int (*PFNCOMPARE)(const T* pItem1, const T* pItem2);

	//
	// Constructors/Destructor.
	//
	TArray();
	~TArray();

	//
	// Methods.
	//
	size_t Size() const;

	T At(size_t nIndex) const;
	T operator[](size_t nIndex) const;

	void Set(size_t nIndex, T Item);
	size_t Add(T Item);
	void Insert(size_t nIndex, T Item);

	void Remove(size_t nIndex);
	void RemoveAll();

	int  Find(T Item) const;
	void Swap(size_t nIndex1, size_t nIndex2);

	void Sort(PFNCOMPARE pfnCompare);

	//
	// std::vector compatibility types and methods.
	//
	typedef T*       iterator;
	typedef const T* const_iterator;

	size_t size() const;

	const_iterator begin() const;
	const_iterator end() const;

	iterator begin();
	iterator end();

private:
	// Disallow copies for now.
	TArray(const TArray<T>&);
	void operator=(const TArray<T>&);
};

/******************************************************************************
** 
** This is a TArray based class used for arrays of pointers to objects.
**
*******************************************************************************
*/

template<class T> class TPtrArray : public TArray<T*>
{
public:
	//
	// Constructors/Destructor.
	//
	TPtrArray();
	~TPtrArray();

	//
	// Methods.
	//
	void Delete(size_t nIndex);
	void DeleteAll();

	void ShallowCopy(const TPtrArray<T>& oRHS);
	void DeepCopy   (const TPtrArray<T>& oRHS);

private:
	// Disallow copies for now.
	TPtrArray(const TPtrArray<T>&);
	void operator=(const TPtrArray<T>&);
};

/******************************************************************************
** 
** This is a TPtrArray based class used for arrays of references to objects.
**
*******************************************************************************
*/

template<class T> class TRefArray : public TPtrArray<T>
{
public:
	//
	// Constructors/Destructor.
	//
	TRefArray();
	~TRefArray();

	//
	// Methods.
	//
	T& At(size_t nIndex) const;
	T& operator[](size_t nIndex) const;

	void Set(size_t nIndex, T& rItem);
	void Set(size_t nIndex, T* pItem);
	size_t Add(T& pItem);
	size_t Add(T* rItem);
	void Insert(size_t nIndex, T& rItem);
	void Insert(size_t nIndex, T* pItem);

private:
	// Disallow copies for now.
	TRefArray(const TRefArray<T>&);
	void operator=(const TRefArray<T>&);
};

/******************************************************************************
**
** Implementation of TArray inline functions.
**
*******************************************************************************
*/

template<class T> inline TArray<T>::TArray()
	: CArray(sizeof(T))
{
}

template<class T> inline TArray<T>::~TArray()
{
}

template<class T> inline size_t TArray<T>::Size() const
{
	return CArray::Size();
}

template<class T> inline T TArray<T>::At(size_t nIndex) const
{
	return *(static_cast<T*>(CArray::At(nIndex)));
}

template<class T> inline T TArray<T>::operator[](size_t nIndex) const
{
	return *(static_cast<T*>(CArray::At(nIndex)));
}

template<class T> inline void TArray<T>::Set(size_t nIndex, T Item)
{
	CArray::Set(nIndex, &Item);
}

template<class T> inline size_t TArray<T>::Add(T Item)
{
	return CArray::Add(&Item);
}

template<class T> inline void TArray<T>::Insert(size_t nIndex, T Item)
{
	CArray::Insert(nIndex, &Item);
}

template<class T> inline void TArray<T>::Remove(size_t nIndex)
{
	CArray::Remove(nIndex);
}

template<class T> inline void TArray<T>::RemoveAll()
{
	CArray::RemoveAll();
}

template<class T> inline int TArray<T>::Find(T Item) const
{
	for (size_t i = 0; i < Size(); ++i)
	{
		if (At(i) == Item)
			return i;
	}

	return -1;
}

template<class T> inline void TArray<T>::Swap(size_t nIndex1, size_t nIndex2)
{
	T Item1 = At(nIndex1);
	T Item2 = At(nIndex2);

	Set(nIndex1, Item2);
	Set(nIndex2, Item1);
}

template<class T> inline void TArray<T>::Sort(PFNCOMPARE pfnCompare)
{
	CArray::Sort((PFNQSCOMPARE)pfnCompare);
}

////////////////////////////////////////////////////////////////////////////////
// std::vector compatibility methods.

template<class T>
inline size_t TArray<T>::size() const
{
	return m_nSize;
}

template<class T>
inline typename TArray<T>::const_iterator TArray<T>::begin() const
{
	const T* base = reinterpret_cast<const T*>(m_pData);

	return base;
}

template<class T>
inline typename TArray<T>::const_iterator TArray<T>::end() const
{
	const T* base = reinterpret_cast<const T*>(m_pData);

	return (base+m_nSize);
}

template<class T>
inline typename TArray<T>::iterator TArray<T>::begin()
{
	T* base = reinterpret_cast<T*>(m_pData);

	return base;
}

template<class T>
inline typename TArray<T>::iterator TArray<T>::end()
{
	T* base = reinterpret_cast<T*>(m_pData);

	return (base+m_nSize);
}

/******************************************************************************
**
** Implementation of TPtrArray inline functions.
**
*******************************************************************************
*/

template<class T> inline TPtrArray<T>::TPtrArray()
{
}

template<class T> inline TPtrArray<T>::~TPtrArray()
{
}

template<class T> inline void TPtrArray<T>::Delete(size_t nIndex)
{
	delete TArray<T*>::At(nIndex);
	Remove(nIndex);
}

template<class T> inline void TPtrArray<T>::DeleteAll()
{
	for (size_t i = 0; i < Size(); ++i)
		delete TArray<T*>::At(i);

	RemoveAll();
}

template<class T> inline void TPtrArray<T>::ShallowCopy(const TPtrArray<T>& oRHS)
{
	Reserve(oRHS.Size());

	for (size_t i = 0; i < oRHS.Size(); ++i)
		Add(oRHS.At(i));
}

template<class T> inline void TPtrArray<T>::DeepCopy(const TPtrArray<T>& oRHS)
{
	Reserve(oRHS.Size());

	for (size_t i = 0; i < oRHS.Size(); ++i)
	{
		Add(new T(*oRHS.At(i)));
	}
}

/******************************************************************************
**
** Implementation of TRefArray inline functions.
**
*******************************************************************************
*/

template<class T> inline TRefArray<T>::TRefArray()
{
}

template<class T> inline TRefArray<T>::~TRefArray()
{
}

template<class T> inline T& TRefArray<T>::At(size_t nIndex) const
{
	return *(TPtrArray<T>::At(nIndex));
}

template<class T> inline T& TRefArray<T>::operator[](size_t nIndex) const
{
	return *(TPtrArray<T>::At(nIndex));
}

template<class T> inline void TRefArray<T>::Set(size_t nIndex, T& rItem)
{
	TPtrArray<T>::Set(nIndex, &rItem);
}

template<class T> inline void TRefArray<T>::Set(size_t nIndex, T* pItem)
{
	ASSERT(pItem != NULL);

	TPtrArray<T>::Set(nIndex, pItem);
}

template<class T> inline size_t TRefArray<T>::Add(T& rItem)
{
	return TPtrArray<T>::Add(&rItem);
}

template<class T> inline size_t TRefArray<T>::Add(T* pItem)
{
	ASSERT(pItem != NULL);

	return TPtrArray<T>::Add(pItem);
}

template<class T> inline void TRefArray<T>::Insert(size_t nIndex, T& rItem)
{
	TPtrArray<T>::Insert(nIndex, &rItem);
}

template<class T> inline void TRefArray<T>::Insert(size_t nIndex, T* pItem)
{
	ASSERT(pItem != NULL);

	TPtrArray<T>::Insert(nIndex, pItem);
}

#endif // WCL_TARRAY_HPP
