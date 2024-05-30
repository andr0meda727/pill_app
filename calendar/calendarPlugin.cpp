#include "calendar.h"
#include "calendarPlugin.h"

#include <QtCore/QtPlugin>

calendarPlugin::calendarPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void calendarPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool calendarPlugin::isInitialized() const
{
    return initialized;
}

QWidget *calendarPlugin::createWidget(QWidget *parent)
{
    return new calendar(parent);
}

QString calendarPlugin::name() const
{
    return "calendar";
}

QString calendarPlugin::group() const
{
    return "My Plugins";
}

QIcon calendarPlugin::icon() const
{
    return QIcon();
}

QString calendarPlugin::toolTip() const
{
    return QString();
}

QString calendarPlugin::whatsThis() const
{
    return QString();
}

bool calendarPlugin::isContainer() const
{
    return false;
}

QString calendarPlugin::domXml() const
{
    return "<widget class=\"calendar\" name=\"calendar\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString calendarPlugin::includeFile() const
{
    return "calendar.h";
}
