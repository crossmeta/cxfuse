/*
 * This is FUSE alike interface for User mode file system development
 * with CROSSMETA Windows Kernel.
 * (C) Copyright 2012 Sammandam, Supramani <suprasam@crossmeta.org>
 */
#ifndef _CROSSMETA_FUSE_H_
#define _CROSSMETA_FUSE_H_

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/statvfs.h>
#include <sys/uio.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_FUSEINTERNAL)
#define	FUSEAPI
#define	FUSECALL
#else
#define	FUSEAPI		_CRTIMP
#define	FUSECALL	__cdecl
#endif

struct cxfuse_file_info {
	unsigned flags;	/* open flags. relevant in open() and release() */
	unsigned int page_io : 1;
	unsigned int direct_io : 1;
	unsigned int keep_cache : 1;
	unsigned int flush : 1;
	unsigned int nonseekable : 1;
	unsigned int padding : 27;
	uint64_t fh;
	uint64_t lock_owner;
};

#define	FUSE_CAP_ASYNC_READ	(1 << 0)
#define	FUSE_CAP_POSIX_LOCKS	(1 << 1)
#define	FUSE_CAP_ATOMIC_O_TRUNC	(1 << 3)
#define	FUSE_CAP_EXPORT_SUPPORT	(1 << 4)
#define	FUSE_CAP_BIG_WRITES	(1 << 5)
#define	FUSE_CAP_DONT_MASK	(1 << 6)

#define	FUSE_IOCTL_COMPAT	(1 << 0)
#define	FUSE_IOCTL_UNRESTRICTED	(1 << 1)
#define	FUSE_IOCTL_RETRY	(1 << 2)

#define	ST_ATIMNSEC(stbuf)	((stbuf)->st_atimespec.tv_nsec)
#define	ST_CTIMNSEC(stbuf)	((stbuf)->st_ctimespec.tv_nsec)
#define	ST_MTIMNSEC(stbuf)	((stbuf)->st_mtimespec.tv_nsec)

#define	ST_ATIMNSEC_SET(stbuf, val)	(stbuf)->st_atimespec.tv_nsec = (val)
#define	ST_MTIMNSEC_SET(stbuf, val)	(stbuf)->st_mtimespec.tv_nsec = (val)

struct cxfuse_conn_info {
	unsigned proto_major;
	unsigned proto_minor;
	unsigned async_read;
	unsigned max_write;
	unsigned max_readahead;
	unsigned capable;
	unsigned want;
	unsigned reserved[25];
};

struct cxfuse_chan;

FUSEAPI struct cxfuse_chan * FUSECALL cxfuse_mount(const char *mountpoint, struct fuse_mount_args *args);

FUSEAPI void FUSECALL cxfuse_unmount(const char *mountpoint, struct cxfuse_chan *ch);
FUSEAPI void FUSECALL cxfuse_kern_unmount(const char *mountpoint);

FUSEAPI int FUSECALL parse_cmdline(struct cxfuse_args *args, char **mountpoint,
				int *multithreaded, int *foreground);

int cxfuse_service(int foreground);
int cxfuse_version(void);
FUSEAPI int FUSECALL cxfuse_svcrun(void);

#if 0
FUSEAPI int cxfuse_set_signal_handlers(struct cxfuse_session *);
FUSEAPI void cxfuse_remove_signal_handlers(struct cxfuse_session *);


typedef int (*cxfuse_fill_dir_t) (void *buf, const char *name,
				const struct stat *stbuf, off_t off);

/* Used by deprecated getdir() method */
typedef struct cxfuse_dirhandle *cxfuse_dirh_t;
typedef int (*cxfuse_dirfil_t) (cxfuse_dirh_t h, const char *name, int type,
			      ino_t ino);
#endif

struct cxfuse_context {
	struct fuse *fuse;
	uid_t uid;
	gid_t gid;
	pid_t pid;
	mode_t umask;
	void *private_data;
};

#define	FUSE_ROOT_ID	1

#ifdef _FUSE_LOWLEVEL_
/*
 * FUSE LOW LEVEL
 */
struct fuse_mount_args {
        int allow_other;
        int allow_root;
	int no_pagecache;
        unsigned int rootmode;
        uid_t user_id;
        gid_t group_id;
        unsigned flags;
        unsigned int max_read;
        unsigned int blksize;
        char portname[32];
};

typedef unsigned long cxfuse_ino_t;
typedef struct cxfuse_req *cxfuse_req_t;
struct cxfuse_session;
struct cxfuse_chan;

struct cxfuse_entry_param {
	cxfuse_ino_t ino;
	unsigned long generation;
	struct stat attr;
	double attr_timeout;
	double entry_timeout;
};

struct cxfuse_ctx {
	uid_t	uid;
	gid_t	gid;
	pid_t	pid;
	mode_t	umask;
};

struct cxfuse_lowlevel_ops {
	void (*init) (void *userdata, struct cxfuse_conn_info *conn);
	void (*destroy) (void *userdata);
	void (*lookup) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name);
	void (*forget) (cxfuse_req_t req, cxfuse_ino_t ino,
			unsigned long nlookup);
	void (*getattr) (cxfuse_req_t req, cxfuse_ino_t ino,
	   		struct cxfuse_file_info * fi);
	void (*setattr) (cxfuse_req_t req, cxfuse_ino_t ino,
			struct stat *attr, int to_set,
			struct cxfuse_file_info * fi);
	void (*access) (cxfuse_req_t req, cxfuse_ino_t ino,
			int mask);
	void (*readlink) (cxfuse_req_t req, cxfuse_ino_t ino);
	void (*mknod) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name, mode_t mode, dev_t rdev);
	void (*mkdir) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name, mode_t mode);
	void (*unlink) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name);
	void (*rmdir) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name);
	void (*symlink) (cxfuse_req_t req, const char *link,
			cxfuse_ino_t parent, const char *name);
	void (*rename) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name, cxfuse_ino_t newparent,
			const char *newname);
	void (*link) (cxfuse_req_t req, cxfuse_ino_t ino,
			cxfuse_ino_t newparent, const char *newname);
	void (*create) (cxfuse_req_t req, cxfuse_ino_t parent,
			const char *name, mode_t mode,
			struct cxfuse_file_info * fi);
	void (*open) (cxfuse_req_t req, cxfuse_ino_t ino,
			struct cxfuse_file_info * fi);
	void (*read) (cxfuse_req_t req, cxfuse_ino_t ino,
			size_t size, off_t off,
			struct cxfuse_file_info * fi);
	void (*write) (cxfuse_req_t req, cxfuse_ino_t ino,
			const char *buf, size_t size, off_t off,
			struct cxfuse_file_info * fi);
	void (*flush) (cxfuse_req_t req, cxfuse_ino_t ino,
			struct cxfuse_file_info * fi);
	void (*release) (cxfuse_req_t req, cxfuse_ino_t ino,
			   struct cxfuse_file_info * fi);
	void (*fsync) (cxfuse_req_t req, cxfuse_ino_t ino,
			int datasync, struct cxfuse_file_info * fi);
	void (*opendir) (cxfuse_req_t req, cxfuse_ino_t ino,
		   struct cxfuse_file_info * fi);
	void (*readdir) (cxfuse_req_t req, cxfuse_ino_t ino,
			size_t size, off_t off,
			struct cxfuse_file_info * fi);
	void (*releasedir) (cxfuse_req_t req, cxfuse_ino_t ino,
		      struct cxfuse_file_info * fi);

	void (*fsyncdir) (cxfuse_req_t req, cxfuse_ino_t ino,
			int datasync, struct cxfuse_file_info * fi);
	void (*statfs) (cxfuse_req_t req, cxfuse_ino_t ino);
	void (*setxattr) (cxfuse_req_t req, cxfuse_ino_t ino,
			const char *name, const char *value, size_t size,
			int flags);
	void (*getxattr) (cxfuse_req_t req, cxfuse_ino_t ino,
			const char *name, size_t size);
	void (*listxattr) (cxfuse_req_t req, cxfuse_ino_t ino,
			size_t size);
	void (*removexattr) (cxfuse_req_t req, cxfuse_ino_t ino,
				const char *name);
	void (*getlk) (cxfuse_req_t req, cxfuse_ino_t ino,
			struct cxfuse_file_info * fi,
			struct flock * lock);
	void (*setlk) (cxfuse_req_t req, cxfuse_ino_t ino,
			struct cxfuse_file_info * fi,
			 struct flock * lock, int sleep);
	void (*bmap) (cxfuse_req_t req, cxfuse_ino_t ino,
			size_t blocksize, uint64_t idx);
	void (*ioctl) (cxfuse_req_t req, cxfuse_ino_t ino, int cmd, void *arg,
			struct cxfuse_file_info *fi, unsigned flags,
			const void *in_buf, size_t in_bufsz, size_t out_bufsz);
	void (*poll) (cxfuse_req_t req, cxfuse_ino_t ino,
			struct cxfuse_file_info *fi,
			struct cxfuse_pollhandle *ph);
};


/* function/macro definitions */


#if 0
int cxfuse_parse_cmdline(struct cxfuse_args *args, char **mountpoint,
                           int *multithreaded, int *foreground);

typedef int (*cxfuse_opt_proc_t) (void *data, const char *arg, int key,
                                    struct cxfuse_args * outargs);
int cxfuse_opt_parse(struct cxfuse_args *args, void *data,
                       const struct cxfuse_opt opts[], cxfuse_opt_proc_t proc);
int cxfuse_opt_add_opt(char **opts, const char *opt);
int cxfuse_opt_add_arg(struct cxfuse_args *args, const char *arg);
int cxfuse_opt_insert_arg(struct cxfuse_args *args, int pos, const char *arg);
FUSEAPI void FUSECALL cxfuse_opt_free_args(struct cxfuse_args *args);
int cxfuse_opt_match(const struct cxfuse_opt opts[], const char *opt);
FUSEAPI int FUSECALL cxfuse_lowlevel_is_lib_option(const char *opt);
#endif

/* reply functions */

FUSEAPI int FUSECALL cxfuse_reply_err(cxfuse_req_t req, int err);
FUSEAPI void FUSECALL cxfuse_reply_none(cxfuse_req_t req);
FUSEAPI int FUSECALL cxfuse_reply_entry(cxfuse_req_t req, const struct cxfuse_entry_param *e);
FUSEAPI int FUSECALL cxfuse_reply_create(cxfuse_req_t req, const struct cxfuse_entry_param *e,
                          const struct cxfuse_file_info *fi);
FUSEAPI int FUSECALL cxfuse_reply_attr(cxfuse_req_t req, const struct stat *attr, double attr_timeout);
FUSEAPI int FUSECALL cxfuse_reply_readlink(cxfuse_req_t req, const char *link);
FUSEAPI int FUSECALL cxfuse_reply_open(cxfuse_req_t req, const struct cxfuse_file_info *fi);
FUSEAPI int FUSECALL cxfuse_reply_write(cxfuse_req_t req, size_t count);
FUSEAPI int FUSECALL cxfuse_reply_buf(cxfuse_req_t req, const char *buf, size_t size);
FUSEAPI int FUSECALL cxfuse_reply_iov(cxfuse_req_t req, const struct iovec *iov, int count);
FUSEAPI int FUSECALL cxfuse_reply_statfs(cxfuse_req_t req, const struct statvfs *stbuf);
FUSEAPI int FUSECALL cxfuse_reply_xattr(cxfuse_req_t req, size_t count);
FUSEAPI int FUSECALL cxfuse_reply_lock(cxfuse_req_t req, struct flock *lock);
FUSEAPI int FUSECALL cxfuse_reply_bmap(cxfuse_req_t req, uint64_t idx);
FUSEAPI size_t FUSECALL cxfuse_add_direntry(cxfuse_req_t req, char *buf, size_t bufsize,
                             const char *name, const struct stat *stbuf, off_t off);
FUSEAPI int FUSECALL cxfuse_reply_ioctl(cxfuse_req_t req, int result, const void *buf, size_t size);
FUSEAPI int FUSECALL cxfuse_reply_poll(cxfuse_req_t req, unsigned revents);
FUSEAPI int FUSECALL cxfuse_lowlevel_notify_poll(struct cxfuse_pollhandle *ph);



/* req functions */

FUSEAPI void *FUSECALL cxfuse_req_userdata(cxfuse_req_t req);
FUSEAPI const struct cxfuse_ctx *FUSECALL cxfuse_req_ctx(cxfuse_req_t req);

typedef void (*cxfuse_interrupt_func_t) (cxfuse_req_t req, void *data);

FUSEAPI void FUSECALL cxfuse_req_interrupt_func(cxfuse_req_t req, cxfuse_interrupt_func_t func,
                                 void *data);
FUSEAPI int FUSECALL cxfuse_req_interrupted(cxfuse_req_t req);

FUSEAPI struct cxfuse_session *FUSECALL cxfuse_lowlevel_new(struct cxfuse_args *args,
                                               const struct cxfuse_lowlevel_ops *op,
                                               size_t op_size, void *userdata);

struct cxfuse_session *cxfuse_lowlevel_new25(struct cxfuse_args *args,
                                                 const struct cxfuse_lowlevel_ops25 *op,
                                                 size_t op_size, void *userdata);

/* session type and calls */

struct cxfuse_session_ops
{
  void (*process) (void *data, const char *buf, size_t len, struct cxfuse_chan * ch);
  void (*exit) (void *data, int val);
  int (*exited) (void *data);
  void (*destroy) (void *data);
};

FUSEAPI struct cxfuse_session *FUSECALL cxfuse_session_new(struct cxfuse_session_ops *op,
                                              void *data);
FUSEAPI void FUSECALL cxfuse_session_add_chan(struct cxfuse_session *se, struct cxfuse_chan *ch);
FUSEAPI void FUSECALL cxfuse_session_remove_chan(struct cxfuse_chan *ch);
FUSEAPI struct cxfuse_chan *FUSECALL cxfuse_session_next_chan(struct cxfuse_session *se,
                                                 struct cxfuse_chan *ch);
FUSEAPI void FUSECALL cxfuse_session_process(struct cxfuse_session *se, const char *buf, size_t len,
                              struct cxfuse_chan *ch);
FUSEAPI void FUSECALL cxfuse_session_destroy(struct cxfuse_session *se);
FUSEAPI void FUSECALL cxfuse_session_exit(struct cxfuse_session *se);
FUSEAPI void FUSECALL cxfuse_session_reset(struct cxfuse_session *se);
FUSEAPI int FUSECALL cxfuse_session_exited(struct cxfuse_session *se);
FUSEAPI int FUSECALL cxfuse_session_loop(struct cxfuse_session *se);
FUSEAPI int FUSECALL cxfuse_session_loop_mt(struct cxfuse_session *se);

/* chan type and calls */

struct cxfuse_chan_ops
{
  int (*receive) (struct cxfuse_chan ** chp, char *buf, size_t size);
  int (*fillhdr) (struct cxfuse_chan * ch, char *in, char *out, size_t size);
  int (*send) (struct cxfuse_chan * ch, char *buf, size_t size);
  void (*destroy) (struct cxfuse_chan * ch);
};

FUSEAPI struct cxfuse_chan *FUSECALL cxfuse_chan_new(struct cxfuse_chan_ops *op, int fd,
                                        size_t bufsize, void *data);
cxfuse_req_t cxfuse_chan_getreq(struct cxfuse_chan *ch);
uint64_t cxfuse_chan_msgid(struct cxfuse_chan *ch, void *hdr);
pid_t cxfuse_chan_clientid(struct cxfuse_chan *ch, void *hdr);
FUSEAPI int FUSECALL cxfuse_chan_fd(struct cxfuse_chan *ch);
FUSEAPI size_t FUSECALL cxfuse_chan_bufsize(struct cxfuse_chan *ch);
FUSEAPI void *FUSECALL cxfuse_chan_data(struct cxfuse_chan *ch);
FUSEAPI struct cxfuse_session *FUSECALL cxfuse_chan_session(struct cxfuse_chan *ch);
FUSEAPI int FUSECALL cxfuse_chan_recv(struct cxfuse_chan **chpp, char *buf, size_t size);
FUSEAPI int FUSECALL cxfuse_chan_fillhdr(struct cxfuse_chan *ch, char *in, char *out, size_t count);
FUSEAPI int FUSECALL cxfuse_chan_send(struct cxfuse_chan *ch, char *buf, size_t size);
FUSEAPI void FUSECALL cxfuse_chan_destroy(struct cxfuse_chan *ch);

//FUSEAPI struct cxfuse_chan *FUSECALL cxfuse_mount(const char *mountpoint, struct fuse_mount_args *args);
int cxfuse_mount25(const char *mountpoint, struct cxfuse_args *args);

void cxfuse_unmount25(const char *mountpoint);
FUSEAPI void FUSECALL cxfuse_unmount(const char *mountpoint, struct cxfuse_chan *ch);

/* for backward compatibility */
int cxfuse_chan_receive(struct cxfuse_chan *ch, char *buf, size_t size);
FUSEAPI struct cxfuse_chan *FUSECALL cxfuse_kern_chan_new(char *name);
size_t cxfuse_dirent_size(size_t namelen);
char *cxfuse_add_dirent(char *buf, const char *name, const struct stat *stbuf,
                          off_t off);

#endif /* _FUSE_LOWLEVEL_ */

#ifdef __cplusplus
}
#endif

#endif /* _CROSSMETA_FUSE_H_ */
