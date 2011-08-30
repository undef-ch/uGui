#include "uwidget.h"

bool uWidget::isInitStatic = false;
uFocusHandler uWidget::focusHandler;


void uWidget::initStatic(){
	if(!isInitStatic){
		isInitStatic = true;
	}
}
uWidget::uWidget():
registeredToOf(false), styleDefault(uStyle::getDefault()), styleFocus(uStyle::getFocus()), styleTrigger(uStyle::getTrigger()), isMouseDown(false), isHidden(false), isDisabled(false)
{
	styleCurrent=styleDefault;
	setSize(100, 100);
	modifierKeysListenTo.add(OF_KEY_MODIFIER);
	modifierKeysListenTo.add(OF_KEY_ALT);
	modifierKeysListenTo.add(OF_KEY_SHIFT);
}

uWidget::~uWidget() {
}

void uWidget::addChild(uWidget* uw) {
	addChild(uWidgetPtr(uw));
}

void uWidget::addChild(uWidgetPtr uw) {
	children.push_back(uw);
	uw->setParent(this);
}

void uWidget::update(ofEventArgs& e) {
	if(isDisabled)
		return;
	uWidgetList::iterator it = children.begin();
	update();
	while(it!=children.end()) {
		(*it)->update(e);
		++it;
	}
}

void uWidget::draw(ofEventArgs& e) {
	if(isHidden)
		return;
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
	if(isDisabled)
		return;
	if(modifierKeysListenTo.contains(e.key))
		modifierKeys.add(e.key);
	
	
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		(*it)->keyPressed(e);
		++it;
	}
	keyPressed(e.key, modifierKeys);
}

void uWidget::keyReleased(ofKeyEventArgs& e) {
	if(isDisabled)
		return;

	if(modifierKeysListenTo.contains(e.key))
		modifierKeys.remove(e.key);
	
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		(*it)->keyReleased(e);
		++it;
	}
	keyReleased(e.key);
}

void uWidget::updateMouseEvent(ofMouseEventArgs& e){
	e.x -= x;
	e.y -= y;
}

void uWidget::mouseDragged(ofMouseEventArgs& e) {
	if(isDisabled)
		return;
	if(registeredToOf){
		if(!inside(e.x, e.y))
			return;
		e.x-=x;
		e.y-=y;
	}
	ofPoint p(e.x, e.y);
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		if((*it)->inside(p)){
			(*it)->mouseDragged(e);
		};
		++it;
	}
	mouseDragged(e.x, e.y, e.button);
}

void uWidget::mouseMoved(ofMouseEventArgs& e) {
	if(isDisabled)
		return;
	if(registeredToOf){
		if(!inside(e.x, e.y))
			return;
		e.x-=x;
		e.y-=y;
	}
	ofPoint p(e.x, e.y);
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		if((*it)->inside(p)){
			(*it)->mouseMoved(e);
		};
		++it;
	}
	mouseMoved(e.x, e.y);
}

void uWidget::mousePressed(ofMouseEventArgs& e) {
	if(isDisabled)
		return;
	if(registeredToOf){
		if(!inside(e.x, e.y))
			return;
		e.x-=x;
		e.y-=y;
	}
	isMouseDown = true;
	ofPoint p(e.x, e.y);
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		if((*it)->inside(p)){
			(*it)->mousePressed(e);
		};
		++it;
	}
	mousePressed(e.x, e.y, e.button);
}

void uWidget::mouseReleased(ofMouseEventArgs& e) {
	if(isDisabled)
		return;
	if(!isMouseDown)
		return;
	if(registeredToOf){
		e.x-=x;
		e.y-=y;
	}
	isMouseDown = false;
	ofPoint p(e.x, e.y);
	uWidgetList::iterator it = children.begin();
	while(it!=children.end()) {
		if((*it)->inside(p)){
			(*it)->mouseReleased(e);
		};
		++it;
	}
	mouseReleased(e.x, e.y, e.button);
}

uWidget* uWidget::getParent() {
	return parent;
}

void uWidget::setParent(uWidget* p) {
	parent = p;
	onSetParent();
}


void uWidget::registerOfEvents() {
	registeredToOf = true;
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
	registeredToOf = false;
	ofRemoveListener(ofEvents.mouseMoved, this, &uWidget::mouseMoved);
	ofRemoveListener(ofEvents.mousePressed, this, &uWidget::mousePressed);
	ofRemoveListener(ofEvents.mouseReleased, this, &uWidget::mouseReleased);
	ofRemoveListener(ofEvents.mouseDragged, this, &uWidget::mouseDragged);
	ofRemoveListener(ofEvents.keyPressed, this, &uWidget::keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &uWidget::keyReleased);
	
	ofRemoveListener(ofEvents.update, this, &uWidget::update);
	ofRemoveListener(ofEvents.draw, this, &uWidget::draw);
}

void uWidget::focus() {
	styleCurrent = styleFocus;
	focusHandler.setFocused(this);
	uFocus::focus();
}

void uWidget::unfocus(){
	styleCurrent = styleDefault;
	uFocus::unfocus();
}

void uWidget::setSize(int w, int h){
	ofPoint oldSize(width, height);
	width = w;
	height = h;
	onSizeChange(getSize(), oldSize);
}

ofPoint uWidget::getSize(){
	innerBounds.set(styleCurrent.padding.left, styleCurrent.padding.top,
					width - styleCurrent.padding.left - styleCurrent.padding.right, height - styleCurrent.padding.top - styleCurrent.padding.bottom);
	return ofPoint(width, height);
}

void uWidget::drawBackground(){
	ofSetColor(styleCurrent.colorBackground);
	ofSetColor(255);
	ofFill();
	ofRect(0, 0, getSize().x, getSize().y);
	if(styleCurrent.drawBorder){
		ofNoFill();
		ofSetColor(styleCurrent.colorBorder);
		ofRect(0, 0, getSize().x, getSize().y);
	}
}

void uWidget::setPosition(float _x, float _y){
	ofPoint oldPosition(x, y);
	x = _x;
	y = _y;
	onPositionChange(getPosition(), oldPosition);
}

ofPoint uWidget::getPosition(){
	return ofPoint(x, y);
}

uWidget* uWidget::getUltimateParent()
{
	if(parent != NULL)
		return parent->parent;
	else 
		return this;
}

void uWidget::hide()
{
	isHidden = true;
}

void uWidget::show()
{
	isHidden = false;
}

void uWidget::disable()
{
	isDisabled = true;
}

void uWidget::enable()
{
	isDisabled = false;
}

