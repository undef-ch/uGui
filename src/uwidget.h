#ifndef UWIDGET_H
#define UWIDGET_H

#include "ofMain.h"

class uWidget;

typedef ofPtr<uWidget> uWidgetPtr;
typedef std::vector<uWidgetPtr> uWidgetList;

class uWidget: public ofRectangle{

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
	virtual void onReparent(){};

	virtual void update(){};
	virtual void draw(){};

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

	void registerOfEvents();
	void unregisterOfEvents();

private:
	uWidget* parent;

	uWidgetList children;
	bool registeredToOf;
};

#endif // UWIDGET_H
