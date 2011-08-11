/*
 *  uutils.h
 *  emptyExample
 *
 *  Created by Philip Whitfield on 8/11/11.
 *  Copyright 2011 undef.ch. You have the rights to remain calm, seated, silent or just yourself.
 *
 */

#ifndef U_UTILS
#define U_UTILS

class uWidget;

#include "ofMain.h"

typedef ofPtr<uWidget> uWidgetPtr;
typedef std::vector<uWidgetPtr> uWidgetList;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class type>
class uList{
public:
	void add(type key){
		//cout << "ADD KEY" << endl;
		if(!contains(key))
			keys.push_back(key);
	}
	
	void remove(type key){
		if(!contains(key))
			return;
		keys.erase(std::find(keys.begin(), keys.end(), key));
	}
	
	bool contains(type key){
		//cout << "check contains with :" << key << " alt is " << int(OF_KEY_ALT) << " IS SAME " << 
		//(std::find(keys.begin(), keys.end(), key) != keys.end()) << endl;
		return std::find(keys.begin(), keys.end(), key) != keys.end();
	}
	
private:
	std::vector<type> keys;
};

typedef uList<int> uModifierKeysList;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class uFocus{
public:
	virtual void onFocus(){};
	virtual void onUnfocus(){};
	
	virtual void setFocused(){onFocus();};
	virtual void setUnfocused(){onUnfocus();};
};

class uFocusHandler{
public:
	uFocusHandler():focused(NULL){}
	void setFocused(uFocus* f);
	void setUnfocused();
	bool hasFocused();
private:
	uFocus* focused;
};

#endif

