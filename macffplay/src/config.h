/* xbmc/config.h.  Generated from config.h.in by configure.  */
/* xbmc/config.h.in.  Generated from configure.ac by autoheader.  */

#pragma once

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 if the `closedir' function returns void instead of `int'. */
/* #undef CLOSEDIR_VOID */

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* FFmpeg version hash */
#define FFMPEG_VER_SHA "2.6.4-Isengard"

/* Define to 0 to disable ALSA support */
#define HAS_ALSA 1

/* Define to 1 if your compiler supports the __sync_add_and_fetch() intrinsic.
   */
#define HAS_BUILTIN_SYNC_ADD_AND_FETCH 1

/* Define to 1 if your compiler supports the __sync_sub_and_fetch() intrinsic.
   */
#define HAS_BUILTIN_SYNC_SUB_AND_FETCH 1

/* Define to 1 if your compiler supports the __sync_val_compare_and_swap()
   intrinsic. */
#define HAS_BUILTIN_SYNC_VAL_COMPARE_AND_SWAP 1

/* Whether OpenSSL inside libcurl is static. */
/* #undef HAS_CURL_STATIC */

/* Define to 1 to have optical drive support */
/* #undef HAS_DVD_DRIVE */

/* Define if supporting EGL based GLES Framebuffer */
#define HAS_EGLGLES 1

/* Define if supporting Hybris based systems */
#define HAS_HYBRIS 1

/* using imxvpu */
/* #undef HAS_IMXVPU */

/* using amcodec */
/* #undef HAS_LIBAMCODEC */

/* Whether to use libRTMP library. */
#define HAS_LIBRTMP 1

/* using libstagefright */
/* #undef HAS_LIBSTAGEFRIGHT */

/* "Define to 1 if MMAL libs is enabled" */
/* #undef HAS_MMAL */

/* using omxplayer */
/* #undef HAS_OMXPLAYER */

/* "Define to 1 if using SDL joystick" */
/* #undef HAS_SDL_JOYSTICK */

/* Whether to build the touch skin. */
/* #undef HAS_TOUCH_SKIN */

/* Define to 1 if you have the `alarm' function. */
#define HAVE_ALARM 1

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* "Define to 1 if Google Breakpad is installed" */
/* #undef HAVE_BREAKPAD */

/* Define to 1 if you have the <cdio/iso9660.h> header file. */
#define HAVE_CDIO_ISO9660_H 1

/* Define to 1 if the system has the type `char16_t'. */
#define HAVE_CHAR16_T 1

/* Define to 1 if the system has the type `char32_t'. */
#define HAVE_CHAR32_T 1

/* Define to 1 if your system has a working `chown' function. */
#define HAVE_CHOWN 1

/* define if the compiler supports basic C++11 syntax */
#define HAVE_CXX11 1

/* "Define to 1 if dbus is installed" */
#define HAVE_DBUS 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the `dup2' function. */
#define HAVE_DUP2 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `fdatasync' function. */
#define HAVE_FDATASYNC 1

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the `floor' function. */
/* #undef HAVE_FLOOR */

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the `fs_stat_dev' function. */
/* #undef HAVE_FS_STAT_DEV */

/* Define to 1 if you have the `ftime' function. */
#define HAVE_FTIME 1

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define if we have gcrypt */
/* #undef HAVE_GCRYPT */

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `gethostbyaddr' function. */
#define HAVE_GETHOSTBYADDR 1

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpass' function. */
#define HAVE_GETPASS 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define if we have gnutls */
#define HAVE_GNUTLS 1

/* Define to 1 if you have the `inet_ntoa' function. */
#define HAVE_INET_NTOA 1

/* Define if we have inotify */
#define HAVE_INOTIFY 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `lchown' function. */
#define HAVE_LCHOWN 1

/* Define to 1 if you have the `android' library (-landroid). */
/* #undef HAVE_LIBANDROID */

/* Define to 1 if you have the `avahi-client' library (-lavahi-client). */
#define HAVE_LIBAVAHI_CLIENT 1

/* Define to 1 if you have the `avahi-common' library (-lavahi-common). */
#define HAVE_LIBAVAHI_COMMON 1

/* Define to 1 if you have the `bluetooth' library (-lbluetooth). */
#define HAVE_LIBBLUETOOTH 1

/* System has libbluray library */
/* #undef HAVE_LIBBLURAY */

/* System has libbluray library with bdj support */
/* #undef HAVE_LIBBLURAY_BDJ */

/* Define to 1 if you have the `bz2' library (-lbz2). */
#define HAVE_LIBBZ2 1

/* Whether to use libcap library. */
#define HAVE_LIBCAP 1

/* "Define to 1 if libcec is installed" */
/* #undef HAVE_LIBCEC */

/* Define to 1 if you have the `crypto' library (-lcrypto). */
#define HAVE_LIBCRYPTO 1

/* Define to 1 if you have the `EGL' library (-lEGL). */
#define HAVE_LIBEGL 1

/* Define to 1 if you have the `gcrypt' library (-lgcrypt). */
/* #undef HAVE_LIBGCRYPT */

/* Define to 1 if you have the `GL' library (-lGL). */
/* #undef HAVE_LIBGL */

/* Define to 1 if you have the `GLESv2' library (-lGLESv2). */
#define HAVE_LIBGLESV2 1

/* Define to 1 if you have the `GLEW' library (-lGLEW). */
/* #undef HAVE_LIBGLEW */

/* Define to 1 if you have the `GLU' library (-lGLU). */
/* #undef HAVE_LIBGLU */

/* Define to 1 if you have the `gpg-error' library (-lgpg-error). */
/* #undef HAVE_LIBGPG_ERROR */

/* Define to 1 if you have the `jasper' library (-ljasper). */
#define HAVE_LIBJASPER 1

/* Define to 1 if you have the `jnigraphics' library (-ljnigraphics). */
/* #undef HAVE_LIBJNIGRAPHICS */

/* Define to 1 if you have the `jpeg' library (-ljpeg). */
#define HAVE_LIBJPEG 1

/* Define to 1 if you have the `log' library (-llog). */
/* #undef HAVE_LIBLOG */

/* Define to 1 if you have the `lzo2' library (-llzo2). */
#define HAVE_LIBLZO2 1

/* Define to 1 if you have the `mDNSEmbedded' library (-lmDNSEmbedded). */
/* #undef HAVE_LIBMDNSEMBEDDED */

/* Define to 1 if you have the `microhttpd' library (-lmicrohttpd). */
#define HAVE_LIBMICROHTTPD 1

/* Define to 1 if you have the `mysqlclient' library (-lmysqlclient). */
#define HAVE_LIBMYSQLCLIENT 1

/* Whether to use libnfs library. */
#define HAVE_LIBNFS 1

/* Define to 1 if you have the OpenMax library. */
/* #undef HAVE_LIBOPENMAX */

/* "Define to 1 if libpcre is installed" */
#define HAVE_LIBPCRE 1

/* "Define to 1 if libpcrecpp is installed" */
#define HAVE_LIBPCRECPP 1

/* "Define to 1 if you have libplist." */
#define HAVE_LIBPLIST 1

/* Define to 1 if you have the `pthread' library (-lpthread). */
#define HAVE_LIBPTHREAD 1

/* Pulse audio enabled */
#define HAVE_LIBPULSE 1

/* Define to 1 if you have the <librtmp/amf.h> header file. */
#define HAVE_LIBRTMP_AMF_H 1

/* Define to 1 if you have the <librtmp/log.h> header file. */
#define HAVE_LIBRTMP_LOG_H 1

/* Define to 1 if you have the <librtmp/rtmp.h> header file. */
#define HAVE_LIBRTMP_RTMP_H 1

/* Define to 1 if you have the `SDL' library (-lSDL). */
/* #undef HAVE_LIBSDL */

/* Define to 1 if you have the `SDL2_gfx' library (-lSDL2_gfx). */
/* #undef HAVE_LIBSDL2_GFX */

/* "Define to 1 if you have libshairplay." */
/* #undef HAVE_LIBSHAIRPLAY */

/* Define to 1 if you have Samba installed */
#define HAVE_LIBSMBCLIENT 1

/* Whether to use libSSH library. */
#define HAVE_LIBSSH 1

/* Define to 1 if you have the `ssl' library (-lssl). */
#define HAVE_LIBSSL 1

/* Define to 1 if you have the `tiff' library (-ltiff). */
#define HAVE_LIBTIFF 1

/* Define to 1 if you have the `tinyxml' library (-ltinyxml). */
/* #undef HAVE_LIBTINYXML */

/* "Define to 1 if libudev is installed" */
#define HAVE_LIBUDEV 1

/* "Define to 1 if libusb is installed" */
/* #undef HAVE_LIBUSB */

/* Define to 1 if you have the 'vaapi' libraries */
/* #undef HAVE_LIBVA */

/* Define to 1 if you have the 'vdpau' library (-lvdpau). */
/* #undef HAVE_LIBVDPAU */

/* Define to 1 if you have the `yajl' library (-lyajl). */
/* #undef HAVE_LIBYAJL */

/* Define to 1 if you have the `z' library (-lz). */
#define HAVE_LIBZ 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* "Lirc enabled" */
#define HAVE_LIRC 1

/* Define to 1 if you have the `localeconv' function. */
#define HAVE_LOCALECONV 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if `lstat' has the bug that it succeeds when given the
   zero-length file name argument. */
/* #undef HAVE_LSTAT_EMPTY_STRING_BUG */

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define to 1 if you have a working `mmap' system call. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `modf' function. */
#define HAVE_MODF 1

/* Define to 1 if you have the `munmap' function. */
#define HAVE_MUNMAP 1

/* "Define to 1 if you have the `mysql' library (-lmysqlclient)." */
#define HAVE_MYSQL 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <nfsc/libnfs.h> header file. */
#define HAVE_NFSC_LIBNFS_H 1

/* "Define to 1 if OMX libs is enabled" */
/* #undef HAVE_OMXLIB */

/* Define to 1 if you have the <OMX_Core.h> header file. */
/* #undef HAVE_OMX_CORE_H */

/* Define if we have openssl */
#define HAVE_OPENSSL 1

/* Define to 1 if you have the `posix_fadvise' function. */
#define HAVE_POSIX_FADVISE 1

/* Define to 1 if you have the `pow' function. */
/* #undef HAVE_POW */

/* "Define to 1 if pthread has pthread_setname_np" */
#define HAVE_PTHREAD_SETNAME_NP 1

/* "Define to 1 if pthread has pthread_set_name_np" */
/* #undef HAVE_PTHREAD_SET_NAME_NP */

/* If available, contains the Python version number currently in use. */
#define HAVE_PYTHON "2.7"

/* Define to 1 if you have the `rmdir' function. */
#define HAVE_RMDIR 1

/* "Define to 1 if using sdl" */
/* #undef HAVE_SDL */

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the <shairplay/raop.h> header file. */
/* #undef HAVE_SHAIRPLAY_RAOP_H */

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the `sqrt' function. */
/* #undef HAVE_SQRT */

/* Define to 1 if `stat' has the bug that it succeeds when given the
   zero-length file name argument. */
/* #undef HAVE_STAT_EMPTY_STRING_BUG */

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if the system has the type `std::u16string'. */
#define HAVE_STD__U16STRING 1

/* Define to 1 if the system has the type `std::u32string'. */
#define HAVE_STD__U32STRING 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strcoll' function and it is properly defined.
   */
#define HAVE_STRCOLL 1

/* Define to 1 if you have the `strcspn' function. */
#define HAVE_STRCSPN 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strspn' function. */
#define HAVE_STRSPN 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if `cls' is a member of `struct raop_callbacks_s'. */
/* #undef HAVE_STRUCT_RAOP_CALLBACKS_S_CLS */

/* Define to 1 if `st_rdev' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_RDEV 1

/* Define to 1 if you have the `sysinfo' function. */
#define HAVE_SYSINFO 1

/* Define to 1 if you have the <sys/capability.h> header file. */
#define HAVE_SYS_CAPABILITY_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/mount.h> header file. */
#define HAVE_SYS_MOUNT_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/timeb.h> header file. */
#define HAVE_SYS_TIMEB_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/vfs.h> header file. */
#define HAVE_SYS_VFS_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the `tzset' function. */
#define HAVE_TZSET 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `utime' function. */
#define HAVE_UTIME 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if `utime(file, NULL)' sets file's timestamp to the present. */
#define HAVE_UTIME_NULL 1

/* Define to 1 if you have the 'VTBDecoder' library. */
/* #undef HAVE_VIDEOTOOLBOXDECODER */

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have Wayland libs installed. */
/* #undef HAVE_WAYLAND */

/* "Define to 1 if the wayland test-protocol will be built" */
/* #undef HAVE_WAYLAND_XBMC_PROTO */

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define to 1 if you have the <wctype.h> header file. */
#define HAVE_WCTYPE_H 1

/* Define to 1 if Weston SDK is installed. */
/* #undef HAVE_WESTON_SDK */

/* Define to 1 if you have X11 libs installed. */
/* #undef HAVE_X11 */

/* Define to 1 to enable non-free components. */
#define HAVE_XBMC_NONFREE 1

/* Define to 1 if you have libxkbcommon installed. */
/* #undef HAVE_XKBCOMMON */

/* Define to 1 if you have the <yajl/yajl_common.h> header file. */
/* #undef HAVE_YAJL_YAJL_COMMON_H */

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Default LIRC device */
#define LIRC_DEVICE "/dev/lircd"

/* Define to 1 if `lstat' dereferences a symlink specified with a trailing
   slash. */
#define LSTAT_FOLLOWS_SLASHED_SYMLINK 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "kodi"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://trac.kodi.tv"

/* Define to the full name of this package. */
#define PACKAGE_NAME "kodi"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "kodi 15.2.000"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "kodi"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "15.2.000"

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* "SDL major version" */
/* #undef SDL_VERSION */

/* Define to the type of arg 1 for `select'. */
#define SELECT_TYPE_ARG1 int

/* Define to the type of args 2, 3 and 4 for `select'. */
#define SELECT_TYPE_ARG234 (fd_set *)

/* Define to the type of arg 5 for `select'. */
#define SELECT_TYPE_ARG5 (struct timeval *)

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 4

/* The size of `wchar_t', as computed by sizeof. */
#define SIZEOF_WCHAR_T 4

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* "Define to 1 if alsa is installed" */
#define USE_ALSA 1

/* Define to 1 to enable ASAP codec. */
/* #undef USE_ASAP_CODEC */

/* FFmpeg linked statically */
#define USE_STATIC_FFMPEG 1

/* Define to 1 to enable UPnP support. */
#define USE_UPNP 1

/* Version number of package */
#define VERSION "15.2.000"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the type of a signed integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int16_t */

/* Define to the type of a signed integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int32_t */

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */

/* Define to the type of a signed integer type of width exactly 8 bits if such
   a type exists and the standard includes do not define it. */
/* #undef int8_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */
