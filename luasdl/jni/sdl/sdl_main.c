#ifdef ANDROID

#include <unistd.h>
#include <jni.h>
#include <android/log.h>
#include "SDL_thread.h"
#include "SDL_main.h"
//#include <ruby.h>
#include <string.h>

/* JNI-C wrapper stuff */

#ifdef __cplusplus
#define C_LINKAGE "C"
#else
#define C_LINKAGE
#endif

#ifndef SDL_JAVA_PACKAGE_PATH
#error You have to define SDL_JAVA_PACKAGE_PATH to your package path with dots replaced with underscores, for example "com_example_SanAngeles"
#endif
#define JAVA_EXPORT_NAME2(name,package) Java_##package##_##name
#define JAVA_EXPORT_NAME1(name,package) JAVA_EXPORT_NAME2(name,package)
#define JAVA_EXPORT_NAME(name) JAVA_EXPORT_NAME1(name,SDL_JAVA_PACKAGE_PATH)

extern void SDL_Android_Init(JNIEnv* env, jclass cls);

extern C_LINKAGE void
JAVA_EXPORT_NAME(DemoRenderer_nativeInit) ( JNIEnv*  env, jobject thiz, jstring currentDirectoryPath_j, jboolean oo, jboolean dr, jstring script_j)
{
	int argc = 1;
	char script_name[256] = {0};
	char *argv[4] = { "sdl", NULL, NULL, NULL };
    //if (oo) argv[argc++] = "--open-only";
    //if (dr) argv[argc++] = "--disable-rescale";
	argv[argc++] = script_name;

    //FIXME: Modified by weimingtom
JAVA_EXPORT_NAME(DemoRenderer_nativeInitJavaCallbacks)(env, thiz);
	
	// Set current directory
	const char *currentDirectoryPath = (*env)->GetStringUTFChars(env, currentDirectoryPath_j, 0);
	chdir(currentDirectoryPath);
	(*env)->ReleaseStringUTFChars(env, currentDirectoryPath_j, currentDirectoryPath);

	const char *script = (*env)->GetStringUTFChars(env, script_j, 0);
	strncpy(script_name, script, sizeof(script_name) - 1);
	(*env)->ReleaseStringUTFChars(env, script_j, script);

	jclass cls = (*env)->GetObjectClass(env, thiz);
	SDL_Android_Init(env, cls);
	
	//FIXME: Modified by weimingtom
	//ruby_init_jni(env, thiz);

	SDL_main( argc, argv );
};

#undef JAVA_EXPORT_NAME
#undef JAVA_EXPORT_NAME1
#undef JAVA_EXPORT_NAME2
#undef C_LINKAGE

#endif
