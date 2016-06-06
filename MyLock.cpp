/* Copyright 2002-2016 Nikolay Avrionov. All Rights Reserved.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* http://www.apache.org/licenses/LICENSE-2.0
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#include "stdafx.h"
#include "ExplorerXP.h"
#include "MyLock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyLock::CMyLock()
{
	m_Locked = 0;
}

CMyLock::~CMyLock()
{

}

void CMyLock::Lock ()
{
/*	if (m_Locked != 0)
	{
		TRACE(_T(" Locked\n"));
	}*/

	InterlockedIncrement (&m_Locked);	
	m_CrSection.Lock ();
}

void CMyLock::Unlock ()
{
	m_CrSection.Unlock ();
	InterlockedDecrement (&m_Locked);
}

bool CMyLock::isLocked () {
	if (InterlockedCompareExchange (&m_Locked, 0, 0) == 0)
		return false;

	return true;
}
