@set JAVA_HOME="D:\Program Files\Java\jdk1.6.0_26"
@set PATH="D:\Program Files\Java\jdk1.6.0_26\bin";%PATH%
@javah -jni -classpath ./bin/classes -d jni/application com.example.rubyjni.RubyTest
@pause
