package com.testjni.activity;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageView;
import android.widget.TextView;

import com.testjni.test.Student;

public class MainActivity extends Activity {
	private TextView mTestGetString;
	private TextView mTestSetString;
	private TextView mTestAddNum;
	private TextView mTestSumArray;
	private TextView mTestStringArray;
	private TextView mTestStringObj;
	private TextView mTestClick;
	private ImageView mTestImg;
	private Student mStudent;
	
	private boolean isGray = false;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        initUI();
        initData();
    }

	private void initData() {
		mStudent = new Student();

		mTestSetString.setText(mStudent.setJniString("jniTest")+"");
		mTestGetString.setText(mStudent.getJniString());
		mTestAddNum.setText("native return int data : a + b = "+mStudent.addNum(2, 3)+"");
		
		int[] mIntArray = {1, 2, 3, 4};
		mTestSumArray.setText("the sum of mIntArray is : "+mStudent.sumArray(mIntArray)+"");
		
		String[] strs = mStudent.getJniStringArray();
		StringBuilder strbuilder = new StringBuilder();
		for (int i = 0; i < strs.length; i++) {
			strbuilder.append(strs[i]+" ");
		}
		
		mTestStringArray.setText("the StringArray is : "+strbuilder.toString());
		
		Student student = Student.getJniStudentObj();
		mTestStringObj.setText("the student name is : "+student.getName()+", age is : "+student.getAge()+", height is : "+student.getHeight());
		
		mTestImg.setImageResource(R.drawable.ic_launcher);
		mTestClick.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				if (!isGray) {
					//调用本地方法使图片灰化
					//从资源获取位图
					Bitmap tmpImg = ((BitmapDrawable)getResources().getDrawable(R.drawable.ic_launcher)).getBitmap();
					//获取位图的宽高
					int w = tmpImg.getWidth();
					int h = tmpImg.getHeight();
					//获取像素
					int[] pix = new int[w * h];
					tmpImg.getPixels(pix, 0, w, 0, 0, w, h); 
					
					int[] retInt=mStudent.ChangeImgToGray(pix, w, h);  
					
					//新建位图
	                Bitmap resultImg=Bitmap.createBitmap(w, h, Config.RGB_565); 
	                //为位图设置像素
	                resultImg.setPixels(retInt, 0, w, 0, 0,w, h);  
	                //显示
	                mTestImg.setImageBitmap(resultImg); 
					isGray = true;
				}else {
					isGray = false;
					mTestImg.setImageResource(R.drawable.ic_launcher);
				}
			}
		});
	}

	private void initUI() {
		mTestSetString = (TextView)findViewById(R.id.jni_test_setstring);
		mTestGetString = (TextView)findViewById(R.id.jni_test_getstring);
		mTestAddNum = (TextView)findViewById(R.id.jni_test_addnum);
		mTestSumArray = (TextView)findViewById(R.id.jni_test_sumarray);
		mTestStringArray = (TextView)findViewById(R.id.jni_test_stringarray);
		mTestStringObj = (TextView)findViewById(R.id.jni_test_stringobj);
		mTestClick = (TextView)findViewById(R.id.jni_test_click);
		mTestImg = (ImageView)findViewById(R.id.jni_test_img);
	}
}
