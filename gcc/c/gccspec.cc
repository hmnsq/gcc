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

#समावेश "config.h"
#समावेश "system.h"
#समावेश "coretypes.h"
#समावेश "tm.h"
#समावेश "opts.h"

/* Filter command line before processing by the gcc driver proper.  */
व्योम
lang_specific_driver (काष्ठा cl_decoded_option **in_decoded_options ATTRIBUTE_UNUSED,
		      अचिन्हित पूर्णांक *in_decoded_options_गिनती ATTRIBUTE_UNUSED,
		      पूर्णांक *in_added_libraries ATTRIBUTE_UNUSED)
{
  /* Systems which use the NeXT runtime by default should arrange
     for the shared libgcc to be used when -fgnu-runtime is passed
     through specs.  */
#अगर defined(ENABLE_SHARED_LIBGCC) && ! अग्र_OBJC_RUNTIME
  अचिन्हित पूर्णांक i;

  /* The new argument list will be contained in this.  */
  काष्ठा cl_decoded_option *new_decoded_options;

  /* True if we should add -shared-libgcc to the command-line.  */
  पूर्णांक shared_libgcc = 0;

  /* The total number of arguments with the new stuff.  */
  अचिन्हित पूर्णांक argc;

  /* The argument list.  */
  काष्ठा cl_decoded_option *decoded_options;

  argc = *in_decoded_options_गिनती;
  decoded_options = *in_decoded_options;

  क्रम (i = 1; i < argc; i++)
    {
      चयन (decoded_options[i].opt_सूचकांक)
	{
	हाल OPT_static_libgcc:
	हाल OPT_static:
	  वापस;

	हाल OPT_SPECIAL_निवेश_file:
	  {
	    स्थिर अक्षर *file = decoded_options[i].arg;
	    पूर्णांक len;

	    /* If the filename ends in .m or .mi, we are compiling
	       ObjC and want to pass -shared-libgcc.  */
	    len = म_माप (file);
	    अगर ((len > 2 && file[len - 2] == '.' && file[len - 1] == 'm')
		||  (len > 3 && file[len - 3] == '.' && file[len - 2] == 'm'
		     && file[len - 1] == 'i'))
	      shared_libgcc = 1;
	  }
	  अवरोध;
	}
    }

  अगर  (shared_libgcc)
    {
      new_decoded_options = XNEWVEC (काष्ठा cl_decoded_option, argc + 1);

      i = 0;
      करो
	{
	  new_decoded_options[i] = decoded_options[i];
	  i++;
	}
      जबतक (i < argc);

      generate_option (OPT_shared_libgcc, शून्य, 1, CL_DRIVER,
		       &new_decoded_options[i++]);

      *in_decoded_options_गिनती = i;
      *in_decoded_options = new_decoded_options;
    }
#पूर्ण_अगर
}

/* Called before linking.  Returns 0 on success and -1 on failure.  */
पूर्णांक
lang_specific_pre_link (व्योम)
{
  वापस 0;  /* Not used for C.  */
}

/* Number of extra output files that lang_specific_pre_link may generate.  */
पूर्णांक lang_specific_extra_outfiles = 0;  /* Not used for C.  */
