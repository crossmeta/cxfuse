/*-
 * Copyright (c) 1991, 1993, 1994
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
 *	@(#)unistd.h	8.12 (Berkeley) 4/27/95
 * $FreeBSD: src/include/unistd.h,v 1.35 2000/02/05 18:42:30 joe Exp $
 */

#ifndef _UNISTD_H_
#define	_UNISTD_H_

#define	_CRT_SYSTEM_DEFINED
#include <stdlib.h>
#include <stdio.h>
#include <cdefs.h>
#include <err.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <process.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define	STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */

#ifndef SEEK_SET
#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2
#endif

#define	strdup		_strdup
#define	snprintf 	_snprintf
#define	strnicmp 	_strnicmp
#define	strncasecmp	_strnicmp
#define	strcasecmp	_stricmp
#define	putenv		_putenv
#define	index		strchr
#define	rindex		strrchr
#define dup		_dup
#define dup2		_dup2
#define	environ		_environ
#define	isatty		_isatty

#define	system		__system

static __inline int 
sleep(unsigned long x)
{
	_CRTIMP void __cdecl _sleep(unsigned long);
	_sleep(x);
	return (0);
}

#if __STDC__
#define isascii		__isascii
#define toascii		__toascii
#ifndef	__MINGW32__
#define alloca		_alloca
#endif
#endif

#define popen		_popen
#define pclose		_pclose

#ifndef bcopy
#define bcopy(s, d, len)	memcpy(d, s, len)
#endif

#ifndef bcmp
#define bcmp(s1, s2, len)	memcmp(s1, s2, len)
#endif

#ifndef bzero
#define bzero(s, len)	memset(s, 0, len)
#endif

#define creat(p, m)	open(p, O_RDWR|O_CREAT|O_TRUNC, m)
#define	pread	pread64
#define	pwrite	pwrite64

extern char *optarg;			/* getopt(3) external variables */
extern char *__progname;		/* getopt(3) external variables */
extern int optind, opterr, optopt;
extern int optreset;			/* getopt(3) external variable */
int	 getopt(int, char * const [], const char *);

extern char *suboptarg;
int	getsubopt(char **, char * const *, char **);

int 	CDECL asprintf(char **, const char *fmt, ...);
int64_t	atoll(char *);
int	access(const char *, int);
char	*basename(const char *);
char	*dirname(const char *);
char 	*crypt(const char *, const char *);
int	close(int);
ssize_t	read(int, void *, size_t);
int	des_cipher(const char *, char *, long, int);
int	des_setkey(const char *key);
int	encrypt(char *, int);
int	chown(const char *, uid_t, gid_t);
int	chdir(const char *);
int	fchdir(int);
int	fchown(int, uid_t, gid_t);
char	*fflagstostr(u_long);
FILE 	*__stdcall cxsys_fopen(const char *, const char *);
#define fopen	cxsys_fopen
int	fileno(FILE *);
FILE 	*fdopen(int, char *);
pid_t	__stdcall fork(void);
int	__stdcall fsync(int);
int 	truncate64(const char *path, off64_t length);
int	ftruncate(int, off_t);
int	ftruncate64(int, off64_t);
char	*getbsize(int *, long *);
char	*getcwd(char *, size_t);
int	__stdcall gethostname(char *, int);
int	__stdcall getdomainname(char *, int);
gid_t	__stdcall getegid(void);
uid_t	geteuid(void);
gid_t	__stdcall getgid(void);
int	getgroups(int, gid_t[]);
int	getgrouplist(const char *, int, int *, int *);
char	*getlogin(void);
int	getpagesize(void);
uid_t	__stdcall getuid(void);
int	lchown(const char *, uid_t, gid_t);
int	link(const char *, const char *);
int	lseek(int, off_t, int);
off64_t	lseek64(int, off64_t, int);
int	mergesort(void *, size_t, size_t,
		 int (CDECL *) __P((const void *, const void *)));
void	*memalign(size_t, size_t);
int	mknod(char *, mode_t, dev_t);
int	mkstemp(char *);
int	pipe(int *);
long	__stdcall random(void);
void	__stdcall srandom(unsigned long);
int	get_random_bytes(char *buf, size_t len);
int	readlink(const char *, char *, int);
void 	*reallocf(void *, size_t);
char	*__stdcall realpath(const char *, char *);
int	__stdcall cxsys_rename(const char *, const char *);
#define rename cxsys_rename		/* include stdio.h before unistd.h */
int	rmdir(const char *);
int	setenv(const char *, const char *, int);
int	symlink(const char *, const char *);
void	sync(void);
int64_t	strtoll(const char *, char **, int);
void	strmode(int, char *);
char 	*__stdcall strsep(char **, char *);
char	*user_from_uid(uid_t, int);
char	*group_from_gid(gid_t, int);
pid_t	getppid(void);
pid_t	getpid(void);
int	unlink(const char *);
int 	execv(const char *path, char *const argv[]);
int 	CDECL execlp(const char *name, const char *arg, ...);
int 	CDECL execl(const char *name, const char *arg, ...);

int 	devopen(char *, int);
int 	devcreate(char *, u_long);
int 	devread(int, char *, int, off_t);
int 	devstat(char *, struct stat *);
int 	devsize(int, u_long *);
int 	devwrite(int, char *, int, off_t);
int 	devioctl(int, u_long, void *, u_long, void *, u_long);
int 	devclose(int);
int 	devmounted(char *);
char 	*vfsregentry(char *, char *);
char 	*vfsmakepath(char *);
int	vfspath_to_NT(char *,struct _UNICODE_STRING *,struct _UNICODE_STRING *);
int     vfs_syscall(int, void *, u_long, void *, u_long);
int 	mapsyserr(u_long);
ssize_t	__stdcall write(int, const void *, size_t);
ssize_t	__stdcall pread64(int fd, void *buf, size_t count, off64_t offset);
ssize_t	__stdcall pwrite64(int fd, void *buf, size_t count, off64_t offset);
int 	__system(const char *command);
void	__stdcall cxsys_exit(int status);
const char *cxrootdir(void);
void execlog(char *fmt, ...);
void forklog(char *fmt, ...);

_CRTIMP int __cdecl _dup(int);
_CRTIMP int __cdecl _dup2(int, int);
_CRTIMP int __cdecl _close(int);
_CRTIMP int __cdecl _isatty(int);
_CRTIMP int __cdecl _read(int, const void *, unsigned int);
_CRTIMP int __cdecl _write(int, const void *, unsigned int);
_CRTIMP void __cdecl _abort(int);
_CRTIMP int __cdecl _fseeki64(FILE * , __int64 , int);
extern int __cdecl __crtconsole(void);

#if defined(__cplusplus)
	}
#endif

#endif /* !_UNISTD_H_ */
