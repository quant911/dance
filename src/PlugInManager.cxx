
#include "PlugInManager.h"
#include "danceTcl.h"


#include <stdlib.h>
#ifdef WIN32
#include "windlfcn.h"
#else
#include <dlfcn.h>
#endif



/**
 * Adds an entry in the PlugInManager registry for the given PlugIn.
 *
 * Only an entry in the registry is created without creating an actual instance.
 * This is useful in situations where a plugin may need another plugin for successful
 * linking, but not require an actual instance.
 * @param char *type
 * @return PlugIn 
 */
PlugIn *PlugInManager::AddProxy(char *type)
{
    PlugIn *proxy =	(PlugIn	*)get(type);
    if (proxy == NULL)
    {
	char *filename = GetPlugInFilename(type);
	proxy =	LoadPlugIn(filename);
	if (proxy == NULL)  
	{
	    danceTcl::OutputMessage("Cannot load plugin file: %s. It may depend on "
				    "another plugin that is not loaded.",filename);
	    return(NULL);
	}
	
	
	proxy->setFileName(filename);
	
	// Sets	name to	type of	class, and type	to base	class.
	proxy->setName(type);
	proxy->setType(type);
	add(proxy);
	danceTcl::OutputMessage("PlugIn %s added to DANCE.",type);
	
    }
    
    return proxy;
}

PlugIn *PlugInManager::GetInstance(Tcl_Interp *interp, char *type, char	*name,
				   int argc, char **argv)
{
	// Check if proxy already exists for the type of plugin.
	// The name stores the type of the object created. The type stores
	// its base class name which is	the same as the	type.
	// This	is only	for the	proxy which doesn't relaly have	a name.

	PlugIn *proxy =	AddProxy(type);
	if (proxy == NULL) 
		return(NULL);
	
	PlugIn *instance = proxy->create(interp, argc, argv);
	if (instance ==	NULL)
		return(NULL);

	instance->setName(name);
	instance->setType(type);

	return(instance);
}

char *PlugInManager::GetPlugInFilename(char *type)
{
	static char plugInName[256];


    // Add extension if	required.
#ifdef WIN32
	    sprintf(plugInName,"%s/plugins/WinNT/%s",getenv("DANCE_DIR"),type);
	    if (strcmp(&(type[strlen(type)-4]),".dll") != 0)
		strcat(plugInName,".dll");
#else
#ifdef SGI
    sprintf(plugInName,"%s/plugins/Irix/%s",getenv("DANCE_DIR"),type);
#else // Linux
    sprintf(plugInName,"%s/plugins/Linux/%s",getenv("DANCE_DIR"),type);
#endif
    if (strcmp(&(type[strlen(type)-3]),".so") != 0)
		strcat(plugInName,".so");
#endif

    return (plugInName);
}

typedef	PlugIn * (*plugInFactory)();
PlugIn *PlugInManager::LoadPlugIn(char *filename)
{
    void *handle = NULL;


    FILE *fp = fopen(filename, "r") ;
    if( fp == NULL ) 
    {
	danceTcl::OutputMessage("ERROR:LoadPlugIn: File %s doesn't exist.",  filename) ;
	return NULL ;
    }
    else fclose(fp) ;

    handle = dlopen(filename, RTLD_NOW|RTLD_GLOBAL);
    if(	handle == NULL ) 
    {
	danceTcl::OutputMessage("ERROR:LoadPlugin: Cannot get handle on %s.", filename) ;
	danceTcl::OutputMessage("%s", dlerror()) ;
	return	NULL;
    }    
    plugInFactory proxyFactory = (plugInFactory) dlsym(handle, "Proxy");
    if (proxyFactory == NULL) {
	danceTcl::OutputMessage("ERROR: Cannot find Proxy in %s",
				filename) ;
	dlclose(handle);
	return (NULL);
    }
    
    PlugIn *proxy = proxyFactory();
    
    return(proxy);
}

// Tests if given type is a plugin (dynamically loaded)
int PlugInManager::IsPlugin(char * type)
{
	PlugIn *proxy = (PlugIn	*)get(type);
	if (proxy != NULL)
		return 1;
	return 0;
}
