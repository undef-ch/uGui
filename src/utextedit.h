#ifndef UTEXTEDIT_H
#define UTEXTEDIT_H

#include "uwidget.h" // Base class: uWidget

class uTextEdit : public uWidget {

public:
	uTextEdit();
	~uTextEdit();

	void setText(string text);
	string getText();
	
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key, uModifierKeysList mod);
	
private:
	void updateLineBreaks();
	
	bool editing;
	string text;
	string textDisplay;
	int blinkerCount;
	bool showBlinker;
	ofTrueTypeFont* font;
	int selectFrom;
	int selectTo;
	int numLines;
	int numCharsLastLine;
};

#endif // UTEXTEDIT_H
