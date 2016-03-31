package com.testjni.activity;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.testjni.test.Student;

public class MainActivity extends Activity {
	private TextView mTestGetString;
	private TextView mTestSetString;
	private TextView mTestAddNum;
	private TextView mTestSumArray;
	private TextView mTestStringArray;
	private TextView mTestStringObj;
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
	}

	private void initUI() {
		mTestSetString = (TextView)findViewById(R.id.jni_test_setstring);
		mTestGetString = (TextView)findViewById(R.id.jni_test_getstring);
		mTestAddNum = (TextView)findViewById(R.id.jni_test_addnum);
		mTestSumArray = (TextView)findViewById(R.id.jni_test_sumarray);
		mTestStringArray = (TextView)findViewById(R.id.jni_test_stringarray);
		mTestStringObj = (TextView)findViewById(R.id.jni_test_stringobj);
	}
}
