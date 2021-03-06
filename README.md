[![Build Status](https://travis-ci.org/aconchillo/scew.svg?branch=master)](https://travis-ci.org/aconchillo/scew)

SCEW: A Simple C Expat Wrapper
==============================

   The aim of SCEW is to provide an easy interface around the XML
Expat parser, as well as a simple interface for creating new XML
documents. It provides functions to load and access XML elements
without the need to create Expat event handling routines every time
you want to load a new XML document.

These are the main SCEW features:

- Uses a DOM-like object model for new or parsed XML documents.
- Supports loading concatenated XML documents.
- Can copy and compare full XML documents, elements or attributes.
- Writes XML documents to multiple outputs.
- Allows adding new I/O sources easily.
- UTF-8, ISO-8859-1 and US-ASCII encodings (and UTF-16 in Windows).

Project homepage: http://www.nongnu.org/scew/

SCEW is free software [0]. Please see the file COPYING for details.

For installation instructions please see the INSTALL files.

--

[0] To learn more about GNU, the FSF and its goals, please visit
    http://www.gnu.org.
