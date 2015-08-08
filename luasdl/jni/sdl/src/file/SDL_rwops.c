/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2010 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

/* This file provides a general interface for SDL to read and write
   data sources.  It can easily be extended to files, memory, etc.
*/

#include "SDL_endian.h"
#include "SDL_rwops.h"

#ifdef __APPLE__
#include "cocoa/SDL_rwopsbundlesupport.h"
#endif /* __APPLE__ */

#ifdef __NDS__
/* include libfat headers for fatInitDefault(). */
#include <fat.h>
#endif /* __NDS__ */












#ifdef ANDROID

#include <jni.h>
#include <android/log.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>

static pthread_key_t mThreadKey;
static JavaVM* mJavaVM;

/* Main activity */
static jclass mActivityClass;

static void Android_JNI_ThreadDestroyed(void* value)
{
    /* The thread is being destroyed, detach it from the Java VM and set the mThreadKey value to NULL as required */
    JNIEnv *env = (JNIEnv*) value;
    if (env != NULL) {
        (*mJavaVM)->DetachCurrentThread(mJavaVM);
        pthread_setspecific(mThreadKey, NULL);
    }
}

JNIEnv* Android_JNI_GetEnv(void)
{
    /* From http://developer.android.com/guide/practices/jni.html
     * All threads are Linux threads, scheduled by the kernel.
     * They're usually started from managed code (using Thread.start), but they can also be created elsewhere and then
     * attached to the JavaVM. For example, a thread started with pthread_create can be attached with the
     * JNI AttachCurrentThread or AttachCurrentThreadAsDaemon functions. Until a thread is attached, it has no JNIEnv,
     * and cannot make JNI calls.
     * Attaching a natively-created thread causes a java.lang.Thread object to be constructed and added to the "main"
     * ThreadGroup, making it visible to the debugger. Calling AttachCurrentThread on an already-attached thread
     * is a no-op.
     * Note: You can call this function any number of times for the same thread, there's no harm in it
     */

    JNIEnv *env;
    int status = (*mJavaVM)->AttachCurrentThread(mJavaVM, &env, NULL);
    if(status < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "libSDL", "failed to attach current thread");
        return 0;
    }

    /* From http://developer.android.com/guide/practices/jni.html
     * Threads attached through JNI must call DetachCurrentThread before they exit. If coding this directly is awkward,
     * in Android 2.0 (Eclair) and higher you can use pthread_key_create to define a destructor function that will be
     * called before the thread exits, and call DetachCurrentThread from there. (Use that key with pthread_setspecific
     * to store the JNIEnv in thread-local-storage; that way it'll be passed into your destructor as the argument.)
     * Note: The destructor is not called unless the stored value is != NULL
     * Note: You can call this function any number of times for the same thread, there's no harm in it
     *       (except for some lost CPU cycles)
     */
    pthread_setspecific(mThreadKey, (void*) env);

    return env;
}

int Android_JNI_SetupThread(void)
{
    Android_JNI_GetEnv();
    return 1;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env;
	extern JavaVM *jniVM; /*defined in SDL_androidaudio.c */
    mJavaVM = vm;
	jniVM = vm;
    __android_log_print(ANDROID_LOG_INFO, "libSDL", "JNI_OnLoad called");
    if ((*mJavaVM)->GetEnv(mJavaVM, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "libSDL", "Failed to get the environment using GetEnv()");
        return -1;
    }
    /*
     * Create mThreadKey so we can keep track of the JNIEnv assigned to each thread
     * Refer to http://developer.android.com/guide/practices/design/jni.html for the rationale behind this
     */
    if (pthread_key_create(&mThreadKey, Android_JNI_ThreadDestroyed) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, "libSDL", "Error initializing pthread key");
    }
    Android_JNI_SetupThread();

    return JNI_VERSION_1_4;
}

/* Called before SDL_main() to initialize JNI bindings */
void SDL_Android_Init(JNIEnv* mEnv, jclass cls)
{
    __android_log_print(ANDROID_LOG_INFO, "libSDL", "SDL_Android_Init()");

    Android_JNI_SetupThread();

    mActivityClass = (jclass)((*mEnv)->NewGlobalRef(mEnv, cls));

    __android_log_print(ANDROID_LOG_INFO, "libSDL", "SDL_Android_Init() finished!");
}





static int s_active = 0;
struct LocalReferenceHolder
{
    JNIEnv *m_env;
    const char *m_func;
};

static struct LocalReferenceHolder LocalReferenceHolder_Setup(const char *func)
{
    struct LocalReferenceHolder refholder;
    refholder.m_env = NULL;
    refholder.m_func = func;
#ifdef DEBUG_JNI
    SDL_Log("Entering function %s", func);
#endif
    return refholder;
}

static SDL_bool LocalReferenceHolder_Init(struct LocalReferenceHolder *refholder, JNIEnv *env)
{
    const int capacity = 16;
    if ((*env)->PushLocalFrame(env, capacity) < 0) {
        SDL_SetError("Failed to allocate enough JVM local references");
        return SDL_FALSE;
    }
    ++s_active;
    refholder->m_env = env;
    return SDL_TRUE;
}

static void LocalReferenceHolder_Cleanup(struct LocalReferenceHolder *refholder)
{
#ifdef DEBUG_JNI
    SDL_Log("Leaving function %s", refholder->m_func);
#endif
    if (refholder->m_env) {
        JNIEnv* env = refholder->m_env;
        (*env)->PopLocalFrame(env, NULL);
        --s_active;
    }
}

static SDL_bool LocalReferenceHolder_IsActive()
{
    return s_active > 0;    
}


const char * SDL_AndroidGetInternalStoragePath()
{
    static char *s_AndroidInternalFilesPath = NULL;

    if (!s_AndroidInternalFilesPath) {
        struct LocalReferenceHolder refs = LocalReferenceHolder_Setup(__FUNCTION__);
        jmethodID mid;
        jobject context;
        jobject fileObject;
        jstring pathString;
        const char *path;

        JNIEnv *env = Android_JNI_GetEnv();
        if (!LocalReferenceHolder_Init(&refs, env)) {
            LocalReferenceHolder_Cleanup(&refs);
            return NULL;
        }

        /* context = SDLActivity.getContext(); */
        mid = (*env)->GetStaticMethodID(env, mActivityClass,
                "getContext","()Landroid/content/Context;");
        context = (*env)->CallStaticObjectMethod(env, mActivityClass, mid);

        /* fileObj = context.getFilesDir(); */
        mid = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, context),
                "getFilesDir", "()Ljava/io/File;");
        fileObject = (*env)->CallObjectMethod(env, context, mid);
        if (!fileObject) {
            SDL_SetError("Couldn't get internal directory");
            LocalReferenceHolder_Cleanup(&refs);
            return NULL;
        }

        /* path = fileObject.getAbsolutePath(); */
        mid = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, fileObject),
                "getAbsolutePath", "()Ljava/lang/String;");
        pathString = (jstring)(*env)->CallObjectMethod(env, fileObject, mid);

        path = (*env)->GetStringUTFChars(env, pathString, NULL);
        s_AndroidInternalFilesPath = SDL_strdup(path);
        (*env)->ReleaseStringUTFChars(env, pathString, path);

        LocalReferenceHolder_Cleanup(&refs);
    }
    return s_AndroidInternalFilesPath;
}












static bool Android_JNI_ExceptionOccurred(bool silent)
{
    assert(LocalReferenceHolder_IsActive());
    JNIEnv *mEnv = Android_JNI_GetEnv();

    jthrowable exception = (*mEnv)->ExceptionOccurred(mEnv);
    if (exception != NULL) {
        jmethodID mid;

        /* Until this happens most JNI operations have undefined behaviour */
        (*mEnv)->ExceptionClear(mEnv);

        if (!silent) {
            jclass exceptionClass = (*mEnv)->GetObjectClass(mEnv, exception);
            jclass classClass = (*mEnv)->FindClass(mEnv, "java/lang/Class");

            mid = (*mEnv)->GetMethodID(mEnv, classClass, "getName", "()Ljava/lang/String;");
            jstring exceptionName = (jstring)(*mEnv)->CallObjectMethod(mEnv, exceptionClass, mid);
            const char* exceptionNameUTF8 = (*mEnv)->GetStringUTFChars(mEnv, exceptionName, 0);

            mid = (*mEnv)->GetMethodID(mEnv, exceptionClass, "getMessage", "()Ljava/lang/String;");
            jstring exceptionMessage = (jstring)(*mEnv)->CallObjectMethod(mEnv, exception, mid);

            if (exceptionMessage != NULL) {
                const char* exceptionMessageUTF8 = (*mEnv)->GetStringUTFChars(mEnv, exceptionMessage, 0);
                SDL_SetError("%s: %s", exceptionNameUTF8, exceptionMessageUTF8);
                (*mEnv)->ReleaseStringUTFChars(mEnv, exceptionMessage, exceptionMessageUTF8);
            } else {
                SDL_SetError("%s", exceptionNameUTF8);
            }

            (*mEnv)->ReleaseStringUTFChars(mEnv, exceptionName, exceptionNameUTF8);
        }

        return true;
    }

    return false;
}



static int Internal_Android_JNI_FileOpen(SDL_RWops* ctx)
{
    struct LocalReferenceHolder refs = LocalReferenceHolder_Setup(__FUNCTION__);

    int result = 0;

    jmethodID mid;
    jobject context;
    jobject assetManager;
    jobject inputStream;
    jclass channels;
    jobject readableByteChannel;
    jstring fileNameJString;
    jobject fd;
    jclass fdCls;
    jfieldID descriptor;

    JNIEnv *mEnv = Android_JNI_GetEnv();
    if (!LocalReferenceHolder_Init(&refs, mEnv)) {
        goto failure;
    }

    fileNameJString = (jstring)ctx->hidden.androidio.fileNameRef;
    ctx->hidden.androidio.position = 0;

    /* context = SDLActivity.getContext(); */
    mid = (*mEnv)->GetStaticMethodID(mEnv, mActivityClass,
            "getContext","()Landroid/content/Context;");
    context = (*mEnv)->CallStaticObjectMethod(mEnv, mActivityClass, mid);


    /* assetManager = context.getAssets(); */
    mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, context),
            "getAssets", "()Landroid/content/res/AssetManager;");
    assetManager = (*mEnv)->CallObjectMethod(mEnv, context, mid);

    /* First let's try opening the file to obtain an AssetFileDescriptor.
    * This method reads the files directly from the APKs using standard *nix calls
    */
    mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, assetManager), "openFd", "(Ljava/lang/String;)Landroid/content/res/AssetFileDescriptor;");
    inputStream = (*mEnv)->CallObjectMethod(mEnv, assetManager, mid, fileNameJString);
    if (Android_JNI_ExceptionOccurred(true)) {
        goto fallback;
    }

    mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, inputStream), "getStartOffset", "()J");
    ctx->hidden.androidio.offset = (*mEnv)->CallLongMethod(mEnv, inputStream, mid);
    if (Android_JNI_ExceptionOccurred(true)) {
        goto fallback;
    }

    mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, inputStream), "getDeclaredLength", "()J");
    ctx->hidden.androidio.size = (*mEnv)->CallLongMethod(mEnv, inputStream, mid);
    if (Android_JNI_ExceptionOccurred(true)) {
        goto fallback;
    }

    mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, inputStream), "getFileDescriptor", "()Ljava/io/FileDescriptor;");
    fd = (*mEnv)->CallObjectMethod(mEnv, inputStream, mid);
    fdCls = (*mEnv)->GetObjectClass(mEnv, fd);
    descriptor = (*mEnv)->GetFieldID(mEnv, fdCls, "descriptor", "I");
    ctx->hidden.androidio.fd = (*mEnv)->GetIntField(mEnv, fd, descriptor);
    ctx->hidden.androidio.assetFileDescriptorRef = (*mEnv)->NewGlobalRef(mEnv, inputStream);

    /* Seek to the correct offset in the file. */
    lseek(ctx->hidden.androidio.fd, (off_t)ctx->hidden.androidio.offset, SEEK_SET);

    if (false) {
fallback:
        /* Disabled log message because of spam on the Nexus 7 */
        /* __android_log_print(ANDROID_LOG_DEBUG, "SDL", "Falling back to legacy InputStream method for opening file"); */

        /* Try the old method using InputStream */
        ctx->hidden.androidio.assetFileDescriptorRef = NULL;

        /* inputStream = assetManager.open(<filename>); */
        mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, assetManager),
                "open", "(Ljava/lang/String;I)Ljava/io/InputStream;");
        inputStream = (*mEnv)->CallObjectMethod(mEnv, assetManager, mid, fileNameJString, 1 /* ACCESS_RANDOM */);
        if (Android_JNI_ExceptionOccurred(false)) {
            goto failure;
        }

        ctx->hidden.androidio.inputStreamRef = (*mEnv)->NewGlobalRef(mEnv, inputStream);

        /* Despite all the visible documentation on [Asset]InputStream claiming
         * that the .available() method is not guaranteed to return the entire file
         * size, comments in <sdk>/samples/<ver>/ApiDemos/src/com/example/ ...
         * android/apis/content/ReadAsset.java imply that Android's
         * AssetInputStream.available() /will/ always return the total file size
        */
        
        /* size = inputStream.available(); */
        mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, inputStream),
                "available", "()I");
        ctx->hidden.androidio.size = (long)(*mEnv)->CallIntMethod(mEnv, inputStream, mid);
        if (Android_JNI_ExceptionOccurred(false)) {
            goto failure;
        }

        /* readableByteChannel = Channels.newChannel(inputStream); */
        channels = (*mEnv)->FindClass(mEnv, "java/nio/channels/Channels");
        mid = (*mEnv)->GetStaticMethodID(mEnv, channels,
                "newChannel",
                "(Ljava/io/InputStream;)Ljava/nio/channels/ReadableByteChannel;");
        readableByteChannel = (*mEnv)->CallStaticObjectMethod(
                mEnv, channels, mid, inputStream);
        if (Android_JNI_ExceptionOccurred(false)) {
            goto failure;
        }

        ctx->hidden.androidio.readableByteChannelRef =
            (*mEnv)->NewGlobalRef(mEnv, readableByteChannel);

        /* Store .read id for reading purposes */
        mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, readableByteChannel),
                "read", "(Ljava/nio/ByteBuffer;)I");
        ctx->hidden.androidio.readMethod = mid;
    }

    if (false) {
failure:
        result = -1;

        (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.fileNameRef);

        if(ctx->hidden.androidio.inputStreamRef != NULL) {
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.inputStreamRef);
        }

        if(ctx->hidden.androidio.readableByteChannelRef != NULL) {
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.readableByteChannelRef);
        }

        if(ctx->hidden.androidio.assetFileDescriptorRef != NULL) {
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.assetFileDescriptorRef);
        }

    }
    
    LocalReferenceHolder_Cleanup(&refs);
    return result;
}

int Android_JNI_FileOpen(SDL_RWops* ctx,
        const char* fileName, const char* mode)
{
    struct LocalReferenceHolder refs = LocalReferenceHolder_Setup(__FUNCTION__);
    JNIEnv *mEnv = Android_JNI_GetEnv();
    int retval;

    if (!LocalReferenceHolder_Init(&refs, mEnv)) {
        LocalReferenceHolder_Cleanup(&refs);        
        return -1;
    }

    if (!ctx) {
        LocalReferenceHolder_Cleanup(&refs);
        return -1;
    }

    jstring fileNameJString = (*mEnv)->NewStringUTF(mEnv, fileName);
    ctx->hidden.androidio.fileNameRef = (*mEnv)->NewGlobalRef(mEnv, fileNameJString);
    ctx->hidden.androidio.inputStreamRef = NULL;
    ctx->hidden.androidio.readableByteChannelRef = NULL;
    ctx->hidden.androidio.readMethod = NULL;
    ctx->hidden.androidio.assetFileDescriptorRef = NULL;

    retval = Internal_Android_JNI_FileOpen(ctx);
    LocalReferenceHolder_Cleanup(&refs);
    return retval;
}

size_t Android_JNI_FileRead(SDL_RWops* ctx, void* buffer,
        size_t size, size_t maxnum)
{
    struct LocalReferenceHolder refs = LocalReferenceHolder_Setup(__FUNCTION__);

    if (ctx->hidden.androidio.assetFileDescriptorRef) {
        size_t bytesMax = size * maxnum;
        if (ctx->hidden.androidio.size != -1 /* UNKNOWN_LENGTH */ && ctx->hidden.androidio.position + bytesMax > ctx->hidden.androidio.size) {
            bytesMax = ctx->hidden.androidio.size - ctx->hidden.androidio.position;
        }
        size_t result = read(ctx->hidden.androidio.fd, buffer, bytesMax );
        if (result > 0) {
            ctx->hidden.androidio.position += result;
            LocalReferenceHolder_Cleanup(&refs);
            return result / size;
        }
        LocalReferenceHolder_Cleanup(&refs);
        return 0;
    } else {
        jlong bytesRemaining = (jlong) (size * maxnum);
        jlong bytesMax = (jlong) (ctx->hidden.androidio.size -  ctx->hidden.androidio.position);
        int bytesRead = 0;

        /* Don't read more bytes than those that remain in the file, otherwise we get an exception */
        if (bytesRemaining >  bytesMax) bytesRemaining = bytesMax;

        JNIEnv *mEnv = Android_JNI_GetEnv();
        if (!LocalReferenceHolder_Init(&refs, mEnv)) {
            LocalReferenceHolder_Cleanup(&refs);            
            return 0;
        }

        jobject readableByteChannel = (jobject)ctx->hidden.androidio.readableByteChannelRef;
        jmethodID readMethod = (jmethodID)ctx->hidden.androidio.readMethod;
        jobject byteBuffer = (*mEnv)->NewDirectByteBuffer(mEnv, buffer, bytesRemaining);

        while (bytesRemaining > 0) {
            /* result = readableByteChannel.read(...); */
            int result = (*mEnv)->CallIntMethod(mEnv, readableByteChannel, readMethod, byteBuffer);

            if (Android_JNI_ExceptionOccurred(false)) {
                LocalReferenceHolder_Cleanup(&refs);            
                return 0;
            }

            if (result < 0) {
                break;
            }

            bytesRemaining -= result;
            bytesRead += result;
            ctx->hidden.androidio.position += result;
        }
        LocalReferenceHolder_Cleanup(&refs);                    
        return bytesRead / size;
    }
}

size_t Android_JNI_FileWrite(SDL_RWops* ctx, const void* buffer,
        size_t size, size_t num)
{
    SDL_SetError("Cannot write to Android package filesystem");
    return 0;
}

static int Internal_Android_JNI_FileClose(SDL_RWops* ctx, int release)
{
	struct LocalReferenceHolder refs = LocalReferenceHolder_Setup(__FUNCTION__);

    int result = 0;
    JNIEnv *mEnv = Android_JNI_GetEnv();

    if (!LocalReferenceHolder_Init(&refs, mEnv)) {
        LocalReferenceHolder_Cleanup(&refs);
        SDL_SetError("Failed to allocate enough JVM local references");
		return 0;
	}

    if (ctx) {
        if (release) {
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.fileNameRef);
        }

        if (ctx->hidden.androidio.assetFileDescriptorRef) {
            jobject inputStream = (jobject)ctx->hidden.androidio.assetFileDescriptorRef;
            jmethodID mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, inputStream),
                    "close", "()V");
            (*mEnv)->CallVoidMethod(mEnv, inputStream, mid);
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.assetFileDescriptorRef);
            if (Android_JNI_ExceptionOccurred(false)) {
                result = -1;
            }
        }
        else {
            jobject inputStream = (jobject)ctx->hidden.androidio.inputStreamRef;

            /* inputStream.close(); */
            jmethodID mid = (*mEnv)->GetMethodID(mEnv, (*mEnv)->GetObjectClass(mEnv, inputStream),
                    "close", "()V");
            (*mEnv)->CallVoidMethod(mEnv, inputStream, mid);
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.inputStreamRef);
            (*mEnv)->DeleteGlobalRef(mEnv, (jobject)ctx->hidden.androidio.readableByteChannelRef);
            if (Android_JNI_ExceptionOccurred(false)) {
                result = -1;
            }
        }

        if (release) {
            SDL_FreeRW(ctx);
        }
    }

    LocalReferenceHolder_Cleanup(&refs);
    return result;
}


Sint64 Android_JNI_FileSize(SDL_RWops* ctx)
{
    return ctx->hidden.androidio.size;
}

long Android_JNI_FileSeek(SDL_RWops* ctx, long offset, int whence)
{
    if (ctx->hidden.androidio.assetFileDescriptorRef) {
        switch (whence) {
            case RW_SEEK_SET:
                if (ctx->hidden.androidio.size != -1 /* UNKNOWN_LENGTH */ && offset > ctx->hidden.androidio.size) offset = ctx->hidden.androidio.size;
                offset += ctx->hidden.androidio.offset;
                break;
            case RW_SEEK_CUR:
                offset += ctx->hidden.androidio.position;
                if (ctx->hidden.androidio.size != -1 /* UNKNOWN_LENGTH */ && offset > ctx->hidden.androidio.size) offset = ctx->hidden.androidio.size;
                offset += ctx->hidden.androidio.offset;
                break;
            case RW_SEEK_END:
                offset = ctx->hidden.androidio.offset + ctx->hidden.androidio.size + offset;
                break;
            default:
                SDL_SetError("Unknown value for 'whence'");
				return -1;
        }
        whence = SEEK_SET;

        off_t ret = lseek(ctx->hidden.androidio.fd, (off_t)offset, SEEK_SET);
        if (ret == -1) return -1;
        ctx->hidden.androidio.position = ret - ctx->hidden.androidio.offset;
    } else {
        Sint64 newPosition;

        switch (whence) {
            case RW_SEEK_SET:
                newPosition = offset;
                break;
            case RW_SEEK_CUR:
                newPosition = ctx->hidden.androidio.position + offset;
                break;
            case RW_SEEK_END:
                newPosition = ctx->hidden.androidio.size + offset;
                break;
            default:
                SDL_SetError("Unknown value for 'whence'");
				return -1;
        }

        /* Validate the new position */
        if (newPosition < 0) {
            SDL_Error(SDL_EFSEEK);
			return -1;
		}
        if (newPosition > ctx->hidden.androidio.size) {
            newPosition = ctx->hidden.androidio.size;
        }

        Sint64 movement = newPosition - ctx->hidden.androidio.position;
        if (movement > 0) {
            unsigned char buffer[4096];

            /* The easy case where we're seeking forwards */
            while (movement > 0) {
                Sint64 amount = sizeof (buffer);
                if (amount > movement) {
                    amount = movement;
                }
                size_t result = Android_JNI_FileRead(ctx, buffer, 1, amount);
                if (result <= 0) {
                    /* Failed to read/skip the required amount, so fail */
                    return -1;
                }

                movement -= result;
            }

        } else if (movement < 0) {
            /* We can't seek backwards so we have to reopen the file and seek */
            /* forwards which obviously isn't very efficient */
            Internal_Android_JNI_FileClose(ctx, 0);
            Internal_Android_JNI_FileOpen(ctx);
            Android_JNI_FileSeek(ctx, newPosition, RW_SEEK_SET);
        }
    }

    return ctx->hidden.androidio.position;

}

int Android_JNI_FileClose(SDL_RWops* ctx)
{
    return Internal_Android_JNI_FileClose(ctx, 1);
}

#endif /*ANDROID*/
















#ifdef __WIN32__

/* Functions to read/write Win32 API file pointers */
/* Will not use it on WinCE because stdio is buffered, it means
   faster, and all stdio functions anyway are embedded in coredll.dll - 
   the main wince dll*/

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER 0xFFFFFFFF
#endif

#define READAHEAD_BUFFER_SIZE	1024

static int SDLCALL
win32_file_open(SDL_RWops * context, const char *filename, const char *mode)
{
#ifndef _WIN32_WCE
    UINT old_error_mode;
#endif
    HANDLE h;
    DWORD r_right, w_right;
    DWORD must_exist, truncate;
    int a_mode;

    if (!context)
        return -1;              /* failed (invalid call) */

    context->hidden.win32io.h = INVALID_HANDLE_VALUE;   /* mark this as unusable */
    context->hidden.win32io.buffer.data = NULL;
    context->hidden.win32io.buffer.size = 0;
    context->hidden.win32io.buffer.left = 0;

    /* "r" = reading, file must exist */
    /* "w" = writing, truncate existing, file may not exist */
    /* "r+"= reading or writing, file must exist            */
    /* "a" = writing, append file may not exist             */
    /* "a+"= append + read, file may not exist              */
    /* "w+" = read, write, truncate. file may not exist    */

    must_exist = (SDL_strchr(mode, 'r') != NULL) ? OPEN_EXISTING : 0;
    truncate = (SDL_strchr(mode, 'w') != NULL) ? CREATE_ALWAYS : 0;
    r_right = (SDL_strchr(mode, '+') != NULL
               || must_exist) ? GENERIC_READ : 0;
    a_mode = (SDL_strchr(mode, 'a') != NULL) ? OPEN_ALWAYS : 0;
    w_right = (a_mode || SDL_strchr(mode, '+')
               || truncate) ? GENERIC_WRITE : 0;

    if (!r_right && !w_right)   /* inconsistent mode */
        return -1;              /* failed (invalid call) */

    context->hidden.win32io.buffer.data =
        (char *) SDL_malloc(READAHEAD_BUFFER_SIZE);
    if (!context->hidden.win32io.buffer.data) {
        SDL_OutOfMemory();
        return -1;
    }
#ifdef _WIN32_WCE
    {
        size_t size = SDL_strlen(filename) + 1;
        wchar_t *filenameW = SDL_stack_alloc(wchar_t, size);

        if (MultiByteToWideChar(CP_UTF8, 0, filename, -1, filenameW, size) ==
            0) {
            SDL_stack_free(filenameW);
            SDL_free(context->hidden.win32io.buffer.data);
            context->hidden.win32io.buffer.data = NULL;
            SDL_SetError("Unable to convert filename to Unicode");
            return -1;
        }
        h = CreateFile(filenameW, (w_right | r_right),
                       (w_right) ? 0 : FILE_SHARE_READ, NULL,
                       (must_exist | truncate | a_mode),
                       FILE_ATTRIBUTE_NORMAL, NULL);
        SDL_stack_free(filenameW);
    }
#else
    /* Do not open a dialog box if failure */
    old_error_mode =
        SetErrorMode(SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS);

    h = CreateFile(filename, (w_right | r_right),
                   (w_right) ? 0 : FILE_SHARE_READ, NULL,
                   (must_exist | truncate | a_mode), FILE_ATTRIBUTE_NORMAL,
                   NULL);

    /* restore old behaviour */
    SetErrorMode(old_error_mode);
#endif /* _WIN32_WCE */

    if (h == INVALID_HANDLE_VALUE) {
        SDL_free(context->hidden.win32io.buffer.data);
        context->hidden.win32io.buffer.data = NULL;
        SDL_SetError("Couldn't open %s", filename);
        return -2;              /* failed (CreateFile) */
    }
    context->hidden.win32io.h = h;
    context->hidden.win32io.append = a_mode ? SDL_TRUE : SDL_FALSE;

    return 0;                   /* ok */
}

static long SDLCALL
win32_file_seek(SDL_RWops * context, long offset, int whence)
{
    DWORD win32whence;
    long file_pos;

    if (!context || context->hidden.win32io.h == INVALID_HANDLE_VALUE) {
        SDL_SetError("win32_file_seek: invalid context/file not opened");
        return -1;
    }

    /* FIXME: We may be able to satisfy the seek within buffered data */
    if (whence == RW_SEEK_CUR && context->hidden.win32io.buffer.left) {
        offset -= (long)context->hidden.win32io.buffer.left;
    }
    context->hidden.win32io.buffer.left = 0;

    switch (whence) {
    case RW_SEEK_SET:
        win32whence = FILE_BEGIN;
        break;
    case RW_SEEK_CUR:
        win32whence = FILE_CURRENT;
        break;
    case RW_SEEK_END:
        win32whence = FILE_END;
        break;
    default:
        SDL_SetError("win32_file_seek: Unknown value for 'whence'");
        return -1;
    }

    file_pos =
        SetFilePointer(context->hidden.win32io.h, offset, NULL, win32whence);

    if (file_pos != INVALID_SET_FILE_POINTER)
        return file_pos;        /* success */

    SDL_Error(SDL_EFSEEK);
    return -1;                  /* error */
}

static size_t SDLCALL
win32_file_read(SDL_RWops * context, void *ptr, size_t size, size_t maxnum)
{
    size_t total_need;
    size_t total_read = 0;
    size_t read_ahead;
    DWORD byte_read;

    total_need = size * maxnum;

    if (!context || context->hidden.win32io.h == INVALID_HANDLE_VALUE
        || !total_need)
        return 0;

    if (context->hidden.win32io.buffer.left > 0) {
        void *data = (char *) context->hidden.win32io.buffer.data +
            context->hidden.win32io.buffer.size -
            context->hidden.win32io.buffer.left;
        read_ahead =
            SDL_min(total_need, context->hidden.win32io.buffer.left);
        SDL_memcpy(ptr, data, read_ahead);
        context->hidden.win32io.buffer.left -= read_ahead;

        if (read_ahead == total_need) {
            return maxnum;
        }
        ptr = (char *) ptr + read_ahead;
        total_need -= read_ahead;
        total_read += read_ahead;
    }

    if (total_need < READAHEAD_BUFFER_SIZE) {
        if (!ReadFile
            (context->hidden.win32io.h, context->hidden.win32io.buffer.data,
             READAHEAD_BUFFER_SIZE, &byte_read, NULL)) {
            SDL_Error(SDL_EFREAD);
            return 0;
        }
        read_ahead = SDL_min(total_need, (int) byte_read);
        SDL_memcpy(ptr, context->hidden.win32io.buffer.data, read_ahead);
        context->hidden.win32io.buffer.size = byte_read;
        context->hidden.win32io.buffer.left = byte_read - read_ahead;
        total_read += read_ahead;
    } else {
        if (!ReadFile
            (context->hidden.win32io.h, ptr, (DWORD)total_need, &byte_read, NULL)) {
            SDL_Error(SDL_EFREAD);
            return 0;
        }
        total_read += byte_read;
    }
    return (total_read / size);
}

static size_t SDLCALL
win32_file_write(SDL_RWops * context, const void *ptr, size_t size,
                 size_t num)
{

    size_t total_bytes;
    DWORD byte_written;
    size_t nwritten;

    total_bytes = size * num;

    if (!context || context->hidden.win32io.h == INVALID_HANDLE_VALUE
        || total_bytes <= 0 || !size)
        return 0;

    if (context->hidden.win32io.buffer.left) {
        SetFilePointer(context->hidden.win32io.h,
                       -(LONG)context->hidden.win32io.buffer.left, NULL,
                       FILE_CURRENT);
        context->hidden.win32io.buffer.left = 0;
    }

    /* if in append mode, we must go to the EOF before write */
    if (context->hidden.win32io.append) {
        if (SetFilePointer(context->hidden.win32io.h, 0L, NULL, FILE_END) ==
            INVALID_SET_FILE_POINTER) {
            SDL_Error(SDL_EFWRITE);
            return 0;
        }
    }

    if (!WriteFile
        (context->hidden.win32io.h, ptr, (DWORD)total_bytes, &byte_written, NULL)) {
        SDL_Error(SDL_EFWRITE);
        return 0;
    }

    nwritten = byte_written / size;
    return nwritten;
}

static int SDLCALL
win32_file_close(SDL_RWops * context)
{

    if (context) {
        if (context->hidden.win32io.h != INVALID_HANDLE_VALUE) {
            CloseHandle(context->hidden.win32io.h);
            context->hidden.win32io.h = INVALID_HANDLE_VALUE;   /* to be sure */
        }
        if (context->hidden.win32io.buffer.data) {
            SDL_free(context->hidden.win32io.buffer.data);
            context->hidden.win32io.buffer.data = NULL;
        }
        SDL_FreeRW(context);
    }
    return (0);
}
#endif /* __WIN32__ */

#ifdef HAVE_STDIO_H

/* Functions to read/write stdio file pointers */

static long SDLCALL
stdio_seek(SDL_RWops * context, long offset, int whence)
{
    if (fseek(context->hidden.stdio.fp, offset, whence) == 0) {
        return (ftell(context->hidden.stdio.fp));
    } else {
        SDL_Error(SDL_EFSEEK);
        return (-1);
    }
}

static size_t SDLCALL
stdio_read(SDL_RWops * context, void *ptr, size_t size, size_t maxnum)
{
    size_t nread;

    nread = fread(ptr, size, maxnum, context->hidden.stdio.fp);
    if (nread == 0 && ferror(context->hidden.stdio.fp)) {
        SDL_Error(SDL_EFREAD);
    }
    return (nread);
}

static size_t SDLCALL
stdio_write(SDL_RWops * context, const void *ptr, size_t size, size_t num)
{
    size_t nwrote;

    nwrote = fwrite(ptr, size, num, context->hidden.stdio.fp);
    if (nwrote == 0 && ferror(context->hidden.stdio.fp)) {
        SDL_Error(SDL_EFWRITE);
    }
    return (nwrote);
}

static int SDLCALL
stdio_close(SDL_RWops * context)
{
    int status = 0;
    if (context) {
        if (context->hidden.stdio.autoclose) {
            /* WARNING:  Check the return value here! */
            if (fclose(context->hidden.stdio.fp) != 0) {
                SDL_Error(SDL_EFWRITE);
                status = -1;
            }
        }
        SDL_FreeRW(context);
    }
    return status;
}
#endif /* !HAVE_STDIO_H */

/* Functions to read/write memory pointers */

static long SDLCALL
mem_seek(SDL_RWops * context, long offset, int whence)
{
    Uint8 *newpos;

    switch (whence) {
    case RW_SEEK_SET:
        newpos = context->hidden.mem.base + offset;
        break;
    case RW_SEEK_CUR:
        newpos = context->hidden.mem.here + offset;
        break;
    case RW_SEEK_END:
        newpos = context->hidden.mem.stop + offset;
        break;
    default:
        SDL_SetError("Unknown value for 'whence'");
        return (-1);
    }
    if (newpos < context->hidden.mem.base) {
        newpos = context->hidden.mem.base;
    }
    if (newpos > context->hidden.mem.stop) {
        newpos = context->hidden.mem.stop;
    }
    context->hidden.mem.here = newpos;
    return (long)(context->hidden.mem.here - context->hidden.mem.base);
}

static size_t SDLCALL
mem_read(SDL_RWops * context, void *ptr, size_t size, size_t maxnum)
{
    size_t total_bytes;
    size_t mem_available;

    total_bytes = (maxnum * size);
    if ((maxnum <= 0) || (size <= 0)
        || ((total_bytes / maxnum) != (size_t) size)) {
        return 0;
    }

    mem_available = (context->hidden.mem.stop - context->hidden.mem.here);
    if (total_bytes > mem_available) {
        total_bytes = mem_available;
    }

    SDL_memcpy(ptr, context->hidden.mem.here, total_bytes);
    context->hidden.mem.here += total_bytes;

    return (total_bytes / size);
}

static size_t SDLCALL
mem_write(SDL_RWops * context, const void *ptr, size_t size, size_t num)
{
    if ((context->hidden.mem.here + (num * size)) > context->hidden.mem.stop) {
        num = (context->hidden.mem.stop - context->hidden.mem.here) / size;
    }
    SDL_memcpy(context->hidden.mem.here, ptr, num * size);
    context->hidden.mem.here += num * size;
    return (num);
}

static size_t SDLCALL
mem_writeconst(SDL_RWops * context, const void *ptr, size_t size, size_t num)
{
    SDL_SetError("Can't write to read-only memory");
    return (-1);
}

static int SDLCALL
mem_close(SDL_RWops * context)
{
    if (context) {
        SDL_FreeRW(context);
    }
    return (0);
}


/* Functions to create SDL_RWops structures from various data sources */

SDL_RWops *
SDL_RWFromFile(const char *file, const char *mode)
{
    SDL_RWops *rwops = NULL;
	char *real_path;
	
#ifdef HAVE_STDIO_H
    FILE *fp = NULL;
#endif
    if (!file || !*file || !mode || !*mode) {
        SDL_SetError("SDL_RWFromFile(): No file or no mode specified");
        return NULL;
    }
#if defined(ANDROID)
#ifdef HAVE_STDIO_H
    /* Try to open the file on the filesystem first */
    if (*file == '/') {
        FILE *fp = fopen(file, mode);
        if (fp) {
            return SDL_RWFromFP(fp, 1);
        }
    } else {
        /* Try opening it from internal storage if it's a relative path */
        char *path;
        FILE *fp;

        path = SDL_stack_alloc(char, PATH_MAX);
        if (path) {
            SDL_snprintf(path, PATH_MAX, "%s/%s",
                         SDL_AndroidGetInternalStoragePath(), file);
            fp = fopen(path, mode);
            SDL_stack_free(path);
            if (fp) {
                return SDL_RWFromFP(fp, 1);
            }
        }
    }
#endif /* HAVE_STDIO_H */

    /* Try to open the file from the asset system */
    rwops = SDL_AllocRW();
    if (!rwops)
        return NULL;            /* SDL_SetError already setup by SDL_AllocRW() */
    if (Android_JNI_FileOpen(rwops, file, mode) < 0) {
        SDL_FreeRW(rwops);
        return NULL;
    }
    /*rwops->size = Android_JNI_FileSize;*/
    rwops->seek = Android_JNI_FileSeek;
    rwops->read = Android_JNI_FileRead;
    rwops->write = Android_JNI_FileWrite;
    rwops->close = Android_JNI_FileClose;
    /*rwops->type = SDL_RWOPS_JNIFILE;*/

#elif defined(__WIN32__)
    rwops = SDL_AllocRW();
    if (!rwops)
        return NULL;            /* SDL_SetError already setup by SDL_AllocRW() */
    
	real_path = (char *)calloc(1024, 1);
	sprintf(real_path, "%s/%s", SDL_MEMORY_FILE_PATH, file);

	if (win32_file_open(rwops, real_path, mode) < 0) {
        if (win32_file_open(rwops, file, mode) < 0) {
			SDL_FreeRW(rwops);
			free(real_path);
			return NULL;
		}
	}
	free(real_path);
    rwops->seek = win32_file_seek;
    rwops->read = win32_file_read;
    rwops->write = win32_file_write;
    rwops->close = win32_file_close;

#elif HAVE_STDIO_H
	#ifdef __APPLE__
	fp = SDL_OpenFPFromBundleOrFallback(file, mode);
    #else
	fp = fopen(file, mode);
	#endif
	if (fp == NULL) {
        SDL_SetError("Couldn't open %s", file);
    } else {
        rwops = SDL_RWFromFP(fp, 1);
    }
#else
    SDL_SetError("SDL not compiled with stdio support");
#endif /* !HAVE_STDIO_H */

    return (rwops);
}

#ifdef HAVE_STDIO_H
SDL_RWops *
SDL_RWFromFP(FILE * fp, SDL_bool autoclose)
{
    SDL_RWops *rwops = NULL;

#if 0
/*#ifdef __NDS__*/
    /* set it up so we can use stdio file function */
    fatInitDefault();
    printf("called fatInitDefault()");
#endif /* __NDS__ */

    rwops = SDL_AllocRW();
    if (rwops != NULL) {
        rwops->seek = stdio_seek;
        rwops->read = stdio_read;
        rwops->write = stdio_write;
        rwops->close = stdio_close;
        rwops->hidden.stdio.fp = fp;
        rwops->hidden.stdio.autoclose = autoclose;
    }
    return (rwops);
}
#else
SDL_RWops *
SDL_RWFromFP(void * fp, SDL_bool autoclose)
{
    SDL_SetError("SDL not compiled with stdio support");
    return NULL;
}
#endif /* HAVE_STDIO_H */

SDL_RWops *
SDL_RWFromMem(void *mem, int size)
{
    SDL_RWops *rwops;

    rwops = SDL_AllocRW();
    if (rwops != NULL) {
        rwops->seek = mem_seek;
        rwops->read = mem_read;
        rwops->write = mem_write;
        rwops->close = mem_close;
        rwops->hidden.mem.base = (Uint8 *) mem;
        rwops->hidden.mem.here = rwops->hidden.mem.base;
        rwops->hidden.mem.stop = rwops->hidden.mem.base + size;
    }
    return (rwops);
}

SDL_RWops *
SDL_RWFromConstMem(const void *mem, int size)
{
    SDL_RWops *rwops;

    rwops = SDL_AllocRW();
    if (rwops != NULL) {
        rwops->seek = mem_seek;
        rwops->read = mem_read;
        rwops->write = mem_writeconst;
        rwops->close = mem_close;
        rwops->hidden.mem.base = (Uint8 *) mem;
        rwops->hidden.mem.here = rwops->hidden.mem.base;
        rwops->hidden.mem.stop = rwops->hidden.mem.base + size;
    }
    return (rwops);
}

SDL_RWops *
SDL_AllocRW(void)
{
    SDL_RWops *area;

    area = (SDL_RWops *) SDL_malloc(sizeof *area);
    if (area == NULL) {
        SDL_OutOfMemory();
    }
    return (area);
}

void
SDL_FreeRW(SDL_RWops * area)
{
    SDL_free(area);
}

/* Functions for dynamically reading and writing endian-specific values */

Uint16
SDL_ReadLE16(SDL_RWops * src)
{
    Uint16 value;

    SDL_RWread(src, &value, (sizeof value), 1);
    return (SDL_SwapLE16(value));
}

Uint16
SDL_ReadBE16(SDL_RWops * src)
{
    Uint16 value;

    SDL_RWread(src, &value, (sizeof value), 1);
    return (SDL_SwapBE16(value));
}

Uint32
SDL_ReadLE32(SDL_RWops * src)
{
    Uint32 value;

    SDL_RWread(src, &value, (sizeof value), 1);
    return (SDL_SwapLE32(value));
}

Uint32
SDL_ReadBE32(SDL_RWops * src)
{
    Uint32 value;

    SDL_RWread(src, &value, (sizeof value), 1);
    return (SDL_SwapBE32(value));
}

Uint64
SDL_ReadLE64(SDL_RWops * src)
{
    Uint64 value;

    SDL_RWread(src, &value, (sizeof value), 1);
    return (SDL_SwapLE64(value));
}

Uint64
SDL_ReadBE64(SDL_RWops * src)
{
    Uint64 value;

    SDL_RWread(src, &value, (sizeof value), 1);
    return (SDL_SwapBE64(value));
}

size_t
SDL_WriteLE16(SDL_RWops * dst, Uint16 value)
{
    value = SDL_SwapLE16(value);
    return (SDL_RWwrite(dst, &value, (sizeof value), 1));
}

size_t
SDL_WriteBE16(SDL_RWops * dst, Uint16 value)
{
    value = SDL_SwapBE16(value);
    return (SDL_RWwrite(dst, &value, (sizeof value), 1));
}

size_t
SDL_WriteLE32(SDL_RWops * dst, Uint32 value)
{
    value = SDL_SwapLE32(value);
    return (SDL_RWwrite(dst, &value, (sizeof value), 1));
}

size_t
SDL_WriteBE32(SDL_RWops * dst, Uint32 value)
{
    value = SDL_SwapBE32(value);
    return (SDL_RWwrite(dst, &value, (sizeof value), 1));
}

size_t
SDL_WriteLE64(SDL_RWops * dst, Uint64 value)
{
    value = SDL_SwapLE64(value);
    return (SDL_RWwrite(dst, &value, (sizeof value), 1));
}

size_t
SDL_WriteBE64(SDL_RWops * dst, Uint64 value)
{
    value = SDL_SwapBE64(value);
    return (SDL_RWwrite(dst, &value, (sizeof value), 1));
}

/* vi: set ts=4 sw=4 expandtab: */
