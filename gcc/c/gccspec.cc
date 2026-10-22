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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "tm.h"
#ಅನ್ತರ್ಭಾವ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
ಶೂನ್ಯ
lang_specific_driver (ಸಂರಚನಾ cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned ಪೂರ್ಣಾಙ್ಕ *in_decoded_options_ಎಣಿಕೆ ATTRIBUTE_UNUSED,
		      ಪೂರ್ಣಾಙ್ಕ *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#ಯದಿ defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned ಪೂರ್ಣಾಙ್ಕ i;

  /* The new argument list will be contained in this.  */
  ಸಂರಚನಾ cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  ಪೂರ್ಣಾಙ್ಕ shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned ಪೂರ್ಣಾಙ್ಕ argc;

  /* The argument list.  */
  ಸಂರಚನಾ cl_decoded_option *decoded_options;

  argc = *in_decoded_options_ಎಣಿಕೆ;
  decoded_options = *in_decoded_options;

  ಪ್ರತಿ (i = 1; i < argc; i++)
    {
      ವಿಕಲ್ಪ (decoded_options[i].opt_index)
	{
	ಪಕ್ಷ OPT_static_libgcc:
	ಪಕ್ಷ OPT_static:
	  ಪ್ರತ್ಯಾಗಮ;

	ಪಕ್ಷ OPT_SPECIAL_ಒಳಹರಿವು_file:
	  {
	    ಧ್ರುವ ವರ್ಣ *file = decoded_options[i].arg;
	    ಪೂರ್ಣಾಙ್ಕ len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    ಯದಿ ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  ಭಙ್ಗ;
	}
    }

  ಯದಿ  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ಸಂರಚನಾ cl_decoded_option, argc + 1);

      i = 0;
      ಕುರು
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      ಯಾವತ್ (i < argc);

      generate_option (OPT_shared_libgcc, ರಿಕ್ತ, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_ಎಣಿಕೆ = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
ಪೂರ್ಣಾಙ್ಕ
lang_specific_pre_link (ಶೂನ್ಯ)
{
  ಪ್ರತ್ಯಾಗಮ 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
ಪೂರ್ಣಾಙ್ಕ lang_specific_extra_outfiles = 0;  /* Not used for C.  */
