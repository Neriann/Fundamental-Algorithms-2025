#ifndef ERRORS_H
#define ERRORS_H

#ifdef __linux__
static const char* errlist[] = {
    [0]  = "Success",
    [1]  = "Operation not permitted",                // EPERM
    [2]  = "No such file or directory",               // ENOENT
    [3]  = "No such process",                         // ESRCH
    [4]  = "Interrupted system call",                 // EINTR
    [5]  = "Input/output error",                      // EIO
    [6]  = "No such device or address",               // ENXIO
    [7]  = "Argument list too long",                  // E2BIG
    [8]  = "Exec format error",                       // ENOEXEC
    [9]  = "Bad file descriptor",                     // EBADF
    [10] = "No child processes",                      // ECHILD
    [11] = "Resource temporarily unavailable",        // EAGAIN / EWOULDBLOCK
    [12] = "Cannot allocate memory",                  // ENOMEM
    [13] = "Permission denied",                       // EACCES
    [14] = "Bad address",                             // EFAULT
    [15] = "Block device required",                   // ENOTBLK
    [16] = "Device or resource busy",                 // EBUSY
    [17] = "File exists",                             // EEXIST
    [18] = "Invalid cross-device link",               // EXDEV
    [19] = "No such device",                          // ENODEV
    [20] = "Not a directory",                         // ENOTDIR
    [21] = "Is a directory",                          // EISDIR
    [22] = "Invalid argument",                        // EINVAL
    [23] = "Too many open files in system",           // ENFILE
    [24] = "Too many open files",                     // EMFILE
    [25] = "Inappropriate ioctl for device",          // ENOTTY
    [26] = "Text file busy",                          // ETXTBSY
    [27] = "File too large",                          // EFBIG
    [28] = "No space left on device",                 // ENOSPC
    [29] = "Illegal seek",                            // ESPIPE
    [30] = "Read-only file system",                   // EROFS
    [31] = "Too many links",                          // EMLINK
    [32] = "Broken pipe",                             // EPIPE
    [33] = "Numerical argument out of domain",        // EDOM
    [34] = "Numerical result out of range",           // ERANGE
    [35] = "Resource deadlock avoided",               // EDEADLK
    [36] = "File name too long",                      // ENAMETOOLONG
    [37] = "No locks available",                      // ENOLCK
    [38] = "Function not implemented",                // ENOSYS
    [39] = "Directory not empty",                     // ENOTEMPTY
    [40] = "Too many levels of symbolic links",       // ELOOP
    [41] = "Destination address required",            // EDESTADDRREQ
    [42] = "Message too long",                        // EMSGSIZE
    [43] = "Protocol wrong type for socket",          // EPROTOTYPE
    [44] = "Protocol not available",                  // ENOPROTOOPT
    [45] = "Protocol not supported",                  // EPROTONOSUPPORT
    [46] = "Socket type not supported",               // ESOCKTNOSUPPORT
    [47] = "Operation not supported",                 // EOPNOTSUPP
    [48] = "Protocol family not supported",            // EPFNOSUPPORT
    [49] = "Address family not supported by protocol", // EAFNOSUPPORT
    [50] = "Address already in use",                   // EADDRINUSE
    [51] = "Cannot assign requested address",          // EADDRNOTAVAIL
    [52] = "Network is down",                          // ENETDOWN
    [53] = "Network is unreachable",                  // ENETUNREACH
    [54] = "Network dropped connection on reset",      // ENETRESET
    [55] = "Software caused connection abort",         // ECONNABORTED
    [56] = "Connection reset by peer",                 // ECONNRESET
    [57] = "No buffer space available",               // ENOBUFS
    [58] = "Socket is already connected",              // EISCONN
    [59] = "Socket is not connected",                  // ENOTCONN
    [60] = "Cannot send after transport endpoint shutdown", // ESHUTDOWN
    [61] = "Too many references: cannot splice",        // ETOOMANYREFS
    [62] = "Connection timed out",                     // ETIMEDOUT
    [63] = "Connection refused",                       // ECONNREFUSED
    [64] = "Host is down",                             // EHOSTDOWN
    [65] = "No route to host",                         // EHOSTUNREACH
    [66] = "Operation already in progress",            // EALREADY
    [67] = "Operation now in progress",                // EINPROGRESS
    [68] = "Stale file handle",                        // ESTALE
    [69] = "Structure needs cleaning",                 // EUCLEAN
    [70] = "Not a XENIX named type file",              // ENOTNAM
    // ... и так далее до максимально поддерживаемых кодов
};
#elif __APPLE__
static const char *errlist[] = {
    [0]  = "Undefined error: 0",
    [1]  = "Operation not permitted",                 // EPERM
    [2]  = "No such file or directory",                // ENOENT
    [3]  = "No such process",                          // ESRCH
    [4]  = "Interrupted system call",                  // EINTR
    [5]  = "Input/output error",                       // EIO
    [6]  = "Device not configured",                    // ENXIO on mac
    [7]  = "Argument list too long",                   // E2BIG
    [8]  = "Exec format error",                        // ENOEXEC
    [9]  = "Bad file descriptor",                      // EBADF
    [10] = "No child processes",                       // ECHILD
    [11] = "Resource deadlock avoided",                // EDEADLK on BSD
    [12] = "Cannot allocate memory",                   // ENOMEM
    [13] = "Permission denied",                        // EACCES
    [14] = "Bad address",                              // EFAULT
    [15] = "Block device required",                    // ENOTBLK (mac might not use)
    [16] = "Device busy",                              // EBUSY
    [17] = "File exists",                              // EEXIST
    [18] = "Cross-device link",                        // EXDEV
    [19] = "Operation not supported by device",        // ENODEV maybe
    [20] = "Not a directory",                          // ENOTDIR
    [21] = "Is a directory",                           // EISDIR
    [22] = "Invalid argument",                         // EINVAL
    [23] = "Too many open files in system",            // ENFILE
    [24] = "Too many open files",                      // EMFILE
    [25] = "Inappropriate ioctl for device",           // ENOTTY
    [26] = "Text file busy",                           // ETXTBSY
    [27] = "File too large",                           // EFBIG
    [28] = "No space left on device",                  // ENOSPC
    [29] = "Illegal seek",                             // ESPIPE
    [30] = "Read-only file system",                    // EROFS
    [31] = "Too many links",                           // EMLINK
    [32] = "Broken pipe",                              // EPIPE
    [33] = "Numerical argument out of domain",         // EDOM
    [34] = "Numerical result out of range",            // ERANGE
    [35] = "Resource deadlock avoided",                // EDEADLK alias
    [36] = "File name too long",                       // ENAMETOOLONG
    [37] = "No locks available",                       // ENOLCK
    [38] = "Function not implemented",                 // ENOSYS
    [39] = "Directory not empty",                      // ENOTEMPTY
    [40] = "Too many levels of symbolic links",        // ELOOP
    [41] = "Too many processes",                       // ??? (BSD-specific)
    [42] = "Network is down",                          // ENETDOWN
    [43] = "Network is unreachable",                   // ENETUNREACH
    [44] = "Network dropped connection on reset",       // ENETRESET
    [45] = "Software caused connection abort",          // ECONNABORTED
    [46] = "Connection reset by peer",                  // ECONNRESET
    [47] = "No buffer space available",                // ENOBUFS
    [48] = "Socket is already connected",               // EISCONN
    [49] = "Socket is not connected",                   // ENOTCONN
    [50] = "Destination address required",             // EDESTADDRREQ
    [51] = "Operation queued",                         // ??? (BSD-specific)
    [52] = "Too many connections",                      // ??? etc
    [53] = "Permission denied",                         // duplicate EACCES
    [54] = "Not supported",                             // EOPNOTSUPP
    [55] = "Address family not supported by protocol",   // EAFNOSUPPORT
    [56] = "Address already in use",                     // EADDRINUSE
    [57] = "Cannot assign requested address",            // EADDRNOTAVAIL
    [58] = "Network is down",                            // ENETDOWN (duplicate)
    [59] = "Connection timed out",                       // ETIMEDOUT
    [60] = "Connection refused",                         // ECONNREFUSED
    [61] = "Too many references: can't splice",          // ETOOMANYREFS
    [62] = "Operation already in progress",              // EALREADY
    [63] = "Operation now in progress",                  // EINPROGRESS
    [64] = "Stale file handle",                          // ESTALE
    [65] = "Structure needs cleaning",                   // EUCLEAN
    [66] = "Too many files open for process",             // ??? etc
    [67] = "Too many users",                             // ??? etc
    // … и другие специфичные ошибки macOS
};
#else
#error "Unsupported Operating System"
#endif

#endif //ERRORS_H

const int max_error = sizeof(errlist) / sizeof(errlist[0]);
