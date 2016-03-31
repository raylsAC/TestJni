package com.testjni.test;

public class Student {
	
	private String name;
	private int age;
	private double height;
	
	public Student() {
	}
	
	public Student(String nameString, int age, double height) {
		this.name = nameString;
		this.age = age;
		this.height = height;
	}
	
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public double getHeight() {
		return height;
	}
	public void setHeight(double height) {
		this.height = height;
	}
	
	public void setStudentInfo(String name, int age, double height){
		this.name = name;
		this.age = age;
		this.height = height;
	}
	
	//jni字符串操作
	public native int setJniString(String str);
	public native String getJniString();
	
	//jni基本数据类型操作
	public native int addNum(int a, int b);
	
	//jni输入一个数组
	public native int sumArray(int[] a);
	//jni返回一字符串数组
	public native String[] getJniStringArray();
	
	//jni返回一个对象
	public native static Student getJniStudentObj();
	
	//jni使图片灰化
	public native int[] ChangeImgToGray(int[] pix, int w, int h);
	
	
	static {
        System.loadLibrary("TestJni");
    }
	
}
