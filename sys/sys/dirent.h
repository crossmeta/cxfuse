
#ifndef	_SYS_DIRENT_H_
#define	_SYS_DIRENT_H_

#define MAXNAMLEN	255

/*
 * File system independent directory entry
 */
struct dirent {
	ino64_t		d_ino;		/* inode number of entry */
	off64_t		d_off;		/* offset of disk directory entry */
	ushort_t 	d_reclen;	/* length of this record */
	char		d_name[1];	/* name of file */
};

typedef	struct dirent dirent_t;

#ifdef _KERNEL
#define DSIZE	((uint_t)((char *)((struct dirent *)0)->d_name - (char *)0))
#define	DIRHDSIZ	DSIZE
#define nextdp(dp)      ((struct dirent *)((caddr_t)(dp) + (dp)->d_reclen))
#endif

/*
 * Convert between stat structure types and directory types.
 */
#define	IFTODT(mode)	(((mode) & 0170000) >> 12)

/*
 * The _GENERIC_DIRSIZ macro gives the minimum record length which will hold
 * the directory entry.	 This requires the amount of space in struct direct
 * without the d_name field, plus enough space for the name with a terminating
 * null byte (dp->d_namlen+1), rounded up to a 4 byte boundary.
 */
#define _GENERIC_DIRSIZ(dp,n) \
    (sizeof (struct dirent)  + ((n+1 + 3) &~ 3))

#ifdef _KERNEL
#define GENERIC_DIRSIZ(dp,n)	_GENERIC_DIRSIZ(dp,n)
#endif



#endif /* !_SYS_DIRENT_H_ */
