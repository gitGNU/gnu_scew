/**
 *
 * @file     parser.h
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Mon Nov 25, 2002 00:57
 * @brief    SCEW parser type declaration
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2002 Aleix Conchillo Flaque
 *
 * SCEW is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SCEW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * @endif
 *
 * These are the parser functions which allows to read an XML tree
 * element from a file or a memory buffer. A free parser function is
 * also provided.
 */


#ifndef PARSER_H_ALEIX0211250057
#define PARSER_H_ALEIX0211250057

#include <expat.h>

/**
 * This is the type declaration of the SCEW parser.
 */
typedef struct _scew_parser scew_parser;


/**
 * Creates a parser which is needed to load XML trees. You must call
 * this function in order to use all other SCEW functions.
 */
extern scew_parser*
scew_parser_create();

/**
 * Returns the internal Expat parser. Probably some low-level Expat
 * functions need to be called. This function gives you access to the
 * Expat parser so you will be able to call those functions. If you
 * modify the Expat parser event handling routines, SCEW will not be
 * able to load the XML tree.
 */
extern XML_Parser
scew_parser_expat(scew_parser* parser);

/**
 * Frees a parser memory structure. Call this function when you are
 * done with your XML.
 */
extern void
scew_parser_free(scew_parser* parser);

/**
 * Loads an XML tree from the specified file name using the given
 * parser.
 *
 * @param parser the SCEW parser.
 * @param file_name the file to load the XML from.
 *
 * @see scew_parser_create
 */
extern unsigned int
scew_load_file(scew_parser* parser, char const* file_name);

/**
 * Loads an XML tree from the specified memory buffer of the specified
 * size using the given parser.
 *
 * @param parser the SCEW parser.
 * @param buffer memory buffer to load XML from.
 * @param size size in bytes of the memory buffer.
 *
 * @see scew_parser_create
 */
extern unsigned int
scew_load_buffer(scew_parser* parser, unsigned char const* buffer,
                 unsigned int size);


#endif /* PARSER_H_ALEIX0211250057 */
