package jp.ogapee.onscripter;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;
import android.view.KeyEvent;
import android.media.AudioManager;

class DemoRenderer extends GLSurfaceView_SDL.Renderer {
	private static Context mSingleton;
	private Activity context = null;
	private EGL10 mEgl = null;
	private EGLDisplay mEglDisplay = null;
	private EGLSurface mEglSurface = null;
	private EGLContext mEglContext = null;
	private int skipFrames = 0;
	
	public static Context getContext() {
		return mSingleton;
	}
	
	public DemoRenderer(Activity _context) {
		context = _context;
		mSingleton = _context;
		//FIXME:
		/**
		 * E/libEGL(3404): call to OpenGL ES API with no current context 
		 * (logged once per thread)
		 */
		/*
		nativeInit(ONScripter.gCurrentDirectoryPath, true,
				ONScripter.gDisableRescale);
		*/
	}
	
	public int swapBuffers() {
		return super.SwapBuffers() ? 1 : 0;
	}

	public void exitApp() {
		nativeDone();
	}
	
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// nativeInit();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int w, int h) {
		// gl.glViewport(0, 0, w, h);
		gl.glMatrixMode(GL10.GL_PROJECTION);
		gl.glLoadIdentity();
		gl.glMatrixMode(GL10.GL_MODELVIEW);
		gl.glLoadIdentity();
		gl.glViewport(0, 0, w, h);
		gl.glOrthof(0.0f, (float) w, (float) h, 0.0f, 0.0f, 1.0f);
		nativeResize(w, h);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		nativeInitJavaCallbacks();
		nativeInit(ONScripter.gCurrentDirectoryPath, 
			false,
			ONScripter.gDisableRescale, 
			//"alphadraw.rb"
			"alpha.rb"
			//"aadraw.rb"
			//"test_fib.rb"
		);
	}

	//FIXME: jni\sdl\src\video\android\SDL_androidvideo.c
	private native void nativeInitJavaCallbacks();

	//FIXME: jni\sdl\src\video\android\SDL_androidvideo.c
	//FIXME: jni\sdl_main\sdl_main.c
	private native void nativeInit(String currentDirectoryPath, boolean oo,
			boolean dr, String script);

	//FIXME: jni\sdl\src\video\android\SDL_androidvideo.c
	private native void nativeResize(int w, int h);

	//FIXME: jni\sdl\src\video\android\SDL_androidvideo.c
	private native void nativeDone();
	
	
	//RubyJNI
	
	private static final boolean D = true;
	private static final String TAG = "RubyJNI";
	
	private static final String FIB_RUBY = 
			"# calculate Fibonacci(20)\n" + 
			"# for benchmark\n" + 
			"def fib(n)\n" +
			"  if n<2\n" + 
			"    n\n" + 
			"  else\n" + 
			"    fib(n-2)+fib(n-1)\n" + 
			"  end\n" + 
			"end\n" + 
			"print(fib(20), \"\\n\");\n" + 
			"print(\"Hello, world !\")";
	
	public native int exec(String filename);
	
	private void log(String str) {
		Log.d(TAG, str);
	}
	
	private String readfile(String filename) {
//		return FIB_RUBY;//"hello xxx";
		if (filename == null) {
			return "";
		}
		if (filename.startsWith("./") || filename.startsWith(".\\")) {
			filename = filename.substring(2);
		}
    	StringBuffer sb = new StringBuffer();
		InputStream istr = null;
		InputStreamReader reader = null;
		BufferedReader rbuf = null;
		try {
			istr = context.getAssets().open(filename);
			reader = new InputStreamReader(istr, "utf8");
			rbuf = new BufferedReader(reader);
			String line;
			while (null != (line = rbuf.readLine())) {
				sb.append(line);
				if (D) {
					Log.e(TAG, "readfile " + filename + " return ====> " + line);
				}
				sb.append("\n");
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (rbuf != null) {
				try {
					rbuf.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			if (istr != null) {
				try {
					istr.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
//		if (D) {
//			Log.e(TAG, "readfile " + filename + " return ====> " + sb.toString());
//		}
		return sb.toString();
    }
	
	private int isfileexist(String filename) {
//		if (filename != null && filename.equals("fib.rb")) {
//			return 1;
//		} else {
//			return 0;
//		}
		if (filename == null) {
			return 0;
		}
		if (filename.startsWith("./") || filename.startsWith(".\\")) {
			filename = filename.substring(2);
		}
		InputStream istr = null;
		try {
			istr = context.getAssets().open(filename);
		} catch (IOException e) {
			//e.printStackTrace();
		} finally {
			if (istr != null) {
				try {
					istr.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				if (D) {
					Log.e(TAG, "isfileexist return 1 : " + filename);
				}
				return 1;
			}
		}
		if (D) {
			Log.e(TAG, "isfileexist return 0 : " + filename);
		}
		return 0;
	}
}

class DemoGLSurfaceView extends GLSurfaceView_SDL {
	DemoRenderer mRenderer;
	
	public DemoGLSurfaceView(Activity context) {
		super(context);
		mRenderer = new DemoRenderer(context);
		setRenderer(mRenderer);
	}

	public void exitApp() {
		mRenderer.exitApp();
	}
	
	@Override
	public boolean onTouchEvent(final MotionEvent event) {
		int action = -1;
		if (event.getAction() == MotionEvent.ACTION_DOWN)
			action = 0;
		if (event.getAction() == MotionEvent.ACTION_UP)
			action = 1;
		if (event.getAction() == MotionEvent.ACTION_MOVE)
			action = 2;
		if (action >= 0)
			nativeMouse((int) event.getX(), (int) event.getY(), action);
		return true;
	}

	@Override
	public boolean onKeyDown(int keyCode, final KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_VOLUME_UP
				|| keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) {
			Activity activity = (Activity) this.getContext();
			AudioManager audio = (AudioManager) activity
					.getSystemService(Context.AUDIO_SERVICE);
			int volume = audio.getStreamVolume(AudioManager.STREAM_MUSIC)
					+ (keyCode == KeyEvent.KEYCODE_VOLUME_UP ? 1 : (-1));
			if (volume >= 0
					&& volume <= audio
							.getStreamMaxVolume(AudioManager.STREAM_MUSIC)) {
				audio.setStreamVolume(AudioManager.STREAM_MUSIC, volume,
						AudioManager.FLAG_SHOW_UI);
			}
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_MENU) {
			super.onKeyDown(keyCode, event);
			return false;
		}
		nativeKey(keyCode, 1);
		return true;
	}

	@Override
	public boolean onKeyUp(int keyCode, final KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_MENU) {
			super.onKeyUp(keyCode, event);
			return false;
		}
		nativeKey(keyCode, 0);
		return true;
	}

	@Override
	public void onPause() {
		nativeKey(0, 3); // send SDL_ACTIVEEVENT
		super.onPause();
		surfaceDestroyed(this.getHolder());
	}

	@Override
	public void onResume() {
		super.onResume();
		nativeKey(0, 3); // send SDL_ACTIVEEVENT
	}

	@Override
	public void onStop() {
		super.onStop();
	}
	
	//FIXME: jni\sdl\src\video\android\SDL_androidinput.c
	public native void nativeMouse(int x, int y, int action);
	
	//FIXME: jni\sdl\src\video\android\SDL_androidinput.c
	public native void nativeKey(int keyCode, int down);
}
