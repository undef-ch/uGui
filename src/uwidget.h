#ifndef UWIDGET_H
#define UWIDGET_H

#include "ofMain.h"
#include "ustyle.h" 

class uWidget;

typedef ofPtr<uWidget> uWidgetPtr;
typedef std::vector<uWidgetPtr> uWidgetList;

class uWidget: protected ofRectangle{

public:
	uWidget();
	~uWidget();

	// TO OVERRIDE
	virtual void keyPressed( int key ) {}
	virtual void keyReleased( int key ) {}

	virtual void mouseMoved( int x, int y ) {}
	virtual void mouseDragged( int x, int y, int button ) {}
	virtual void mousePressed( int x, int y, int button ) {}
	virtual void mouseReleased(int x, int y, int button ) {}

	virtual void onFocus(){};
	virtual void onUnfocus(){};
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

	void setFocus();
	void unsetFocus();

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

protected:
	ofRectangle innerBounds;
	
private:
	uWidget* parent;

	uWidgetList children;
	bool registeredToOf;
};

#endif // UWIDGET_H
