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

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
void
lang_specific_driver (sa_nracanaa cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned puur_naa_nka *in_decoded_options_count ATTRIBUTE_UNUSED,
		      puur_naa_nka *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#ᯀᯮᯝ defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned puur_naa_nka i;

  /* The new argument list will be contained in this.  */
  sa_nracanaa cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  puur_naa_nka shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned puur_naa_nka argc;

  /* The argument list.  */
  sa_nracanaa cl_decoded_option *decoded_options;

  argc = *in_decoded_options_count;
  decoded_options = *in_decoded_options;

  for (i = 1; i < argc; i++)
    {
      switch (decoded_options[i].opt_index)
	{
	pak_sa OPT_static_libgcc:
	pak_sa OPT_static:
	  ᯀᯮᯞ;

	pak_sa OPT_SPECIAL_input_file:
	  {
	    const var_na *file = decoded_options[i].arg;
	    puur_naa_nka len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    ᯀᯮᯝ ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  bha_nga;
	}
    }

  ᯀᯮᯝ  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (sa_nracanaa cl_decoded_option, argc + 1);

      i = 0;
      do
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      ᯀᯬᯝ (i < argc);

      generate_option (OPT_shared_libgcc, NULL, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_count = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
puur_naa_nka
lang_specific_pre_link (void)
{
  ᯀᯮᯞ 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
puur_naa_nka lang_specific_extra_outfiles = 0;  /* Not used for C.  */
