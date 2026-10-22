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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "system.h"
#অন্তর্ভাৱ "coretypes.h"
#অন্তর্ভাৱ "tm.h"
#অন্তর্ভাৱ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
শূন্য
lang_specific_driver (সংরচনা cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned পূর্ণাঙ্ক *in_decoded_options_গুনতি ATTRIBUTE_UNUSED,
		      পূর্ণাঙ্ক *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#যদি defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned পূর্ণাঙ্ক i;

  /* The new argument list will be contained in this.  */
  সংরচনা cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  পূর্ণাঙ্ক shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned পূর্ণাঙ্ক argc;

  /* The argument list.  */
  সংরচনা cl_decoded_option *decoded_options;

  argc = *in_decoded_options_গুনতি;
  decoded_options = *in_decoded_options;

  বাবে (i = 1; i < argc; i++)
    {
      ৱিকল্প (decoded_options[i].opt_index)
	{
	পক্ষ OPT_static_libgcc:
	পক্ষ OPT_static:
	  ঘূৰাই;

	পক্ষ OPT_SPECIAL_প্ৰবেশ_file:
	  {
	    ধ্রুৱ ৱর্ণ *file = decoded_options[i].arg;
	    পূর্ণাঙ্ক len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    যদি ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  ভঙ্গ;
	}
    }

  যদি  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (সংরচনা cl_decoded_option, argc + 1);

      i = 0;
      কৰা
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      যেতিয়ালৈ (i < argc);

      generate_option (OPT_shared_libgcc, রিক্ত, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_গুনতি = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
পূর্ণাঙ্ক
lang_specific_pre_link (শূন্য)
{
  ঘূৰাই 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
পূর্ণাঙ্ক lang_specific_extra_outfiles = 0;  /* Not used for C.  */
