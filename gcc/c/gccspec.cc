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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "tm.h"
#அந்தர்பாவ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
வெறுமை
lang_specific_driver (கட்டமைப்பு cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned முழு *in_decoded_options_மொத்தம் ATTRIBUTE_UNUSED,
		      முழு *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#எனில் defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned முழு i;

  /* The new argument list will be contained in this.  */
  கட்டமைப்பு cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  முழு shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned முழு argc;

  /* The argument list.  */
  கட்டமைப்பு cl_decoded_option *decoded_options;

  argc = *in_decoded_options_மொத்தம்;
  decoded_options = *in_decoded_options;

  க்கு (i = 1; i < argc; i++)
    {
      தேர்வு (decoded_options[i].opt_index)
	{
	நிலை OPT_static_libgcc:
	நிலை OPT_static:
	  திரும்பு;

	நிலை OPT_SPECIAL_உள்ளீடு_file:
	  {
	    மாறிலி எழுத்து *file = decoded_options[i].arg;
	    முழு len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    எனில் ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  நிறுத்து;
	}
    }

  எனில்  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (கட்டமைப்பு cl_decoded_option, argc + 1);

      i = 0;
      செய்
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      போது (i < argc);

      generate_option (OPT_shared_libgcc, வெற்று, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_மொத்தம் = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
முழு
lang_specific_pre_link (வெறுமை)
{
  திரும்பு 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
முழு lang_specific_extra_outfiles = 0;  /* Not used for C.  */
