//
// Created by ldoublej on 18-11-30.
//

#ifndef SIMPLE_OGL_TESTCEGUI_H

#include "Application.h"

#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CEGUI.h>

class TestCEGUI : public BaseApp
{
public:
    using BaseApp::BaseApp;
private:
    bool Init()
    {
        glViewport(0, 0, 800, 600);
        using namespace CEGUI;
        CEGUI::OpenGL3Renderer& myRenderer =
                CEGUI::OpenGL3Renderer::bootstrapSystem();

        CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
        rp->setResourceGroupDirectory("schemes", "datafiles/schemes/");
        rp->setResourceGroupDirectory("imagesets", "datafiles/imagesets/");
        rp->setResourceGroupDirectory("fonts", "datafiles/fonts/");
        rp->setResourceGroupDirectory("layouts", "datafiles/layouts/");
        rp->setResourceGroupDirectory("looknfeels", "datafiles/looknfeel/");
        rp->setResourceGroupDirectory("lua_scripts", "datafiles/lua_scripts/");
        rp->setResourceGroupDirectory("schemas", "datafiles/xml_schemas/");


        CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
        CEGUI::Font::setDefaultResourceGroup("fonts");
        CEGUI::Scheme::setDefaultResourceGroup("schemes");
        CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
        CEGUI::WindowManager::setDefaultResourceGroup("layouts");
        CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

        CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
        if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
            parser->setProperty("SchemaDefaultResourceGroup", "schemas");

        CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );
// create (load) a font.
// The first font loaded automatically becomes the default font, but note
// that the scheme might have already loaded a font, so there may already
// be a default set - if we want the "DejaVuSans-10" font to definitely
// be the default, we should set the default explicitly afterwards.
        CEGUI::FontManager::getSingleton().createFromFile( "DejaVuSans-10.font" );

        WindowManager& wmgr = WindowManager::getSingleton();
        Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
        System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
        FrameWindow* fWnd = static_cast<FrameWindow*>( wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));
        myRoot->addChild( fWnd );
        // position a quarter of the way in from the top-left of parent.
        fWnd->setPosition( UVector2( UDim( 0.25f, 0.0f ), UDim( 0.25f, 0.0f ) ) );
        // set size to be half the size of the parent
        fWnd->setSize( USize( UDim( 0.5f, 0.0f ), UDim( 0.5f, 0.0f ) ) );
        fWnd->setText( "Hello World!" );
        return true;
    }
    void RenderLoop() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        CEGUI::System::getSingleton().renderAllGUIContexts();
        glClearColor(0.2, 0.2, 0.3, 1.0);
    }
};
#define SIMPLE_OGL_TESTCEGUI_H

#endif //SIMPLE_OGL_TESTCEGUI_H
