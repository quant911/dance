#ifndef	__DLFCN_H__
#define	__DLFCN_H__

#ifdef WIN32

#ifdef __cplusplus
extern "C" {
#endif

#define	DLLEXPORT __declspec(dllexport)
DLLEXPORT void *dlopen(const char	*, int);
DLLEXPORT void *dlsym(void *, const char *);
DLLEXPORT int dlclose(void *);
DLLEXPORT char *dlerror(void);

/* valid values	for mode argument to dlopen/sgidladd/sgidlopen_version */
#define	RTLD_LAZY	1	/* lazy	function call binding */
#define	RTLD_NOW	2	/* immediate function call binding */
#define	RTLD_GLOBAL	4	/* symbols in this dlopen'ed obj are visible to	other dlopen'ed	objs */

#ifdef __cplusplus
}
#endif

#endif /* WIN32	*/

#endif /* !__DLFCN_H__ */
