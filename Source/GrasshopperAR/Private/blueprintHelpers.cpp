// Fill out your copyright notice in the Description page of Project Settings.


#include "blueprintHelpers.h"
#include "HAL/FileManagerGeneric.h"
#include "Modules/ModuleManager.h"
#include "DDLog.h"
#include "DDManager.h"

TArray<UDDModuleWidget*>
UblueprintHelpers::createPluginWidgets(UUserWidget *parentWidget)
{
    TArray<UDDModuleWidget*> pluginWidgets;
    IDDModuleManagerInterface *ddManager = FDDModuleManager::getSharedInstance();
    
    if (!ddManager)
    {
        DLOG_WARN("failed to obtain DDManager reference");
        return pluginWidgets;
    }
    
    DLOG_DEBUG("{} total DDModules registered", ddManager->getRegisteredModules().size());
    
    for (auto ddModule : ddManager->getRegisteredModules())
    {
        DLOG_DEBUG("module {} version {}",
                   TCHAR_TO_ANSI(*ddModule->getModuleName()),
                   TCHAR_TO_ANSI(*ddModule->getModuleVersion()));
        
        if (ddModule->getWidgetBlueprint())
        {
            DLOG_DEBUG("creating widget for module {}",
                       TCHAR_TO_ANSI(*ddModule->getModuleName()));
            
            UDDModuleWidget *w = CreateWidget<UDDModuleWidget>(parentWidget,
                                                               ddModule->getWidgetBlueprint());
            
            if (w)
            {
                w->setModule(ddModule);
                pluginWidgets.Add(w);
                
                DLOG_DEBUG("successfully created widget for module {}",
                            TCHAR_TO_ANSI(*ddModule->getModuleName()));
            }
            else
                DLOG_WARN("Failed to create widget for module {}",
                           TCHAR_TO_ANSI(*ddModule->getModuleName()));
        }
        else
            DLOG_DEBUG("module {} has no default widget",
                       TCHAR_TO_ANSI(*ddModule->getModuleName()));
    }

    return pluginWidgets;
}
