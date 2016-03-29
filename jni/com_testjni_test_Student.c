#include "com_testjni_test_Student.h"

JNIEXPORT void JNICALL Java_com_testjni_test_Student_setJniString
  (JNIEnv *env, jobject this, jstring str){

	const char *ret;
	ret = (*env)->GetStringUTFChars(env, str, NULL);
	if(ret != NULL){
		printf("ret = %s", ret);
		LOGD("by log ret = %s", ret);
	}

	(*env)->ReleaseStringUTFChars(env, str, ret);


}

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
