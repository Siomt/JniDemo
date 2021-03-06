#include <jni.h>
#include <string>
#include <android/log.h>

//访问属性
extern "C" JNIEXPORT jstring JNICALL
Java_top_andnux_jnidemo_JniNatice_accessField(JNIEnv *env, jobject instance) {

    jclass jclazz = env->GetObjectClass(instance);
    jfieldID fieldID = env->GetFieldID(jclazz, "key", "Ljava/lang/String;");
    jstring jstring1 = static_cast<jstring>(env->GetObjectField(instance, fieldID));
    char *cstr = const_cast<char *>(env->GetStringUTFChars(jstring1, JNI_FALSE));
    char text[30] = "key ";
    strcat(text, cstr);
    jstring jstring2 = env->NewStringUTF(text);
    env->SetObjectField(instance, fieldID, jstring2);
    return jstring2;
}

//访问静态属性
extern "C"
JNIEXPORT jstring JNICALL
Java_top_andnux_jnidemo_JniNatice_accessStaticField(JNIEnv *env, jobject instance) {
    jclass jclazz = env->GetObjectClass(instance);
    jfieldID fieldID = env->GetStaticFieldID(jclazz, "key2", "Ljava/lang/String;");
    jstring jstring1 = static_cast<jstring>(env->GetStaticObjectField(jclazz, fieldID));
    char *cstr = const_cast<char *>(env->GetStringUTFChars(jstring1, JNI_FALSE));
    char text[30] = "key2 ";
    strcat(text, cstr);
    jstring jstring2 = env->NewStringUTF(text);
    env->SetStaticObjectField(jclazz, fieldID, jstring2);
    return jstring2;
}

// 访问方法
extern "C"
JNIEXPORT jint JNICALL
Java_top_andnux_jnidemo_JniNatice_accessMethod(JNIEnv *env, jobject instance) {
    jclass jclazz = env->GetObjectClass(instance);
    jmethodID jmethodID1 = env->GetMethodID(jclazz, "randomInt", "()I;");
    jint value = env->CallIntMethod(instance, jmethodID1);
    return value;
}

//访问静态方法
extern "C"
JNIEXPORT jstring JNICALL
Java_top_andnux_jnidemo_JniNatice_accessStaticMethod(JNIEnv *env, jobject instance) {
    jclass jclazz = env->GetObjectClass(instance);
    jmethodID jmethodID1 = env->GetStaticMethodID(jclazz, "randomUUID", "()Ljava/lang/String;");
    jstring jstring1 = static_cast<jstring>(env->CallStaticObjectMethod(jclazz, jmethodID1));
    return jstring1;
}

//访问构造方法
extern "C"
JNIEXPORT jlong JNICALL
Java_top_andnux_jnidemo_JniNatice_accessConstructor(JNIEnv *env, jobject instance) {
    jclass jclazz = env->FindClass("java/util/Date");
    jmethodID jmethodID1 = env->GetMethodID(jclazz, "<init>", "()V");
    jobject jobject1 = env->NewObject(jclazz, jmethodID1);
    jmethodID jmethodID2 = env->GetMethodID(jclazz, "getTime", "()J");
    jlong jlong1 = env->CallLongMethod(jobject1, jmethodID2);
    return jlong1;
}

//访问父类的方法
extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_jnidemo_JniNatice_accessNonvirtualMethod(JNIEnv *env, jobject instance) {
    jclass jclazz = env->GetObjectClass(instance);
    jfieldID jfieldID1 = env->GetFieldID(jclazz, "a", "Ltop/andnux/jnidemo/A;");
    jobject jobject1 = env->GetObjectField(instance, jfieldID1);
    jclass jclass1 = env->FindClass("top/andnux/jnidemo/A");
    jmethodID jmethodID1 = env->GetMethodID(jclass1, "a", "()V");
    env->CallNonvirtualVoidMethod(jobject1, jclass1, jmethodID1);
}

//字符串乱码问题
extern "C"
JNIEXPORT jstring JNICALL
Java_top_andnux_jnidemo_JniNatice_chineseChars(JNIEnv *env, jobject instance) {
    char *c_str = const_cast<char *>("jnidemo");
    jclass jclass1 = env->FindClass("java/lang/String");
    jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "([BLjava/lang/String;)V");
    jbyteArray jbyteArray1 = env->NewByteArray(static_cast<jsize>(strlen(c_str)));
    env->SetByteArrayRegion(jbyteArray1, 0, static_cast<jsize>(strlen(c_str)),
                            reinterpret_cast<const jbyte *>(c_str));
    jstring charsetName = env->NewStringUTF("UTF-8");
    return static_cast<jstring>(env->NewObject(jclass1, jmethodID1,
                                               jbyteArray1, charsetName));
//    return env->NewStringUTF(c_str);
}

//int (*__comparator)(const void* __lhs, const void* __rhs)
int comparator(const int *a, const int *b) {
    return (*a) - (*b);
}

//访问JAVA数组
extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_jnidemo_JniNatice_qsort(JNIEnv *env, jobject instance, jintArray datas_) {
    jint *datas = env->GetIntArrayElements(datas_, NULL);
    jint len = (env->GetArrayLength(datas_));
    qsort(datas, static_cast<size_t>(len), sizeof(int),
          reinterpret_cast<int (*)(const void *, const void *)>(comparator));
    env->ReleaseIntArrayElements(datas_, datas, 0);
}

//返回JAVA数组
extern "C"
JNIEXPORT jintArray JNICALL
Java_top_andnux_jnidemo_JniNatice_getArray(JNIEnv *env, jobject instance) {
    jintArray array = env->NewIntArray(10);
    jint len = env->GetArrayLength(array);
    jint *elems = env->GetIntArrayElements(array, JNI_FALSE);
    for (int i = 0; i < len; ++i) {
        elems[i] = i;
    }
    env->ReleaseIntArrayElements(array, elems, 0);
    return array;
}

//局部引用
extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_jnidemo_JniNatice_localReference(JNIEnv *env, jobject instance) {
    for (int i = 0; i < 100; ++i) {
        jclass jclass1 = env->FindClass("java/util/Date");
        jmethodID jmethodID1 = env->GetMethodID(jclass1, "<init>", "()V");
        jobject jobject1 = env->NewObject(jclass1, jmethodID1);
        env->DeleteLocalRef(jobject1);
    }
}

//全局引用
static jstring globalString;
extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_jnidemo_JniNatice_createGlobalReference(JNIEnv *env, jobject instance) {
    jstring glob = env->NewStringUTF("哈哈哈哈");
    globalString = static_cast<jstring>(env->NewGlobalRef(glob));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_top_andnux_jnidemo_JniNatice_getGlobalReference(JNIEnv *env, jobject instance) {
    return globalString;
}

extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_jnidemo_JniNatice_releaseGlobalReference(JNIEnv *env, jobject instance) {
    env->DeleteGlobalRef(globalString);
}

//异常
extern "C"
JNIEXPORT jstring JNICALL
Java_top_andnux_jnidemo_JniNatice_exception(JNIEnv *env, jobject instance) {

    jclass jclazz = env->GetObjectClass(instance);
    jfieldID fieldID = env->GetFieldID(jclazz, "key2", "Ljava/lang/String;");
    jthrowable jthrowable1 = env->ExceptionOccurred();
    if (jthrowable1 != NULL) {
        //保证JAVA代码可运行
        env->ExceptionClear();
        //补救措施
        fieldID = env->GetFieldID(jclazz, "key", "Ljava/lang/String;");
    }
    jstring jstring1 = static_cast<jstring>(env->GetObjectField(instance, fieldID));
    char *ptr = (char *) env->GetStringChars(jstring1, JNI_FALSE);
    if (strcmp(ptr, "andnux") != 0) {
        jclass jclass1 = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(jclass1, "参数错误");
    }
    return jstring1;
}