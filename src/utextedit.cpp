#include "ustyle.h"
#include "utextedit.h"

uTextEdit::uTextEdit(bool singleline):uWidget(),
	editing(false), selectFrom(0), selectTo(0), 
	numLines(0), numCharsLastLine(0), isSingleline(false) 
{
	font = uStyle::getFont();
	setSingleline(singleline);
	if(isSingleline)
		setSize(300, font->getLineHeight()+styleCurrent.padding.top+styleCurrent.padding.bottom);
	else
		setSize(300, 100);
	
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
	
	//draw selection
	if(editing){
		ofSetColor(styleCurrent.colorSelection);
		//ofRect(20, 20, 40, 40);
	}
	
	//draw text
	ofSetColor(styleCurrent.colorForeground);
	font->drawString(textDisplay, 0, font->getSize());
	
	if(editing){
		blinkerCount++;
		if(blinkerCount>20) {
			showBlinker=!showBlinker;
			blinkerCount=0;
		}
		if(showBlinker) {
			/*
			//get position of cursor
			ofPoint blinkerPos(0,0);
			blinkerPos.y = numLines * font->getLineHeight();
			if (numCharsLastLine<=textDisplay.size()){
				string tText=textDisplay;
				blinkerPos.x = font->stringWidth(tText.substr(tText.size() - numCharsLastLine, numCharsLastLine));
			}
			//FIX FOR MISSING POSITION UPDATE WHEN LAST CHAR IS SPACE
			int pos = 0;
			while(textDisplay.size()>pos && textDisplay[textDisplay.size()-pos-1] == ' '){
				pos++;
			}
			blinkerPos.x += pos*font->stringWidth("-");
			
			ofSetColor(styleCurrent.colorForeground);
			ofRect(blinkerPos.x, blinkerPos.y, 3, font->getSize());*/
			
		}
	}
	ofPopMatrix();
}

void uTextEdit::keyPressed(int key, uModifierKeysList mod) {
	if(!editing)
		return;
	switch(key){
			
		case OF_KEY_BACKSPACE:
			if(mod.contains(OF_KEY_ALT))
				cout << "ALT PRESSED" << endl; //Doesn't work, no signal on alt key from of
			text = text.substr(0, text.length() - 1);
			break;
			
		case OF_KEY_RETURN:
			if(!isSingleline)
				text += "\n";
			break;
		default:
			text += char(key);
	}
	
	updateLineBreaks();
}

void uTextEdit::updateLineBreaks(){
	//update line breaks
	textDisplay.clear();
	ofRectangle bounds = font->getStringBoundingBox(text, 0, 0);
	if(bounds.width > innerBounds.width && !isSingleline){
		//too big, do automatic line breaking
		vector<string> words = ofSplitString(text, " ", true, true);
		
		int curPos=0;
		int curW=0;
		int spaceWidth = font->stringWidth("_");
		
		string curStr;
		vector<string>::iterator it = words.begin();
		while (it != words.end()) {
			curStr = (*it);
			
			std::vector<string> lineSplit;
			if(curStr.size()>0)
				lineSplit = ofSplitString(curStr, "\n", true, true);
			else
				lineSplit.push_back(curStr);

			std::vector<string>::iterator sIt = lineSplit.begin();

			while(sIt != lineSplit.end()){
				curStr = *sIt;
				++it;
				++sIt;
				
				int strW = font->stringWidth(curStr);
				if (curW+strW > innerBounds.width || sIt != lineSplit.end()) {
					textDisplay += "\n";
					curW = 0;
				}
				textDisplay += curStr;
				if(it != words.end() && sIt == lineSplit.end()) textDisplay += " ";
				curW += strW;
				curW += spaceWidth;
				curPos += curStr.size()+1;
			}
		}
	}else{
		textDisplay = text;
	}
	
	//Number of lines
	std::string str = textDisplay;
	if (str.find("\n") != string::npos) {
		//find number of lines
		numLines = 0;
		int lastOcurence = 0;
		while(str.find("\n") != string::npos) {
			size_t pos = str.find("\n");
			lastOcurence = pos;
			str.replace(pos, 1, "", 0, 0);
			numLines++;
		}
		//numCharsLastLine = text.size() - lastOcurence + numLines;
	}else{
		//numCharsLastLine = text.size();
	}
	
}

void uTextEdit::setSingleline(bool s){
	isSingleline = s;
}

void uTextEdit::mousePressed(int x, int y, int button) {
	selectFrom = selectTo = -1; 
	if(!isFocused){
		setFocused();
	}else{
		int lineNumber = floorf((y-innerBounds.y)/font->getLineHeight());
		if(lineNumber>numLines){
			selectFrom = -1;
			selectTo = -1;
		}else{
			std::vector<string> lines = ofSplitString(textDisplay, "\n");
			string str = lines[lineNumber];
			int curX = 0;
			for(int i=0;i<str.size();i++){
				char c = str[i];
				if(c == ' '){
					c = '-';
				}
				stringstream ss;
				string s;
				ss << c;
				ss >> s;
				int w = font->stringWidth(s);
				if(w+curX>x-innerBounds.x){
					cout << s << endl;
					break;
				}
				curX+=w+font->getLetterSpacing();
			}
		}
	}
}

void uTextEdit::mouseReleased(int x, int y, int button) {
	
}

void uTextEdit::onFocus()
{
	blinkerCount = 0;
	editing = true;
	showBlinker = true;
}

void uTextEdit::onUnfocus()
{
	editing = false;
}

