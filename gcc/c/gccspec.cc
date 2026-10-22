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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "tm.h"
#અન્તર્ભાવ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
શૂન્ય
lang_specific_driver (સંરચના cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned પૂર્ણાંક *in_decoded_options_ગણતરી ATTRIBUTE_UNUSED,
		      પૂર્ણાંક *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#જો defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned પૂર્ણાંક i;

  /* The new argument list will be contained in this.  */
  સંરચના cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  પૂર્ણાંક shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned પૂર્ણાંક argc;

  /* The argument list.  */
  સંરચના cl_decoded_option *decoded_options;

  argc = *in_decoded_options_ગણતરી;
  decoded_options = *in_decoded_options;

  માટે (i = 1; i < argc; i++)
    {
      પસંદગી (decoded_options[i].opt_index)
	{
	સ્થિતિ OPT_static_libgcc:
	સ્થિતિ OPT_static:
	  પાછા;

	સ્થિતિ OPT_SPECIAL_આગત_file:
	  {
	    અચલ અક્ષર *file = decoded_options[i].arg;
	    પૂર્ણાંક len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    જો ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  તોડો;
	}
    }

  જો  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (સંરચના cl_decoded_option, argc + 1);

      i = 0;
      કરો
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      જ્યારે (i < argc);

      generate_option (OPT_shared_libgcc, ખાલી, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_ગણતરી = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
પૂર્ણાંક
lang_specific_pre_link (શૂન્ય)
{
  પાછા 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
પૂર્ણાંક lang_specific_extra_outfiles = 0;  /* Not used for C.  */
