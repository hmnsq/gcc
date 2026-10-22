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
خالی
lang_specific_driver (ساخت cl_decoded_option **اندر_decoded_options ATTRIBUTE_غیر_مستعمل,
		      غیرعلامتی صحیح *اندر_decoded_options_گنتی ATTRIBUTE_غیر_مستعمل,
		      صحیح *اندر_added_libraries ATTRIBUTE_غیر_مستعمل)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#اگر defined(ENABLE_SHARED_LIBGCC) && ! اگلا_OBJC_RUNTIME
  غیرعلامتی صحیح i;

  /* The new argument list will be contained in this.  */
  ساخت cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  صحیح shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  غیرعلامتی صحیح argc;

  /* The argument list.  */
  ساخت cl_decoded_option *decoded_options;

  argc = *اندر_decoded_options_گنتی;
  decoded_options = *اندر_decoded_options;

  برائے (i = 1; i < argc; i++)
    {
      انتخاب (decoded_options[i].opt_اشاریہ)
	{
	حالت OPT_static_libgcc:
	حالت OPT_static:
	  واپس;

	حالت OPT_SPECIAL_داخلہ_file:
	  {
	    ثابت حرف *file = decoded_options[i].arg;
	    صحیح len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = لڑی_لمبائی (file);
	    اگر ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  توڑو;
	}
    }

  اگر  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ساخت cl_decoded_option, argc + 1);

      i = 0;
      کرو
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      جب (i < argc);

      generate_option (OPT_shared_libgcc, تہی, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *اندر_decoded_options_گنتی = i;
      *اندر_decoded_options = new_decoded_options;
    }
#اگر_ختم
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
صحیح
lang_specific_pre_link (خالی)
{
  واپس 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
صحیح lang_specific_extra_outfiles = 0;  /* Not used for C.  */
