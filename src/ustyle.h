#ifndef USTYLE_H
#define USTYLE_H

#include "ofMain.h"

class uStyle {
public:
	static uStyle getDefault(){
		uStyle ret;
		ret.backgroundColor.set(120);
	}

	uStyle();
	~uStyle();
	ofColor backgroundColor;
	ofColor foregroundColor;
	ofColor borderColor;
	bool hasBorder;
};

#endif // USTYLE_H
