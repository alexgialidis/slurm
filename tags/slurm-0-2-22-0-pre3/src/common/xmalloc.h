/*****************************************************************************\
 *  xmalloc.h - enhanced malloc routines for slurm
 *  - default: never return if errors are encountered.
 *  - attempt to report file, line, and calling function on assertion failure
 *  - use configurable slurm log facility for reporting errors
 *  $Id$
 *****************************************************************************
 *  Copyright (C) 2002 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Jim Garlick <garlick1@llnl.gov> and 
 *	Mark Grondona <mgrondona@llnl.gov>
 *  UCRL-CODE-2002-040.
 *  
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.llnl.gov/linux/slurm/>.
 *  
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *  
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *****************************************************************************
 * Description:
 *
 * void *xmalloc(size_t size);
 * void *try_xmalloc(size_t size);
 * void xrealloc(void *p, size_t newsize);
 * int  try_xrealloc(void *p, size_t newsize);
 * void xfree(void *p);
 * int  xsize(void *p);
 *
 * xmalloc(size) allocates size bytes and returns a pointer to the allocated
 * memory. The memory is set to zero. xmalloc() will not return unless
 * there are no errors. The memory must be freed using xfree().
 *
 * try_xmalloc(size) is the same as above, but a NULL pointer is returned
 * when there is an error allocating the memory.
 *
 * xrealloc(p, newsize) changes the size of the block pointed to by p to the
 * value of newsize. Newly allocated memory is not zeroed. If p is NULL, 
 * xrealloc() performs the same function as  `p = xmalloc(newsize)'. If p 
 * is not NULL, it is required to have been initialized with a call to 
 * [try_]xmalloc() or [try_]xrealloc().
 *
 * try_xrealloc(p, newsize) is the same as above, but returns <= 0 if the
 * there is an error allocating the requested memory.
 * 
 * xfree(p) frees the memory block pointed to by p. The memory must have been
 * initialized with a call to [try_]xmalloc() or [try_]xrealloc().
 *
 * xsize(p) returns the current size of the memory allocation pointed to by
 * p. The memory must have been allocated with [try_]xmalloc() or 
 * [try_]xrealloc().
 *
\*****************************************************************************/

#ifndef _XMALLOC_H
#define _XMALLOC_H

#if HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif

#include "macros.h"

#define xmalloc(__sz) 		\
	_xmalloc (__sz, __FILE__, __LINE__, __CURRENT_FUNC__)

#define try_xmalloc(__sz)	\
	_try_xmalloc(__sz, __FILE__, __LINE__, __CURRENT_FUNC__)

#define xfree(__p)		\
	_xfree((void **)&(__p), __FILE__, __LINE__, __CURRENT_FUNC__)

#define xrealloc(__p, __sz) 	\
        _xrealloc((void **)&(__p), __sz, __FILE__, __LINE__, __CURRENT_FUNC__)

#define try_xrealloc(__p, __sz) \
	_try_xrealloc((void **)&(__p), __sz, __FILE__, __LINE__, \
		      __CURRENT_FUNC__)

#define xsize(__p)		\
	_xsize((void *)__p, __FILE__, __LINE__, __CURRENT_FUNC__)

void *_xmalloc(size_t size, const char *file, int line, const char *func);
void *_try_xmalloc(size_t size, const char *file, int line, const char *func);
void _xfree(void **p, const char *file, int line, const char *func);
void *_xrealloc(void **p, size_t newsize, 
	       const char *file, int line, const char *func);
int  _try_xrealloc(void **p, size_t newsize,
		   const char *file, int line, const char *func);
int  _xsize(void *p, const char *file, int line, const char *func);

#define XMALLOC_MAGIC 0x42

#endif /* !_XMALLOC_H */
