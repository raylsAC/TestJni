#include "com_testjni_test_Student.h"

//����һ���ַ���
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

//����һ���ַ���
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

//���������������
JNIEXPORT jint JNICALL Java_com_testjni_test_Student_addNum
  (JNIEnv *env, jobject this, jint a, jint b){
	return a+b;
}

//���������������
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

	(*env)->ReleaseIntArrayElements(env, marray, arr_p, 0);	//�ǵ��ͷ�

	return sum_ret;
}

//����һ���ַ�������
JNIEXPORT jobjectArray JNICALL Java_com_testjni_test_Student_getJniStringArray
  (JNIEnv *env, jobject this){

	int i, arr_len;
	jstring tmpstr;
	//�ȶ���һ�ַ����������ڸ�ֵ
	char *arr[] = {"this", "is", "jni", "getJniStringArray", "fun"};
	arr_len = 5;

	//�ҵ�java string��
	jclass  arr_cls = (*env)->FindClass(env, "java/lang/String");
	if(arr_cls == NULL){
		return NULL;
	}

	//����java�ַ�������
	jobjectArray arr_ret = (*env)->NewObjectArray(env, arr_len, arr_cls, 0);
	if(arr_ret == NULL){
		return NULL;
	}

	//��Java���鸳ֵ
	for(i = 0; i < arr_len; i++){
		tmpstr = (*env)->NewStringUTF(env, arr[i]);
		(*env)->SetObjectArrayElement(env, arr_ret, i, tmpstr);
	}

	return arr_ret;
}

//����һ������
JNIEXPORT jobject JNICALL Java_com_testjni_test_Student_getJniStudentObj
  (JNIEnv *env, jobject this){

	jobject obj_ret;

	//��ȡ����������
	jclass obj_cls = (*env)->FindClass(env, "com/testjni/test/Student");

	//��ȡ���и������Ժͷ���id
	jfieldID nameID = (*env)->GetFieldID(env, obj_cls,"name","Ljava/lang/String;");
	jfieldID ageID = (*env)->GetFieldID(env, obj_cls,"age", "I");
	jfieldID heightID = (*env)->GetFieldID(env, obj_cls,"height", "D");

	// ��ȡ�����췽����id��ĳ��������id
	jmethodID  constructID =  (*env)->GetMethodID(env, obj_cls,"<init>", "()V");
	jmethodID  setStudID = (*env)->GetMethodID(env, obj_cls, "setStudentInfo","(Ljava/lang/String;ID)V");

	//����һ��Java����
	obj_ret = (*env)->NewObject(env, obj_cls, constructID);

	//���ö����е�����ֵ
	(*env)->SetObjectField(env, obj_ret,nameID,   (*env)->NewStringUTF(env, "rayls"));
	(*env)->SetIntField(env, obj_ret, ageID, 24);
	(*env)->SetDoubleField(env, obj_ret, heightID, 1.70);

//	//���ö��󷽷�
	(*env)->CallVoidMethod(env, obj_ret, setStudID, (*env)->NewStringUTF(env, "haha"), 28, 1.78);

	return obj_ret;
}

//��ͼƬ���ؽ��лһ�������㷨
JNIEXPORT jintArray JNICALL Java_com_testjni_test_Student_ChangeImgToGray
  (JNIEnv *env, jobject this, jintArray pix, jint w, jint h){

	//��java���������黺�浽c������,�������ò��˸���Ԫ��
	jint *p_pix = (*env)->GetIntArrayElements(env, pix, NULL);
	if(p_pix == NULL){
		return NULL;
	}

	jint alpha = 0xFF<<24;
	jint i, j;

	for(i = 0; i < h; i++){
		for(j = 0; j < w; j++){
				jint color = p_pix[w*i+j];
				jint red = ((color & 0x00FF0000) >> 16);
				jint green = ((color & 0x0000FF00) >> 8);
				jint blue = color & 0x000000FF;
				color = (red + green + blue)/3;
				color = alpha | (color << 16) | (color << 8) | color;
				p_pix[w*i+j] = color;
			}
	}
	jint size=w * h;
//	jintArray result = (*env)->NewIntArray(env, size);
//	(*env)->SetIntArrayRegion(env, result, 0, size, p_pix);
//	(*env)->ReleaseIntArrayElements(env, pix, p_pix, 0);

//	return result;

	//����Ҳ��
	(*env)->SetIntArrayRegion(env, pix, 0, size, p_pix);
	(*env)->ReleaseIntArrayElements(env, pix, p_pix, 0);

	return pix;
}





