/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#include <dlfcn.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#if (!defined __GNUC__ || __GNUC__ < 3) && __cplusplus < 201103L
# error "This program requires Meyer's singleton to be thread-safe.  It appears your compiler doesn't support that."
#endif

namespace {

// First argument is useless. Only to help deduce type
template <typename T> inline
T *get_addr(T *&, const char *name)
{
	return reinterpret_cast<T *>(dlsym(RTLD_NEXT, name));
}

} // namespace

extern "C" {

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	if (addr->sa_family == AF_INET) {
		errno = ENETUNREACH;
		return -1;
	}
	static int (*next_connect)(int, const sockaddr *, socklen_t) = get_addr(next_connect, "connect");
	return next_connect(sockfd, addr, addrlen);
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	if (addr->sa_family == AF_INET) {
		errno = ENETUNREACH;
		return -1;
	}
	static int (*next_bind)(int, const sockaddr *, socklen_t) = get_addr(next_bind, "bind");
	return next_bind(sockfd, addr, addrlen);
}

ssize_t sendto(int fd, const void *buf, size_t len, int flags, const sockaddr *addr, socklen_t addrlen)
{
	if (addr->sa_family == AF_INET) {
		errno = ENETUNREACH;
		return -1;
	}
	static ssize_t (*next_sendto)(int, const void *, size_t, int, const sockaddr *, socklen_t) = get_addr(next_sendto, "sendto");
	return next_sendto(fd, buf, len, flags, addr, addrlen);
}

} // extern "C"
