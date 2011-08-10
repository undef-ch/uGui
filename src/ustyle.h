#ifndef USTYLE_H
#define USTYLE_H

#include "ofMain.h"

class uStyle {
public:
	static uStyle getDefault(){
		uStyle ret;
		ret.backgroundColor.set(120);
		return ret;
	}

	static uStyle getActive(){
		uStyle ret;
		ret.backgroundColor.set(120);
		return ret;
	}

	static uStyle getFocus(){
		uStyle ret;
		ret.backgroundColor.set(120);
		return ret;
	}

	static ofTrueTypeFont* getFont(){
		ofTrueTypeFont* ret = new ofTrueTypeFont(); //TODO should be shared pointer to know when to delete font...
		ret->loadFont("asenine.ttf", 12);
		return ret;
	}

	uStyle();
	~uStyle();
	ofColor backgroundColor;
	ofColor foregroundColor;
	ofColor borderColor;
	bool hasBorder;
};

#endif // USTYLE_H
