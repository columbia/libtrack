/*
 * wrap_end.h
 * Copyright (C) 2012-2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 * finish up the wrapper entry points
 */
#ifndef USE_NDK
#ifndef __ASSEMBLY__
#error "This file should only be included from ARM assembly files!"
#endif
#endif

#undef WRAP_LIB
#undef WRAP_FUNC
#undef CUSTOM_WRAP_FUNC
#undef PASS_FUNC
