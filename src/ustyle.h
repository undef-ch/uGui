#ifndef USTYLE_H
#define USTYLE_H

#include "ofMain.h"

class uDistances{
public:
	void set(float val){
		top = left = bottom = right = val;
	}
	float top;
	float left;
	float bottom;
	float right;
};

class uStyle {
public:
	static uStyle getDefault(){
		uStyle ret;
		ret.drawBorder = false;
		ret.colorBackground.set(120);
		ret.colorForeground.set(30);
		ret.colorSelection.setHex(0xFF6600);
		ret.padding.set(5);
		return ret;
	}

	static uStyle getFocus(){
		uStyle ret = getDefault();
		ret.colorBackground.set(120);
		ret.drawBorder = true;
		ret.colorBorder.set(0);
		return ret;
	}

	static uStyle getTrigger(){
		uStyle ret = getDefault();
		ret.colorBackground.set(120);
		return ret;
	}

	static ofTrueTypeFont* getFont(){
		ofTrueTypeFont* ret = new ofTrueTypeFont(); //TODO should be shared pointer to know when to delete font...
		ret->loadFont("asenine.ttf", 12);
		return ret;
	}

	uStyle();
	~uStyle();
	
	ofColor colorBackground;
	ofColor colorForeground;
	ofColor colorBorder;
	ofColor colorSelection;
	
	bool drawBorder;
	
	uDistances padding;
	uDistances margin;
};

#endif // USTYLE_H
