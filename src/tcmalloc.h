// -*- Mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*-
// Copyright (c) 2007, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// ---
// Author: Craig Silverstein <opensource@google.com>
//
// Some obscure memory-allocation routines may not be declared on all
// systems.  In those cases, we'll just declare them ourselves.
// This file is meant to be used only internally, for unittests.

#include <config.h>

#ifndef _XOPEN_SOURCE
# define _XOPEN_SOURCE 600  // for posix_memalign
#endif
#include <stdlib.h>         // for posix_memalign
// FreeBSD has malloc.h, but complains if you use it
#if defined(HAVE_MALLOC_H) && !defined(__FreeBSD__)
#include <malloc.h>         // for memalign, valloc, pvalloc
#endif

// __THROW is defined in glibc systems.  It means, counter-intuitively,
// "This function will never throw an exception."  It's an optional
// optimization tool, but we may need to use it to match glibc prototypes.
#ifndef __THROW    // I guess we're not on a glibc system
# define __THROW   // __THROW is just an optimization, so ok to make it ""
#endif

#if !HAVE_DECL_CFREE
#ifndef __QNX__
 extern "C" void cfree(void* ptr) __THROW;
#else
extern "C" int cfree(void* ptr) __THROW;
#endif
#endif
#if !HAVE_DECL_POSIX_MEMALIGN
extern "C" int posix_memalign(void** ptr, size_t align, size_t size) __THROW;
#endif
#if !HAVE_DECL_MEMALIGN
extern "C" void* memalign(size_t __alignment, size_t __size) __THROW;
#endif
#if !HAVE_DECL_VALLOC
extern "C" void* valloc(size_t __size) __THROW;
#endif
#if !HAVE_DECL_PVALLOC
extern "C" void* pvalloc(size_t __size) __THROW;
#endif
