#include "ustyle.h"
#include "utextedit.h"

uTextEdit::uTextEdit():uWidget(),editing(false) {
	setSize(300, 100);
	font = uStyle::getFont();
	setText("das hier ist ein viel zu langer text, viel zu lang, so dermassen lang! das hier ist ein viel zu langer text, viel zu lang, so dermassen lang");
	setText(getText()+" Und hier noch was dazu, damit es einen fehler gibt");
}

uTextEdit::~uTextEdit() {
}

void uTextEdit::setText(string t){
	text = t;
	updateLineBreaks();
}

string uTextEdit::getText(){
	return text;
}

void uTextEdit::draw() {
	drawBackground();
	
	ofPushMatrix();
	ofTranslate(innerBounds.x, innerBounds.y);
	
	ofSetColor(styleCurrent.colorForeground);
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
		blinkerPos.y = font->getStringBoundingBox(text, 0, 0).height;
		
		int brPos = text.find_last_of("\n");
		if(brPos != -1)
			blinkerPos.x = font->stringWidth(text.substr(brPos, text.size()-brPos))+2;
		else
			blinkerPos.x = font->stringWidth(text)+2;
		
		if(text.length()>1 && text[text.length()-1] == ' ')
			blinkerPos.x += font->stringWidth("s");
		ofRect(blinkerPos.x, blinkerPos.y-font->getSize()+3, 2, font->getSize()-3);
	}
	ofPopMatrix();
}

void uTextEdit::keyPressed(int key) {
	if(!editing)
		return;
	if(key == OF_KEY_BACKSPACE) {
		text = text.substr(0, text.length() - 1);
	}else if(key == OF_KEY_RETURN){
		text += "\n";
	}else{
		text += char(key);
	}
	updateLineBreaks();
}

void uTextEdit::updateLineBreaks(){
	//update line breaks
	ofRectangle bounds = font->getStringBoundingBox(text, 0, 0);
	if(bounds.width > innerBounds.width){
		//too big, do automatic line breaking
		vector<string> words = ofSplitString(text, " ", true, true);
		vector<string>::iterator it = words.begin();
		string curStr;
		int curPos=0;
		int curW=0;
		int spaceWidth = font->stringWidth("_");
		text.clear();
		while (it != words.end()) {
			curStr = (*it);
			
			if(curStr.size() > 1 && curStr[curStr.size()-1] == '\n'){
				curW = 0;
			}
			
			int strW = font->stringWidth(curStr);
			if (curW+strW > innerBounds.width) {
				text += "\n";
				curW = 0;
			}
			text += curStr + " ";
			curW += strW;
			curW += spaceWidth;
			curPos += curStr.size()+1;
			++it;
		}
	}
}

void uTextEdit::mousePressed(int x, int y, int button) {

}

void uTextEdit::mouseReleased(int x, int y, int button) {
	blinkerCount = 0;
	editing = true;
	showBlinker = true;
}
