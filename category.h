/*
 * Copyright (c) 2001, Robert Collins.
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     A copy of the GNU General Public License can be found at
 *     http://www.gnu.org/
 *
 * Written by Robert Collins  <rbtcollins@hotmail.com>
 *
 */

#ifndef SETUP_CATEGORY_H
#define SETUP_CATEGORY_H

/* categories for packages */

#include "String++.h"
#include <vector>
#include <utility>

class packagemeta;
typedef std::pair <String const, std::vector <packagemeta *> > Category;

#endif /* SETUP_CATEGORY_H */
