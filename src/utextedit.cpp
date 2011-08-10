#include "ustyle.h"
#include "utextedit.h"

uTextEdit::uTextEdit() {
	width = 200;
	height = 80;

	font = uStyle::getFont();
}

uTextEdit::~uTextEdit() {
}

void uTextEdit::draw() {
	ofRect(x, y, width, height);
	if(!editing)
		return;
	blinkerCount++;
	if(blinkerCount>20){
		showBlinker=!showBlinker;
		blinkerCount=0;
	}

	ofPoint blinkerPos;
}
void uTextEdit::keyPressed(int key) {
	text += char(key);
}

void uTextEdit::mousePressed(int x, int y, int button) {
	blinkerCount = 0;
	editing = !editing;
	showBlinker = true;
}

void uTextEdit::mouseReleased(int x, int y, int button) {

}
