#include "ulayout.h"
#include "uwidget.h"

uLayout::uLayout()
{
}

uLayout::~uLayout()
{
}

void uLayout::setWidget(uWidget* w)
{
	widget = w;
	ofAddListener(widget->events.resize, this, &uLayout::onWidgetEvent);
	ofAddListener(widget->events.childAdd, this, &uLayout::onWidgetEvent);
	ofAddListener(widget->events.childRemove, this, &uLayout::onWidgetEvent);
}

void uLayout::onWidgetEvent(uWidgetEvent& e)
{
}
