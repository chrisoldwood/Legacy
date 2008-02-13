/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILEFINDER.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFileFinder class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FILEFINDER_HPP
#define FILEFINDER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/Path.hpp>
#include <WCL/StrArray.hpp>
#include "TTree.hpp"
#include "TTreeIter.hpp"

/******************************************************************************
** 
** The class used to hold the file list for a directory.
**
*******************************************************************************
*/

class CDirFiles
{
public:
	//
	// Members.
	//
	CPath		m_strPath;
	CStrArray	m_astrDirs;
	CStrArray	m_astrFiles;
};

// Template shortname.
typedef TTreeNode<CDirFiles>    CFileTreeNode;
typedef TTree<CDirFiles>        CFileTree;
typedef TTreeFwdIter<CDirFiles>	CFileTreeIter;

/******************************************************************************
** 
** This class is used to find files and directories.
**
*******************************************************************************
*/

class CFileFinder
{
public:
	//
	// Constructors/Destructor.
	//
	CFileFinder();
	~CFileFinder();
	
	//
	// Methods.
	//
	void Find(const tchar* pszPath, const tchar* pszMask, bool bRecurse, CFileTree& oTree);

protected:
	//
	// Members.
	//

	//
	// Internal methods.
	//
	void Find(CFileTreeNode& oNode, const tchar* pszMask, bool bRecurse);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FILEFINDER_HPP
