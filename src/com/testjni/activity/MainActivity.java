package com.testjni.activity;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.testjni.test.Student;

public class MainActivity extends Activity {
	private TextView mTestGetString;
	private Student mStudent;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        initUI();
        initData();
    }

	private void initData() {
		mStudent = new Student();

		mStudent.setJniString("this is student.cls of jniTest");
		mTestGetString.setText(mStudent.getJniString());
	}

	private void initUI() {
		mTestGetString = (TextView)findViewById(R.id.jni_test_getstring);
	}
}
