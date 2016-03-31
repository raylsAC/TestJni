#include "com_testjni_test_Student.h"

//输入一个字符串
JNIEXPORT jint JNICALL Java_com_testjni_test_Student_setJniString
  (JNIEnv *env, jobject this, jstring str){

	const char *ret;
	ret = (*env)->GetStringUTFChars(env, str, NULL);
	if(ret != NULL){
		return 1;
	}

	(*env)->ReleaseStringUTFChars(env, str, ret);
	return -1;

}

//返回一个字符串
JNIEXPORT jstring JNICALL Java_com_testjni_test_Student_getJniString
  (JNIEnv *env, jobject this){

	jstring jstr;
	const char *tmp = "hello jni";

	jstr = (*env)->NewStringUTF(env, tmp);
	if(jstr == NULL){
		return NULL;
	}

	return jstr;
}

//输入基本数据类型
JNIEXPORT jint JNICALL Java_com_testjni_test_Student_addNum
  (JNIEnv *env, jobject this, jint a, jint b){
	return a+b;
}

//输入基本类型数组
JNIEXPORT jint JNICALL Java_com_testjni_test_Student_sumArray
  (JNIEnv *env, jobject this, jintArray marray){

	if(marray == NULL){
		return 0;
	}

	jint sum_ret = 0, i;
	jint *arr_p = (*env)->GetIntArrayElements(env, marray, NULL);
	if(arr_p == NULL){
		return -1;
	}
	jint arr_len = (*env)->GetArrayLength(env, marray);

	for(i=0; i<arr_len; i++){
		sum_ret += arr_p[i];
	}

	(*env)->ReleaseIntArrayElements(env, marray, arr_p, 0);	//记得释放

	return sum_ret;
}

//返回一个字符串数组
JNIEXPORT jobjectArray JNICALL Java_com_testjni_test_Student_getJniStringArray
  (JNIEnv *env, jobject this){

	int i, arr_len;
	jstring tmpstr;
	//先定义一字符串数组用于赋值
	char *arr[] = {"this", "is", "jni", "getJniStringArray", "fun"};
	arr_len = 5;

	//找到java string类
	jclass  arr_cls = (*env)->FindClass(env, "java/lang/String");
	if(arr_cls == NULL){
		return NULL;
	}

	//创建java字符串数组
	jobjectArray arr_ret = (*env)->NewObjectArray(env, arr_len, arr_cls, 0);
	if(arr_ret == NULL){
		return NULL;
	}

	//给Java数组赋值
	for(i = 0; i < arr_len; i++){
		tmpstr = (*env)->NewStringUTF(env, arr[i]);
		(*env)->SetObjectArrayElement(env, arr_ret, i, tmpstr);
	}

	return arr_ret;
}

//返回一个对象
JNIEXPORT jobject JNICALL Java_com_testjni_test_Student_getJniStudentObj
  (JNIEnv *env, jobject this){

	jobject obj_ret;

	//获取对象所在类
	jclass obj_cls = (*env)->FindClass(env, "com/testjni/test/Student");

	//获取类中各个属性和方法id
	jfieldID nameID = (*env)->GetFieldID(env, obj_cls,"name","Ljava/lang/String;");
	jfieldID ageID = (*env)->GetFieldID(env, obj_cls,"age", "I");
	jfieldID heightID = (*env)->GetFieldID(env, obj_cls,"height", "D");

	// 获取到构造方法的id和某个方法的id
	jmethodID  constructID =  (*env)->GetMethodID(env, obj_cls,"<init>", "()V");
	jmethodID  setStudID = (*env)->GetMethodID(env, obj_cls, "setStudentInfo","(Ljava/lang/String;ID)V");

	//创建一个Java对象
	obj_ret = (*env)->NewObject(env, obj_cls, constructID);

	//设置对象中的属性值
	(*env)->SetObjectField(env, obj_ret,nameID,   (*env)->NewStringUTF(env, "rayls"));
	(*env)->SetIntField(env, obj_ret, ageID, 24);
	(*env)->SetDoubleField(env, obj_ret, heightID, 1.70);

//	//调用对象方法
	(*env)->CallVoidMethod(env, obj_ret, setStudID, (*env)->NewStringUTF(env, "haha"), 28, 1.78);

	return obj_ret;
}





