/*
 * vfs.h
 *	Virtual File System header file for Crossmeta Kernel.
 * (c) Copyright 2003 Sammandam, Supramani
 *	
 */
#ifndef _SYS_VFS_H_
#define _SYS_VFS_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*
 *  File system identifier. Should be unique (at least per machine).
 */
typedef struct fsid { int32_t val[2]; } fsid_t;	/* file system id type */

/*
 * Check for equal file system ids
 */
#define eqfsid(fsid1, fsid2)                                            \
	(bcmp((char *)fsid1, (char *)fsid2, (int)sizeof(fsid_t)) == 0)

/*
 * File identifier.  Should be unique per filesystem on a single
 * machine.  This is typically called by a stateless file server
 * in order to generate "file handles".
 */
#define	MAXFIDSZ	16
#define	freefid(fidp) \
	kmem_free((fidp), sizeof (struct fid) - MAXFIDSZ + (fidp)->fid_len)

typedef struct fid {
	ushort_t	fid_len;		/* length of data in bytes */
	uchar_t		fid_data[MAXFIDSZ];	/* data (variable length) */
} fid_t;

/*
 * Check for equal file ids
 */
#define eqfid(fid1, fid2)	\
	((fid1)->fid_len == (fid2)->fid_len &&                          \
	bcmp((char *)(fid1)->fid_data, (char *)(fid2)->fid_data,        \
		(int)(fid1)->fid_len) == 0)

#if defined(_KERNEL)

/*
 * Structure per mounted file system.  Each mounted file system has
 * an array of operations and an instance record.  The file systems
 * are kept on a singly linked list headed by "rootvfs" and terminated
 * by NULL.
 */
typedef struct vfs {
	struct vfs	*vfs_next;		/* next VFS in VFS list */
	struct vfsops	*vfs_op;		/* operations on VFS */
	struct vnode	*vfs_vnodecovered;	/* vnode mounted on */
	ulong_t		vfs_flag;		/* copy of mount flags */
	ulong_t		vfs_count;		/* number of references */
	ulong_t		vfs_bsize;		/* native block size */
	ulong_t		vfs_nrablks;		/* number of read-ahead blks */
	int		vfs_fstype;		/* file system type index */
	fsid_t		vfs_fsid;		/* file system id */
	void		*vfs_data;		/* private data */
	dev_t		vfs_dev;		/* device of mounted VFS */
	void		*vfs_devobp;		/* device object ptr of above */
	ulong_t		vfs_bcount;		/* I/O count (accounting) */
} vfs_t;

/*
 * Filesystem type switch table.
 */
typedef struct vfssw {
	char	*vsw_name;		/* type name string */
	int	(*vsw_init)(struct vfssw *, int); /* init routine */
	int	(*vsw_unload)(); 	/* unload routine */
	struct	vfsops *vsw_vfsops;	/* filesystem operations vector */
	long	vsw_flag;		/* flags */
} vfssw_t;

#define VSW_DOINIT	0x01		/* call init routine before mount */
#define VSW_REMOTE	0x02		/* remote network file system */

#define VFS_READAHEAD_SIZE	0x10000	/* default read-ahead size of 64KB */
#endif /* _KERNEL */

/*
 * VFS flags.
 */
#define VFS_RDONLY	MNT_RDONLY	/* read-only vfs */
#define VFS_ASYNC	MNT_ASYNC	/* asynchronous i/o preferred */
#define	VFS_NOEXEC	MNT_NOEXEC	/* can't exec from filesystem */
#define	VFS_NOATIME	MNT_NOATIME
#define	VFS_NODEV	MNT_NODEV
#define	VFS_ROOTFS	MNT_ROOTFS	/* root of the whole world */
#define VFS_REMOUNT	MNT_UPDATE
#define	VFS_LOCAL	MNT_LOCAL
#define VFS_UNION	MNT_UNION
#define VFS_NOVMIO	0x10000000	/* no cache manager support needed */
#define	VFS_NOEXPORT	0x20000000	/* file system cannot be shared */
#define	VFS_DMI		0x40000000

/*
 * Reasons for calling the vfs_mountroot() operation.
 */

typedef enum whymountroot {
	ROOT_INIT, ROOT_REMOUNT, ROOT_UNMOUNT
} whymountroot_t;


#if defined(_KERNEL)

/*
 * Operations supported on virtual file system.
 */
typedef struct vfsops {
	int	(*vfs_mount)(struct vfs *, struct vnode *,
			      struct mount_args *, struct ucred *);
	int	(*vfs_unmount)(struct vfs *, int, struct ucred *);
	int	(*vfs_root)(struct vfs *, struct vnode **);
	int	(*vfs_statfs)(struct vfs *, struct statfs *);
	int	(*vfs_sync)(struct vfs *, int, struct ucred *);
	int	(*vfs_vget)(struct vfs *, struct vnode **, struct fid *);
	int	(*vfs_mountroot)(struct vfs *, enum whymountroot);
} vfsops_t;

#define VFS_MOUNT(vfsp, mvp, uap, cr) \
	(*(vfsp)->vfs_op->vfs_mount)(vfsp, mvp, uap, cr)
#define VFS_UNMOUNT(vfsp,f,cr)	(*(vfsp)->vfs_op->vfs_unmount)(vfsp, f, cr)
#define VFS_ROOT(vfsp, vpp)	(*(vfsp)->vfs_op->vfs_root)(vfsp, vpp)
#define	VFS_STATFS(vfsp, sp)	(*(vfsp)->vfs_op->vfs_statfs)(vfsp, sp)
#define VFS_SYNC(vfsp, flag, cr) \
		(*(vfsp)->vfs_op->vfs_sync)(vfsp, flag, cr)
#define VFS_VGET(vfsp, vpp, fidp) \
		(*(vfsp)->vfs_op->vfs_vget)(vfsp, vpp, fidp)
#define VFS_MOUNTROOT(vfsp, init) \
		 (*(vfsp)->vfs_op->vfs_mountroot)(vfsp, init)
#define VFS_SWAPVP(vfsp, vpp, nm) \
		(*(vfsp)->vfs_op->vfs_swapvp)(vfsp, vpp, nm)
/*
 * Public operations.
 */
void 	vfs_init(void);			/* initialize the VFS subsystem */
void 	vfs_shutdown(void);
int	vfs_mountroot(void);		/* mount the root */
int 	vfs_unmountroot(struct vfs *);
int 	vfs_unmountall(int);
vfssw_t *vfs_getvfssw(char *);
int	vfs_invalidate();
int	on_sysproc(void);
NTSTATUS mountroot(PDEVICE_OBJECT, PVPB); 

CXVFSAPI int vfs_registerfs(char *, int (*initproc)(vfssw_t *, int),
				struct vfsops *);
CXVFSAPI int vfs_unregisterfs(char *);
CXVFSAPI void vfs_add(struct vnode *, struct vfs *);
CXVFSAPI void	vfs_remove(struct vfs *);
CXVFSAPI struct vfs *vfs_getvfs(fsid_t *);
CXVFSAPI vfs_t 	*vfs_devsearch(dev_t);
CXVFSAPI ulong_t vfs_mapflag(ulong_t vflag);
CXVFSAPI void	vfs_list_lock(void);
CXVFSAPI void	vfs_list_unlock(void);
CXVFSAPI void vfs_notify_change(struct vfs *vfsp,  struct file *fp,
		u_long filter, u_long action);
CXVFSAPI NTSTATUS ntstatus(int);
CXVFSAPI void *attach_fsflush(void *);
CXVFSAPI void detach_fsflush(void *);
CXVFSAPI void wakeup_fsflush(void);


#define VFS_INIT(vfsp, op, data)	{			\
	(vfsp)->vfs_next = (struct vfs *)0;			\
	(vfsp)->vfs_op = (op);					\
	(vfsp)->vfs_flag = 0;					\
	(vfsp)->vfs_data = (data);				\
}

#define	VFS_HOLD(vfsp)	{					\
	pl_t	ipl;						\
	ipl = VFS_LOCK(vfsp, &ipl);				\
	(vfsp)->vfs_count++;					\
	VFS_UNLOCK(vfsp, ipl);					\
}

#define	VFS_RELE(vfsp)	{					\
	pl_t	ipl;						\
	ipl = VFS_LOCK(vfsp, &ipl);				\
	(vfsp)->vfs_count--;					\
	VFS_UNLOCK(vfsp, ipl);					\
}


extern int	vfs_debug_level;

#if DBG
#define VFSLOG(lvl, _msg_)					\
		if (lvl & vfs_debug_level)			\
			DbgPrint _msg_
#else
#define VFSLOG(lvl, _msg_)					\
		if (lvl & vfs_debug_level)			\
			printf _msg_
#endif /* DBG */

#if DBG
#define VASSERT(exp)	\
	if (!(exp))	{\
		DbgPrint("\n*** VFS Assertion failed: %s\n* Source File: %s line %ld\n\n", #exp, __FILE__, __LINE__);				\
		DbgBreakPoint();				\
	}
#else
#define	VASSERT(exp)
#endif

/*
 * Globals.
 */
#ifndef _CXVFS
extern struct vfs *rootvfs;		/* ptr to root vfs structure */
extern dev_t rootdev;			/* ptr to root device */
extern PDEVICE_OBJECT	rootobj;
extern struct vfssw vfssw[];		/* table of filesystem types */
extern fsleep_t vfschain_lock;		/* Vfs list lock */
extern struct ucred syscred;
extern int maxvfsconf;			/* max vfs file systems configured */
extern int vfs_readahead_size;
extern char rootdevname[];
extern char rootfstype[];
#endif

int 		vstrcmpi(uchar_t *, uchar_t *);
CXVFSAPI void 	vfs_getnewfsid(struct vfs *, int);
CXVFSAPI void	vfs_list_lock(void);
CXVFSAPI void	vfs_list_unlock(void);
PDEVICE_OBJECT vfs_realdev_object(struct vfs *vfsp);


#endif /* _KERNEL */

#if defined(__cplusplus)
	}
#endif

#include <sys/mount.h>
#ifdef _KERNEL
#include <sys/vfs_ntfsd.h>
#endif

#endif /* _SYS_VFS_H_ */
