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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tm.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
ਖਾਲੀ
lang_specific_driver (ਬਣਤਰ cl_decoded_option **ਵਿੱਚ_decoded_options ATTRIBUTE_ਅਣਵਰਤਿਆ,
		      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਵਿੱਚ_decoded_options_ਗਿਣਤੀ ATTRIBUTE_ਅਣਵਰਤਿਆ,
		      ਪੂਰਨ *ਵਿੱਚ_added_libraries ATTRIBUTE_ਅਣਵਰਤਿਆ)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#ਜੇ defined(ENABLE_SHARED_LIBGCC) && ! ਅਗਲਾ_OBJC_RUNTIME
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;

  /* The new argument list will be contained in this.  */
  ਬਣਤਰ cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  ਪੂਰਨ shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ argc;

  /* The argument list.  */
  ਬਣਤਰ cl_decoded_option *decoded_options;

  argc = *ਵਿੱਚ_decoded_options_ਗਿਣਤੀ;
  decoded_options = *ਵਿੱਚ_decoded_options;

  ਲਈ (i = 1; i < argc; i++)
    {
      ਚੋਣ (decoded_options[i].opt_ਸੂਚਕਾਂਕ)
	{
	ਹਾਲਤ OPT_static_libgcc:
	ਹਾਲਤ OPT_static:
	  ਵਾਪਸ;

	ਹਾਲਤ OPT_SPECIAL_ਨਿਵੇਸ਼_file:
	  {
	    ਅਚਲ ਅੱਖਰ *file = decoded_options[i].arg;
	    ਪੂਰਨ len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = ਲੜੀ_ਲੰਬਾਈ (file);
	    ਜੇ ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  ਰੋਕੋ;
	}
    }

  ਜੇ  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (ਬਣਤਰ cl_decoded_option, argc + 1);

      i = 0;
      ਕਰੋ
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      ਜਦੋਂ (i < argc);

      generate_option (OPT_shared_libgcc, ਨਿਰਾ, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *ਵਿੱਚ_decoded_options_ਗਿਣਤੀ = i;
      *ਵਿੱਚ_decoded_options = new_decoded_options;
    }
#ਜੇ_ਅੰਤ
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
ਪੂਰਨ
lang_specific_pre_link (ਖਾਲੀ)
{
  ਵਾਪਸ 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
ਪੂਰਨ lang_specific_extra_outfiles = 0;  /* Not used for C.  */
