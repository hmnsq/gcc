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
lang_specific_driver (ರಚನೆ cl_decoded_option **ಒಳ_decoded_options ATTRIBUTE_ಬಳಸದ,
		      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಒಳ_decoded_options_ಎಣಿಕೆ ATTRIBUTE_ಬಳಸದ,
		      ಪೂರ್ಣಾಂಕ *ಒಳ_added_libraries ATTRIBUTE_ಬಳಸದ)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#ಆದರೆ defined(ENABLE_SHARED_LIBGCC) && ! ಮುಂದಿನ_OBJC_RUNTIME
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;

  /* The new argument list will be contained in this.  */
  ರಚನೆ cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  ಪೂರ್ಣಾಂಕ shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ argc;

  /* The argument list.  */
  ರಚನೆ cl_decoded_option *decoded_options;

  argc = *ಒಳ_decoded_options_ಎಣಿಕೆ;
  decoded_options = *ಒಳ_decoded_options;

  ಗಾಗಿ (i = 1; i < argc; i++)
    {
      ಆಯ್ಕೆ (decoded_options[i].opt_ಸೂಚ್ಯಂಕ)
	{
	ಸ್ಥಿತಿ OPT_static_libgcc:
	ಸ್ಥಿತಿ OPT_static:
	  ಹಿಂತಿರುಗಿ;

	ಸ್ಥಿತಿ OPT_SPECIAL_ಒಳಹರಿವು_file:
	  {
	    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file = decoded_options[i].arg;
	    ಪೂರ್ಣಾಂಕ len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (file);
	    ಆದರೆ ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  ನಿಲ್ಲಿಸು;
	}
    }

  ಆದರೆ  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ರಚನೆ cl_decoded_option, argc + 1);

      i = 0;
      ಮಾಡು
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      ಆಗ (i < argc);

      generate_option (OPT_shared_libgcc, ಖಾಲಿ, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *ಒಳ_decoded_options_ಎಣಿಕೆ = i;
      *ಒಳ_decoded_options = new_decoded_options;
    }
#ಆದರೆ_ಅಂತ್ಯ
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
ಪೂರ್ಣಾಂಕ
lang_specific_pre_link (ಶೂನ್ಯ)
{
  ಹಿಂತಿರುಗಿ 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
ಪೂರ್ಣಾಂಕ lang_specific_extra_outfiles = 0;  /* Not used for C.  */
