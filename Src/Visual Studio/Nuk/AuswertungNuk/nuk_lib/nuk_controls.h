#pragma once
#ifndef NUK_CONTROLS_H
#define NUK_CONTROLS_H



//OOP-Approach to wrap nk-calls into a classic Dialog-Framework-Hierarchy
//alternatives might be ECS, where each drawable Item has some predefined
//set of Components that contain Meta and Drawing-Data.
//can't wrap my head around building a listview this way.. so oop for a start.

#include <IComponent.h>
#include <NkEdit.h>
#include <NkLabel.h>
#include <NkGroupBox.h>
#include <NkButton.h>
#include <NkListBox.h>
#include <NkCheckBox.h>
#include <NkCombobox.h>
#include <NkMemo.h>
#include <NkGrid.h>
#include <NkStatusBar.h>
#include <NKForm.h>
#include <NKRowLayouts.h>
#include <NKSpaceLayout.h>
#endif