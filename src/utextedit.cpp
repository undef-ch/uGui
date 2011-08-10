#include "ustyle.h"
#include "utextedit.h"

uTextEdit::uTextEdit():uWidget(),editing(false) {
	width = 200;
	height = 80;

	font = uStyle::getFont();
}

uTextEdit::~uTextEdit() {
}

void uTextEdit::draw() {
	ofSetColor(255);
	ofRect(x, y, width, height);
	ofSetColor(120);
	font->drawString(text, 0, font->getSize());

	if(!editing)
		return;
	blinkerCount++;
	if(blinkerCount>20) {
		showBlinker=!showBlinker;
		blinkerCount=0;
	}
	if(showBlinker) {
		ofPoint blinkerPos;
		blinkerPos.x = font->stringWidth(text)+2;
		if(text.length()>1 && text[text.length()-1] == ' ')
			blinkerPos.x += font->stringWidth("s");
		ofLine(blinkerPos.x, blinkerPos.y+3, blinkerPos.x, blinkerPos.y+font->getSize());
	}
}
void uTextEdit::keyPressed(int key) {
	if(!editing)
		return;
	if(key == OF_KEY_BACKSPACE) {
		text = text.substr(0, text.length() - 1);
		return;
	}
	text += char(key);
}

void uTextEdit::mousePressed(int x, int y, int button) {

}

void uTextEdit::mouseReleased(int x, int y, int button) {
	blinkerCount = 0;
	editing = true;
	showBlinker = true;
}
