#ifndef ANY_FUNCTIONS
#define ANY_FUNCTIONS


#include "WorkspaceData.h"


Any abs(const Any &a);
Any pow(const Any &a1, const Any &a2);
Any sqrt(const Any &a);

Any exp(const Any &a);
Any log(const Any &a);
Any log10(const Any &a);

Any cos(const Any &a);
Any sin(const Any &a);
Any tan(const Any &a);
Any acos(const Any &a);
Any asin(const Any &a);
Any atan(const Any &a);


#endif

/*
OK : "abs","pow","sqrt"
OK : "exp","log","log10"
OK : "cos","sin","tan"
OK : "acos","asin","atan"
TBD : "tan2","atan2"
*/

