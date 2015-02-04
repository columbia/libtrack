/*
 * dummy_wrap_cache.c
 * Copyright (C) 2015 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */
#include <unistd.h>

#include "backtrace.h"
#include "wrap_lib.h"
#include "wrap_tls.h"

/*
 * TODO: implement this interface!
 *       (probably just copy from Android/x86)
 */


void __hidden setup_wrap_cache(void)
{
}

/**
 * @wrap_symbol_mod
 *
 */
void __hidden wrap_symbol_mod(struct tls_info *tls)
{
	(void)tls;
}

/**
 * @wrap_symbol_notrace
 *
 */
int __hidden wrap_symbol_notrace(struct tls_info *tls)
{
	(void)tls;
	return 0;
}

/**
 * @wrap_symbol_notime
 *
 */
int __hidden wrap_symbol_notime(struct tls_info *tls)
{
	(void)tls;
	return 0;
}

/**
 * @wrap_symbol_noargs
 *
 */
int __hidden wrap_symbol_noargs(struct tls_info *tls)
{
	(void)tls;
	return 0;
}

/**
 * @wrap_symbol_callstr
 *
 */
const char __hidden *wrap_symbol_callstr(struct tls_info *tls, int *len)
{
	(void)tls;
	(void)len;
	return NULL;
}

/**
 * @wrap_special
 */
int __hidden wrap_special(struct tls_info *tls)
{
	(void)tls;
	return 0;
}
