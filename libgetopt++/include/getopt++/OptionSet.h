/*
 * Copyright (c) 2002 Robert Collins.
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     A copy of the GNU General Public License can be found at
 *     http://www.gnu.org/
 *
 * Written by Robert Collins <robertc@hotmail.com>
 *
 */

#ifndef _OPTIONSET_H_
#define _OPTIONSET_H_

#include <getopt.h>
#include <iosfwd>
#include <vector>

class Option;

class OptionSet
{
public:
  OptionSet();
  virtual ~OptionSet();
  virtual void Register (Option *);
  virtual bool Process (int argc, char **argv, OptionSet *defaultOptionSet=0);
  virtual void ParameterUsage (std::ostream &);
  virtual std::vector<Option *> const &optionsInSet() const;
protected:
  OptionSet (OptionSet const &);
  OptionSet &operator= (OptionSet const &);
  // force initialisation of variables
  void Init ();
private:
  std::vector<Option *>options;
};

#endif // _OPTIONSET_H_
