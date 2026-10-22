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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "tm.h"
#ଅନ୍ତର୍ଭାଵ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
ଶୂନ୍ୟ
lang_specific_driver (ସଂରଚନା cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *in_decoded_options_ଗଣନା ATTRIBUTE_UNUSED,
		      ପୂର୍ଣ୍ଣସଂଖ୍ୟା *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#ଯଦି defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

  /* The new argument list will be contained in this.  */
  ସଂରଚନା cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc;

  /* The argument list.  */
  ସଂରଚନା cl_decoded_option *decoded_options;

  argc = *in_decoded_options_ଗଣନା;
  decoded_options = *in_decoded_options;

  ପାଇଁ (i = 1; i < argc; i++)
    {
      ବାଛ (decoded_options[i].opt_index)
	{
	ସ୍ଥିତି OPT_static_libgcc:
	ସ୍ଥିତି OPT_static:
	  ଫେରନ୍ତୁ;

	ସ୍ଥିତି OPT_SPECIAL_ନିବେଶ_file:
	  {
	    ଅଚଳ ଅକ୍ଷର *file = decoded_options[i].arg;
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    ଯଦି ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  ଭାଙ୍ଗ;
	}
    }

  ଯଦି  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ସଂରଚନା cl_decoded_option, argc + 1);

      i = 0;
      କର
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      ଯେତେବେଳେ (i < argc);

      generate_option (OPT_shared_libgcc, ଖାଲି, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_ଗଣନା = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା
lang_specific_pre_link (ଶୂନ୍ୟ)
{
  ଫେରନ୍ତୁ 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା lang_specific_extra_outfiles = 0;  /* Not used for C.  */
