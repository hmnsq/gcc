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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "system.h"
#അന്തര്ഭാവ "coretypes.h"
#അന്തര്ഭാവ "tm.h"
#അന്തര്ഭാവ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
ശൂന്യം
lang_specific_driver (ഘടന cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      unsigned പൂർണ്ണസംഖ്യ *in_decoded_options_എണ്ണം ATTRIBUTE_UNUSED,
		      പൂർണ്ണസംഖ്യ *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#എങ്കിൽ defined(ENABLE_SHARED_LIBGCC) && ! NEXT_OBJC_RUNTIME
  unsigned പൂർണ്ണസംഖ്യ i;

  /* The new argument list will be contained in this.  */
  ഘടന cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  പൂർണ്ണസംഖ്യ shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  unsigned പൂർണ്ണസംഖ്യ argc;

  /* The argument list.  */
  ഘടന cl_decoded_option *decoded_options;

  argc = *in_decoded_options_എണ്ണം;
  decoded_options = *in_decoded_options;

  വേണ്ടി (i = 1; i < argc; i++)
    {
      തിരഞ്ഞെടുപ്പ് (decoded_options[i].opt_index)
	{
	അവസ്ഥ OPT_static_libgcc:
	അവസ്ഥ OPT_static:
	  തിരികെ;

	അവസ്ഥ OPT_SPECIAL_നിവേശം_file:
	  {
	    സ്ഥിരം അക്ഷരം *file = decoded_options[i].arg;
	    പൂർണ്ണസംഖ്യ len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = strlen (file);
	    എങ്കിൽ ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  നിർത്തുക;
	}
    }

  എങ്കിൽ  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ഘടന cl_decoded_option, argc + 1);

      i = 0;
      ചെയ്യുക
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      ആകുമ്പോൾ (i < argc);

      generate_option (OPT_shared_libgcc, ശൂന്യ, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_എണ്ണം = i;
      *in_decoded_options = new_decoded_options;
    }
#endif
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
പൂർണ്ണസംഖ്യ
lang_specific_pre_link (ശൂന്യം)
{
  തിരികെ 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
പൂർണ്ണസംഖ്യ lang_specific_extra_outfiles = 0;  /* Not used for C.  */
