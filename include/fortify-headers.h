/*
 * Copyright (C) 2015-2016 Dimitris Papastamos <sin@2f30.org>
 * Copyright (C) 2022 q66 <q66@chimera-linux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _FORTIFY_HEADERS_H
#define _FORTIFY_HEADERS_H

#ifdef __clang__

/* clang uses overloads; see https://github.com/llvm/llvm-project/issues/53516 */
#define _FORTIFY_POSN(n) const __attribute__((__pass_object_size__(n)))
/* we can't use extern inline with overloads without making them external */
#define _FORTIFY_INLINE static __inline__ \
	__attribute__((__always_inline__,__artificial__,__overloadable__))

#else /* !__clang__ */

#define _FORTIFY_POSN(n)
#define _FORTIFY_INLINE extern __inline__ \
	__attribute__((__always_inline__,__gnu_inline__,__artificial__))

#endif /* __clang__ */

#define _FORTIFY_POS0 _FORTIFY_POSN(0)
#define _FORTIFY_POS1 _FORTIFY_POSN(1)
#define _FORTIFY_POS2 _FORTIFY_POSN(2)

#define _FORTIFY_STR(s) #s
#define _FORTIFY_ORIG(p,fn) __typeof__(fn) __orig_##fn __asm__(_FORTIFY_STR(p) #fn)
#define _FORTIFY_FNB(fn) _FORTIFY_ORIG(__USER_LABEL_PREFIX__,fn)
#define _FORTIFY_FN(fn) _FORTIFY_FNB(fn); _FORTIFY_INLINE

#endif
