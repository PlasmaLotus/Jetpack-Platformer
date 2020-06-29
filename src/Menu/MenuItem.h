/*
Created by PlasmaLotus
Updated Sept 10, 2019
*/

#ifndef _Menu_Item_
#define _Menu_Item_

#include <string>
/*
typedef std::function<void() > command;

enum MenuItemType{
	NONE, TOGGLE, PLAYER, RANGE, LIST};
*/
class Menu;
//namespace Menu{}

//Abstract Class Item for a Menu
class MenuItem {
public:

	//Ctor as visible and selectable
	MenuItem(std::string label);
	MenuItem(std::string label, bool visible, bool selectable,  bool shiftable, bool disabled);
	~MenuItem();

#pragma region Accessers

	//Item can be hovered by mouse or menu selection
	virtual bool hoverable() const;

	//Item can be activated by click or menu selection
	virtual bool selectable() const;

	//Item is visible in the menu
	virtual bool visible() const;

	//Item is unable to be interacted with
	virtual bool disabled() const;

	//Item can be shifted left or right
	virtual bool shiftable() const;

	//When the Item is added in a Menu
	virtual void Added(Menu* menu);


	//When the Item is removed from a Menu
	//virtual void Removed();

	//Get the parent Menu, this Item's container
	Menu* getParent() const;
	Menu* getContainer() const;

	//Set the parent Menu, this Item's container
	void setParent(Menu* menu);
	void setContainer(Menu* menu);
	//void setParent(Menu* container);


	//Main label access

	//Set the label of this MenuItem
	void setOptionLabel(const std::string label) {
		mLabel = label;
	}
	void setOptionLabel(char* label) {
		setOptionLabel(std::string(label));
	}
	std::string getLabel() {
		return mLabel;
	}

#pragma endregion Getters and Setters

#pragma region Actions
	///Actions

	//Action to perform when the Item is pressed
	virtual void ConfirmAction();

	//Action to perform when the Item is pressed alternatively
	virtual void AltAction();

	//Action to perform when the Item is indexed left (when left is pressed on the item)
	virtual void LeftShift();

	//Action to perform when the Item is indexed right (when right is pressed on the item)
	virtual void RightShift();

#pragma endregion Behaviour on Menu input

#pragma region Callbacks
	///Callbacks

	//Callback when the Item is updated
	virtual void OnUpdate();

	//Callback when the Item is hovered or highlighted
	virtual void OnEnter();

	//Callback when the Item is Un-highlighted or Un-hovered
	virtual void OnLeave();

	//Callback when the Item is Pressed or Selected
	virtual void OnConfirm();

	//Callback when the Item is Pressed or Selected
	virtual void OnAltConfirm();

	//Callback when the Item is shifted
	virtual void OnShift();

	//Callback when the Item is shifted to the Left
	virtual void OnShiftLeft();

	//Callback when the Item is shifted to the Right
	virtual void OnShiftRight();

#pragma endregion Callbacks
	
#pragma region Loop
	///Handling - Loop

	//Update the Item based on a certain elapsed time frame
	virtual void Update(const float dt);

	//Display the Item on a rendering target
	virtual void Render(void* renderTarget);
#pragma endregion Loop

	/*
	MenuItem(std::string name, command c);
	MenuItem(std::string name, int value, int max, MenuItemType type);
	//MenuItem(std::string name, command * commandStack, int max);
	MenuItem(std::string name, command c, int value, int max, MenuItemType type);
	virtual ~MenuItem();
	command getFn() const;
	void increase();
	void decrease();
	//void select();
	//void handleInput();
	void setMenuType(MenuItemType t);
	MenuItemType getMenuType();
	std::string getName();
	const std::string getOptionString() const;
	//void addListItem()
	//MenuItemType menuItemType;
	std::string getRangeString();
	void setFn(command c);
	int getRangeValue();
	*/

protected:
	Menu* mParent;//Container
	std::string mLabel;

	bool mSelectable;
	bool mVisible;
	bool mDisabled;
	bool mShiftable;
};



//class MenuObserver


#endif
