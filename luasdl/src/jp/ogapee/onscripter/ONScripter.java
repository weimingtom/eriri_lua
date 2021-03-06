package jp.ogapee.onscripter;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileFilter;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.Arrays;
import java.util.Comparator;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.PowerManager;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SubMenu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.iteye.weimingtom.luasdl.R;

public class ONScripter extends Activity implements
		AdapterView.OnItemClickListener, Runnable {
	private File mCurrentDirectory = null;
	private File mOldCurrentDirectory = null;
	private File[] mDirectoryFiles = null;
	private ListView listView = null;
	private int num_file = 0;
	private byte[] buf = null;
	private int screen_w, screen_h;
	private int button_w, button_h;
	private Button btn1, btn2, btn3, btn4, btn5, btn6;
	private LinearLayout layout = null;
	private LinearLayout layout1 = null;
	private LinearLayout layout2 = null;
	private LinearLayout layout3 = null;
	private boolean mIsLandscape = true;
	private boolean mButtonVisible = true;
	private boolean mScreenCentered = false;

	static class FileSort implements Comparator<File> {
		@Override
		public int compare(File src, File target) {
			return src.getName().compareTo(target.getName());
		}
	}

	private void setupDirectorySelector() {
		mDirectoryFiles = mCurrentDirectory.listFiles(new FileFilter() {
			@Override
			public boolean accept(File file) {
				return (!file.isHidden() && file.isDirectory());
			}
		});
		Arrays.sort(mDirectoryFiles, new FileSort());
		int length = mDirectoryFiles.length;
		if (mCurrentDirectory.getParent() != null)
			length++;
		String[] names = new String[length];
		int j = 0;
		if (mCurrentDirectory.getParent() != null)
			names[j++] = "..";
		for (int i = 0; i < mDirectoryFiles.length; i++) {
			names[j++] = mDirectoryFiles[i].getName();
		}
		ArrayAdapter<String> arrayAdapter = new ArrayAdapter<String>(this,
				android.R.layout.simple_list_item_1, names);
		listView.setAdapter(arrayAdapter);
		listView.setOnItemClickListener(this);
	}

	private void runLauncher() {
		mCurrentDirectory = new File(gCurrentDirectoryPath);
		if (mCurrentDirectory.exists() == false) {
			gCurrentDirectoryPath = Environment.getExternalStorageDirectory()
					.getPath();
			mCurrentDirectory = new File(gCurrentDirectoryPath);
			if (mCurrentDirectory.exists() == false)
				showErrorDialog("Could not find SD card.");
		}
		listView = new ListView(this);
		LinearLayout layoutH = new LinearLayout(this);
		checkDR = new CheckBox(this);
		checkDR.setText("Disable rescale");
		checkDR.setBackgroundColor(Color.rgb(244, 244, 255));
		checkDR.setTextColor(Color.BLACK);
		layoutH.addView(checkDR, new LinearLayout.LayoutParams(
				LinearLayout.LayoutParams.FILL_PARENT,
				LinearLayout.LayoutParams.FILL_PARENT, 1.0f));
		listView.addHeaderView(layoutH, null, false);
		setupDirectorySelector();
		setContentView(listView);
	}

	@Override
	public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
		position--;
		TextView textView = (TextView) v;
		mOldCurrentDirectory = mCurrentDirectory;
		if (textView.getText().equals("..")) {
			mCurrentDirectory = new File(mCurrentDirectory.getParent());
			gCurrentDirectoryPath = mCurrentDirectory.getPath();
		} else {
			if (mCurrentDirectory.getParent() != null)
				position--;
			gCurrentDirectoryPath = mDirectoryFiles[position].getPath();
			mCurrentDirectory = new File(gCurrentDirectoryPath);
		}
		mDirectoryFiles = mCurrentDirectory.listFiles(new FileFilter() {
			@Override
			public boolean accept(File file) {
				return (file.isFile() && (file.getName().equals("0.txt")
						|| file.getName().equals("00.txt")
						|| file.getName().equals("nscr_sec.dat")
						|| file.getName().equals("nscript.___") || file
						.getName().equals("nscript.dat")));
			}
		});
		if (mDirectoryFiles.length == 0) {
			setupDirectorySelector();
		} else {
			mDirectoryFiles = mCurrentDirectory.listFiles(new FileFilter() {
				@Override
				public boolean accept(File file) {
					return (file.isFile() && (file.getName()
							.equals("default.ttf")));
				}
			});
			if (mDirectoryFiles.length == 0) {
				alertDialogBuilder.setTitle(getString(R.string.app_name));
				alertDialogBuilder.setMessage("default.ttf is missing.");
				alertDialogBuilder.setPositiveButton("OK",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int whichButton) {
								setResult(RESULT_OK);
							}
						});
				AlertDialog alertDialog = alertDialogBuilder.create();
				alertDialog.show();
				mCurrentDirectory = mOldCurrentDirectory;
				setupDirectorySelector();
			} else {
				gDisableRescale = checkDR.isChecked();
				runSDLApp();
			}
		}
	}

	private void runDownloader() {
		File file = new File(gCurrentDirectoryPath + "/"
				+ getResources().getString(R.string.download_version));
		if (file.exists() == false) {
			progDialog = new ProgressDialog(this);
			progDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
			progDialog.setMessage("Downloading archives from Internet:");
			progDialog.show();
			PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
			wakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK,
					"ONScripter");
			wakeLock.acquire();
		} else {
			runSDLApp();
		}
	}

	private void runCopier() {
		File file = new File(gCurrentDirectoryPath + "/"
				+ getResources().getString(R.string.download_version));
		if (file.exists() == false) {
			progDialog = new ProgressDialog(this);
			progDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
			progDialog.setMessage("Copying archives: ");
			progDialog.show();

			PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
			wakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK,
					"ONScripter");
			wakeLock.acquire();

			new Thread(this).start();
		} else {
			runSDLApp();
		}
	}

	@Override
	public void run() {
		num_file = 0;
		buf = new byte[8192 * 2];

		copyRecursive("");

		File file = new File(gCurrentDirectoryPath + "/"
				+ getResources().getString(R.string.download_version));
		try {
			file.createNewFile();
		} catch (Exception e) {
			sendMessage(-2, 0, "Failed to create version file: " + e.toString());
		}
		;

		sendMessage(-1, 0, null);
	}

	private void copyRecursive(String path) {
		AssetManager as = getResources().getAssets();
		try {
			File file = new File(gCurrentDirectoryPath + "/" + path);
			if (!file.exists()) {
				file.mkdir();
			}

			String[] file_list = as.list(path);
			for (String str : file_list) {
				InputStream is = null;
				String path2 = path;
				if (!path.equals(""))
					path2 += "/";
				path2 += str;

				int total_size = 0;
				try {
					is = as.open(path2);
					AssetFileDescriptor afd = as.openFd(path2);
					total_size = (int) afd.getLength();
					afd.close();
				} catch (Exception e) {
					copyRecursive(path2);
					is = null;
				}
				if (is == null)
					continue;

				File dst_file = new File(gCurrentDirectoryPath + "/" + path2);
				BufferedOutputStream os = new BufferedOutputStream(
						new FileOutputStream(dst_file));

				num_file++;
				int len = is.read(buf);
				int total_read = 0;
				while (len >= 0) {
					if (len > 0)
						os.write(buf, 0, len);
					total_read += len;
					sendMessage(total_read, total_size, "Copying archives: "
							+ num_file);

					len = is.read(buf);
					try {
						Thread.sleep(1);
					} catch (InterruptedException e) {
					}
				}
				os.flush();
				os.close();
				is.close();
			}
		} catch (Exception e) {
			progDialog.dismiss();
			sendMessage(-2, 0, "Failed to write: " + e.toString());
		}
	}

	/**
	 * FIXME: main entry
	 */
	private void runSDLApp() {
		//nativeInitJavaCallbacks();
		mAudioThread = new AudioThread(this);
		mGLView = new DemoGLSurfaceView(this);
		mGLView.setFocusableInTouchMode(true);
		mGLView.setFocusable(true);
		mGLView.requestFocus();
		int game_width = nativeGetWidth();
		int game_height = nativeGetHeight();
		Display disp = ((WindowManager) this
				.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
		int dw = disp.getWidth();
		int dh = disp.getHeight();
		screen_w = dw;
		screen_h = dh;
		mIsLandscape = true;
		if (dw * game_height >= dh * game_width) {
			screen_w = (dh * game_width / game_height) & (~0x01); // to be 2								// aligned
			button_w = dw - screen_w;
			button_h = dh / 4;
		} else {
			mIsLandscape = false;
			screen_h = dw * game_height / game_width;
			button_w = dw / 4;
			button_h = dh - screen_h;
		}
		btn1 = new Button(this);
		btn1.setText(getResources().getString(R.string.button_rclick));
		btn1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				mGLView.nativeKey(KeyEvent.KEYCODE_BACK, 1);
				mGLView.nativeKey(KeyEvent.KEYCODE_BACK, 0);
			}
		});
		btn2 = new Button(this);
		btn2.setText(getResources().getString(R.string.button_lclick));
		btn2.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				mGLView.nativeKey(KeyEvent.KEYCODE_ENTER, 1);
				mGLView.nativeKey(KeyEvent.KEYCODE_ENTER, 0);
			}
		});
		btn3 = new Button(this);
		btn3.setText(getResources().getString(R.string.button_up));
		btn3.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				mGLView.nativeKey(KeyEvent.KEYCODE_DPAD_UP, 1);
				mGLView.nativeKey(KeyEvent.KEYCODE_DPAD_UP, 0);
			}
		});
		btn4 = new Button(this);
		btn4.setText(getResources().getString(R.string.button_down));
		btn4.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				mGLView.nativeKey(KeyEvent.KEYCODE_DPAD_DOWN, 1);
				mGLView.nativeKey(KeyEvent.KEYCODE_DPAD_DOWN, 0);
			}
		});
		btn5 = new Button(this); // dummy button for Android 1.6
		btn5.setVisibility(View.INVISIBLE);
		btn6 = new Button(this); // dummy button for Android 1.6
		btn6.setVisibility(View.INVISIBLE);
		layout = new LinearLayout(this);
		layout1 = new LinearLayout(this);
		layout2 = new LinearLayout(this);
		layout3 = new LinearLayout(this);
		if (mIsLandscape) {
			layout2.setOrientation(LinearLayout.VERTICAL);
		} else {
			layout.setOrientation(LinearLayout.VERTICAL);
		}
		layout1.addView(btn5);
		layout.addView(layout1, 0);
		layout.addView(mGLView, 1, new LinearLayout.LayoutParams(screen_w,
				screen_h));
		layout2.addView(btn1, 0);
		layout2.addView(btn2, 1);
		layout2.addView(btn3, 2);
		layout2.addView(btn4, 3);
		layout.addView(layout2, 2);
		layout3.addView(btn6);
		layout.addView(layout3, 3);
		resetLayout();
		setContentView(layout);
		if (wakeLock == null) {
			PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
			wakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK,
					"ONScripter");
			wakeLock.acquire();
		}
	}

	public void resetLayout() {
		Display disp = ((WindowManager) this
				.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
		int dw = disp.getWidth();
		int dh = disp.getHeight();
		int bw = button_w, bh = button_h;
		int w1 = 0, h1 = 0;
		int w2 = dw, h2 = dh;
		if (mIsLandscape == true) {
			if (mScreenCentered) {
				w1 = bw - bw / 2;
				bw /= 2;
			}
			if (bw > bh * 4 / 3)
				bw = bh * 4 / 3;
			h1 = dh;
			w2 = bw;
		} else {
			if (mScreenCentered) {
				h1 = bh - bh / 2;
				bh /= 2;
			}
			if (bh > bw * 3 / 4)
				bh = bw * 3 / 4;
			w1 = dw;
			h2 = bh;
		}
		btn1.setMinWidth(bw);
		btn1.setMinHeight(bh);
		btn1.setWidth(bw);
		btn1.setHeight(bh);
		btn2.setMinWidth(bw);
		btn2.setMinHeight(bh);
		btn2.setWidth(bw);
		btn2.setHeight(bh);
		btn3.setMinWidth(bw);
		btn3.setMinHeight(bh);
		btn3.setWidth(bw);
		btn3.setHeight(bh);
		btn4.setMinWidth(bw);
		btn4.setMinHeight(bh);
		btn4.setWidth(bw);
		btn4.setHeight(bh);
		if (mButtonVisible) {
			layout2.setVisibility(View.VISIBLE);
		} else {
			layout2.setVisibility(View.INVISIBLE);
		}
		layout.updateViewLayout(layout1, new LinearLayout.LayoutParams(w1, h1));
		layout.updateViewLayout(layout2, new LinearLayout.LayoutParams(w2, h2));
		layout.updateViewLayout(layout3, new LinearLayout.LayoutParams(dw
				- screen_w - w1 - w2, dh - screen_h - h1 - h2));
	}

	public void playVideo(char[] filename) {
		try {
			String filename2 = "file:/" + gCurrentDirectoryPath + "/"
					+ new String(filename);
			filename2 = filename2.replace('\\', '/');
			Log.v("ONS", "playVideo: " + filename2);
			Uri uri = Uri.parse(filename2);
			Intent i = new Intent(Intent.ACTION_VIEW);
			i.setDataAndType(uri, "video/*");
			startActivityForResult(i, -1);
		} catch (Exception e) {
			Log.e("ONS", "playVideo error:  " + e.getClass().getName());
		}
	}

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		gCurrentDirectoryPath = Environment.getExternalStorageDirectory()
				+ "/Android/data/" + getApplicationContext().getPackageName();
		alertDialogBuilder = new AlertDialog.Builder(this);
		SharedPreferences sp = getSharedPreferences("pref", MODE_PRIVATE);
		mButtonVisible = sp.getBoolean("button_visible", getResources()
				.getBoolean(R.bool.button_visible));
		mScreenCentered = sp.getBoolean("screen_centered", getResources()
				.getBoolean(R.bool.screen_centered));
		//FXIME:
		/*
		if (getResources().getBoolean(R.bool.use_launcher)) {
			gCurrentDirectoryPath = Environment.getExternalStorageDirectory()
					+ "/ons";
			runLauncher();
		} else if (getResources().getBoolean(R.bool.use_download)) {
			runDownloader();
		} else {
			runCopier();
		}
		*/
		this.runSDLApp();
	}

	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		super.onPrepareOptionsMenu(menu);
		if (mGLView != null) {
			menu.clear();
			menu.add(Menu.NONE, Menu.FIRST, 0,
					getResources().getString(R.string.menu_automode));
			menu.add(Menu.NONE, Menu.FIRST + 1, 0,
					getResources().getString(R.string.menu_skip));
			menu.add(Menu.NONE, Menu.FIRST + 2, 0,
					getResources().getString(R.string.menu_speed));
			SubMenu sm = menu.addSubMenu(getResources().getString(
					R.string.menu_settings));
			if (mButtonVisible) {
				sm.add(Menu.NONE, Menu.FIRST + 4, 0,
						getResources().getString(R.string.menu_hide_buttons));
			} else {
				sm.add(Menu.NONE, Menu.FIRST + 3, 0,
						getResources().getString(R.string.menu_show_buttons));
			}
			if (mScreenCentered) {
				sm.add(Menu.NONE, Menu.FIRST + 5, 0,
						getResources().getString(R.string.menu_topleft));
			} else {
				sm.add(Menu.NONE, Menu.FIRST + 6, 0,
						getResources().getString(R.string.menu_center));
			}
			sm.add(Menu.NONE, Menu.FIRST + 7, 0,
					getResources().getString(R.string.menu_version));
			menu.add(Menu.NONE, Menu.FIRST + 8, 0,
					getResources().getString(R.string.menu_quit));
		}
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		if (item.getItemId() == Menu.FIRST) {
			mGLView.nativeKey(KeyEvent.KEYCODE_A, 1);
			mGLView.nativeKey(KeyEvent.KEYCODE_A, 0);
		} else if (item.getItemId() == Menu.FIRST + 1) {
			mGLView.nativeKey(KeyEvent.KEYCODE_S, 1);
			mGLView.nativeKey(KeyEvent.KEYCODE_S, 0);
		} else if (item.getItemId() == Menu.FIRST + 2) {
			mGLView.nativeKey(KeyEvent.KEYCODE_O, 1);
			mGLView.nativeKey(KeyEvent.KEYCODE_O, 0);
		} else if (item.getItemId() == Menu.FIRST + 3) {
			mButtonVisible = true;
			resetLayout();
		} else if (item.getItemId() == Menu.FIRST + 4) {
			mButtonVisible = false;
			resetLayout();
		} else if (item.getItemId() == Menu.FIRST + 5) {
			mScreenCentered = false;
			resetLayout();
		} else if (item.getItemId() == Menu.FIRST + 6) {
			mScreenCentered = true;
			resetLayout();
		} else if (item.getItemId() == Menu.FIRST + 7) {
			alertDialogBuilder.setTitle(getResources().getString(
					R.string.menu_version));
			alertDialogBuilder.setMessage(getResources().getString(
					R.string.version));
			alertDialogBuilder.setPositiveButton("OK",
					new DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface dialog,
								int whichButton) {
							setResult(RESULT_OK);
						}
					});
			AlertDialog alertDialog = alertDialogBuilder.create();
			alertDialog.show();
		} else if (item.getItemId() == Menu.FIRST + 8) {
			mGLView.nativeKey(KeyEvent.KEYCODE_MENU, 2); // send SDL_QUIT
		} else {
			return false;
		}
		Editor e = getSharedPreferences("pref", MODE_PRIVATE).edit();
		e.putBoolean("button_visible", mButtonVisible);
		e.putBoolean("screen_centered", mScreenCentered);
		e.commit();
		return true;
	}

	@Override
	protected void onPause() {
		if (wakeLock != null) {
			wakeLock.release();
		}
		super.onPause();
		if (mGLView != null) {
			mGLView.onPause();
		}
		if (mAudioThread != null) {
			mAudioThread.onPause();
		}
	}

	@Override
	protected void onResume() {
		if (wakeLock != null && !wakeLock.isHeld()) {
			wakeLock.acquire();
		}
		super.onResume();
		if (mGLView != null) {
			mGLView.onResume();
		}
		if (mAudioThread != null) {
			mAudioThread.onResume();
		}
	}

	@Override
	protected void onStop() {
		super.onStop();
		if (mGLView != null) {
			mGLView.onStop();
		}
	}

	@Override
	protected void onDestroy() {
		if (mGLView != null) {
			mGLView.exitApp();
		}
		super.onDestroy();
	}

	final Handler handler = new Handler() {
		public void handleMessage(Message msg) {
			int current = msg.getData().getInt("current");
			if (current == -1) {
				progDialog.dismiss();
				runSDLApp();
			} else if (current == -2) {
				progDialog.dismiss();
				showErrorDialog(msg.getData().getString("message"));
			} else {
				progDialog.setMessage(msg.getData().getString("message"));
				int total = msg.getData().getInt("total");
				if (total != progDialog.getMax())
					progDialog.setMax(total);
				progDialog.setProgress(current);
			}
		}
	};

	private void showErrorDialog(String mes) {
		alertDialogBuilder.setTitle("Error");
		alertDialogBuilder.setMessage(mes);
		alertDialogBuilder.setPositiveButton("Quit",
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int whichButton) {
						finish();
					}
				});
		AlertDialog alertDialog = alertDialogBuilder.create();
		alertDialog.show();
	}

	public void sendMessage(int current, int total, String str) {
		Message msg = handler.obtainMessage();
		Bundle b = new Bundle();
		b.putInt("total", total);
		b.putInt("current", current);
		b.putString("message", str);
		msg.setData(b);
		handler.sendMessage(msg);
	}

	private DemoGLSurfaceView mGLView = null;
	private AudioThread mAudioThread = null;
	private PowerManager.WakeLock wakeLock = null;
	public static String gCurrentDirectoryPath; //FIXME:
	public static Boolean gDisableRescale = false;
	public static Boolean gWideScreen = false;
	public static CheckBox checkDR = null;

	/*
	//FIXME: onscripter-20120112\ONScripter_sound.cpp
	private native int nativeInitJavaCallbacks();
	*/
	
	//FIXME: onscripter-20120112\onscripter_main.cpp
	private native int nativeGetWidth();

	//FIXME: onscripter-20120112\onscripter_main.cpp
	private native int nativeGetHeight();
	
	
	private AlertDialog.Builder alertDialogBuilder = null;
	private ProgressDialog progDialog = null;

	static {
		//System.loadLibrary("sdl");
		System.loadLibrary("application");
	}
}
