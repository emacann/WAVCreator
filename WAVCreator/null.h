#ifndef _NULL_H
#define _NULL_H

////////////////////////////////////////////////////////////////////////////////
/// NULL Value /////////////////////////////////////////////////////////////////

#ifdef NULL
 #undef NULL
#endif // !NULL

#if defined(__cplusplus) && __cplusplus > 199711L
 #define NULL   nullptr
#else // C or older versions of C++
 #define NULL   0
#endif // !__cplusplus

#endif // !_NULL_H