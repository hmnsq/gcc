/* Specific flags and argument handling of the C front-end.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "tm.h"
#ضمن "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
فراغ
lang_specific_driver (بنية cl_decoded_option **دننه_decoded_options ATTRIBUTE_ناکارول_شوی,
		      بینښه صحيح *دننه_decoded_options_شمېر ATTRIBUTE_ناکارول_شوی,
		      صحيح *دننه_added_libraries ATTRIBUTE_ناکارول_شوی)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#إذا defined(ENABLE_SHARED_LIBGCC) && ! بل_OBJC_RUNTIME
  بینښه صحيح i;

  /* The new argument list will be contained in this.  */
  بنية cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  صحيح shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  بینښه صحيح argc;

  /* The argument list.  */
  بنية cl_decoded_option *decoded_options;

  argc = *دننه_decoded_options_شمېر;
  decoded_options = *دننه_decoded_options;

  لكل (i = 1; i < argc; i++)
    {
      بدل (decoded_options[i].opt_شاخص)
	{
	حالة OPT_static_libgcc:
	حالة OPT_static:
	  أرجع;

	حالة OPT_SPECIAL_ننوت_file:
	  {
	    ثابت حرف *file = decoded_options[i].arg;
	    صحيح len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = مزي_اوږدوالی (file);
	    إذا ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  اكسر;
	}
    }

  إذا  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (بنية cl_decoded_option, argc + 1);

      i = 0;
      افعل
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      طالما (i < argc);

      generate_option (OPT_shared_libgcc, عدم, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *دننه_decoded_options_شمېر = i;
      *دننه_decoded_options = new_decoded_options;
    }
#د_که_پای
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
صحيح
lang_specific_pre_link (فراغ)
{
  أرجع 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
صحيح lang_specific_extra_outfiles = 0;  /* Not used for C.  */
