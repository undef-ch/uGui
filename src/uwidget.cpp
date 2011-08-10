#include "uwidget.h"

uWidget::uWidget() {
}

uWidget::~uWidget() {
}

void uWidget::addChild(uWidget* uw) {
	addChild(uWidgetPtr(uw));
}

void uWidget::addChild(uWidgetPtr uw) {
	uw->setParent(this);
	children.push_back(uw);
}

void uWidget::update(ofEventArgs& e) {
	uWidgetList::iterator it = children.begin();
	update();
	while(it!=children.end()) {
		(*it)->update(e);
		++it;
	}
}

void uWidget::draw(ofEventArgs& e) {
	ofPushMatrix();
	ofTranslate(x, y);
	uWidgetList::iterator it = children.begin();
	draw();
	while(it!=children.end()) {
		(*it)->draw(e);
		++it;
	}
	ofPopMatrix();
}

void uWidget::keyPressed(ofKeyEventArgs& e) {
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		(*it)->keyPressed(e);
		++it;
	}
	keyPressed(e.key);
}

void uWidget::keyReleased(ofKeyEventArgs& e) {
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		(*it)->keyReleased(e);
		++it;
	}
	keyReleased(e.key);
}

void uWidget::mouseDragged(ofMouseEventArgs& e) {
	mouseDragged(e.x, e.y, e.button);
}

void uWidget::mouseMoved(ofMouseEventArgs& e) {
	mouseMoved(e.x, e.y);
}

void uWidget::mousePressed(ofMouseEventArgs& e) {
	mousePressed(e.x, e.y, e.button);
}

void uWidget::mouseReleased(ofMouseEventArgs& e) {
	mouseReleased(e.x, e.y, e.button);
}

uWidget* uWidget::getParent() {
	return parent;
}

void uWidget::setParent(uWidget* p) {
	parent = p;
}


void uWidget::registerOfEvents() {
	ofAddListener(ofEvents.mouseMoved, this, &uWidget::mouseMoved);
	ofAddListener(ofEvents.mousePressed, this, &uWidget::mousePressed);
	ofAddListener(ofEvents.mouseReleased, this, &uWidget::mouseReleased);
	ofAddListener(ofEvents.mouseDragged, this, &uWidget::mouseDragged);
	ofAddListener(ofEvents.keyPressed, this, &uWidget::keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &uWidget::keyReleased);

	ofAddListener(ofEvents.update, this, &uWidget::update);
	ofAddListener(ofEvents.draw, this, &uWidget::draw);
}

void uWidget::unregisterOfEvents() {
	ofRemoveListener(ofEvents.mouseMoved, this, &uWidget::mouseMoved);
	ofRemoveListener(ofEvents.mousePressed, this, &uWidget::mousePressed);
	ofRemoveListener(ofEvents.mouseReleased, this, &uWidget::mouseReleased);
	ofRemoveListener(ofEvents.mouseDragged, this, &uWidget::mouseDragged);
	ofRemoveListener(ofEvents.keyPressed, this, &uWidget::keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &uWidget::keyReleased);
}

void uWidget::setFocus() {
}
