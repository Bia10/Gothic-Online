/* GO source file */
#ifndef GO_SHAREDINCLUDES_H
#define GO_SHAREDINCLUDES_H

//Silnik sieciowy
#include "RaknetIncludes.h"
//Implementacja listy
#include "List/List.h"
//Biblioteki obliczeniowe (funkcje podajemy razem z przestrzeniami nazw) goMath::getdistance3d..
#include "goMath/goMath.h"
//Biblioteki z użytecznymi funkcjami. Przestrzeń nazw utility
#include "Utility/utility.h"
//TinyXML
#include "tinyxml/tinyxml.h"
//Wątki
#include "TinyThread/tinythread.h"
#include "TinyThread/fast_mutex.h"
using namespace tthread;
//identyfikatory messagesow
#include "Network/GOMessages.h"
//Squirrel
#include "SquirrelIncludes.h"

#endif //GO_SHAREDINCLUDES_H