#include "Inventory.h"

Inventory::Inventory(){
	CtrlLayout(*this, "Inventory Tracker 1.0");
	CtrlLayout(add);
	CtrlLayout(modify);
	tab.Add(add, "Add");
	tab.Add(modify, "Modify");
	array.AddColumn("Bin");
	array.AddColumn("Description");
	array.AddColumn("Quantity");
	add.remove ^= THISFN(Remove);
	modify.change ^= THISFN(Change);
	add.add ^= THISFN(Add);
	ActiveFocus(modify.quantity);

#ifdef PLATFORM_COCOA
	SetMainMenu([=](Bar& bar) {
		bar.Sub("File", [=](Bar& bar) {
			bar.Add("About", THISFN(About));
			bar.Add("Quit", THISFN(Quit));
			
		});
	});
#else
	menu.Set([=](Bar& bar) {
		bar.Sub("File", [=](Bar& bar) {
			bar.Add("About", THISFN(About));
			bar.Add("Quit", THISFN(Quit));
			
		});
	});
#endif
}

void Inventory::Add() {
	 if(~add.part == "") {
        PromptOK("Error: Enter a part name!");
        return;
    }
    int bnum = array.GetCount() + 1;
    int quantity = ~add.quantity;

    if (quantity  > 30) {
        PromptOK("Error: Bin cannot hold more than 30 parts!");
        modify.quantity.Clear();
        return;
    } else if (quantity < 0) {
        PromptOK("Error: Bin cannot hold a negative number of parts!");
        modify.quantity.Clear();
        return;
    }

    array.Add(bnum, ~add.part, quantity);
    array.GoEnd();
    add.part.Clear();
    add.quantity.Clear();
}

void Inventory::Remove() {
    if(!array.IsCursor()){
        PromptOK("Error: No bin is selected!");
        return;
    }

    int i = array.GetCursor();
    array.Remove(i);
    add.part.Clear();
    add.quantity.Clear();
    Number();
}

void Inventory::Change() {
	int quantity = ~modify.quantity;
	
	if(!array.IsCursor()){
        PromptOK("Error: No item is selected.");
        return;
    } else if (quantity > 30) {
     	PromptOK("Error: Bin cannot hold more than 30 parts!");
    	modify.quantity.Clear();
		return;
    } else if (quantity < 0) {
        PromptOK("Error: Bin cannot hold a negative number of parts!");
        modify.quantity.Clear();
        return;
    }
	array.Set(2, quantity);
	modify.quantity.Erase();
}

void Inventory::Number() {
	int total = array.GetCount();
	for (int i = 1; i < total; i++) {
		array.Set(i, 0, i+1);
	}
}

void Inventory::Quit(){
	Break();
}  

void Inventory::About() {
	PromptOK("Developed by Derek Greene - Copyright \u00A9 2024");
}

void Inventory::InitializeArrayData() {
	add.part.Erase();
	add.quantity.Erase();
	modify.quantity.Erase();
		
    vector<string> partd {"Valve", "Bearing", "Bushing", "Coupling", "Flange", "Gear", "Gear Housing", "Vacuum Gripper", "Cable", "Rod" };
	vector<int> partc {10, 5, 15, 21, 7, 5, 5, 25, 18, 12};

    for (int i = 1; i < partd.size() + 1; i++) {
    	array.Add(i, partd[i-1], partc[i-1]);
    }
}

GUI_APP_MAIN {
	Inventory inventory;
	inventory.InitializeArrayData();
	inventory.Run();
}