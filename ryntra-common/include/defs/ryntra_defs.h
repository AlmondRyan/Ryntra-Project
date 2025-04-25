#ifndef RYNTRA_GLOBAL_DEFS
#define RYNTRA_GLOBAL_DEFS

/// A macro, extend to standard keyword \c inline. For keeping all the project a same naming conventions.
#define R_INLINE inline

/// \brief A macro, extend to attribute \c __forceinline  (on MSVC) or \c __attribute__((always_inline)) on other compiler.
///
/// This is designed for Force Inline (Because \c inline is basically a 'flag'. You can't just inline it if you want to,
/// it mainly depends on the compiler's optimization strategy.)
///
/// So if some functions that we think it must be inline-ed, we should need FORCE_INLINE. This flag told
/// the compiler: This function I make sure it is better than un-inline, so please inline it!
#ifdef _MSC_VER
#define R_FORCE_INLINE __forceinline
#else
#define R_FORCE_INLINE __attribute__((always_inline))
#endif

#endif // RYNTRA_GLOBAL_DEFS