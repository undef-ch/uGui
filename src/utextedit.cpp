#include "ustyle.h"
#include "utextedit.h"

uTextEdit::uTextEdit(bool singleline):uWidget(),
	editing(false), selectFrom(0), selectTo(0),
	numLines(0), numCharsLastLine(0), isSingleline(false) {
	font = uStyle::getFont();
	setSingleline(singleline);
	if(isSingleline)
		setSize(300, font->getLineHeight()+styleCurrent.padding.top+styleCurrent.padding.bottom);
	else
		setSize(300, 100);
}

uTextEdit::~uTextEdit() {
}

void uTextEdit::setText(string t) {
	text = t;
	updateLineBreaks();
}

string uTextEdit::getText() {
	return text;
}

void uTextEdit::draw() {
	drawBackground();

	ofPushMatrix();
	ofTranslate(innerBounds.x, innerBounds.y);

	//draw selection
	if(editing) {
		ofSetColor(styleCurrent.colorSelection);
	}

	//draw text
	ofSetColor(styleCurrent.colorForeground);
	font->drawString(textDisplay, 0, font->getSize());

	if(editing) {
		cursorBlinkCount++;
		if(cursorBlinkCount>20) {
			showBlinker=!showBlinker;
			cursorBlinkCount=0;
		}
		if(showBlinker) {
			ofFill();
			ofSetColor(styleCurrent.colorForeground);
			ofPoint tP = getPosOfCharAt(selectFrom);
			ofRect(tP.x, tP.y-font->getLineHeight(), 2, font->getSize());
		}
	}
	ofPopMatrix();
}

void uTextEdit::keyPressed(int key, uModifierKeysList mod) {
	if(!editing)
		return;
	switch(key) {

	case OF_KEY_BACKSPACE:
		if(selectFrom <= 0)
			break;

		if(mod.contains(OF_KEY_ALT))
			cout << "ALT PRESSED" << endl; //Doesn't work, no signal on alt key from of
		text.erase(displayToTextPos(selectFrom), 1);
		selectFrom--;
		break;

	case OF_KEY_DEL:
		if(selectFrom >= textDisplay.size())
			break;

		if(mod.contains(OF_KEY_ALT))
			cout << "ALT PRESSED" << endl; //Doesn't work, no signal on alt key from of
		text.erase(displayToTextPos(selectFrom+1), 1);
		break;

	case OF_KEY_RETURN:
		ofLog(OF_LOG_WARNING, "sorry, manual line breaks are not yet supported");
		break;
		if(!isSingleline)
			text += "\n";
		break;
	case OF_KEY_LEFT:
		selectFrom--;
		break;
	case OF_KEY_RIGHT:
		selectFrom++;
		break;
	case OF_KEY_UP:
		break;
	case OF_KEY_DOWN:
		break;
	default:
		if(text.size()==0) {
			text+= char(key);
			selectFrom = 1;
		}else{
			text.insert(displayToTextPos(selectFrom)+1, 1, char(key));
			selectFrom++;
		}

		break;
	}

	updateLineBreaks();
}

void uTextEdit::updateLineBreaks() {
	//update line breaks
	textDisplay.clear();
	ofRectangle bounds = font->getStringBoundingBox(text, 0, 0);
	int breaksBefore = ofSplitString(textDisplay, "\n").size()-1;
	int breaksNow =0;
	if(bounds.width > innerBounds.width && !isSingleline) {
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

			while(sIt != lineSplit.end()) {
				curStr = *sIt;
				++sIt;

				int strW = font->stringWidth(curStr);
				if (curW+strW > innerBounds.width || sIt != lineSplit.end()) {
					textDisplay += "\n";
					breaksNow++;
					curW = 0;
				}
				textDisplay += curStr;
				if(it != words.end() && sIt == lineSplit.end()) textDisplay += " ";
				curW += strW;
				curW += spaceWidth;
				curPos += curStr.size()+1;
			}
			++it;
		}
	} else {
		textDisplay = text;
	}
	selectFrom += breaksNow-breaksBefore;
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
	} else {
		//numCharsLastLine = text.size();
	}
	checkSelectFromTo();
}

void uTextEdit::setSingleline(bool s) {
	isSingleline = s;
}

void uTextEdit::mousePressed(int x, int y, int button) {
	selectFrom = selectTo = -1;

	if(!isFocused) {
		focus();
	} else {
		int lineNumber = floorf((y-innerBounds.y)/font->getLineHeight());
		if(lineNumber>numLines) {
			selectFrom = textDisplay.size()-1;
			selectTo = -1;
		} else {
			std::vector<string> lines = ofSplitString(textDisplay, "\n");
			int curPos = 0;
			for(int i=0; i<lineNumber; i++) {
				curPos+=lines[i].size()+1;
			}
			string str = lines[lineNumber];
			int curX = 0;
			for(int i=0; i<str.size(); i++) {
				curPos++;
				char c = str[i];
				if(c == ' ') {
					c = '-';
				}
				stringstream ss;
				string s;
				ss << c;
				ss >> s;
				int w = font->stringWidth(s);
				if(w+curX>x-innerBounds.x) {
					selectFrom = curPos;
					break;
				}
				curX+=w+font->getLetterSpacing();
				if(i==str.size()-1)
					selectFrom = textDisplay.size()-1;
			}
		}
	}
	checkSelectFromTo();
}

void uTextEdit::mouseReleased(int x, int y, int button) {

}

void uTextEdit::onFocus() {
	cursorBlinkCount = 0;
	editing = true;
	showBlinker = true;
}

void uTextEdit::onUnfocus() {
	editing = false;
}

ofPoint uTextEdit::getPosOfCharAt(int pos) {
	if(pos<0)
		pos=0;
	if(pos>=textDisplay.size())
		pos = textDisplay.size();
	ofPoint ret;
	string strToPos = textDisplay.substr(0, pos);
	std::vector<string> lines = ofSplitString(strToPos, "\n");
	ret.y = lines.size() * font->getLineHeight();
	string lastLine = lines[lines.size()-1];

	for(int i=lastLine.size()-1; i>=0; i--) {
		if(lastLine[i]==' ')
			lastLine[i] = '-';
		else
			break;
	}

	for(int i=0; i<lastLine.size(); i++) {
		if(lastLine[i]==' ')
			lastLine[i] = '-';
		else
			break;
	}

	ret.x = font->stringWidth(lastLine);
	return ret;
}

int uTextEdit::displayToTextPos(int pos) {
	string strToPos = textDisplay.substr(0, pos);
	int p = pos - ofSplitString(strToPos, "\n").size();
	if(p>=text.size())
		p = text.size()-1;
	if(p<0)
		p=0;
	return p;
}

void uTextEdit::checkSelectFromTo() {
	if(selectFrom>textDisplay.size())
		selectFrom = textDisplay.size();
	if(selectFrom<0)
		selectFrom=0;
}
