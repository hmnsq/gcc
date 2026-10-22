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

#అన్తర్భావ "config.h"
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "tm.h"
#అన్తర్భావ "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
శూన్య
lang_specific_driver (నిర్మాణం cl_decoded_option **లోపల_decoded_options ATTRIBUTE_వాడని,
		      గుర్తులేని పూర్ణాంకం *లోపల_decoded_options_లెక్క ATTRIBUTE_వాడని,
		      పూర్ణాంకం *లోపల_added_libraries ATTRIBUTE_వాడని)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#ఒకవేళ defined(ENABLE_SHARED_LIBGCC) && ! తదుపరి_OBJC_RUNTIME
  గుర్తులేని పూర్ణాంకం i;

  /* The new argument list will be contained in this.  */
  నిర్మాణం cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  పూర్ణాంకం shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  గుర్తులేని పూర్ణాంకం argc;

  /* The argument list.  */
  నిర్మాణం cl_decoded_option *decoded_options;

  argc = *లోపల_decoded_options_లెక్క;
  decoded_options = *లోపల_decoded_options;

  కొరకు (i = 1; i < argc; i++)
    {
      ఎంపిక (decoded_options[i].opt_సూచీ)
	{
	స్థితి OPT_static_libgcc:
	స్థితి OPT_static:
	  తిరిగి;

	స్థితి OPT_SPECIAL_ఆదానం_file:
	  {
	    స్థిరరాశి అక్షరం *file = decoded_options[i].arg;
	    పూర్ణాంకం len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = అక్షరశ్రేణి_పొడవు (file);
	    ఒకవేళ ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  ఆపు;
	}
    }

  ఒకవేళ  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (నిర్మాణం cl_decoded_option, argc + 1);

      i = 0;
      చేయి
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      అయితే (i < argc);

      generate_option (OPT_shared_libgcc, ఖాళీ, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *లోపల_decoded_options_లెక్క = i;
      *లోపల_decoded_options = new_decoded_options;
    }
#అయితే_ముగింపు
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
పూర్ణాంకం
lang_specific_pre_link (శూన్య)
{
  తిరిగి 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
పూర్ణాంకం lang_specific_extra_outfiles = 0;  /* Not used for C.  */
