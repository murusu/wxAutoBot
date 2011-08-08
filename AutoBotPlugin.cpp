#include "AutoBotPlugin.h"

PluginManager::PluginManager()
{
    wxDynamicLibrary* temp_loader = new wxDynamicLibrary();
    temp_loader->Load(wxT("test.plg"));
}

PluginManager::~PluginManager()
{

}
