/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TREE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTree class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TREE_HPP
#define TREE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "TArray.hpp"

/******************************************************************************
** 
** The template class used to hold a node in the tree.
**
*******************************************************************************
*/

template<class T> class TTreeNode
{
public:
	//
	// Constructors/Destructor.
	//
	TTreeNode();
	virtual ~TTreeNode();

	//
	// Accessors.
	//
	size_t        NumNodes() const;
	TTreeNode<T>* Node(size_t n) const;
	TTreeNode<T>* Parent() const;

	//
	// Mutators.
	//
	void Node(size_t n, TTreeNode<T>* pNode);
	void AddNode(TTreeNode<T>* pNode);
	void Parent(TTreeNode<T>* pNode);

	//
	// Members.
	//
	T	m_oData;

protected:
	// Template typedefs.
	typedef TPtrArray<TTreeNode> CNodes;

	//
	// Members.
	//
	CNodes			m_apNodes;
	TTreeNode<T>*	m_pParent;

private:
	//
	// Disallow copies.
	//
	TTreeNode(const TTreeNode<T>&);
	void operator=(const TTreeNode<T>&);
};

/******************************************************************************
** 
** The template class used for tree collections.
**
*******************************************************************************
*/

template<class T> class TTree
{
public:
	//
	// Constructors/Destructor.
	//
	TTree();
	virtual ~TTree();

	//
	// Accessors.
	//
	TTreeNode<T>* Root() const;

	//
	// Mutators.
	//
	void Root(TTreeNode<T>* pNode);

	//
	// Methods.
	//
	void Clear();

protected:
	//
	// Members.
	//
	TTreeNode<T>*	m_pRoot;	// The root node.

private:
	//
	// Disallow copies.
	//
	TTree(const TTree<T>&);
	void operator=(const TTree<T>&);
};

/******************************************************************************
**
** Implementation of TTreeNode inline functions.
**
*******************************************************************************
*/

template<class T> inline TTreeNode<T>::TTreeNode()
	: m_pParent(NULL)
{
}

template<class T> inline TTreeNode<T>::~TTreeNode()
{
	for (size_t i = 0; i < m_apNodes.Size(); ++i)
		delete m_apNodes[i];
}

template<class T> inline size_t TTreeNode<T>::NumNodes() const
{
	return m_apNodes.Size();
}

template<class T> inline TTreeNode<T>* TTreeNode<T>::Node(size_t n) const
{
	return m_apNodes[n];
}

template<class T> inline TTreeNode<T>* TTreeNode<T>::Parent() const
{
	return m_pParent;
}

template<class T> inline void TTreeNode<T>::Node(size_t n, TTreeNode<T>* pNode)
{
	pNode->Parent(this);
	m_apNodes.Set(n, pNode);
}

template<class T> inline void TTreeNode<T>::AddNode(TTreeNode<T>* pNode)
{
	pNode->Parent(this);
	m_apNodes.Add(pNode);
}

template<class T> inline void TTreeNode<T>::Parent(TTreeNode<T>* pNode)
{
	m_pParent = pNode;
}

/******************************************************************************
**
** Implementation of TTree inline functions.
**
*******************************************************************************
*/

template<class T> inline TTree<T>::TTree()
	: m_pRoot(NULL)
{
}

template<class T> inline TTree<T>::~TTree()
{
	Clear();
}

template<class T> inline TTreeNode<T>* TTree<T>::Root() const
{
	return m_pRoot;
}

template<class T> inline void TTree<T>::Root(TTreeNode<T>* pNode)
{
	ASSERT(m_pRoot == NULL);

	m_pRoot = pNode;
}

template<class T> inline void TTree<T>::Clear()
{
	delete m_pRoot;

	m_pRoot = NULL;
}

#endif //TREE_HPP
