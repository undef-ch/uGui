#ifndef UTEXTEDIT_H
#define UTEXTEDIT_H

#include "uwidget.h" // Base class: uWidget

class uTextEdit : public uWidget {

public:
	uTextEdit(bool singleline=true);
	~uTextEdit();

	void setText(string text);
	string getText();
	
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key, uModifierKeysList mod);
	void setSingleline(bool singleline);

	void onFocus();
	void onUnfocus();
	
private:
	ofPoint getPosOfCharAt(int pos);
	int displayToTextPos(int pos);
	void updateLineBreaks();
	void checkSelectFromTo();
	
	bool editing;
	string text;
	string textDisplay;
	int cursorBlinkCount;
	bool showBlinker;
	ofPoint cursorPos;
	ofTrueTypeFont* font;
	int selectFrom;
	int selectTo;
	int numLines;
	int numCharsLastLine;
	bool isSingleline;
};

#endif // UTEXTEDIT_H
