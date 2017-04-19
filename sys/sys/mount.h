/*
 * Copyright (c) 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)mount.h	8.21 (Berkeley) 5/20/95
 * $FreeBSD: src/sys/sys/mount.h,v 1.89 2000/01/19 06:07:34 rwatson Exp $
 */

#ifndef _SYS_MOUNT_H_
#define _SYS_MOUNT_H_

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef fsid_t
#include <sys/vfs.h>
#endif

/*
 * file system statistics
 */

#define MFSNAMELEN	16	/* length of fs type name, including null */
#define	MNAMELEN	80	/* length of buffer for returned name */

struct statfs {
	u_long	f_bsize;		/* fundamental file system block size */
	u_long	f_iosize;		/* optimal transfer block size */
	uquad_t	f_blocks;		/* total data blocks in file system */
	uquad_t	f_bfree;		/* free blocks in fs */
	uquad_t	f_bavail;		/* free blocks avail to non-superuser */
	uquad_t	f_files;		/* total file nodes in file system */
	uquad_t	f_ffree;		/* free file nodes in fs */
	fsid_t	f_fsid;			/* file system id */
	uid_t	f_owner;		/* user that mounted the filesystem */
	int	f_type;			/* type of filesystem */
	int	f_flags;		/* copy of mount exported flags */
	u_long	f_syncwrites;		/* count of sync writes since mount */
	u_long	f_asyncwrites;		/* count of async writes since mount */
	u_long	f_syncreads;		/* count of sync reads since mount */
	u_long	f_asyncreads;		/* count of async reads since mount */
	char	f_mntfromname[MNAMELEN];/* mounted filesystem */
	char	f_mntonname[MNAMELEN];	/* directory on which mounted */
	char	f_fstypename[MFSNAMELEN]; /* fs type name */
};

/*
 * User specifiable flags.
 */
#define	MNT_RDONLY	0x00000001	/* read only filesystem */
#define	MNT_SYNCHRONOUS	0x00000002	/* file system written synchronously */
#define	MNT_NOEXEC	0x00000004	/* can't exec from filesystem */
#define	MNT_NOSUID	0x00000008	/* don't honor setuid bits on fs */
#define	MNT_NODEV	0x00000010	/* don't interpret special files */
#define	MNT_UNION	0x00000020	/* union with underlying filesystem */
#define	MNT_ASYNC	0x00000040	/* file system written asynchronously */
#define	MNT_SUIDDIR	0x00000080	/* special handling of SUID on dirs */
#define	MNT_SOFTDEP	0x00000100	/* soft updates being done */
#define	MNT_NOSYMFOLLOW	0x00000200	/* do not follow symlinks */
#define	MNT_NOATIME	0x00000400	/* disable update of file access time */
#define	MNT_NOCLUSTERR	0x00000800	/* disable cluster read */
#define	MNT_NOCLUSTERW	0x00001000	/* disable cluster write */

/*
 * NFS export related mount flags.
 */
#define	MNT_EXRDONLY	0x00002000	/* exported read only */
#define	MNT_EXPORTED	0x00004000	/* file system is exported */
#define	MNT_DEFEXPORTED	0x00008000	/* exported to the world */
#define	MNT_EXPORTANON	0x00010000	/* use anon uid mapping for everyone */
#define	MNT_EXKERB	0x00020000	/* exported with Kerberos uid mapping */
#define	MNT_EXPUBLIC	0x00040000	/* public export (WebNFS) */

/*
 * Flags set by internal operations,
 * but visible to the user.
 * XXX some of these are not quite right.. (I've never seen the root flag set)
 */
#define	MNT_LOCAL	0x00080000	/* filesystem is stored locally */
#define	MNT_QUOTA	0x00100000	/* quotas are enabled on filesystem */
#define	MNT_ROOTFS	0x00200000	/* identifies the root filesystem */
#define	MNT_USER	0x00400000	/* mounted by a user */
#define	MNT_IGNORE	0x00800000	/* do not show entry in df */

/*
 * Mask of flags that are visible to statfs()
 * XXX I think that this could now become (~(MNT_CMDFLAGS))
 * but the 'mount' program may need changing to handle this.
 * XXX MNT_EXPUBLIC is presently left out. I don't know why.
 */
#define	MNT_VISFLAGMASK	(MNT_RDONLY	| MNT_SYNCHRONOUS | MNT_NOEXEC	| \
			MNT_NOSUID	| MNT_NODEV	| MNT_UNION	| \
			MNT_ASYNC	| MNT_EXRDONLY	| MNT_EXPORTED	| \
			MNT_DEFEXPORTED	| MNT_EXPORTANON| MNT_EXKERB	| \
			MNT_LOCAL	| MNT_USER	| MNT_QUOTA	| \
			MNT_ROOTFS	| MNT_NOATIME	| MNT_NOCLUSTERR| \
			MNT_NOCLUSTERW	| MNT_SUIDDIR	| MNT_SOFTDEP	| \
			MNT_IGNORE \
			/*	| MNT_EXPUBLIC */)
/*
 * External filesystem command modifier flags.
 * Unmount can use the MNT_FORCE flag.
 * XXX These are not STATES and really should be somewhere else.
 */
#define	MNT_UPDATE	0x01000000	/* not a real mount, just an update */
#define	MNT_DELEXPORT	0x02000000	/* delete export host lists */
#define	MNT_RELOAD	0x04000000	/* reload filesystem data */
#define	MNT_FORCE	0x08000000	/* force unmount or readonly change */
#define	MNT_WANTRDWR	0x10000000	/* want upgrade to read/write */
#define	MNT_NOFLUSH	0x40000000	/* don't flush */

#define	MNT_PNPQUERY	0x20000000	/* PnP query to unmount */
#define	MNT_PNPREMOVE	0x80000000	/* PnP remove unmount state */

/*
 * Internal filesystem control flags stored in mnt_kern_flag.
 *
 * MNTK_UNMOUNT locks the mount entry so that name lookup cannot proceed
 * past the mount point.  This keeps the subtree stable during mounts
 * and unmounts.
 */
#define MNTK_UNMOUNT	0x01000000	/* unmount in progress */
#define	MNTK_MWAIT	0x02000000	/* waiting for unmount to finish */
#define MNTK_WANTRDWR	0x04000000	/* upgrade to read/write requested */

/*
 * Sysctl CTL_VFS definitions.
 *
 * Second level identifier specifies which filesystem. Second level
 * identifier VFS_VFSCONF returns information about all filesystems.
 * Second level identifier VFS_GENERIC is non-terminal.
 */
#define	VFS_VFSCONF		0	/* get configured filesystems */
#define	VFS_GENERIC		0	/* generic filesystem information */
/*
 * Third level identifiers for VFS_GENERIC are given below; third
 * level identifiers for specific filesystems are given in their
 * mount specific header files.
 */
#define VFS_MAXTYPENUM	1	/* int: highest defined filesystem type */
#define VFS_CONF	2	/* struct: vfsconf for filesystem given
				   as next argument */

/*
 * Flags for various system call interfaces.
 *
 * waitfor flags to vfs_sync() and getfsstat()
 */
#define MNT_WAIT	1	/* synchronously wait for I/O to complete */
#define MNT_NOWAIT	2	/* start all I/O, but do not wait for it */
#define MNT_LAZY	3	/* push data not written by filesystem syncer */

/*
 * Filesystem configuration information. One of these exists for each
 * type of filesystem supported by the kernel. These are searched at
 * mount time to identify the requested filesystem.
 */
struct vfsconf {
	struct	vfsops *vfc_vfsops;	/* filesystem operations vector */
	char	vfc_name[MFSNAMELEN];	/* filesystem type name */
	int	vfc_typenum;		/* historic filesystem type number */
	int	vfc_refcount;		/* number mounted of this type */
	int	vfc_flags;		/* permanent flags */
	struct	vfsconf *vfc_next;	/* next in list */
};

#ifdef _WIN64
struct vfsconf_32 {
	struct	vfsops * POINTER_32 vfc_vfsops;
	char	vfc_name[MFSNAMELEN];	/* filesystem type name */
	int	vfc_typenum;		/* historic filesystem type number */
	int	vfc_refcount;		/* number mounted of this type */
	int	vfc_flags;		/* permanent flags */
	struct	vfsconf * POINTER_32 vfc_next;
};
#endif

/*
 * NB: these flags refer to IMPLEMENTATION properties, not properties of
 * any actual mounts; i.e., it does not make sense to change the flags.
 */
#define	VFCF_STATIC	0x00010000	/* statically compiled into kernel */
#define	VFCF_NETWORK	0x00020000	/* may get data over the network */
#define	VFCF_READONLY	0x00040000	/* writes are not implemented */
#define VFCF_SYNTHETIC	0x00080000	/* data does not represent real files */
#define	VFCF_LOOPBACK	0x00100000	/* aliases some other mounted FS */
#define	VFCF_UNICODE	0x00200000	/* stores file names as Unicode*/


/*
 * mount args for individual file system
 */
struct ufs_args {
	char	*POINTER_32 fspec;	/* block special device to mount */
};

struct regfs_args {
	char	*POINTER_32 regname;	/* registry path to be mounted */
};

struct winfs_args {
	char	*POINTER_32 dosdev;	/* windows device to be mounted */
};


#if defined (_KERNEL)
int	cancel_unmount(struct vfsmount *, cred_t *);
int	dounmount(struct vfsmount *, int, cred_t *);
#else
#include <cdefs.h>

int	__stdcall fstatfs __P((int, struct statfs *));
int	__stdcall getfsstat __P((struct statfs *, long, int));
int	__stdcall getmntinfo __P((struct statfs **, int));
int	__stdcall mount __P((const char *, const char *, int, void *));
int	__stdcall statfs __P((const char *, struct statfs *));
int	__stdcall unmount(const char *, int);

/* C library stuff */
void	__stdcall endvfsent __P((void));
int 	__stdcall getvfsbyname __P((const char *, struct vfsconf *));
struct	vfsconf *getvfsbytype __P((int));
struct	vfsconf *getvfsent __P((void));
int	__stdcall vfsisloadable __P((const char *));
int	__stdcall vfsload __P((const char *));
#endif

#if defined(__cplusplus)
	}
#endif

#endif /* !_SYS_MOUNT_H_ */
