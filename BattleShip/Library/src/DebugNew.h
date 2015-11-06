#ifndef _DEBUGNEW_H_
#define _DEBUGNEW_H_

#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#define new DBG_NEW
#endif

#endif