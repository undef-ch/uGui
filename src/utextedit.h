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
	void keyPressed(int key);
	
private:
	void updateLineBreaks();
	
	bool editing;
	string text;
	int blinkerCount;
	bool showBlinker;
	ofTrueTypeFont* font;
};

#endif // UTEXTEDIT_H
