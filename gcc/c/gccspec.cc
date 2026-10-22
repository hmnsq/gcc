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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "tm.h"
#अन्तर्भाव "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
शून्य
lang_specific_driver (संरचना cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned पूर्णाङ्क *in_decoded_options_गिनती ATTRIBUTE_UNUSED,
		      पूर्णाङ्क *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#यदि defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned पूर्णाङ्क i;

  /* The new argument list will be contained in this.  */
  संरचना cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  पूर्णाङ्क shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned पूर्णाङ्क argc;

  /* The argument list.  */
  संरचना cl_decoded_option *decoded_options;

  argc = *in_decoded_options_गिनती;
  decoded_options = *in_decoded_options;

  प्रति (i = 1; i < argc; i++)
    {
      विकल्प (decoded_options[i].opt_index)
	{
	पक्ष OPT_static_libgcc:
	पक्ष OPT_static:
	  प्रत्यागम;

	पक्ष OPT_SPECIAL_निवेश_file:
	  {
	    ध्रुव वर्ण *file = decoded_options[i].arg;
	    पूर्णाङ्क len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    यदि ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  भङ्ग;
	}
    }

  यदि  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (संरचना cl_decoded_option, argc + 1);

      i = 0;
      कुरु
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      यावत् (i < argc);

      generate_option (OPT_shared_libgcc, रिक्त, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_गिनती = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
पूर्णाङ्क
lang_specific_pre_link (शून्य)
{
  प्रत्यागम 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
पूर्णाङ्क lang_specific_extra_outfiles = 0;  /* Not used for C.  */
