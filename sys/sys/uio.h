#ifndef _SYS_UIO_H_
#define _SYS_UIO_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * I/O parameter information.  A uio structure describes the I/O which
 * is to be performed by an operation.  Typically the data movement will
 * be performed by a routine such as uiomove(), which updates the uio
 * structure to reflect what was done.
 */

/*
 * I/O direction.
 */
typedef enum uio_rw { UIO_READ, UIO_WRITE } uio_rw_t;

/*
 * Segment flag values.
 */
typedef enum uio_seg { UIO_USERSPACE, UIO_SYSSPACE, UIO_USERISPACE } uio_seg_t;

typedef struct iovec {
	caddr_t	iov_base;
	int	iov_len;
} iovec_t;

#if defined(_KERNEL)
static __inline size_t
iov_length(const struct iovec *iov, unsigned nr_segs)
{
	unsigned i;
	size_t ret = 0;
	for (i = 0; i < nr_segs; i++)
		ret += iov[i].iov_len;
	return ret;
}

typedef struct uio {
	iovec_t	*uio_iov;	/* pointer to array of iovecs */
	int	uio_iovcnt;	/* number of iovecs */
	off64_t	uio_offset;	/* file offset */
	int	uio_resid;	/* residual count */
	enum uio_seg uio_segflag;	/* address space (kernel or user) */
	enum uio_rw uio_rw;
	struct proc *uio_procp;
	struct file *uio_filp;
} uio_t;

extern int uiomove_catch(void *kernbuf, long n, uio_rw_t rw, uio_t *uiop,
			 uint_t catch_flags);
extern int ureadc(int val, uio_t *uiop);
extern int uwritec(uio_t *uiop);
extern int uiomvuio(uio_t *ruiop, uio_t *wuiop);
extern void uioskip(uio_t *uiop, long n);
extern void uioupdate(uio_t *uiop, long n);
#endif /* _KERNEL */

#if defined(__cplusplus)
	}
#endif

#endif /* _SYS_UIO_H_ */
