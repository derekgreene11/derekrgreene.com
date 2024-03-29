#ifndef _Inventory_Inventory_h_
#define _Inventory_Inventory_h_
#include <CtrlLib/CtrlLib.h>
#include <Report/Report.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;
using namespace Upp;

#define LAYOUTFILE <Inventory/Inventory.lay>
#include <CtrlCore/lay.h>

class Inventory : public WithInventoryLayout<TopWindow> {
	WithModifyLayout<ParentCtrl> modify;
	WithAddLayout<ParentCtrl> add;
	FileSel fs;
	String  filename;

	void Add();
	void Change();
	void Remove();
	void Quit();
	void About();
	
	typedef Inventory CLASSNAME;

public:
	void Number();
	Inventory();
	void InitializeArrayData();
};
#endif