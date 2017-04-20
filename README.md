## Crossmeta FUSE for Windows

Crossmeta FUSE (Filesystem in Userspace) is the easiest way to port your favorite FUSE programs to Windows. It is a set of kernel-mode and user mode software that provides:

#### POSIX File system semantics are provided by Crossmeta Kernel

This means symbolic links, hardlinks, mount, etc are available readily for easy integration with your FUSE program.

#### Multi-threaded FUSE DLL in userspace 
Hides all the complexity of interfacing with kernel-mode driver interface and provides both the popular APIs
* Fuse *high-level*, synchronous API 
* Fuse *low-level*, asynchronous API.


Fuse mounts are managed in NT kernel namespace and is available to all Windows applications.

## Examples
FUSE comes with following examples. 
**hello.c**
The "Hello World" sample FUSE program shows uses the high-level API by including fuse.h.  It shows how easy it is to get started. Only changes required was manual initialization 

	static struct fuse_operations hello_oper = {
		.getattr        = hello_getattr,
		.readdir        = hello_readdir,
		.open           = hello_open,
		.read           = hello_read,
	};

Changed to

	hello_oper.getattr      = hello_getattr;
	hello_oper.readdir      = hello_readdir;
	hello_oper.open         = hello_open;
	hello_oper.read         = hello_read;


**hello_ll.c**
The same "Hello World" program using the FUSE Low level API by including `fuse_lowlevel.h`. Once again only changes required was the manual initialzation of `fuse_operations` structure.


## Build Environments

Uses standard Microsoft Build environment and Compilers. The most convenient way is to use the Microsoft DDK build environment.

Install Microsoft DDK 7.1 and start command shell with DDK build environment set to i386.


	git clone https://github.com/crossmeta/cxfuse.git
	set VFS_LIB_PATH=c:\users\user\cxfuse\lib
	cd cxfuse\hello
	build -cz


## Installation

* Download [Crossmeta 2.0] (https://github.com/crossmeta/cxfuse/releases/download/v2.0/crossmeta-fuse-2_0.zip)
* Extract **crossmeta-fuse\_2\_0.zip** to %TEMP\temp\crossmeta
* Launch elevated cmd prompt (Administrator) console
* cd %TEMP%\crossmeta
* Run setup.exe
Follow instructions to install Crossmeta Release 2.0 software.

*No reboot required*

Check Crossmeta kernel is up and running

	cd c:\program files\crossmeta
	service_crossmeta status
	cxvfs is RUNNING
	cxfuse is STOPPED
	cxnfs is STOPPED
	cxhfs is STOPPED
	cxvfsmgr is RUNNING

Start cxfuse service

	C:\Program Files\crossmeta>net start cxfuse

The CROSSMETA FUSE kernel mode driver service was started successfully.

Run hello.exe with mount point in the Crossmeta namespace, which is any directory in V:\ drive

	C:\Program Files\crossmeta>busybox.exe ls /

	bin    cachefs  etc  lib  lost+found  proc  sbin  tmp   var  dev  home
	lib64  mnt      root testdir  usr

copy C:\user\user\cxfuse\lib\w2k\free\i386\hello.exe

	C:\Program Files\crossmeta>hello.exe /mnt
	Sorry run in background not supported.

From another command window

	V:\>cd \mnt
	V:\mnt>dir
	 Volume in drive V is vfsroot
	 Volume Serial Number is 0122-B5C1

	 Directory of V:\mnt

	12/31/1969  05:00 PM    <DIR>          .
	12/31/1969  05:00 PM    <DIR>          ..
	12/31/1969  05:00 PM                13 hello
		       1 File(s)             13 bytes
		       2 Dir(s)       5,242,880 bytes free
	V:\mnt>type hello

	Hello World!

	V:\mnt>

To stop the FUSE program, just issue umount /mnt

	Crossmeta BusyBox v0.60.5 (2017.03.23-21:18+0000) Built-in shell (ash)
	Enter 'help' for a list of built-in commands.

	sh: can't access tty; job control turned off
	# umount /mnt
	#

## Summary
With Crossmeta FUSE for Windows, it is not only easiest to port FUSE programs but also the fastest with no or minimal changes required to your existing FUSE program. Also the Crossmeta kernel provides the necessary POSIX APIs without dependency on yet another software package.

