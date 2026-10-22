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

#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "tm.h"
#شامل "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
تهی
lang_specific_driver (ساختار cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned صحیح *in_decoded_options_شمار ATTRIBUTE_UNUSED,
		      صحیح *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#اگر defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned صحیح i;

  /* The new argument list will be contained in this.  */
  ساختار cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  صحیح shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned صحیح argc;

  /* The argument list.  */
  ساختار cl_decoded_option *decoded_options;

  argc = *in_decoded_options_شمار;
  decoded_options = *in_decoded_options;

  برای (i = 1; i < argc; i++)
    {
      انتخاب (decoded_options[i].opt_index)
	{
	حالت OPT_static_libgcc:
	حالت OPT_static:
	  بازگشت;

	حالت OPT_SPECIAL_درون_داد_file:
	  {
	    ثابت نویسه *file = decoded_options[i].arg;
	    صحیح len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    اگر ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  بشکن;
	}
    }

  اگر  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ساختار cl_decoded_option, argc + 1);

      i = 0;
      انجامبده
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      وقتی (i < argc);

      generate_option (OPT_shared_libgcc, پوچ, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_شمار = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
صحیح
lang_specific_pre_link (تهی)
{
  بازگشت 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
صحیح lang_specific_extra_outfiles = 0;  /* Not used for C.  */
