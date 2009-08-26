/**
 * @file     element_attribute.c
 * @brief    element.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Aug 27, 2009 01:43
 *
 * @if copyright
 *
 * Copyright (C) 2009 Aleix Conchillo Flaque
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @endif
 */

#include "xelement.h"

#include "str.h"

#include "xattribute.h"
#include "xerror.h"

#include <assert.h>



/* Private */

static scew_bool cmp_attr_name_ (void const *attribute, void const *name);



/* Public */

unsigned int
scew_element_attribute_count (scew_element const *element)
{
  assert (element != NULL);

  return element->n_attributes;
}

scew_list*
scew_element_attributes (scew_element const *element)
{
  assert (element != NULL);

  return element->attributes;
}

scew_attribute*
scew_element_attribute_by_name (scew_element const *element,
				XML_Char const *name)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (name != NULL);

  if (element->attributes != NULL)
    {
      item = scew_list_find_custom (element->attributes, name, cmp_attr_name_);
    }

  return (item == NULL) ? NULL : (scew_attribute *) scew_list_data (item);
}

scew_attribute*
scew_element_attribute_by_index (scew_element const *element, unsigned int idx)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (idx < element->n_attributes);

  if (element->attributes != NULL)
    {
      item = scew_list_index (element->attributes, idx);
    }

  return (item == NULL) ? NULL : (scew_attribute *) scew_list_data (item);
}

scew_attribute*
scew_element_add_attribute (scew_element *element, scew_attribute *attribute)
{
  scew_attribute *old_attribute = NULL;

  assert (element != NULL);
  assert (attribute != NULL);

  old_attribute =
    scew_element_attribute_by_name (element, scew_attribute_name (attribute));

  /**
   * If attribute is not already in the element and is not part of
   * another element, append it to its attributes.
   */
  if ((old_attribute == NULL) && (scew_attribute_parent (attribute) == NULL))
    {
      scew_list *item = NULL;

      item = scew_list_append (element->last_attribute, attribute);

      if (item != NULL)
        {
          /* Initialise attributes list. */
          if (element->attributes == NULL)
            {
              element->attributes = item;
            }

          scew_attribute_set_parent_ (attribute, element);

          /* Update performance variables. */
          element->last_attribute = item;
          element->n_attributes += 1;

          /* Update the return value. */
          old_attribute = attribute;
        }
      else
        {
          scew_error_set_last_error_ (scew_error_no_memory);
        }
    }

  return old_attribute;
}

scew_attribute*
scew_element_add_attribute_pair (scew_element *element,
                                 XML_Char const *name,
                                 XML_Char const *value)
{
  scew_attribute *attribute = NULL;

  assert (element != NULL);
  assert (name != NULL);
  assert (value != NULL);

  attribute = scew_attribute_create (name, value);

  if (attribute != NULL)
    {
      scew_attribute *new_attribute = NULL;

      new_attribute = scew_element_add_attribute (element, attribute);
      if (new_attribute == NULL)
        {
          /* We need to free the created attribute as it could not be
             added. */
          scew_attribute_free (attribute);
        }
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return attribute;
}

void
scew_element_delete_attribute (scew_element *element,
                               scew_attribute *attribute)
{
  assert (element != NULL);
  assert (attribute != NULL);

  element->attributes = scew_list_delete (element->attributes, attribute);
  element->n_attributes -= 1;

  scew_attribute_set_parent_ (attribute, NULL);
}

void
scew_element_delete_attribute_all (scew_element *element)
{
  scew_list *list = NULL;

  assert (element != NULL);

  list = element->attributes;
  while (list != NULL)
    {
      scew_attribute *aux = scew_list_data (list);
      list = scew_list_next (list);
      scew_attribute_free (aux);
    }
  scew_list_free (element->attributes);

  element->attributes = NULL;
  element->last_attribute = NULL;
  element->n_attributes = 0;
}

void
scew_element_delete_attribute_by_name (scew_element *element,
                                       XML_Char const* name)
{
  assert (element != NULL);
  assert (name != NULL);

  if (element->attributes != NULL)
    {
      scew_list *item =
        scew_list_find_custom (element->attributes, name, cmp_attr_name_);

      if (item != NULL)
        {
          element->attributes =
            scew_list_delete_item (element->attributes, item);
          element->n_attributes -= 1;
        }
    }
}

void
scew_element_delete_attribute_by_index (scew_element *element,
                                        unsigned int idx)
{
  assert (element != NULL);
  assert (idx < element->n_attributes);

  if (element->attributes != NULL)
    {
      scew_list *item = scew_list_index (element->attributes, idx);

      if (item != NULL)
        {
          element->attributes =
            scew_list_delete_item (element->attributes, item);
          element->n_attributes -= 1;
        }
    }
}


/* Private */

scew_bool
cmp_attr_name_ (void const *attribute, void const *name)
{
  return (scew_strcmp (scew_attribute_name ((scew_attribute *) attribute),
                       (XML_Char *) name) == 0);
}
