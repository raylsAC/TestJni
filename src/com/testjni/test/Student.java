package com.testjni.test;

public class Student {
	
	private String name;
	private int age;
	private double height;
	
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
		this.age =age;
		this.height = height;
	}
	
	public native void setJniString(String str);
	public native String getJniString();
	
	static {
        System.loadLibrary("TestJni");
    }
	
}
