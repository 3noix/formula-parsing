#ifndef ANY_OPERATORS
#define ANY_OPERATORS


#include "ProjectData.h"


Any operator+(const Any &a1, const Any &a2);
Any operator-(const Any &a1, const Any &a2);
Any operator-(const Any &a);
Any operator*(const Any &a1, const Any &a2);
Any operator/(const Any &a1, const Any &a2);
Any operator%(const Any &a1, const Any &a2);

Any operator&&(const Any &a1, const Any &a2);
Any operator||(const Any &a1, const Any &a2);
Any operator!(const Any &a);

Any operator==(const Any &a1, const Any &a2);
Any operator!=(const Any &a1, const Any &a2);

Any operator<(const Any &a1, const Any &a2);
Any operator<=(const Any &a1, const Any &a2);
Any operator>(const Any &a1, const Any &a2);
Any operator>=(const Any &a1, const Any &a2);


#endif

/*
OK : "+","-","*","/","%"
OK : "&&","||","!"
OK : "==","!="
OK : "<","<=",">",">="
OK/NTD : "**"

NTD : "&","|","~","^"
NTD : "<<",">>"
*/

