#ifndef _SYS_STATVFS_H
#define _SYS_STATVFS_H

#include <sys/vfs.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Structure returned by statvfs(2).
 */

#define	FSTYPSZ	16

typedef struct statvfs {
	u_long	f_bsize;	/* fundamental file system block size */
	u_long	f_frsize;	/* fragment size */
	uquad_t	f_blocks;	/* total # of blocks of f_frsize on fs */
	uquad_t	f_bfree;	/* total # of free blocks of f_frsize */
	uquad_t	f_bavail;	/* # of free blocks avail to non-superuser */
	uquad_t	f_files;	/* total # of file nodes (inodes) */
	uquad_t	f_ffree;	/* total # of free file nodes */
	uquad_t	f_favail;	/* # of free nodes avail to non-superuser */
	u_long	f_fsid;		/* file system id (dev for now) */
	char	f_basetype[FSTYPSZ]; /* target fs type name, null-terminated */
	u_long	f_flag;		/* bit-mask of flags */
	u_long	f_namemax;	/* maximum file name length */
	char	f_fstr[32];	/* filesystem-specific string */
	u_long	f_filler[16];	/* reserved for future expansion */
} statvfs_t;

/*
 * Flag definitions.
 */
#define	ST_RDONLY	VFS_RDONLY
#define	ST_NOSUID	VFS_NOSUID

#if !defined(_KERNEL)
int statvfs(const char *, struct statvfs *);
int fstatvfs(int, struct statvfs *);
#define	statvfs64	statvfs
#define	fstatvfs64	fstatvfs
#endif

#if defined(__cplusplus)
	}
#endif

#endif	/* _SYS_STATVFS_H */
