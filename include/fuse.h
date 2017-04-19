/*
 * FUSE interface mapped to Crossmeta FUSE on Windows
 * (C) Copyright 2012 Sammandam, Supramani <suprasam@crossmeta.org>
 */
#ifndef	_FUSE_H_
#define	_FUSE_H_

#include <cxfuse.h>

#ifdef __cplusplus
extern "C" {
#endif

/* We look like FUSE version 2.8 */
#define	FUSE_MAJOR_VERSION	2
#define	FUSE_MINOR_VERSION	8

#define	FUSE_MAKE_VERSION(maj, min)	((maj) * 10 + (min))
#define	FUSE_VERSION FUSE_MAKE_VERSION(FUSE_MAJOR_VERSION, FUSE_MINOR_VERSION)

/* 'to_set' flags in setattr */
#define FUSE_SET_ATTR_MODE	(1 << 0)
#define FUSE_SET_ATTR_UID	(1 << 1)
#define FUSE_SET_ATTR_GID	(1 << 2)
#define FUSE_SET_ATTR_SIZE	(1 << 3)
#define FUSE_SET_ATTR_ATIME	(1 << 4)
#define FUSE_SET_ATTR_MTIME	(1 << 5)
#define FUSE_SET_ATTR_ATIME_NOW	(1 << 7)
#define FUSE_SET_ATTR_MTIME_NOW	(1 << 8)


/*
 * Associate them to fuse types with the same name
 * so no change is needed for FUSE-binded filesystems.
 */
#define fuse_ino_t             cxfuse_ino_t
#define fuse_req_t             cxfuse_req_t
#define fuse_session	       cxfuse_session
#define fuse_chan	       cxfuse_chan
#define fuse_entry_param       cxfuse_entry_param
#define fuse_ctx               cxfuse_ctx
#define fuse_conn_info         cxfuse_conn_info
#define fuse_file_info         cxfuse_file_info
#define	fuse_context		cxfuse_context
//#define fuse_args              cxfuse_args
#define fuse_opt               cxfuse_opt
#define fuse_opt_proc_t        cxfuse_opt_proc_t
#define fuse_interrupt_func_t  cxfuse_interrupt_func_t
#define fuse_session_ops       cxfuse_session_ops
#define fuse_chan_ops          cxfuse_chan_ops
#define	fuse_lowlevel_ops	cxfuse_lowlevel_ops

/* call bindings */
#define fuse_parse_cmdline     cxfuse_parse_cmdline

#define fuse_reply_err      cxfuse_reply_err
#define fuse_reply_none     cxfuse_reply_none
#define fuse_reply_entry    cxfuse_reply_entry
#define fuse_reply_create   cxfuse_reply_create
#define fuse_reply_attr     cxfuse_reply_attr
#define fuse_reply_readlink cxfuse_reply_readlink
#define fuse_reply_open     cxfuse_reply_open
#define fuse_reply_write    cxfuse_reply_write
#define fuse_reply_buf      cxfuse_reply_buf
#define fuse_reply_iov      cxfuse_reply_iov
#define fuse_reply_statfs   cxfuse_reply_statfs
#define fuse_reply_xattr    cxfuse_reply_xattr
#define fuse_reply_lock     cxfuse_reply_lock
#define fuse_reply_bmap     cxfuse_reply_bmap
#define fuse_add_direntry   cxfuse_add_direntry
#define	fuse_reply_ioctl	cxfuse_reply_ioctl
#define	fuse_reply_poll		cxfuse_reply_poll

#define fuse_req_userdata   cxfuse_req_userdata
#define fuse_req_ctx        cxfuse_req_ctx
#define fuse_req_interrupt_func cxfuse_req_interrupt_func
#define fuse_req_interrupted    cxfuse_req_interrupted

#define fuse_session_new 	cxfuse_session_new
#define fuse_session_add_chan 	cxfuse_session_add_chan
#define fuse_session_remove_chan cxfuse_session_remove_chan
#define fuse_session_next_chan	cxfuse_session_next_chan
#define fuse_session_process	cxfuse_session_process
#define fuse_session_destroy	cxfuse_session_destroy
#define fuse_session_exit	cxfuse_session_exit
#define fuse_session_reset	cxfuse_session_reset
#define fuse_session_exited	cxfuse_session_exited

#define	fuse_lowlevel_new	cxfuse_lowlevel_new
#define	fuse_lowlevel_notify_poll	cxfuse_lowlevel_notify_poll
#define	fuse_lowlevel_is_lib_option	cxfuse_lowlevel_is_lib_option

#define fuse_chan_new           cxfuse_chan_new
#define fuse_chan_fd            cxfuse_chan_fd
#define fuse_chan_bufsize       cxfuse_chan_bufsize
#define fuse_chan_data          cxfuse_chan_data
#define fuse_chan_session       cxfuse_chan_session
#define fuse_chan_recv          cxfuse_chan_recv
#define fuse_chan_send          cxfuse_chan_send
#define fuse_chan_destroy       cxfuse_chan_destroy
#define fuse_chan_receive       cxfuse_chan_receive
#define fuse_kern_chan_new 	cxfuse_kern_chan_new
#define fuse_kern_unmount	cxfuse_kern_unmount

#define fuse_dirent_size	cxfuse_dirent_size
#define fuse_add_dirent		cxfuse_add_dirent

typedef int (*fuse_fill_dir_t) (void *buf, const char *name,
				const struct stat *stbuf, off_t off);
/* Obsolete */
typedef struct fuse_dirhandle *fuse_dirh_t;
typedef int (*fuse_dirfil_t) (fuse_dirh_t h, const char *name, int type,
				ino_t ino);

struct fuse_cmd {
	char *buf;
	size_t buflen;
	struct fuse_chan *ch;
};

struct fuse_operations {
	int (FUSECALL *getattr) (const char *, struct stat *);
	int (FUSECALL *readlink) (const char *, char *, size_t);
	/* not used anymore, use readdir instead */
	int (FUSECALL *getdir) (const char *, fuse_dirh_t, fuse_dirfil_t);
	int (FUSECALL *mknod) (const char *, mode_t, dev_t);
	int (FUSECALL *mkdir) (const char *, mode_t);
	int (FUSECALL *unlink) (const char *);
	int (FUSECALL *rmdir) (const char *);
	int (FUSECALL *symlink) (const char *, const char *);
	int (FUSECALL *rename) (const char *, const char *);
	int (FUSECALL *link) (const char *, const char *);
	int (FUSECALL *chmod) (const char *, mode_t);
	int (FUSECALL *chown) (const char *, uid_t, gid_t);
	int (FUSECALL *truncate) (const char *, off_t);
	int (FUSECALL *utime) (const char *, struct utimbuf *);
	int (FUSECALL *open) (const char *, struct cxfuse_file_info *);
	int (FUSECALL *read) (const char *, char *, size_t, off_t,
		     struct cxfuse_file_info *);
	int (FUSECALL *write) (const char *, const char *, size_t, off_t,
		      struct cxfuse_file_info *);
	int (FUSECALL *statfs) (const char *, struct statvfs *);
	int (FUSECALL *flush) (const char *, struct cxfuse_file_info *);
	int (FUSECALL *release) (const char *, struct cxfuse_file_info *);
	int (FUSECALL *fsync) (const char *, int, struct cxfuse_file_info *);
	int (FUSECALL *setxattr) (const char *, const char *, const char *, size_t, int);
	int (FUSECALL *getxattr) (const char *, const char *, char *, size_t);
	int (FUSECALL *listxattr) (const char *, char *, size_t);
	int (FUSECALL *removexattr) (const char *, const char *);
	int (FUSECALL *opendir) (const char *, struct cxfuse_file_info *);
	int (FUSECALL *readdir) (const char *, void *, fuse_fill_dir_t, off_t,
			struct cxfuse_file_info *);
	int (FUSECALL *releasedir) (const char *, struct cxfuse_file_info *);
	int (FUSECALL *fsyncdir) (const char *, int, struct cxfuse_file_info *);
	void *(FUSECALL *init) (struct cxfuse_conn_info *conn);
	void (FUSECALL *destroy) (void *);
	int (FUSECALL *access) (const char *, int);
	int (FUSECALL *create) (const char *, mode_t, struct cxfuse_file_info *);
	int (FUSECALL *ftruncate) (const char *, off_t, struct cxfuse_file_info *);
	int (FUSECALL *fgetattr) (const char *, struct stat *, struct cxfuse_file_info *);
	int (FUSECALL *lock) (const char *, struct cxfuse_file_info *, int cmd,
		     struct flock *);
	int (FUSECALL *utimens) (const char *, const struct timespec tv[2]);
	int (FUSECALL *bmap) (const char *, size_t blocksize, uint64_t *idx);

	unsigned int flag_nullpath_ok : 1;
	unsigned int flag_reserved : 31;

	int (FUSECALL *ioctl) (const char *, int cmd, void *arg,
		      struct cxfuse_file_info *, unsigned int flags, void *data);

	int (FUSECALL *poll) (const char *, struct cxfuse_file_info *,
		     struct cxfuse_pollhandle *ph, unsigned *reventsp);
};

#define	fuse_main(argc, argv, op, user_data) 	\
		fuse_main_real(argc, argv, op, sizeof(*(op)), user_data)

struct fuse *fuse_new(struct fuse_chan *ch, struct fuse_args *args,
			const struct fuse_operations *op, size_t op_size,
			void *user_data);

void fuse_destroy(struct fuse *f);

int fuse_loop(struct fuse *f);

void fuse_exit(struct fuse *f);

int fuse_loop_mt(struct fuse *f);

struct fuse_context *fuse_get_context(void);

int fuse_getgroups(int size, gid_t list[]);

int fuse_interrupted(void);

int fuse_main_real(int argc, char *argv[], const struct fuse_operations *op,
                   size_t op_size, void *user_data);

/**
 * Fuse filesystem object
 *
 * This is opaque object represents a filesystem layer
 */
struct fuse_fs;


/* Fuse option parsing */
#ifndef	offsetof
#define	offsetof(t,f)	FIELD_OFFSET(t,f)
#endif

struct fuse_opt {
	const char *templ;
	unsigned long offset;
	int value;
};

#define	FUSE_OPT_KEY(templ, key) { templ, -1U, key }
#define FUSE_OPT_END { NULL, 0, 0 }

struct fuse_args {
	int argc;
	char **argv;
	int allocated;
};

/* macro binding */
#define FUSE_ARGS_INIT(_argc_, _argv_) { _argc_, _argv_, 0 }

#define	FUSE_OPT_KEY_OPT	-1
#define	FUSE_OPT_KEY_NONOPT	-2
#define	FUSE_OPT_KEY_KEEP	-3
#define	FUSE_OPT_KEY_DISCARD	-4

typedef int (CDECL *fuse_opt_proc_t)(void *data, const char *arg, int key,
		struct fuse_args *outargs);

int FUSECALL fuse_opt_parse(struct fuse_args *args, void *data,
			const struct fuse_opt opts[], fuse_opt_proc_t proc);
int FUSECALL fuse_opt_add_opt(char **opts, const char *opt);
int FUSECALL fuse_opt_add_opt_escaped(char **opts, const char *opt);
int FUSECALL fuse_opt_add_arg(struct fuse_args *args, const char *arg);
int FUSECALL fuse_opt_insert_arg(struct fuse_args *args, int pos, const char *arg);
void FUSECALL fuse_opt_free_args(struct fuse_args *args);
int FUSECALL fuse_opt_match(const struct fuse_opt opts[], const char *opt);

struct fuse_module {
	const char *name;
	struct fuse_fs *(*factory)(struct fuse_args *args,
				struct fuse_fs *fs[]);
	struct fuse_module *next;
	struct fusemod_so *so;
	int ctr;
};

/** Function type used to process commands */
typedef void (CDECL *fuse_processor_t)(struct fuse *, struct fuse_cmd *, void *);

#ifdef __cplusplus
}
#endif

#endif	/* _FUSE_H_ */
