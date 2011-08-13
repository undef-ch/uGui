#ifndef UWIDGET_H
#define UWIDGET_H

#include "ofMain.h"
#include "ustyle.h" 
#include "uutils.h"

class uWidget: protected ofRectangle, public uFocus{

public:
	uWidget();
	~uWidget();

	// TO OVERRIDE
	virtual void keyPressed( int key ) {}
	virtual void keyPressed( int key, uModifierKeysList modifierKeys) {keyPressed(key);}
	virtual void keyReleased( int key ) {}

	virtual void mouseMoved( int x, int y ) {}
	virtual void mouseDragged( int x, int y, int button ) {}
	virtual void mousePressed( int x, int y, int button ) {}
	virtual void mouseReleased(int x, int y, int button ) {}

	virtual void onSetParent(){};

	virtual void update(){};
	virtual void draw(){};
	
	virtual void onSizeChange(ofPoint newSize, ofPoint oldSize){};
	virtual void onPositionChange(ofPoint newPosition, ofPoint oldPosition){};
	
	// CORE FUNCTIONALITY
	void update(ofEventArgs& e);
	void draw(ofEventArgs& e);

	void keyPressed(ofKeyEventArgs& e);
	void keyReleased(ofKeyEventArgs& e);

	void mouseMoved(ofMouseEventArgs& e );
	void mouseDragged(ofMouseEventArgs& e );
	void mousePressed(ofMouseEventArgs& e );
	void mouseReleased(ofMouseEventArgs& e );

	void addChild(uWidget* uw);
	void addChild(uWidgetPtr uw);

	void setParent(uWidget* parent);
	uWidget* getParent();

	void registerOfEvents();
	void unregisterOfEvents();
	
	ofPoint getSize();
	void setSize(int w, int h);
	
	void setPosition(float x, float y);
	ofPoint getPosition();
	
	
	void drawBackground();
	
	uStyle styleDefault;
	uStyle styleFocus;
	uStyle styleTrigger;
	uStyle styleCurrent;
	
	void setFocused();
	void setUnfocused();
	
	uWidget* getUltimateParent();
	
	int mouseX;
	int mouseY;
	
protected:
	ofRectangle innerBounds;
	static uFocusHandler focusHandler ;
	
private:
	void updateMouseEvent(ofMouseEventArgs& e);
	
	static void initStatic();
	
	uWidget* parent;
	
	uModifierKeysList modifierKeysListenTo;
	uModifierKeysList modifierKeys;
		
	uWidgetList children;
	bool registeredToOf;
	
	static bool isInitStatic;
	
};

#endif // UWIDGET_H
