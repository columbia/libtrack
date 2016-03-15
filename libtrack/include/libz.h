/*
 * libz.h
 * Copyright (C) 2013 Jeremy C. Andrus <jeremya@cs.columbia.edu>
 *
 */
#ifndef WRAPPER_LIBZ_H
#define WRAPPER_LIBZ_H

#include <sys/cdefs.h>

#if defined(ANDROID)
#  define ZLIB_PATH "/system/lib"
#  define ZLIBNAME "libz.so"
#elif defined(__APPLE__)
#  define ZLIB_PATH "/usr/lib"
#  define ZLIBNAME "libz.dylib"
#else
#  define ZLIB_PATH "/lib"
#  define ZLIBNAME "libz.so.1"
#endif

#define ZLIB_DFLT_PATH ZLIB_PATH "/" ZLIBNAME

__BEGIN_DECLS

#define Z_NO_FLUSH               0
#define Z_PARTIAL_FLUSH          1
#define Z_SYNC_FLUSH             2
#define Z_FULL_FLUSH             3
#define Z_FINISH                 4
#define Z_BLOCK                  5
#define Z_TREES                  6

#define Z_NO_COMPRESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPRESSION       9
#define Z_DEFAULT_COMPRESSION  (-1)

#define Z_FILTERED               1
#define Z_HUFFMAN_ONLY           2
#define Z_RLE                    3
#define Z_FIXED                  4
#define Z_DEFAULT_STRATEGY       0

struct gzFile;

struct zlib_iface {
	void *dso;
	int   valid;

	struct gzFile *(*gzdopen)(int fd, const char *mode);
	int (*gzsetparams)(struct gzFile *file, int level, int strategy);
	int (*gzwrite)(struct gzFile *file, void *buf, unsigned len);
	int (*gzprintf)(struct gzFile *file, const char *format, ...);
	int (*gzflush)(struct gzFile *file, int flush);
	int (*gzclose)(struct gzFile *file);
};

extern struct zlib_iface zlib;

extern void init_zlib_iface(struct zlib_iface *zlib, const char *path);

extern void close_zlib_iface(struct zlib_iface *zlib);

__END_DECLS
#endif /* WRAPPER_LIBZ_H */
