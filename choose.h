/*
 * Copyright (c) 2000, Red Hat, Inc.
 * Copyright (c) 2003 Robert Collins <rbtcollins@hotmail.com>
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     A copy of the GNU General Public License can be found at
 *     http://www.gnu.org/
 *
 * Written by Robert Collins <rbtcollins@hotmail.com>
 *
 */

#ifndef SETUP_CHOOSE_H
#define SETUP_CHOOSE_H

#include "proppage.h"
#include "package_meta.h"
#include "PickView.h"

#define CATEGORY_EXPANDED  0
#define CATEGORY_COLLAPSED 1

class ChooserPage:public PropertyPage
{
public:
  static HWND lv;
  static PickView *chooser;

  ChooserPage ()
  {
  };
  virtual ~ ChooserPage ()
  {
  };

  virtual bool OnMessageCmd (int id, HWND hwndctl, UINT code);

  bool Create ();
  virtual void OnInit ();
  virtual long OnNext ();
  virtual long OnBack ();
  virtual void OnActivate ();
  virtual long OnUnattended ()
  {
    return OnNext ();
  }; 
  private:
  void createListview (HWND dlg, RECT * r);
  void defaultTrust (HWND h, trusts trust);
  void fillMissingCategory();
  void getParentRect (HWND parent, HWND child, RECT * r);
  void keepClicked();
  static LRESULT CALLBACK list_click (HWND hwnd, BOOL dblclk, int x, int y, UINT hitCode);
  static LRESULT CALLBACK list_hscroll (HWND hwnd, HWND hctl, UINT code, int pos);
  static LRESULT CALLBACK list_vscroll (HWND hwnd, HWND hctl, UINT code, int pos);  
  static LRESULT CALLBACK listview_proc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
  void logOnePackageResult(packagemeta const *aPkg);
  void logResults();
  static void paint (HWND hwnd);
  void registerWindows (HINSTANCE hinst);
  void setExistence();
  void setPrompt(char const *aPrompt);
  void setViewMode (HWND h, PickView::views mode);
  template<class C> bool ifChecked(int const &id, void (C::*fn)()) {
     if (IsDlgButtonChecked (GetHWND (), id)) {
       (this->*fn)();
       return true;
     }
    else
      return false;
  }
  template <trusts aTrust> void changeTrust();
};

#endif /* SETUP_CHOOSE_H */
