/*
 * Crossmeta Windows kernel data types.
 * (C) Copyright 2003 Sammandam, Supramani
 */

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#ifdef _WIN64
#include <crtdefs.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Definitions of all the basic system types that is present in UNIX.
 */

/* POSIX Extensions */

typedef	unsigned char	uchar_t;

typedef	unsigned short	ushort_t;

typedef	unsigned int	uint_t;

typedef	unsigned long	ulong_t;

typedef __int64 quad_t;
typedef unsigned __int64 uquad_t, u_quad_t;

#define QUAD_LOWPART(q)		(((PLARGE_INTEGER)(q))->LowPart)
#define QUAD_HIGHPART(q)	(((PLARGE_INTEGER)(q))->HighPart)
#define UQUAD_LOWPART(q)	(((PULARGE_INTEGER)(q))->LowPart)
#define UQUAD_HIGHPART(q)	(((PULARGE_INTEGER)(q))->HighPart)

typedef	unsigned short	wchar_t;

typedef char *	addr_t;			/* ?<core address> type (BSD compat) */
typedef	char *	caddr_t;		/* ?<core address> type */
/*
 * Do not change daddr_t to unsigned, otherwise FFS code will break
 */
#ifdef	_WIN64
typedef	LONGLONG daddr_t;		/* <disk address> type */
#else
typedef	long	daddr_t;		/* <disk address> type */
#endif
typedef	quad_t	daddr64_t;		/* <disk address> type */
typedef char *	faddr_t;		/* XENIX compat */
typedef __int32	ufs_daddr_t;

#ifdef	_WIN64
typedef	LONGLONG	off_t;			/* ?<offset> type */
#else
typedef	long	off_t;			/* ?<offset> type */
#endif	/* _WIN64 */
typedef	quad_t	off64_t;		/* ?<offset64> type */

typedef	short	cnt_t;			/* ?<count> type */
typedef	ulong_t	vaddr_t;		/* <virtual address> type */
typedef	ulong_t	paddr_t;		/* <physical address> type */
typedef uint_t	ppid_t;			/* <physical page id> type */
typedef	uchar_t	use_t;			/* use count for swap */
typedef	short	sysid_t;		/* system ID (RFS) */
typedef	short	index_t;		/* bitmap index (no longer used) */

/* POSIX and XOPEN Declarations */

typedef	int	key_t;			/* IPC key type		*/

typedef	ulong_t mode_t;			/* file attribute type	*/

typedef	unsigned long	uid_t;		/* UID type		*/

typedef	uid_t	gid_t;			/* GID type		*/

typedef	ulong_t nlink_t;		/* file link type	*/


typedef ulong_t	ino_t;			/* expanded inode type	*/
typedef unsigned __int64 ino64_t;		/* expanded inode type	*/
typedef	 __int64	id_t;		/* can hold a gid_t, pid_t, or uid_t */
typedef	 __int64	rlim_t;		/* resource limit - intentionally */

typedef long	pid_t;			/* process id type	*/

typedef	uint_t	size32_t;		/* len param for string funcs */

typedef	int	ssize_t;	/* return byte count or indicate error */

/* windows 64bit collisions */
#ifndef POINTER_32
#define	POINTER_32
#endif
#ifndef _SIZE_T_DEFINED
typedef uint_t	size_t;
#define	_SIZE_T_DEFINED
#endif
#ifndef _TIME_T_DEFINED
typedef	long	time_t;		/* time of day in seconds */
#endif
typedef	char *	POINTER_32 caddr32_t;	/* ?<core address> 32bit type */

#ifndef _UINTPTR_T_DEFINED
#ifdef	_WIN64
typedef	unsigned __int64 uintptr_t;
#else
typedef	unsigned int uintptr_t;
#endif
#define	_UINTPTR_T_DEFINED
#endif

#ifndef _CLOCK_T_DEFINED
typedef	long	clock_t; /* relative time in a specified resolution */
#define _CLOCK_T_DEFINED
#endif

typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

/*
 * Basic integral types.
 */
typedef signed char		int8_t;
typedef unsigned char		u_int8_t, uint8_t;
typedef short			int16_t;
typedef unsigned short		u_int16_t, uint16_t;
typedef int			int32_t;
typedef unsigned int		u_int32_t, uint32_t;
typedef __int64			int64_t;
typedef unsigned __int64	u_int64_t, uint64_t;

#ifdef _KERNEL
struct specinfo;

typedef u_int32_t	udev_t;		/* device number */
typedef struct specinfo *dev_t;
#else
typedef ulong_t	dev_t;			/* expanded device type */
#define	udev_t	dev_t
#define	major(x)	((int)(((u_int)(x) >> 8)&0xff)) /* major number */
#define	minor(x)	((int)((x)&0xffff00ff))         /* minor number */
#define makedev(x,y)	((dev_t)(((x) << 8) | (y)))     /* create dev_t */

#endif

#ifdef _CXVFS
#define	CXVFSAPI	DECLSPEC_IMPORT
#else
#define	CXVFSAPI
#endif

#ifndef CDECL
#define	CDECL	__cdecl
#endif

#ifndef _CRTIMP
#ifdef  _DLL
#define _CRTIMP __declspec(dllimport)
#else   /* ndef _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* _CRTIMP */

#ifndef FASTCALL
#define FASTCALL __fastcall
#endif

#if DBG
#define STATIC
#define KASSERT(exp,msg)	do { if (!(exp)) panic msg; } while (0)
#else
#define STATIC		static
#define	KASSERT(exp,msg)	
#endif /* DBG */

#if defined(__cplusplus)
        }
#endif
#endif /* !_SYS_TYPES_H_ */
