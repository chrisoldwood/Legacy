/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMap class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <typeinfo.h>

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
**
** Class members.
**
*******************************************************************************
*/

// Array of map sizes.
int CMap::s_aiSizes[NUM_MAP_SIZES] =
{
	3, 7, 17, 31, 61, 127, 257, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65537
};

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	iSize	The size of the map.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMap::CMap()
	: m_iSize(s_aiSizes[0])
	, m_pMap(NULL)
	, m_iCount(0)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMap::~CMap()
{
	RemoveAll();

	ASSERT(m_iCount == 0);
	ASSERT(m_pMap   == NULL);
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds an item to the map.
**
** Parameters:	rItem	The item to add.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMap::Add(CMapItem& rItem)
{
	ASSERT(Find(rItem) == NULL);

	// Map allocated?
	if (m_iCount == 0)
		m_pMap = (CMapItem**) calloc(m_iSize, sizeof(CMapItem*));
	
	ASSERT(m_pMap);

	// Calculate map bucket.
	int i = Hash(rItem);
	
	ASSERT((i >= 0) && (i < m_iSize));

	// Add to head of collision chain.
	rItem.m_pNext = m_pMap[i];
	m_pMap[i] = &rItem;

#ifdef _DEBUG
/*	int nChainLen = 0;

	CMapItem* pItem = m_pMap[i];

	// Find chain length.
	while (pItem != NULL)
	{
		pItem = pItem->m_pNext;
		nChainLen++;
	}

	// Chain bigger than expected?
	if (nChainLen > MAX_CHAIN_LEN)
	{
		TRACE5("CMap::Add() chain length exceeded: %d (Size: %d Count: %d)(Key: 0x%08X Bucket: %d)\n",
				nChainLen, m_iSize, m_iCount, rItem.Key(), i);

		TRACE("Chain keys...");

		CMapItem* pItem = m_pMap[i];

		// Dump chain keys.
		while (pItem != NULL)
		{
			TRACE1("0x%08X ", pItem->Key());
			pItem = pItem->m_pNext;
		}

		TRACE("\n");
	}*/
#endif

	m_iCount++;
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes an item from the map.
**
** Parameters:	rItem	The item to remove.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMap::Remove(const CMapItem& rItem)
{
	ASSERT(m_pMap);
	ASSERT(m_iCount);

	// Calculate map bucket.
	int i = Hash(rItem);
	
	ASSERT((i >= 0) && (i < m_iSize));
	
	// Get head of collision chain.
	CMapItem*  pItem  = m_pMap[i];
	CMapItem** ppPrev = &m_pMap[i];

	// Find item.
	while ( (pItem) && (rItem != *pItem) )
	{
		ppPrev = &pItem->m_pNext;
		pItem  = pItem->m_pNext;
	}

	ASSERT(pItem);

	// Remove.
	*ppPrev = pItem->m_pNext;
	delete pItem;

	// Map now empty?
	if (--m_iCount == 0)
	{
		free(m_pMap);
		m_pMap = NULL;
	}
}

/******************************************************************************
** Method:		RemoveAll()
**
** Description:	Removes all items from the map.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMap::RemoveAll()
{
	// Map not already empty?
	if (m_iCount != 0)
	{
		// For all buckets.
		for (int i = 0; i < m_iSize; i++)
		{
			CMapItem* pItem = m_pMap[i];

			// Run down the chain.
			while (pItem != NULL)
			{
				CMapItem* pNextItem = pItem->m_pNext;
				
				delete pItem;
				m_iCount--;

				pItem = pNextItem;
			}
		}

		free(m_pMap);
		m_pMap = NULL;
	}
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds an item in the map.
**
** Parameters:	rItem	The item to find.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMapItem* CMap::Find(const CMapItem& rItem) const
{
	// Map not allocated yet?
	if (m_pMap == NULL)
		return NULL;

	// Calculate map bucket.
	int i = Hash(rItem);
	
	ASSERT((i >= 0) && (i < m_iSize));

	// Get head of collision chain.
	CMapItem*	pItem = m_pMap[i];
	int			nProbes = 0;

	// Find item.
	while ( (pItem) && (rItem != *pItem) )
	{
		pItem = pItem->m_pNext;
		nProbes++;
	}

	return pItem;
}

/******************************************************************************
** Method:		Hash()
**
** Description:	Calculates the collision bucket for the given item.
**
** Parameters:	rItem	The item to hash.
**
** Returns:		The bucket array index.
**
*******************************************************************************
*/

int CMap::Hash(const CMapItem& rItem) const
{
	return (rItem.Key() % m_iSize);
}

/******************************************************************************
** Method:		Reserve()
**
** Description:	Allocates the hash table to hold the specified number of items.
**				It will grow the table if already allocated.
**
** Parameters:	nItems		The number of items that will be stored.
**
** Returns:		The bucket array index.
**
*******************************************************************************
*/

void CMap::Reserve(int nItems)
{
	ASSERT(m_pMap == NULL);

	// Calculate min table size.
	int nMinSize = nItems / MAX_CHAIN_LEN;

	// Search the map 'size' table.
	for (int i = NUM_MAP_SIZES-1; i > 0; i--)
	{
		// Size too small?
		if (s_aiSizes[i] < nMinSize)
			break;

		m_iSize = s_aiSizes[i];
	}

	ASSERT(m_iSize >= nMinSize);
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMapItem::CMapItem()
	: m_pNext(NULL)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMapItem::~CMapItem()
{
}
